#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
signals:

public slots:
    void onTimeOut();

protected:
    void paintEvent(QPaintEvent *event);

private:
    int gridResolution;
    int gridXStartPos;
    int gridYStartPos;
    QColor bkColor;
    QColor lineColor;

};

#endif // PAINTWIDGET_H
