#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

// 前向声明 (Forward declarations)
// 这样做可以避免在头文件中包含完整的类定义，从而加快编译速度。
// 我们只需要指针，所以前向声明就足够了。
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

// 定义 FindDialog 类，它继承自 QDialog
class FindDialog : public QDialog
{
    Q_OBJECT // 宏，用于启用信号与槽机制
public:
    // 构造函数，QWidget* parent = nullptr 是 C++11
    // 的标准写法，表示它可以没有父窗口
    FindDialog(QWidget *parent = nullptr);

    // 信号部分：用于向外部发送消息
signals:
    // findNext 和 findPrevious 是自定义信号
    // Qt::CaseSensitivity 用于表示查找时是否区分大小写
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

    // 槽部分：用于接收和处理来自其他对象的信号
private slots:
    void findClicked();
    void enableFindButton(const QString &text);

    // 私有成员变量部分
private:
    // 声明界面上的所有控件
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
