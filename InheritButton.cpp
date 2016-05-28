#include "InheritButton.h"

/************************************************************************/
/**°´Å¥
/************************************************************************/
InheritButton::InheritButton(QWidget *parent)
: QPushButton(parent)
{

}

InheritButton::~InheritButton()
{

}

void InheritButton::enterEvent(QEvent *)
{
	setCursor(Qt::PointingHandCursor);
}

void InheritButton::leaveEvent(QEvent *)
{
	setCursor(Qt::ArrowCursor);
}