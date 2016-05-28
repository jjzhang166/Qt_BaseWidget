/************************************************************************/
/**���ڻ���
/**���ڿ��ƴ����������϶�����Ϊ
/************************************************************************/


#ifndef MOVEWIDGET_H
#define MOVEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QLabel>
#include "InheritButton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#pragma execution_character_set("utf-8")

#define TOP_HEIGHT 50

class BaseWidget : public QWidget
{
	Q_OBJECT

public:
	BaseWidget(QWidget *parent = 0);
	~BaseWidget();
	void setResizable(bool bResiable);	//�����Ƿ��������
	void setMargin(const int &);		//��������������Ե�ķ�Χ
	void setWindowTitle(const QString &);//���ô��ڱ���

protected:
	virtual bool eventFilter(QObject *, QEvent *);

private:
	void changeMouseStyle(const QPoint&);	//�ı������ʽ
	void initControl();						//��ʼ��������ؼ�
	void initSignalSlotConn();				//��ʼ���źŲ�����

private slots:
	void onMaxBtnClickedSlot();				//��󻯰�ť�����ۺ���

protected:
	QWidget *m_pMainWgt;		//������

private:
	bool m_bResizable;	//�����Ƿ��������
	int m_iMarginWidth;	//���λ������ڽ����Ե�ľ���
	bool m_bPressed;	//����Ƿ���
	QPoint m_ptPressPos;//��갴��ʱ��λ��
	bool m_bIsMax;		//�ж��Ƿ������

	QWidget *m_pTopWgt;				//����
	InheritButton *m_pMinBtn;		//��С��
	InheritButton *m_pMaxBtn;		//���
	InheritButton *m_pCloseBtn;		//�ر�
	QLabel *m_pTitleBtn;			//����
	QRect m_maxRect;
	QRect m_normalRect;
};

#endif // MOVEWIDGET_H