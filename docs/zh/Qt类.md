```mermaid
classDiagram
    direction TD

    subgraph QtCore
        class QObject
        class QCoreApplication
        QObject <|-- QCoreApplication
    end

    subgraph QtGui
        class QPaintDevice
        class QWindow
        class QGuiApplication
        QObject <|-- QWindow
        QPaintDevice <|-- QWindow
        QCoreApplication <|-- QGuiApplication
    end

    subgraph QtWidgets
        direction TD
        class QWidget
        class QApplication
        class QLayout
        class QFrame
        class QDialog
        class QMainWindow
        class QAbstractButton
        class QAbstractSlider
        class QAbstractSpinBox
        class QAbstractScrollArea
        class QAbstractItemView

        QGuiApplication <|-- QApplication
        QObject <|-- QLayout
        QObject <|-- QWidget
        QPaintDevice <|-- QWidget

        QWidget <|-- QFrame
        QWidget <|-- QDialog
        QWidget <|-- QMainWindow
        QWidget <|-- QAbstractButton
        QWidget <|-- QAbstractSlider
        QWidget <|-- QAbstractSpinBox
        QWidget <|-- QLineEdit
        QWidget <|-- QComboBox
        QWidget <|-- QProgressBar
        QWidget <|-- QGroupBox
        QWidget <|-- QTabWidget

        QFrame <|-- QLabel
        QFrame <|-- QSplitter
        QFrame <|-- QAbstractScrollArea

        QAbstractScrollArea <|-- QTextEdit
        QAbstractScrollArea <|-- QPlainTextEdit
        QAbstractScrollArea <|-- QAbstractItemView

        QAbstractItemView <|-- QListView
        QAbstractItemView <|-- QTableView
        QAbstractItemView <|-- QTreeView
        QListView <|-- QListWidget
        QTableView <|-- QTableWidget
        QTreeView <|-- QTreeWidget

        QDialog <|-- QMessageBox
        QDialog <|-- QFileDialog
        QDialog <|-- QProgressDialog
        QDialog <|-- QInputDialog

        QAbstractButton <|-- QPushButton
        QAbstractButton <|-- QCheckBox
        QAbstractButton <|-- QRadioButton
        QAbstractButton <|-- QToolButton

        QAbstractSlider <|-- QSlider
        QAbstractSlider <|-- QScrollBar

        QAbstractSpinBox <|-- QSpinBox

        class QBoxLayout
        QLayout <|-- QBoxLayout
        QLayout <|-- QGridLayout
        QBoxLayout <|-- QHBoxLayout
        QBoxLayout <|-- QVBoxLayout
    end
```

