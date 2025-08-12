# Qt入门
## hello
### 新建hello.cpp
```cpp
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // QLabel* hello = new QLabel("Hello Qt !");
  QLabel *hello =
      new QLabel("<h2><i>Hello</i> <font color='red'>Qt !</font></h2>");
  hello->show();
  return a.exec();
}
```
### QApplication
`QApplication` 类用于管理 Qt 应用程序的生命周期和控制流。任何一个使用 Qt GUI 的应用程序都必须有且仅有一个 `QApplication` 对象。

- **主要职责:**
  - **事件循环管理:** 它包含主事件循环，负责处理和分发所有来自窗口系统和其他来源的事件（如鼠标点击、键盘输入、定时器事件等）。`a.exec()` 这行代码就是启动事件循环的入口。程序会在此处阻塞，直到应用程序退出。
  - **全局设置:** 管理应用程序级别的设置，如应用程序名称、样式、字体和调色板等。
  - **命令行参数处理:** 构造函数 `QApplication(argc, argv)` 可以接收 `main` 函数的命令行参数，并处理其中一些 Qt 相关的标准参数（如 `-style`）。

在 `hello.cpp` 示例中，`QApplication a(argc, argv);` 创建了应用程序对象，是整个程序能够运行的基础。

### QLabel
`QLabel` 是一个用于显示文本或图像的控件。它是最基础的显示类控件之一。

- **主要功能:**
  - **显示静态文本:** 可以显示简单的纯文本。
  - **富文本显示:** 支持 HTML 格式的富文本。在示例中，`<h2><i>Hello</i> <font color='red'>Qt !</font></h2>` 就是一个 HTML 字符串，它使得 "Hello" 变为斜体，并且 "Qt !" 显示为红色。这展示了 `QLabel` 的强大格式化能力。
  - **显示图片:** 可以用来显示 `QPixmap` 或 `QPicture` 对象，从而在界面上展示图片。
  - **伙伴关系 (Buddy):** 可以与一个输入控件（如 `QLineEdit`）关联，当用户按下 `QLabel` 的快捷键时，焦点会自动转移到其伙伴控件上。

在 `hello.cpp` 中，`QLabel` 被用来在窗口中显示格式化的欢迎信息。`hello->show()` 方法使标签可见。默认情况下，一个没有父控件的 `QLabel` 会作为一个独立的窗口显示。

## Qt 命令行编译步骤详解 (Windows + MSVC)

本文档详细解释了在 Windows 环境下，使用 Qt 和 Microsoft Visual C++ (MSVC) 编译器时，通过命令行构建一个 Qt 项目所需的各个命令。

---

#### **前提条件：正确的命令行环境**

所有命令都必须在特定的命令行环境中执行，而不是普通的 `cmd.exe` 或 `PowerShell`。你需要根据你的目标平台（32位或64位）启动对应的 Visual Studio 工具提示符。

*   **对于 64 位编译 (x64):**
    *   在开始菜单搜索并打开 **`x64 Native Tools Command Prompt for VS 2022`** (或你的 VS 版本对应的名称)。
    *   这是最常用的选项，因为你的 Qt 库是64位的 (`msvc2019_64`)。

*   **对于 32 位编译 (x86):**
    *   在开始菜单搜索并打开 **`x86 Native Tools Command Prompt for VS 2022`**。

**为什么这很重要？**
这个专用的命令行工具会预先设置好所有必要的环境变量，让 `qmake` 和 `nmake` 能够找到编译器 (`cl.exe`)、链接器 (`link.exe`) 以及所有系统和 C++ 库。如果使用普通终端，就会出现 `cl` 找不到或者库冲突的错误。

---

#### **第一步：生成项目文件 (`.pro`)**

**命令:**
```bash
qmake -project
```

*   **作用:** 这个命令会扫描当前目录下的所有 C++ 源文件 (`.cpp`) 和头文件 (`.h`)，并自动生成一个与平台无关的 Qt 项目文件。这个文件的默认名字通常是根据当前文件夹名来的，扩展名为 `.pro` (例如 `01hello.pro`)。
*   **何时使用:** 当你只有源代码，还没有 `.pro` 文件时，这是创建项目的第一步。
*   **注意:** 自动生成的文件可能不完整。例如，它不会自动添加所需的 Qt 模块（如 `widgets`、`network` 等），这需要手动编辑 `.pro` 文件来添加。

---

#### **第二步：生成 Makefile**

**命令:**
```bash
qmake 01hello.pro
```
(请将 `01hello.pro` 替换为你的实际项目文件名)

*   **作用:** `qmake` 读取 `.pro` 文件，并根据其中的配置（如 `TARGET`, `SOURCES`, `QT += widgets` 等）生成一个平台相关的 `Makefile`。
    *   在 Windows + MSVC 环境下，它会生成供 `nmake` 使用的 `Makefile` 文件 (`Makefile`, `Makefile.Debug`, `Makefile.Release`)。
    *   在 Linux 或 MinGW 环境下，它会生成供 `make` 或 `mingw32-make` 使用的 Makefile。
*   **何时使用:**
    1.  在第一次创建项目时，紧跟 `qmake -project` 之后。
    2.  **每次修改 `.pro` 文件之后**（比如添加了新的源文件或 Qt 模块），都必须重新运行此命令来更新 `Makefile`。

---

#### **第三步：编译和链接**

**命令:**
```bash
nmake
```

*   **作用:** `nmake` 是 Microsoft 的 `make` 工具。它会读取上一步生成的 `Makefile` 文件，并执行其中定义的编译和链接规则。
    *   **编译 (Compiling):** 调用 C++ 编译器 (`cl.exe`) 将每个 `.cpp` 源文件编译成中间目标文件 (`.obj`)。
    *   **链接 (Linking):** 调用链接器 (`link.exe`) 将所有的 `.obj` 文件和项目所需的 Qt 库、系统库链接在一起，最终生成可执行文件 (`.exe`)。
*   **何时使用:** 在生成 `Makefile` 之后，用此命令来构建你的应用程序。
*   **编译模式:**
    *   直接运行 `nmake` 默认会构建 `release` 版本。
    *   要构建 `debug` 版本，可以运行 `nmake debug`。

---

#### **第四步（可选）：清理项目**

**命令:**
```bash
nmake clean       # 清理中间文件
nmake distclean   # 彻底清理
```

*   **`nmake clean`:** 删除编译过程中产生的中间文件（如 `.obj` 文件），但保留 `Makefile` 和最终的 `.exe` 文件。
*   **`nmake distclean`:** 进行最彻底的清理。它会删除所有由 `qmake` 和 `nmake` 生成的文件，包括 `.obj` 文件、`.exe` 文件以及 `Makefile` 本身。执行后，项目会回到一个几乎只剩下源代码和 `.pro` 文件的干净状态。
*   **何时使用:** 当你遇到奇怪的编译链接错误，或者想从头开始重新构建整个项目时，`distclean` 是一个非常有用的命令。在切换编译配置（比如从 Debug 换到 Release，或者从 x86 换到 x64）之前，执行 `distclean` 是一个好习惯。

---

#### **高级用法：生成 Visual Studio 项目文件**

**命令:**
```bash
qmake -tp vc 01hello.pro
```

*   **作用:** 这个命令会读取 `.pro` 文件，并生成一个 Visual Studio 项目文件 (`.vcxproj`) 和解决方案文件 (`.sln`)。
*   **`-tp vc` 的含义:** `-tp` 是 "template" (模板) 的缩写，`vc` 指的是 "Visual C++"。所以这个参数的作用就是告诉 `qmake` 使用 Visual C++ 的项目模板。
*   **为何使用此命令:**
    *   **IDE 集成:** 生成 VS 项目后，你就可以直接在 Visual Studio IDE 中打开这个项目。
    *   **强大的调试功能:** 你可以利用 Visual Studio 强大的图形化调试器来设置断点、检查变量、单步执行代码等。
    *   **智能提示与代码编辑:** 可以享受 Visual Studio 的 IntelliSense 智能代码补全和导航功能。
    *   **无缝开发体验:** 对于习惯使用 Visual Studio 的开发者来说，这提供了一个无缝的开发体验，无需在命令行和编辑器之间频繁切换。
*   **何时使用:** 当你想脱离命令行，完全在 Visual Studio IDE 中进行开发、编译和调试时，就使用这个命令。它为你搭建了从 Qt 项目到 VS IDE 的桥梁。
*   **注意:** 生成 `.vcxproj` 文件后，对源文件或项目设置的修改（比如添加新文件）应该在 Visual Studio 中进行，或者在修改 `.pro` 文件后重新运行此命令来同步更新 VS 项目。
  
#### **总结：一个完整的构建流程**

假设你从零开始，在一个名为 `my_app` 的文件夹里只有 `main.cpp`。

1.  打开 **`x64 Native Tools Command Prompt`**。
2.  `cd path\to\my_app`
3.  `qmake -project`  -> 生成 `my_app.pro`
4.  编辑 `my_app.pro`，添加 `QT += widgets`
5.  `qmake my_app.pro` -> 生成 `Makefile`
6.  `nmake` -> 生成 `release\my_app.exe`
7.  如果需要重新构建：`nmake distclean`，然后回到第 5 步。


## QObject::connect
### quit.cpp
```cpp
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QPushButton *quit = new QPushButton("quit");
  QObject::connect(quit, SIGNAL(clicked()), &a, SLOT(quit()));
  quit->show();
  return a.exec();
}
```
### QPushButton
`QPushButton` 是一个标准的按钮控件，是用户与应用程序交互最常见的方式之一。

- **核心功能:**
  - **点击信号:** 当用户点击按钮时，它会发出一个 `clicked()` 信号。这是 `QPushButton` 最核心的特性。
  - **文本和图标:** 按钮上可以显示文本、图标，或者两者都有。
  - **多种按钮类型:**
    - **普通按钮:** 默认类型。
    - **可切换按钮 (Toggle Button):** 可以有两种状态（按下/弹起）。
    - **自动重复按钮 (Auto-repeat Button):** 按住不放时会持续触发 `clicked()` 信号。
    - **默认按钮 (Default Button):** 在对话框中，按 Enter 键时会自动触发的按钮。

在 `quit.cpp` 示例中，`new QPushButton("quit")` 创建了一个显示文本 "quit" 的按钮。通过 `QObject::connect` 将其 `clicked()` 信号连接到应用程序的 `quit()` 槽，实现了点击按钮退出程序的功能。

# 窗口布局
```cpp
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget window;
  window.setWindowTitle("Slider and SpinBox Example");

  QSlider *slider = new QSlider(Qt::Horizontal);
  slider->setRange(0, 100);
  slider->setValue(50);

  QSpinBox *spinBox = new QSpinBox;
  spinBox->setRange(0, 100);
  spinBox->setValue(50);

  QObject::connect(slider, &QSlider::valueChanged, spinBox,
                   &QSpinBox::setValue);
  QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider,
                   &QSlider::setValue);

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(slider);
  layout->addWidget(spinBox);
  window.setLayout(layout);

  window.show();
  return a.exec();
}
```
## QWidget
`QWidget` 是所有用户界面对象的基类，通常被称为“窗口部件”或“控件”。

- **核心概念:**
  - **窗口和控件的基石:** 在 Qt 中，所有能显示在屏幕上的东西（如按钮、标签、文本框，甚至窗口本身）都直接或间接地继承自 `QWidget`。
  - **父子关系:** `QWidget` 可以包含其他 `QWidget` 对象，形成一个层次结构。一个控件可以是另一个控件的“子控件”。当父控件被销毁时，它的所有子控件也会被自动销毁。当父控件移动时，子控件也会跟着移动。
  - **窗口容器:** 如果一个 `QWidget` 没有父控件，它就会成为一个独立的窗口（顶级窗口），拥有自己的窗口边框和标题栏。
  - **事件处理:** `QWidget` 能够接收和处理鼠标、键盘等事件。

在“窗口布局”示例中，`QWidget window;` 创建了一个顶级窗口，作为所有其他控件（滑块、数字输入框）的容器。

### QHBoxLayout
`QHBoxLayout` 是一个布局管理器，用于将控件在水平方向上排列。

- **主要作用:**
  - **自动排列:** 它可以自动管理其内部控件的位置和大小，将它们从左到右依次排列。
  - **空间分配:** `QHBoxLayout` 会智能地分配水平空间。你可以为控件设置伸展因子 (stretch factor)，来控制它们在有多余空间时如何拉伸。
  - **响应式布局:** 当窗口大小改变时，`QHBoxLayout` 会自动调整其内部控件的大小和位置，以适应新的窗口尺寸，保持布局的美观和可用性。

在示例中，`QHBoxLayout` 被用来将 `QSlider` 和 `QSpinBox` 水平并排放在 `window` 控件中。`layout->addWidget()` 方法将控件添加到布局中，`window.setLayout(layout)` 将该布局应用到窗口上。

### QSlider
`QSlider` 是一个经典的滑块控件，允许用户通过拖动滑块在一个指定的整数范围内选择一个值。

- **主要特性:**
  - **方向:** 可以是水平的 (`Qt::Horizontal`) 或垂直的 (`Qt::Vertical`)。
  - **范围和值:**
    - `setRange(min, max)`: 设置滑块可以表示的最小值和最大值。
    - `setValue(value)`: 设置滑块的当前值。
    - `value()`: 获取滑块的当前值。
  - **信号:**
    - `valueChanged(int value)`: 当滑块的值发生改变时（无论是通过用户拖动还是代码设置），此信号会被发出。这是 `QSlider` 最常用的信号。
    - `sliderMoved(int position)`: 仅当用户拖动滑块时发出。
    - `sliderPressed()` / `sliderReleased()`: 当用户按下或释放滑块时发出。

在示例中，`QSlider` 和 `QSpinBox` 的 `valueChanged` 信号与对方的 `setValue` 槽相连接，实现了两者之间的双向数据同步。

### QSpinBox
`QSpinBox` 是一个数字输入控件，通常由一个显示当前值的文本框和一对用于增加/减少值的上下箭头按钮组成。

- **主要特性:**
  - **整数范围:** 用于处理整数值。对于浮点数，应该使用 `QDoubleSpinBox`。
  - **范围和步长:**
    - `setRange(min, max)`: 设置允许的最小值和最大值。
    - `setValue(value)`: 设置当前值。
    - `setSingleStep(step)`: 设置每次点击箭头按钮时值改变的步长。
  - **前后缀:** 可以为显示的数字添加前缀（如 `$`）或后缀（如 `°C`）。
  - **信号:**
    - `valueChanged(int value)`: 当值改变时发出。
    - `valueChanged(const QString &text)`: 当值改变时，以字符串形式发出。

在示例中，`QSpinBox` 提供了一种精确输入数值的方式，并与 `QSlider` 实现了数据同步，用户既可以通过拖动滑块来改变值，也可以通过点击箭头或直接输入来改变值。


### 参考文档

#### 官方在线文档 (最推荐)
这是最权威、最及时、内容最全面的方式。Qt 官方会持续更新在线文档。

访问地址: doc.qt.io
优点:
永远是最新版本。
包含所有 Qt 模块、类、函数以及详细的示例代码。
强大的搜索功能。
使用建议: 将这个网站收藏到您的浏览器书签中。在开发时，这是最可靠的参考来源。您可以直接搜索类名，例如搜索 QSlider 就能找到其详细文档。
#### Qt Assistant (离线文档)
这是一个包含在 Qt SDK 中的离线文档查看器。如果您在安装 Qt 时选择了文档组件，那么它就已经在您的电脑上了。

如何启动:
在 Windows 的开始菜单中搜索 "Qt Assistant"。
它通常位于您的 Qt 安装目录的 bin 文件夹下，例如 C:\Qt\5.15.2\msvc2019_64\bin\assistant.exe。
优点:
完全离线: 无需网络连接，访问速度极快。
内容全面，与您安装的 Qt 版本完全对应。
使用建议: 当您在没有网络的环境下开发，或者希望快速查找文档时，Qt Assistant 是最佳选择。
#### IDE 集成 (最高效)
如果您使用专门的 C++ IDE (如 Qt Creator 或带有 Qt VS Tools 插件的 Visual Studio)，可以直接在代码中获取帮助。

如何使用:
将光标放在您想查询的 Qt 类名或函数名上（例如 QSlider）。
按下 F1 键。
效果:
IDE 会自动跳转到 Qt Assistant 或其内置的帮助浏览器，并直接显示该类的文档页面。
优点:
这是在编码过程中查阅文档效率最高的方式，无需离开编辑器去手动搜索。