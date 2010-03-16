#include "splitbutton.h"
#include <QtGui>

SplitButton::SplitButton(QWidget *parent) :
QPushButton(parent)
{
}


void SplitButton::setMenu( QMenu* menu )
{
	if (menu)
	{
		line=new QFrame(this);
		line->setFrameShape(QFrame::VLine);
		line->setFrameShadow(QFrame::Sunken);
	}

	QPushButton::setMenu(menu);
}

void SplitButton::resizeEvent ( QResizeEvent * event )	
{
	if (menu())
	{
		int width=event->size().width();
		int height=event->size().height();
                line->setGeometry(QRect(width-18, 4, 3, height-8));
	}
}

void SplitButton::keyPressEvent ( QKeyEvent * event )
{
	if (menu())
	{
		switch (event->key()) 
		{
		case Qt::Key_Enter:
		case Qt::Key_Return:
			emit clicked();
			break;
		case Qt::Key_Up:
		case Qt::Key_Down:
			showMenu();
			break;
		default:
			QPushButton::keyPressEvent(event);
		}

	}
	else
		QPushButton::keyPressEvent(event);
}

void SplitButton::mousePressEvent( QMouseEvent * event )
{
	if (menu())
	{
		if((width()-event->x())<=15)
			showMenu();
		else
			setDown(true);
	}
	else
		QPushButton::mousePressEvent(event);
}
