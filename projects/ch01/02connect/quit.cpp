#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QPushButton *quit = new QPushButton("quit");
  QObject::connect(quit, SIGNAL(clicked()), &a, SLOT(quit()));
  quit->show();
  return a.exec();
}
