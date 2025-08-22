#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QPushButton *btn1 = new QPushButton("按钮1");
    QPushButton *btn2 = new QPushButton("按钮2");
    QPushButton *btn3 = new QPushButton("按钮3");
    QPushButton *btn4 = new QPushButton("按钮4");
    QPushButton *btn5 = new QPushButton("按钮5");
    QPushButton *btnClear = new QPushButton("清除");
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setMinimumHeight(60);
    textEdit->setAlignment(Qt::AlignTop);
    textEdit->setReadOnly(true);
    textEdit->setStyleSheet("QTextEdit { font-size: 16px; }");

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);
    layout->addWidget(btn5);
    layout->addWidget(btnClear);
    layout->addWidget(textEdit);

    // 1. 一个信号连接一个槽
    // 当按钮1被点击时，标签内容叠加“按钮1被点击”
    QObject::connect(btn1, &QPushButton::clicked, [&]() { textEdit->append("按钮1被点击"); });

    // 2. 一个信号连接多个槽
    // 当按钮2被点击时，标签内容叠加“按钮2被点击”，并禁用按钮1
    QObject::connect(btn2, &QPushButton::clicked, [&]() { textEdit->append("按钮2被点击"); });
    QObject::connect(btn3, &QPushButton::clicked, [&]() { textEdit->append("按钮3被点击"); });
    QObject::connect(btn4, &QPushButton::clicked, [&]() { textEdit->append("按钮4被点击"); });
    QObject::connect(btn5, &QPushButton::clicked, [&]() { textEdit->append("按钮5被点击"); });
    QObject::connect(btn2, &QPushButton::clicked, btn1, &QPushButton::setDisabled);
    QObject::connect(btn3, &QPushButton::clicked, btn1, &QPushButton::setEnabled);

    // 3. 多个信号连接同一个槽
    // 无论哪个按钮被点击，标签内容叠加“有按钮被点击”
    auto appendClickedText = [&]() { textEdit->append("有按钮被点击"); };
    QObject::connect(btn1, &QPushButton::clicked, appendClickedText);
    QObject::connect(btn2, &QPushButton::clicked, appendClickedText);
    QObject::connect(btn3, &QPushButton::clicked, appendClickedText);
    QObject::connect(btn4, &QPushButton::clicked, appendClickedText);
    QObject::connect(btn5, &QPushButton::clicked, appendClickedText);
    QObject::connect(btnClear, &QPushButton::clicked, appendClickedText);

    // 清除按钮
    QObject::connect(btnClear, &QPushButton::clicked, [&]() { textEdit->clear(); });

    // 4. 信号A连接信号B VS 信号B连接信号A
    // 信号A连接信号B：当A发出时，B也会被触发
    QObject::connect(btn4, &QPushButton::clicked, btn5, &QPushButton::clicked);
    QObject::connect(btn5, &QPushButton::clicked, btnClear, &QPushButton::clicked);
    // 信号B连接信号A：当B发出时，A也会被触发
    // QObject::connect(btn2, &QPushButton::clicked, btn1, &QPushButton::clicked);
    // 两者方向不同，触发链路也不同，可能导致递归或死循环，实际开发需谨慎

    // 断开信号连接
    QObject::connect(btnClear, &QPushButton::clicked,
                     [&]() { QObject::disconnect(btn4, &QPushButton::clicked, btn5, &QPushButton::clicked); });
    window.show();
    return a.exec();
}
