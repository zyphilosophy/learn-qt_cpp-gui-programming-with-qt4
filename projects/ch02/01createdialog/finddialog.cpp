#include <QtWidgets> // 包含所有 Qt Widgets 类的头文件

#include "finddialog.h"

// FindDialog 构造函数的实现
FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    // 1. 创建控件
    label = new QLabel(tr("Find &what:")); // "Find &what:" 中的 '&w' 表示 Alt+W 是快捷键
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit); // 设置伙伴关系，按 Alt+W 会将焦点设置到 lineEdit

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);  // 设置为默认按钮 (按 Enter 键会触发)
    findButton->setEnabled(false); // 初始状态下禁用

    closeButton = new QPushButton(tr("Close"));

    // 2. 连接信号与槽
    // 当 lineEdit 的文本改变时，调用 enableFindButton 槽
    connect(lineEdit, &QLineEdit::textChanged, this, &FindDialog::enableFindButton);
    // 当 findButton 被点击时，调用 findClicked 槽
    connect(findButton, &QPushButton::clicked, this, &FindDialog::findClicked);
    // 当 closeButton 被点击时，调用对话框的 close 槽 (QDialog 内置的槽)
    connect(closeButton, &QPushButton::clicked, this, &FindDialog::close);

    // 3. 设置布局
    // 水平布局，放置 "Find what:" 标签和输入框
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    // 垂直布局，放置左上角的水平布局和两个复选框
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    // 垂直布局，放置 "Find" 和 "Close" 按钮
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch(); // 添加一个伸缩弹簧，让按钮不会被拉伸

    // 主布局，水平排列左右两个垂直布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    // 将主布局应用到对话框
    setLayout(mainLayout);

    // 设置窗口标题和固定大小
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height()); // 固定窗口高度，防止垂直拉伸
}

// findClicked 槽函数的实现
void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs); // 如果选中向后搜索，则发出 findPrevious 信号
    }
    else {
        emit findNext(text, cs); // 否则发出 findNext 信号
    }
}

// enableFindButton 槽函数的实现
void FindDialog::enableFindButton(const QString &text)
{
    // 只有当输入框 (text) 不为空时，findButton 才可用
    findButton->setEnabled(!text.isEmpty());
}
