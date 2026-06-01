# 🖥️ SmartDesktopHelper - 智能桌面生活助手系统

一套面向日常办公与生活服务的智能桌面助手系统，使用 C++、Qt 框架、本地文件存储、定时器机制、多窗口交互开发完成。

## 📋 项目特点

- ✅ **模块化分层架构**：界面交互层、业务功能层、本地数据存储层
- ✅ **零基础友好**：代码结构清晰，适合学习和实训
- ✅ **功能完整**：包含日期/时间、待办、备忘录、工具、设置
- ✅ **实时更新**：基于Qt定时器的秒级刷新机制
- ✅ **数据持久化**：本地JSON文件存储

## 🏗️ 项目架构

```
┌─────────────────────────────────────┐
│     界面交互层 (UI Layer)            │
│  - 首页、待办、备忘录、工具、设置    │
├─────────────────────────────────────┤
│     业务功能层 (Business Logic)      │
│  - 任务管理、记事管理、时区转换等    │
├─────────────────────────────────────┤
│     本地数据存储层 (Data Layer)      │
│  - JSON文件存储、数据持久化          │
└─────────────────────────────────────┘
```

## 🎯 功能模块

### 一、首页总览界面
- 📅 实时动态显示系统当前日期、星期与精确时间
- 🌍 **多时区数字时钟**：北京、纽约、伦敦、东京、悉尼
- 🔘 集中展示系统所有功能模块快捷入口
- 📊 界面底部状态栏实时提示系统运行状态

### 二、待办事项管理界面
- ✏️ 支持手动新增待办任务
- 📌 设置任务完成优先级
- ☑️ 任务状态勾选功能
- 🗑️ 编辑与删除功能
- 💾 自动保存至本地文件

### 三、备忘录记事界面
- 📝 多行文本编辑区域
- 💾 内容保存、一键清空、内容读取
- 📄 自动换行适配长文本
- 🗂️ 独立存储文件

### 四、实用工具界面
- 🧮 简易计算器（加减乘除）
- 🖼️ 图片浏览功能

### 五、系统设置与提示界面
- ⚙️ 基础系统参数配置
- 🎨 界面样式调整
- 💬 全场景消息弹窗提示

## 🚀 快速开始

### 环境要求
- Qt 6.0+
- CMake 3.16+
- C++17 编译器
- Windows/Linux/macOS

### 编译步骤

```bash
# 1. 克隆仓库
git clone https://github.com/Fengfengex/SmartDesktopHelper.git
cd SmartDesktopHelper

# 2. 创建构建目录
mkdir build && cd build

# 3. 使用CMake构建
cmake ..
cmake --build .

# 4. 运行程序
./bin/SmartDesktopHelper
```

### Qt Creator 方式

1. 使用 Qt Creator 打开 `CMakeLists.txt`
2. 选择合适的 Kit 和 Build 目录
3. 点击 **Build** 编译
4. 点击 **Run** 运行

## 📁 项目结构

```
SmartDesktopHelper/
├── CMakeLists.txt              # 构建配置
├── README.md                   # 项目说明
├── .gitignore
│
├── src/
│   ├── main.cpp                # 主入口
│   ├── mainwindow.h/cpp        # 主窗口
│   ├── mainwindow.ui
│   │
│   ├── HomePage/
│   │   ├── homepage.h/cpp      # 首页
│   │   ├── homepage.ui
│   │   └── clockdisplay.h/cpp  # 多时区时钟
│   │
│   ├── TodoModule/             # 待办事项模块
│   ├── NoteModule/             # 备忘录模块
│   ├── ToolsModule/            # 工具模块
│   ├── SettingsModule/         # 设置模块
│   │
│   └── Utils/
│       ├── timezonemanager.h/cpp
│       ├── filemanager.h/cpp
│       └── constants.h
│
├── data/                       # 数据存储
│   ├── timezones.json
│   ├── tasks.json
│   └── notes.json
│
└── resources/
    ├── resources.qrc
    ├── styles/
    │   └── style.qss
    └── icons/
```

## 🔧 核心类说明

### TimeZoneManager
管理多个时区的时间转换和显示。

```cpp
TimeZoneManager manager;
manager.addTimeZone("Asia/Shanghai", "北京");
QDateTime beijing = manager.getTimeInZone("Asia/Shanghai");
```

### ClockDisplay
实时显示多时区数字时钟。

```cpp
ClockDisplay *clock = new ClockDisplay();
layout->addWidget(clock);
clock->initialize();
```

### FileManager
处理本地数据的读写存储。

```cpp
FileManager::ensureDataDirectory("./data");
QJsonDocument data = FileManager::readJsonFile("data/tasks.json");
```

## 📝 使用规范

### 命名规范
- 类名：PascalCase（如 `ClockDisplay`）
- 方法名：camelCase（如 `getTimeInZone`）
- 成员变量：m_前缀（如 `m_timer`）
- 常量：UPPER_CASE（如 `DEFAULT_TIMEZONE`）

### 文件组织
- 每个模块独立文件夹
- `.h` 和 `.cpp` 分离
- UI 文件单独放置

## 🤝 贡献指南

欢迎提交 Pull Request！

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交改动 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 📄 许可证

本项目采用 MIT 许可证

## 📧 联系方式

- GitHub: [@Fengfengex](https://github.com/Fengfengex)
- 项目地址: [SmartDesktopHelper](https://github.com/Fengfengex/SmartDesktopHelper)

---

**Happy Coding! 🚀**