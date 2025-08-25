#include <QApplication>
#include <QFile>
#include <QUiLoader>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file("normalDialog.ui");
    if (!file.open(QFile::ReadOnly)) return -1;
    QUiLoader loader;
    QWidget *myWidget = loader.load(&file);
    file.close();
    if (!myWidget) return -2;
    myWidget->show();
    return app.exec();
}