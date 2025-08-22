#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include "ui_gotocelldialog.h" // 包含自动生成的 UI 头文件

#include <QDialog>

class GoToCellDialog
    : public QDialog
    , public Ui::GoToCellDialog
{
    Q_OBJECT
public:
    explicit GoToCellDialog(QWidget *parent = nullptr);
    ~GoToCellDialog();

private slots:
    void on_lineEdit_textChanged(const QString &text);
};

#endif // GOTOCELLDIALOG_H
