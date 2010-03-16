#include "deletewidget.h"
#include "deletebutton.h"
#include <QtGui>

DeleteWidget::DeleteWidget(QWidget *parent) :
    QWidget(parent),
    curText("")
{
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setContentsMargins(2, 2, 2, 2);

    horizontalSpacer=new QSpacerItem(1000,20);
    horizontalLayout->addItem(horizontalSpacer);

    btn=new DeleteButton(this);
    connect(btn,SIGNAL(clicked()),this,SLOT(deleteItem()));
    horizontalLayout->addWidget(btn);
    setLayout(horizontalLayout);
}

void DeleteWidget::deleteItem()
{
    emit clicked(curText);
}
