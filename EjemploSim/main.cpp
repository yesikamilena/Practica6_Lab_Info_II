#include "simulator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulator w;
    w.showMaximized();
    //w.show();
    return a.exec();
}
