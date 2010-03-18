#include <QtGui/QApplication>
#include "cugblinker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CUGBLinker w;
	w.setWindowFlags(Qt::WindowMinimizeButtonHint);
    w.show();
    return a.exec();
}
