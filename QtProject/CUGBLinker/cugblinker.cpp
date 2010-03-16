#include "cugblinker.h"
#include "ui_cugblinker.h"
#include <QtGui>

CUGBLinker::CUGBLinker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CUGBLinker)
{
    ui->setupUi(this);

    QMenu *menu=new QMenu();
    menu->addMenu("test");
    ui->btnDisCon->setMenu(menu);
}

CUGBLinker::~CUGBLinker()
{
    delete ui;
}

void CUGBLinker::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CUGBLinker::onConnect()
{
    conThread.connect();
}

void CUGBLinker::onDisconnect()
{
    conThread.disconnect();
}
