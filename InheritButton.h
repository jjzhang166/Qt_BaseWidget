#ifndef INHERITBUTTON_H
#define INHERITBUTTON_H

#include <QPushButton>

class InheritButton : public QPushButton
{
public:
	InheritButton(QWidget *);
	~InheritButton();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private:
};

#endif