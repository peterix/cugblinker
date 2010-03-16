#include "deletedelegate.h"

DeleteDelegate::DeleteDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QSize DeleteDelegate::sizeHint (const QStyleOptionViewItem & /*option*/, const QModelIndex & /*index*/) const
{
    return QSize(0,30);
}
