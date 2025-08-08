
---

### `README_zh.md` (中文版模板)

```markdown
# 学习《C++ GUI Programming with Qt 4》笔记与源码

![Qt Version](https://img.shields.io/badge/Qt-5.15.2%20LTS-brightgreen)
![Language](https://img.shields.io/badge/Language-C++-blue.svg)
![License](https://img.shields.io/badge/License-MIT-orange.svg)

本仓库是我学习经典书籍 **《C++ GUI Programming with Qt 4, 第二版》** (作者 Jasmin Blanchette, Mark Summerfield) 的学习记录。其中包含了我的个人学习笔记、课后习题解答以及所有实践代码。所有代码均已适配现代化的 Qt 环境 (Qt 5/6)。

> **[View in English (查看英文版)](./README.md)**

---

## 🎯 项目目标

*   系统性地掌握 Qt GUI 编程的基础知识。
*   亲手实践并实现书中的所有示例。
*   记录并总结将代码从 Qt 4 迁移到 Qt 5/6 版本的差异点与适配方法。
*   打造一个组织良好、可供未来参考的个人 Qt 知识库。

## 📂 仓库结构

本仓库主要分为两个目录：`docs` 用于存放学习笔记，`projects` 用于存放源码。

```bash
learn-qt_cpp-gui-programming-with-qt4/
│
├── .gitignore
├── LICENSE
├── README.md           # 英文版说明
└── README_zh.md        # 本文件 (中文版)
│
├── docs/               # 存放所有 Markdown 格式的学习笔记
│   ├── en/             # 英文笔记
│   └── zh/             # 中文笔记
│
└── projects/           # 存放所有 Qt 源码项目
    ├── ch01-getting-started/
    │   └── 01-hello/
    ├── ch02-creating-dialogs/
    │   ├── 01-find/
    │   └── 02-gotocell/
    └── ...             # 每个示例都是一个独立的、可编译的 Qt 项目
