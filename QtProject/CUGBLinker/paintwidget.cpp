#include "paintwidget.h"
#include <QtGui>

PaintWidget::PaintWidget(QWidget *parent) :
        QWidget(parent),
        gridResolution(10),
        gridXStartPos(5),
        gridYStartPos(5),
        bkColor(0,0,80),
        lineColor(Qt::darkGreen)
{
    QTimer *updateTimer=new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    updateTimer->start(50);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.setRenderHint(QPainter::NonCosmeticDefaultPen,true);

    QRect widgetRect=rect();
    //»­±³¾°
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(bkColor,Qt::SolidPattern));
    painter.drawRoundedRect(widgetRect,5,5);

    //»­Íø¸ñ
    int xGridLines=widgetRect.width()/gridResolution;
    int yGridLines=widgetRect.height()/gridResolution;

    QPen gridPen(lineColor,1);
    painter.setPen(gridPen);
    for(int x=0;x<xGridLines;x++)
    {
        painter.drawLine(x*gridResolution+gridXStartPos,0,x*gridResolution+gridXStartPos,widgetRect.width());
    }
    for(int y=0;y<yGridLines;y++)
    {
        painter.drawLine(0,y*gridResolution+gridYStartPos,widgetRect.width(),y*gridResolution+gridYStartPos);
    }

}

void PaintWidget::onTimeOut()
{
    gridXStartPos-=1;
    if(gridXStartPos < 0)
        gridXStartPos += gridResolution;
    if(gridXStartPos > gridResolution)
        gridXStartPos -= gridResolution;
    if(gridYStartPos < 0)
        gridYStartPos += gridResolution;
    if(gridYStartPos > gridResolution)
        gridYStartPos -= gridResolution;

    this->update();
}
