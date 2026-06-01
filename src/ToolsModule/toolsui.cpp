#include "toolsui.h"
#include "../Utils/constants.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QDebug>

ToolsUI::ToolsUI(QWidget *parent)
    : QWidget(parent),
      m_stackedWidget(nullptr),
      m_calculatorUI(nullptr),
      m_imageViewerUI(nullptr),
      m_calculatorBtn(nullptr),
      m_imageViewerBtn(nullptr),
      m_backBtn(nullptr) {
    
    initializeUI();
    applyStylesheet();
}

ToolsUI::~ToolsUI() {
}

void ToolsUI::initialize() {
    m_calculatorUI->initialize();
    m_imageViewerUI->initialize();
    connectSignals();
    qDebug() << "ToolsUI initialized";
}

void ToolsUI::onCalculatorClicked() {
    m_stackedWidget->setCurrentWidget(m_calculatorUI);
}

void ToolsUI::onImageViewerClicked() {
    m_stackedWidget->setCurrentWidget(m_imageViewerUI);
}

void ToolsUI::onBackHome() {
    emit backToHome();
}

void ToolsUI::initializeUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    // 标题
    QLabel *titleLabel = new QLabel("🔧 工具箱");
    QFont titleFont(AppConstants::FONT_NAME, 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // 工具选择按钮
    QHBoxLayout *toolButtonLayout = new QHBoxLayout();
    
    m_calculatorBtn = new QPushButton("🧮 计算器");
    m_calculatorBtn->setMinimumHeight(50);
    toolButtonLayout->addWidget(m_calculatorBtn);

    m_imageViewerBtn = new QPushButton("🖼️ 图片浏览");
    m_imageViewerBtn->setMinimumHeight(50);
    toolButtonLayout->addWidget(m_imageViewerBtn);

    mainLayout->addLayout(toolButtonLayout);

    // 堆栈窗口
    m_stackedWidget = new QStackedWidget();
    
    m_calculatorUI = new CalculatorUI();
    m_stackedWidget->addWidget(m_calculatorUI);
    connect(m_calculatorUI, &CalculatorUI::backToHome, this, &ToolsUI::onBackHome);
    
    m_imageViewerUI = new ImageViewer();
    m_stackedWidget->addWidget(m_imageViewerUI);
    connect(m_imageViewerUI, &ImageViewer::backToHome, this, &ToolsUI::onBackHome);

    mainLayout->addWidget(m_stackedWidget, 1);

    // 返回按钮
    m_backBtn = new QPushButton("← 返回首页");
    m_backBtn->setMinimumHeight(40);
    mainLayout->addWidget(m_backBtn);

    setLayout(mainLayout);
}

void ToolsUI::connectSignals() {
    connect(m_calculatorBtn, &QPushButton::clicked, this, &ToolsUI::onCalculatorClicked);
    connect(m_imageViewerBtn, &QPushButton::clicked, this, &ToolsUI::onImageViewerClicked);
    connect(m_backBtn, &QPushButton::clicked, this, &ToolsUI::onBackHome);
}

void ToolsUI::applyStylesheet() {
    QString styleSheet = QString(
        "ToolsUI { background-color: %1; }"
        "QPushButton { background-color: %2; color: white; border-radius: 5px; border: none; font-weight: bold; }"
        "QPushButton:hover { background-color: #005a9e; }"
        "QLabel { color: %3; }"
    ).arg(AppConstants::COLOR_BACKGROUND, AppConstants::COLOR_HIGHLIGHT, AppConstants::COLOR_TEXT);
    
    setStyleSheet(styleSheet);
}
