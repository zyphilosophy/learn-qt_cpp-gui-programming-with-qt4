#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // QLabel* hello = new QLabel("Hello Qt !");
  QLabel *hello =
      new QLabel("<h2><i>Hello</i> <font color='red'>Qt !</font></h2>");
  hello->show();
  return a.exec();
}
