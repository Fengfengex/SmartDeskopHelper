#ifndef TODOITEM_H
#define TODOITEM_H

#include <QString>
#include <QJsonObject>
#include <QDateTime>

/**
 * @class TodoItem
 * @brief 待办事项数据类 - 表示一个待办任务
 */
class TodoItem {
public:
    enum Priority {
        Low = 0,      // 低优先级
        Medium = 1,   // 中优先级
        High = 2      // 高优先级
    };

    TodoItem();
    TodoItem(const QString &title, Priority priority = Medium);
    ~TodoItem();

    // Getters
    QString getId() const { return m_id; }
    QString getTitle() const { return m_title; }
    QString getDescription() const { return m_description; }
    Priority getPriority() const { return m_priority; }
    bool isCompleted() const { return m_completed; }
    QDateTime getCreatedTime() const { return m_createdTime; }
    QDateTime getDueDate() const { return m_dueDate; }

    // Setters
    void setTitle(const QString &title) { m_title = title; }
    void setDescription(const QString &desc) { m_description = desc; }
    void setPriority(Priority priority) { m_priority = priority; }
    void setCompleted(bool completed) { m_completed = completed; }
    void setDueDate(const QDateTime &date) { m_dueDate = date; }

    // Utility
    QString getPriorityString() const;
    static Priority stringToPriority(const QString &str);

    // JSON 序列化
    QJsonObject toJson() const;
    static TodoItem fromJson(const QJsonObject &obj);

private:
    QString m_id;
    QString m_title;
    QString m_description;
    Priority m_priority;
    bool m_completed;
    QDateTime m_createdTime;
    QDateTime m_dueDate;
};

#endif // TODOITEM_H
