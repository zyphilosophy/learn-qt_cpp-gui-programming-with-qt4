#pragma once
#include "ui_sortDialog.h"

class SortDialog
    : public QDialog
    , private Ui_Sort
{
    Q_OBJECT

public:
    explicit SortDialog(QWidget *parent = nullptr);
    ~SortDialog();

private:
    void setupConnections();
};
