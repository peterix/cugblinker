#ifndef DELETECOMBOBOX_H
#define DELETECOMBOBOX_H

#include <QWidget>
#include <QComboBox>

class DeleteComboBox : public QComboBox
{
Q_OBJECT
public:
    explicit DeleteComboBox(QWidget *parent = 0);

signals:

public slots:
    void onDeleteItem(QString text);
    void onHighLighted(QString text);

};

#endif // DELETECOMBOBOX_H
