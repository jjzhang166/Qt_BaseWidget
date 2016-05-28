#include "BaseWidget.h"
#include <QHoverEvent>
#include <QDesktopWidget>
#include <QApplication>
enum MouseStyle{ NORMAL, BOTTOM, RIGHT, BOTTOMRIGHT} mouseStyle;

BaseWidget::BaseWidget(QWidget *parent)
	: QWidget(parent)
	, m_bResizable(true)
	, m_iMarginWidth(4)
	, m_bPressed(false)
	, m_bIsMax(false)
	, m_ptPressPos(0, 0)
{
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);	//�ޱ߿�
	this->setAttribute(Qt::WA_Hover);
	this->installEventFilter(this);

	initControl();			//��ʼ�����ؼ�
	initSignalSlotConn();	//��ʼ���źŲ�����

	//������ʽ��
	QFile styleFile("qss/main.qss");
	if (styleFile.open(QIODevice::ReadOnly))
	{
		QString strStyle = styleFile.readAll();
		this->setStyleSheet(strStyle);
	}
}

BaseWidget::~BaseWidget()
{

}

bool BaseWidget::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
		//[1]����ڽ������ƶ�
		case QEvent::HoverMove:
		{
			QHoverEvent *hoverEvent = dynamic_cast<QHoverEvent *>(event);
			if (!m_bPressed)
			{
				changeMouseStyle(hoverEvent->pos());
			}
			else
			{
				if (m_bIsMax)
				{
					QPoint pressPt = this->mapFromGlobal(QCursor::pos());
					if (pressPt.y() < TOP_HEIGHT)
					{
						int iMaxWidth = this->width();
						m_bIsMax = false;
						resize(m_normalRect.width(), m_normalRect.height());
						m_pMaxBtn->setToolTip("���");
						m_bResizable = true;
						m_ptPressPos.setX(pressPt.x() * (this->width() - 80) / (iMaxWidth - 80));
						m_ptPressPos.setY(pressPt.y());
					}
					return false;
				}
				if (mouseStyle == NORMAL)
				{
					this->move(this->mapToGlobal(hoverEvent->pos()) - m_ptPressPos);
					return true;
				}
				QPoint ptGlobalPos = this->mapToGlobal(hoverEvent->pos());
				QPoint ptTopLeft = this->frameGeometry().topLeft();
				QPoint ptBottomRight = this->frameGeometry().bottomRight();
				switch (mouseStyle)
				{
				case BOTTOM:
					if (ptGlobalPos.y() - ptTopLeft.y() > this->minimumHeight())
					{
						ptBottomRight.setY(ptGlobalPos.y());
					}
					else
					{
						ptBottomRight.setY(ptTopLeft.y() + this->minimumHeight());
					}
					break;
				case RIGHT:
					if (ptGlobalPos.x() - ptTopLeft.x() > this->minimumWidth())
					{
						ptBottomRight.setX(ptGlobalPos.x());
					}
					else
					{
						ptBottomRight.setX(ptTopLeft.x() + this->minimumWidth());
					}
					break;
				case BOTTOMRIGHT:
					if (ptGlobalPos.x() - ptTopLeft.x() > this->minimumWidth())
					{
						ptBottomRight.setX(ptGlobalPos.x());
					}
					else
					{
						ptBottomRight.setX(ptTopLeft.x() + this->minimumWidth());
					}
					if (ptGlobalPos.y() - ptTopLeft.y() > this->minimumHeight())
					{
						ptBottomRight.setY(ptGlobalPos.y());
					}
					else
					{
						ptBottomRight.setY(ptTopLeft.y() + this->minimumHeight());
					}
					break;
				default:
					break;
				}
				this->setGeometry(QRect(ptTopLeft, ptBottomRight));
			}
			return true;
		}
		break;
		//[1]end ����ڽ������ƶ�

		//[2]��갴��
		case QEvent::MouseButtonPress:
		{
			QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
			QPoint pressPt = mouseEvent->pos();
			if (pressPt.y() <= TOP_HEIGHT | mouseStyle != NORMAL)
			{
				if (mouseEvent->button() == Qt::LeftButton)
				{
					m_bPressed = true;
					m_ptPressPos = mouseEvent->globalPos() - this->frameGeometry().topLeft();
				}
			}
		}
		break;
		//[2]end ��갴��

		//[3]����ɿ�
		case QEvent::MouseButtonRelease:
		{
			m_bPressed = false;
			QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
			changeMouseStyle(mouseEvent->pos());
		}
		break;
		//[3]end ����ɿ�

		//[4]���˫��
		case QEvent::MouseButtonDblClick:
		{
			if (obj == m_pTopWgt)
			{
				onMaxBtnClickedSlot();
			}
		}
		break;
		//[4]end ���˫��

		default:
		break;
	}
	return false;
}

//�ı������ʽ
void BaseWidget::changeMouseStyle(const QPoint &ptMousePos)
{
	if (!m_bResizable)
	{
		setCursor(Qt::ArrowCursor);//������ʽ
		mouseStyle = NORMAL;
		return;
	}
	int iPosX = ptMousePos.x();
	int iPosY = ptMousePos.y();

	int iWidth = this->width();
	int iHeight = this->height();
	if (iPosX >= iWidth - m_iMarginWidth && iPosX <= iWidth)
	{
		setCursor(Qt::SizeHorCursor);//��
		if (iPosY >= iHeight - m_iMarginWidth && iPosY <= iHeight)
		{
			setCursor(Qt::SizeFDiagCursor);//����
			mouseStyle = BOTTOMRIGHT;
			return;
		}
		mouseStyle = RIGHT;
		return;
	}

	if (iPosY >= iHeight - m_iMarginWidth && iPosY <= iHeight)
	{
		setCursor(Qt::SizeVerCursor);//��
		mouseStyle = BOTTOM;
		return;
	}
	setCursor(Qt::ArrowCursor);//������ʽ
	mouseStyle = NORMAL;
	return;
}

//��ʼ��������ؼ�
void BaseWidget::initControl()
{
	m_maxRect = QApplication::desktop()->availableGeometry();

	m_pTopWgt = new QWidget(this);
	m_pMainWgt = new QWidget(this);
	m_pTopWgt->installEventFilter(this);
	m_pTopWgt->setMinimumHeight(TOP_HEIGHT);
	m_pTopWgt->setMaximumHeight(TOP_HEIGHT);
	QVBoxLayout *pVBLayout = new QVBoxLayout(this);
	pVBLayout->addWidget(m_pTopWgt);
	pVBLayout->addWidget(m_pMainWgt);
	pVBLayout->setMargin(0);
	pVBLayout->setSpacing(0);
	this->setLayout(pVBLayout);

	m_pTitleBtn = new QLabel(this);
	m_pTitleBtn->setFixedHeight(TOP_HEIGHT);


	m_pMinBtn = new InheritButton(this);
	m_pMaxBtn = new InheritButton(this);
	m_pCloseBtn = new InheritButton(this);
	m_pMinBtn->setMinimumSize(22, 34);
	m_pMinBtn->setMaximumSize(22, 34);
	m_pMaxBtn->setMinimumSize(22, 34);
	m_pMaxBtn->setMaximumSize(22, 34);
	m_pCloseBtn->setMinimumSize(22, 34);
	m_pCloseBtn->setMaximumSize(22, 34);
	QHBoxLayout *pHBLayout = new QHBoxLayout(this);
	pHBLayout->setSpacing(0);
	pHBLayout->setContentsMargins(16, 0, 13, 100);
	pHBLayout->addWidget(m_pTitleBtn);
	pHBLayout->addStretch();
	pHBLayout->addWidget(m_pMinBtn);
	pHBLayout->addWidget(m_pMaxBtn);
	pHBLayout->addWidget(m_pCloseBtn);
	m_pTopWgt->setLayout(pHBLayout);


	//���ö�����
	m_pTopWgt->setObjectName("m_pTopWgt");
	m_pMainWgt->setObjectName("m_pMainWgt");
	m_pMinBtn->setObjectName("m_pMinBtn");
	m_pMaxBtn->setObjectName("m_pMaxBtn");
	m_pCloseBtn->setObjectName("m_pCloseBtn");
	m_pTitleBtn->setObjectName("m_pTitleBtn");

	//��ʾ
	m_pMinBtn->setToolTip("��С��");
	m_pMaxBtn->setToolTip("���");
	m_pCloseBtn->setToolTip("�ر�");
}

//��ʼ���źŲ�����
void BaseWidget::initSignalSlotConn()
{
	connect(m_pCloseBtn, &QPushButton::clicked, this, &BaseWidget::hide);
	connect(m_pMaxBtn, &QPushButton::clicked, this, &BaseWidget::onMaxBtnClickedSlot);
	connect(m_pMinBtn, &QPushButton::clicked, this, &BaseWidget::showMinimized);
}

//��󻯰�ť�����ۺ���
void BaseWidget::onMaxBtnClickedSlot()
{
	m_bIsMax = !m_bIsMax;
	if (m_bIsMax)
	{
		m_normalRect.setTopLeft(this->mapToGlobal(QPoint(0, 0)));
		m_normalRect.setSize(this->size());
		setGeometry(m_maxRect);
		m_pMaxBtn->setToolTip("���»�ԭ");
		m_bResizable = false;
	}
	else
	{
		setGeometry(m_normalRect);
		m_pMaxBtn->setToolTip("���");
		m_bResizable = true;
	}
}

void BaseWidget::setResizable(bool bResiable)
{
	m_bResizable = bResiable;
}

void BaseWidget::setMargin(const int &iWidth)
{
	m_iMarginWidth = iWidth;
}

void BaseWidget::setWindowTitle(const QString &strTitle)
{
	m_pTitleBtn->setText(strTitle);
	m_pTitleBtn->setFixedWidth(m_pTitleBtn->sizeHint().width());
}