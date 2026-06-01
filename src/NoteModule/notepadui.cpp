#include "notepadui.h"
#include "../Utils/constants.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFont>
#include <QDebug>

NotepadUI::NotepadUI(QWidget *parent)
    : QWidget(parent),
      m_noteManager(nullptr),
      m_textEdit(nullptr),
      m_saveButton(nullptr),
      m_clearButton(nullptr),
      m_backButton(nullptr),
      m_statusLabel(nullptr) {
    
    m_noteManager = new NoteManager(this);
    initializeUI();
    applyStylesheet();
}

NotepadUI::~NotepadUI() {
}

void NotepadUI::initialize() {
    loadNote();
    connectSignals();
    updateStatusLabel();
    qDebug() << "NotepadUI initialized";
}

void NotepadUI::refresh() {
    loadNote();
    updateStatusLabel();
}

void NotepadUI::onSaveNote() {
    QString content = m_textEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, "警告", "备忘录为空，无法保存");
        return;
    }

    m_noteManager->setNoteContent(content);
    if (m_noteManager->saveNote(AppConstants::NOTES_FILE, content)) {
        QMessageBox::information(this, "成功", "备忘录已保存");
        updateStatusLabel();
    } else {
        QMessageBox::critical(this, "错误", "保存备忘录失败");
    }
}

void NotepadUI::onClearNote() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "确认清空",
                                                               "确定要清空备忘录吗？");
    if (reply == QMessageBox::Yes) {
        m_textEdit->clear();
        m_noteManager->clearNote();
        m_noteManager->saveNote(AppConstants::NOTES_FILE, "");
        updateStatusLabel();
        QMessageBox::information(this, "成功", "备忘录已清空");
    }
}

void NotepadUI::onBackButtonClicked() {
    if (m_noteManager->hasUnsavedChanges()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "未保存的更改",
                                                                   "您有未保存的更改，是否保存？");
        if (reply == QMessageBox::Yes) {
            onSaveNote();
        }
    }
    emit backToHome();
}

void NotepadUI::onContentChanged() {
    updateStatusLabel();
}

void NotepadUI::initializeUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    QLabel *titleLabel = new QLabel("📝 备忘录");
    QFont titleFont(AppConstants::FONT_NAME, 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    m_textEdit = new QTextEdit();
    m_textEdit->setPlaceholderText("在此输入备忘录内容...\n\n支持自动换行和多行文本编辑。");
    m_textEdit->setMinimumHeight(400);
    QFont textFont(AppConstants::FONT_NAME, 11);
    m_textEdit->setFont(textFont);
    mainLayout->addWidget(m_textEdit, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    m_saveButton = new QPushButton("💾 保存");
    m_saveButton->setMinimumHeight(40);
    buttonLayout->addWidget(m_saveButton);

    m_clearButton = new QPushButton("🔄 清空");
    m_clearButton->setMinimumHeight(40);
    buttonLayout->addWidget(m_clearButton);

    buttonLayout->addStretch();

    m_backButton = new QPushButton("← 返回首页");
    m_backButton->setMinimumHeight(40);
    m_backButton->setMaximumWidth(120);
    buttonLayout->addWidget(m_backButton);

    mainLayout->addLayout(buttonLayout);

    m_statusLabel = new QLabel("就绪");
    m_statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 5px; border-radius: 3px;");
    mainLayout->addWidget(m_statusLabel);

    setLayout(mainLayout);
}

void NotepadUI::connectSignals() {
    connect(m_saveButton, &QPushButton::clicked, this, &NotepadUI::onSaveNote);
    connect(m_clearButton, &QPushButton::clicked, this, &NotepadUI::onClearNote);
    connect(m_backButton, &QPushButton::clicked, this, &NotepadUI::onBackButtonClicked);
    connect(m_textEdit, &QTextEdit::textChanged, this, &NotepadUI::onContentChanged);
}

void NotepadUI::applyStylesheet() {
    QString styleSheet = QString(
        "NotepadUI { background-color: %1; }"
        "QPushButton { background-color: %2; color: white; border-radius: 5px; border: none; font-weight: bold; }"
        "QPushButton:hover { background-color: #005a9e; }"
        "QTextEdit { border: 1px solid %3; border-radius: 5px; padding: 5px; }"
        "QLabel { color: %4; }"
    ).arg(AppConstants::COLOR_BACKGROUND, AppConstants::COLOR_HIGHLIGHT, AppConstants::COLOR_BORDER, AppConstants::COLOR_TEXT);
    
    setStyleSheet(styleSheet);
}

void NotepadUI::updateStatusLabel() {
    QString content = m_textEdit->toPlainText();
    int charCount = content.length();
    int lineCount = m_textEdit->document()->blockCount();
    
    QString status;
    if (m_noteManager->hasUnsavedChanges()) {
        status = QString("✎ 字数: %1 | 行数: %2 | 有未保存的更改")
                 .arg(charCount).arg(lineCount);
    } else {
        status = QString("字数: %1 | 行数: %2 | 已保存")
                 .arg(charCount).arg(lineCount);
    }
    
    m_statusLabel->setText(status);
}

void NotepadUI::loadNote() {
    m_noteManager->loadNote(AppConstants::NOTES_FILE);
    m_textEdit->setPlainText(m_noteManager->getNoteContent());
}
