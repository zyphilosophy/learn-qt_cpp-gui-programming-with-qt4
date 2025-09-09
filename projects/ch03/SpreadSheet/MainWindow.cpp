#include "MainWindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include "finddialog.h"
#include "gotocelldialog.h"

#include "sortdialog.h"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDialog = 0;

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (okToContinue()) {
        ui->tableWidget->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open ui->tableWidget"), ".", tr("ui->tableWidget files (*.sp)"));
        if (!fileName.isEmpty()) loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    }
    else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save ui->tableWidget"), ".", tr("ui->tableWidget files (*.sp)"));
    if (fileName.isEmpty()) return false;

    return saveFile(fileName);
}

void MainWindow::find()
{
    if (!findDialog) {
        findDialog = new FindDialog(this);
        connect(findDialog, &FindDialog::findNext, ui->tableWidget, &Spreadsheet::findNext);
        connect(findDialog, &FindDialog::findPrevious, ui->tableWidget, &Spreadsheet::findPrevious);
    }

    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCellDialog dialog(this);
    if (dialog.exec()) {
        QString str = dialog.lineEdit->text().toUpper();
        ui->tableWidget->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
    }
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = ui->tableWidget->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

    if (dialog.exec()) {
        SpreadsheetCompare compare;
        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex() - 1;
        compare.ascending[0] = (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] = (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] = (dialog.tertiaryOrderCombo->currentIndex() == 0);
        ui->tableWidget->sort(compare);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About ui->tableWidget"),
                       tr("<h2>ui->tableWidget 1.1</h2>"
                          "<p>Copyright &copy; 2008 Software Inc."
                          "<p>ui->tableWidget is a small application that "
                          "demonstrates QAction, QMainWindow, QMenuBar, "
                          "QStatusBar, QTableWidget, QToolBar, and many other "
                          "Qt classes."));
}

void MainWindow::openRecentFile()
{
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action) loadFile(action->data().toString());
    }
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(ui->tableWidget->currentLocation());
    formulaLabel->setText(ui->tableWidget->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::createActions()
{
    connect(ui->action_New, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::open);
    connect(ui->action_Save, &QAction::triggered, this, &MainWindow::save);

    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveAs);

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->action_Cut, &QAction::triggered, ui->tableWidget, &Spreadsheet::cut);
    connect(ui->action_Copy, &QAction::triggered, ui->tableWidget, &Spreadsheet::copy);

    connect(ui->action_Paste, &QAction::triggered, ui->tableWidget, &Spreadsheet::paste);
    connect(ui->action_Delete, &QAction::triggered, ui->tableWidget, &Spreadsheet::del);
    connect(ui->actionRow, &QAction::triggered, ui->tableWidget, &Spreadsheet::selectCurrentRow);

    connect(ui->actionColumn, &QAction::triggered, ui->tableWidget, &Spreadsheet::selectCurrentColumn);
    connect(ui->actionAll, &QAction::triggered, ui->tableWidget, &Spreadsheet::selectAll);
    connect(ui->action_Find, &QAction::triggered, this, &MainWindow::find);
    connect(ui->action_Go_To_Cell, &QAction::triggered, this, &MainWindow::goToCell);

    connect(ui->actionRecalculate, &QAction::triggered, ui->tableWidget, &Spreadsheet::recalculate);

    connect(ui->actionSort, &QAction::triggered, this, &MainWindow::sort);

    connect(ui->action_ShowGrid, &QAction::toggled, ui->tableWidget, &Spreadsheet::setShowGrid);
#if QT_VERSION < 0x040102
    // workaround for a QTableWidget bug in Qt 4.1.1
    connect(showGridAction, SIGNAL(toggled(bool)), ui->tableWidget->viewport(), SLOT(update()));
#endif

    connect(ui->action_Auto_Recalculate, &QAction::toggled, ui->tableWidget, &Spreadsheet::setAutoRecalculate);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    separatorAction = ui->menuFile->insertSeparator(ui->actionExit);

    // 倒序插入，以保证最终顺序是正确的 (0, 1, 2, 3...)
    // 因为每次都是插入到同一个位置（分隔符后面）
    for (int i = MaxRecentFiles - 1; i >= 0; --i) {
        ui->menuFile->insertAction(separatorAction, recentFileActions[i]);
    }
}

void MainWindow::createContextMenu()
{
    ui->tableWidget->addAction(ui->action_Cut);
    ui->tableWidget->addAction(ui->action_Copy);
    ui->tableWidget->addAction(ui->action_Paste);
    ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars() {}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(ui->tableWidget, &Spreadsheet::currentCellChanged, this, &MainWindow::updateStatusBar);
    connect(ui->tableWidget, &Spreadsheet::modified, this, &MainWindow::spreadsheetModified);

    updateStatusBar();
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "ui->tableWidget");

    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    ui->action_ShowGrid->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    ui->action_Auto_Recalculate->setChecked(autoRecalc);
}

void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "ui->tableWidget");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", ui->action_ShowGrid->isChecked());
    settings.setValue("autoRecalc", ui->action_Auto_Recalculate->isChecked());
}

bool MainWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("ui->tableWidget"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        }
        else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!ui->tableWidget->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!ui->tableWidget->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("ui->tableWidget")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next())) i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2").arg(j + 1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else {
            recentFileActions[j]->setVisible(false);
        }
    }
    if (separatorAction) separatorAction->setVisible(!recentFiles.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
