#include <QApplication>
#include "sortDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortDialog *dialog = new SortDialog();
    dialog->show();
    return a.exec();
}