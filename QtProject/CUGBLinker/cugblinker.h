#ifndef CUGBLINKER_H
#define CUGBLINKER_H

#include <QDialog>
#include "conthread.h"

namespace Ui {
    class CUGBLinker;
}

class CUGBLinker : public QDialog {
    Q_OBJECT
public:
    CUGBLinker(QWidget *parent = 0);
    ~CUGBLinker();

protected:
    void changeEvent(QEvent *e);

signals:

private slots:
    void onConnect();
    void onDisconnect();

private:
    Ui::CUGBLinker *ui;
    ConThread conThread;
};

#endif // CUGBLINKER_H
