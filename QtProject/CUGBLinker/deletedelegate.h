#ifndef DELETEDELEGATE_H
#define DELETEDELEGATE_H

#include <QStyledItemDelegate>

class DeleteDelegate : public QStyledItemDelegate
{
Q_OBJECT
public:
    explicit DeleteDelegate(QObject *parent = 0);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:

};

#endif // DELETEDELEGATE_H
