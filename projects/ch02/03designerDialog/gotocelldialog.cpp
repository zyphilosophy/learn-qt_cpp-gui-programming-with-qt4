#include "gotocelldialog.h"
#include <QRegExpValidator>
#include "ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][1-9][0-9]{0,2}"), this);
    lineEdit->setValidator(validator);
    // 连接文本变化信号到槽
    connect(this->okButton, &QPushButton::clicked, this, &GoToCellDialog::accept);
    connect(this->cancelButton, &QPushButton::clicked, this, &GoToCellDialog::reject);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &GoToCellDialog::reject);
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &GoToCellDialog::accept);
}

GoToCellDialog::~GoToCellDialog() {}

void GoToCellDialog::on_lineEdit_textChanged(const QString &text)
{
    // 只有输入框有内容时才启用OK按钮
    this->okButton->setEnabled(!text.isEmpty());
}
