#ifndef DELETEWIDGET_H
#define DELETEWIDGET_H

#include <QWidget>

class QHBoxLayout;
class QSpacerItem;
class DeleteButton;
class DeleteWidget : public QWidget
{
Q_OBJECT
public:
    explicit DeleteWidget(QWidget *parent = 0);
signals:
    void clicked(QString curText);
public slots:
    void deleteItem();
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    DeleteButton *btn;
    QString curText;
};

#endif // DELETEWIDGET_H
