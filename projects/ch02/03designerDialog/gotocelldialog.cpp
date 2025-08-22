#include "gotocelldialog.h"
#include "ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    ui->setupUi(this);
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][1-9][0-9]{0,2}"), this);
    ui->lineEdit->setValidator(validator);
    // 连接文本变化信号到槽
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &GoToCellDialog::on_lineEdit_textChanged);
}

GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}

void GoToCellDialog::on_lineEdit_textChanged(const QString &text)
{
    // 只有输入框有内容时才启用OK按钮
    ui->okButton->setEnabled(!text.isEmpty());
}
