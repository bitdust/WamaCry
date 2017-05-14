#include "wamacry.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WamaCry w;
    w.show();

    return a.exec();
}
