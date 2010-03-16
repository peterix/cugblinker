#include "deletecombobox.h"
#include "deletedelegate.h"
#include "deletewidget.h"
#include <QtGui>

DeleteComboBox::DeleteComboBox(QWidget *parent) :
    QComboBox(parent)
{
    setItemDelegate(new DeleteDelegate);
    connect(this,SIGNAL(highlighted(QString)),this,SLOT(onHighLighted(QString)));
}

void DeleteComboBox::onDeleteItem(QString text)
{
    if(QMessageBox::Yes==QMessageBox::question(this,"delete?","delete item?",QMessageBox::Yes,QMessageBox::No))
    {
       removeItem(findText(text));
    }
}

void DeleteComboBox::onHighLighted(QString text)
{
    for(int i=0;i<this->count();i++)
        this->view()->setIndexWidget(this->model()->index(i,0),NULL);

    DeleteWidget *deleteWidget=new DeleteWidget(this);
    deleteWidget->curText=text;
    connect(deleteWidget,SIGNAL(clicked(QString)),this,SLOT(onDeleteItem(QString)));
    this->view()->setIndexWidget(this->model()->index(this->findText(text),0),deleteWidget);
}
