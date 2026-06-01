#include "todoitem.h"
#include <QUuid>
#include <QJsonObject>
#include <QDebug>

TodoItem::TodoItem()
    : m_id(QUuid::createUuid().toString()),
      m_priority(Medium),
      m_completed(false),
      m_createdTime(QDateTime::currentDateTime()) {
}

TodoItem::TodoItem(const QString &title, Priority priority)
    : m_id(QUuid::createUuid().toString()),
      m_title(title),
      m_priority(priority),
      m_completed(false),
      m_createdTime(QDateTime::currentDateTime()) {
}

TodoItem::~TodoItem() {
}

QString TodoItem::getPriorityString() const {
    switch (m_priority) {
        case Low:
            return QStringLiteral("低");
        case Medium:
            return QStringLiteral("中");
        case High:
            return QStringLiteral("高");
        default:
            return QStringLiteral("未知");
    }
}

TodoItem::Priority TodoItem::stringToPriority(const QString &str) {
    if (str == "低") return Low;
    if (str == "中") return Medium;
    if (str == "高") return High;
    return Medium;
}

QJsonObject TodoItem::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["title"] = m_title;
    obj["description"] = m_description;
    obj["priority"] = (int)m_priority;
    obj["completed"] = m_completed;
    obj["createdTime"] = m_createdTime.toString(Qt::ISODate);
    obj["dueDate"] = m_dueDate.toString(Qt::ISODate);
    return obj;
}

TodoItem TodoItem::fromJson(const QJsonObject &obj) {
    TodoItem item;
    item.m_id = obj["id"].toString();
    item.m_title = obj["title"].toString();
    item.m_description = obj["description"].toString();
    item.m_priority = (Priority)obj["priority"].toInt(Medium);
    item.m_completed = obj["completed"].toBool();
    item.m_createdTime = QDateTime::fromString(obj["createdTime"].toString(), Qt::ISODate);
    item.m_dueDate = QDateTime::fromString(obj["dueDate"].toString(), Qt::ISODate);
    return item;
}
