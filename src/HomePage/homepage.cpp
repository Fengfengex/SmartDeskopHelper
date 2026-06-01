#include "homepage.h"
#include "../Utils/constants.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QFont>
#include <QDebug>
#include <QGridLayout>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_dateLabel(nullptr),
      m_weekLabel(nullptr),
      m_timeLabel(nullptr),
      m_systemTimeWidget(nullptr),
      m_clockDisplay(nullptr),
      m_todoButton(nullptr),
      m_noteButton(nullptr),
      m_toolsButton(nullptr),
      m_settingsButton(nullptr),
      m_statusLabel(nullptr),
      m_statusTimer(nullptr),
      m_mainLayout(nullptr),
      m_clockTimer(nullptr) {
    
    // 初始化UI
    initializeUI();
    
    // 应用样式
    applyStylesheet();
}

HomePage::~HomePage() {
    if (m_clockTimer) {
        m_clockTimer->stop();
    }
}

void HomePage::initialize() {
    // 初始化时钟显示
    m_clockDisplay->initialize();
    
    // 初始化定时器
    m_clockTimer = new QTimer(this);
    connect(m_clockTimer, &QTimer::timeout, this, &HomePage::onUpdateClock);
    m_clockTimer->setInterval(1000);
    m_clockTimer->start();
    
    // 初始连接信号槽
    connectSignals();
    
    // 立即更新一次
    updateSystemTime();
    
    qDebug() << "HomePage initialized";
}

void HomePage::updateSystemTime() {
    QDateTime now = QDateTime::currentDateTime();
    
    // 更新日期
    QString dateStr = now.toString("yyyy年MM月dd日");
    m_dateLabel->setText(dateStr);
    
    // 更新星期
    QStringList weeks = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
    int dayOfWeek = now.date().dayOfWeek() - 1;
    if (dayOfWeek < 0) dayOfWeek = 6;
    m_weekLabel->setText(weeks[dayOfWeek]);
    
    // 更新时间
    QString timeStr = now.toString("hh:mm:ss");
    m_timeLabel->setText(timeStr);
}

void HomePage::updateStatusMessage(const QString &message, int duration) {
    m_statusLabel->setText(message);
    
    if (m_statusTimer) {
        m_statusTimer->stop();
        disconnect(m_statusTimer, nullptr, nullptr, nullptr);
    } else {
        m_statusTimer = new QTimer(this);
    }
    
    connect(m_statusTimer, &QTimer::timeout, [this]() {
        m_statusLabel->setText("系统就绪");
        m_statusTimer->stop();
    });
    
    m_statusTimer->start(duration);
}

void HomePage::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}

void HomePage::onUpdateClock() {
    updateSystemTime();
}

void HomePage::onTodoButtonClicked() {
    emit navigationToTodo();
    updateStatusMessage("已跳转至待办事项");
}

void HomePage::onNoteButtonClicked() {
    emit navigationToNote();
    updateStatusMessage("已跳转至备忘录");
}

void HomePage::onToolsButtonClicked() {
    emit navigationToTools();
    updateStatusMessage("已跳转至工具箱");
}

void HomePage::onSettingsButtonClicked() {
    emit navigationToSettings();
    updateStatusMessage("已跳转至系统设置");
}

void HomePage::initializeUI() {
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(15, 15, 15, 15);
    m_mainLayout->setSpacing(15);
    
    // 创建系统时间区域
    createSystemTimeArea();
    
    // 创建时钟显示区域
    createClockArea();
    
    // 创建功能快捷入口
    createFunctionButtonArea();
    
    // 添加弹性空间
    m_mainLayout->addStretch();
    
    // 创建状态栏
    createStatusBar();
    
    setLayout(m_mainLayout);
}

void HomePage::createSystemTimeArea() {
    m_systemTimeWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_systemTimeWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);
    
    // 日期标签
    m_dateLabel = new QLabel();
    QFont dateFont(AppConstants::FONT_NAME, 20, QFont::Bold);
    m_dateLabel->setFont(dateFont);
    m_dateLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_dateLabel);
    
    // 星期标签
    m_weekLabel = new QLabel();
    QFont weekFont(AppConstants::FONT_NAME, 14);
    m_weekLabel->setFont(weekFont);
    m_weekLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_weekLabel);
    
    // 时间标签
    m_timeLabel = new QLabel();
    QFont timeFont(AppConstants::FONT_NAME, 48, QFont::Bold);
    m_timeLabel->setFont(timeFont);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_timeLabel);
    
    m_systemTimeWidget->setLayout(layout);
    m_mainLayout->addWidget(m_systemTimeWidget);
}

void HomePage::createClockArea() {
    m_clockDisplay = new ClockDisplay();
    m_mainLayout->addWidget(m_clockDisplay, 1);
}

void HomePage::createFunctionButtonArea() {
    QWidget *buttonWidget = new QWidget();
    QGridLayout *layout = new QGridLayout(buttonWidget);
    layout->setSpacing(10);
    
    // 创建功能按钮
    m_todoButton = new QPushButton("✓ 待办事项");
    m_noteButton = new QPushButton("📝 备忘录");
    m_toolsButton = new QPushButton("🔧 工具箱");
    m_settingsButton = new QPushButton("⚙️ 系统设置");
    
    // 设置按钮大小
    for (auto btn : {m_todoButton, m_noteButton, m_toolsButton, m_settingsButton}) {
        btn->setMinimumHeight(60);
        QFont btnFont(AppConstants::FONT_NAME, 12, QFont::Bold);
        btn->setFont(btnFont);
    }
    
    // 按2x2网格排列
    layout->addWidget(m_todoButton, 0, 0);
    layout->addWidget(m_noteButton, 0, 1);
    layout->addWidget(m_toolsButton, 1, 0);
    layout->addWidget(m_settingsButton, 1, 1);
    
    buttonWidget->setLayout(layout);
    m_mainLayout->addWidget(buttonWidget);
}

void HomePage::createStatusBar() {
    m_statusLabel = new QLabel("系统就绪");
    QFont statusFont(AppConstants::FONT_NAME, 10);
    m_statusLabel->setFont(statusFont);
    m_statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 5px; border-radius: 3px;");
    m_mainLayout->addWidget(m_statusLabel);
}

void HomePage::connectSignals() {
    connect(m_todoButton, &QPushButton::clicked, this, &HomePage::onTodoButtonClicked);
    connect(m_noteButton, &QPushButton::clicked, this, &HomePage::onNoteButtonClicked);
    connect(m_toolsButton, &QPushButton::clicked, this, &HomePage::onToolsButtonClicked);
    connect(m_settingsButton, &QPushButton::clicked, this, &HomePage::onSettingsButtonClicked);
}

void HomePage::applyStylesheet() {
    QString styleSheet = QString(
        "HomePage { background-color: %1; }"
        "QPushButton { background-color: %2; color: white; border-radius: 5px; border: none; }"
        "QPushButton:hover { background-color: %3; }"
        "QLabel { color: %4; }"
    ).arg(AppConstants::COLOR_BACKGROUND,
          AppConstants::COLOR_HIGHLIGHT,
          "#005a9e",
          AppConstants::COLOR_TEXT);
    
    setStyleSheet(styleSheet);
}
