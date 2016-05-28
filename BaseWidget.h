/************************************************************************/
/**窗口基类
/**用于控制窗口伸缩、拖动等行为
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
	void setResizable(bool bResiable);	//设置是否可以缩放
	void setMargin(const int &);		//设置鼠标距离界面边缘的范围
	void setWindowTitle(const QString &);//设置窗口标题

protected:
	virtual bool eventFilter(QObject *, QEvent *);

private:
	void changeMouseStyle(const QPoint&);	//改变鼠标样式
	void initControl();						//初始化界面各控件
	void initSignalSlotConn();				//初始化信号槽连接

private slots:
	void onMaxBtnClickedSlot();				//最大化按钮单击槽函数

protected:
	QWidget *m_pMainWgt;		//主界面

private:
	bool m_bResizable;	//界面是否可以缩放
	int m_iMarginWidth;	//鼠标位置相对于界面边缘的距离
	bool m_bPressed;	//鼠标是否按下
	QPoint m_ptPressPos;//鼠标按下时的位置
	bool m_bIsMax;		//判断是否是最大化

	QWidget *m_pTopWgt;				//顶部
	InheritButton *m_pMinBtn;		//最小化
	InheritButton *m_pMaxBtn;		//最大化
	InheritButton *m_pCloseBtn;		//关闭
	QLabel *m_pTitleBtn;			//标题
	QRect m_maxRect;
	QRect m_normalRect;
};

#endif // MOVEWIDGET_H