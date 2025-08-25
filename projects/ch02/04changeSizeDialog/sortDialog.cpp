#include "sortDialog.h"
#include <QSizePolicy>

SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    // Qt 5.15 及以后版本 隐藏布局不收缩
    QSizePolicy retain = moreButton->sizePolicy();
    retain.setRetainSizeWhenHidden(true);
    moreButton->setSizePolicy(retain);
    QSizePolicy retain_ = secondaryColumnCombo->sizePolicy();
    retain_.setRetainSizeWhenHidden(true);
    secondaryGroupBox->setSizePolicy(retain_);
    tertiaryGroupBox->setSizePolicy(retain_);
    // setupConnections();
}

SortDialog::~SortDialog() {}

void SortDialog::setupConnections()
{
    // connect(okButton, &QPushButton::clicked, this, &SortDialog::accept);
    // connect(cancelButton, &QPushButton::clicked, this, &SortDialog::reject);
    // connect(moreButton, &QPushButton::toggled, secondaryGroupBox, &QGroupBox::setVisible);
    // connect(moreButton, &QPushButton::toggled, tertiaryGroupBox, &QGroupBox::setVisible);
}
