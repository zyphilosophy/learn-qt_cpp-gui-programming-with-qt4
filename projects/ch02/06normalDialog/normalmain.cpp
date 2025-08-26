#include <QApplication>
#include <QDialog>
#include "ui_normalDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDialog *dialog = new QDialog();
    Ui_Dialog ui;
    ui.setupUi(dialog);
    dialog->show();
    return a.exec();
}