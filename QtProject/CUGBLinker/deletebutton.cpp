#include "deletebutton.h"

DeleteButton::DeleteButton(QWidget *parent) :
    QPushButton(parent)
{
    this->setText("X");
}

QSize DeleteButton::sizeHint() const
{
    return QSize(18,18);
}
