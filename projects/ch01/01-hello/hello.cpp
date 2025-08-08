#include <QApplication>
#include <QLabel>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QLabel* hello = new QLabel("Hello Qt !");
    hello->show();
    return a.exec();
}
