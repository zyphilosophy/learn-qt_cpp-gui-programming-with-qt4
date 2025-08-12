#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QPushButton *quit = new QPushButton("quit");
  // 使用 Qt 5+ 的新语法（推荐，类型安全）
  QObject::connect(quit, &QPushButton::clicked, &a, &QApplication::quit);

  // 使用 Qt 4 的旧语法
  // QObject::connect(quit, SIGNAL(clicked()), &a, SLOT(quit()));
  quit->show();
  return a.exec();
}
