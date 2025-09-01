#include "mwbycode.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MWByCode w;
    w.show();
    return a.exec();
}
