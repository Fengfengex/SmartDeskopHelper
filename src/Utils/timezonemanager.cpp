#include "timezonemanager.h"
#include "constants.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

TimeZoneManager::TimeZoneManager() {
    // 初始化时区容器
}

TimeZoneManager::~TimeZoneManager() {
    // 清理资源
}

bool TimeZoneManager::addTimeZone(const QString &tzId, const QString &displayName) {
    // 检查时区是否已存在
    if (m_timeZones.contains(tzId)) {
        qWarning() << "TimeZone already exists:" << tzId;
        return false;
    }

    // 检查时区ID是否有效
    QTimeZone tz(tzId.toUtf8());
    if (!tz.isValid()) {
        qWarning() << "Invalid TimeZone ID:" << tzId;
        return false;
    }

    TimeZoneInfo info = createTimeZoneInfo(tzId, displayName);
    m_timeZones.insert(tzId, info);
    qDebug() << "Added TimeZone:" << tzId << "-" << displayName;
    return true;
}

bool TimeZoneManager::removeTimeZone(const QString &tzId) {
    if (!m_timeZones.contains(tzId)) {
        qWarning() << "TimeZone not found:" << tzId;
        return false;
    }

    m_timeZones.remove(tzId);
    qDebug() << "Removed TimeZone:" << tzId;
    return true;
}

QDateTime TimeZoneManager::getTimeInZone(const QString &tzId) {
    if (!m_timeZones.contains(tzId)) {
        qWarning() << "TimeZone not found:" << tzId;
        return QDateTime();
    }

    QTimeZone tz(tzId.toUtf8());
    QDateTime now = QDateTime::currentDateTime();
    QDateTime zoneTime = now.toTimeZone(tz);
    return zoneTime;
}

int TimeZoneManager::getUtcOffset(const QString &tzId) {
    if (!m_timeZones.contains(tzId)) {
        return 0;
    }

    QTimeZone tz(tzId.toUtf8());
    return tz.standardTimeOffset(QDateTime::currentDateTime()) / 3600;  // 转换为小时
}

TimeZoneManager::TimeZoneInfo TimeZoneManager::getTimeZoneInfo(const QString &tzId) const {
    if (m_timeZones.contains(tzId)) {
        return m_timeZones.value(tzId);
    }
    return TimeZoneInfo();
}

QVector<TimeZoneManager::TimeZoneInfo> TimeZoneManager::getAllTimeZones() const {
    return m_timeZones.values().toVector();
}

QVector<TimeZoneManager::TimeZoneInfo> TimeZoneManager::getSelectedTimeZones() const {
    QVector<TimeZoneInfo> selected;
    for (const auto &info : m_timeZones.values()) {
        if (info.selected) {
            selected.append(info);
        }
    }
    return selected;
}

void TimeZoneManager::setTimeZoneSelected(const QString &tzId, bool selected) {
    if (m_timeZones.contains(tzId)) {
        m_timeZones[tzId].selected = selected;
    }
}

bool TimeZoneManager::hasTimeZone(const QString &tzId) const {
    return m_timeZones.contains(tzId);
}

void TimeZoneManager::clearAllTimeZones() {
    m_timeZones.clear();
    qDebug() << "Cleared all TimeZones";
}

int TimeZoneManager::timeZoneCount() const {
    return m_timeZones.size();
}

bool TimeZoneManager::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) {
        qWarning() << "Invalid JSON format";
        return false;
    }

    QJsonArray tzArray = doc.object()["timezones"].toArray();
    for (const auto &value : tzArray) {
        TimeZoneInfo info = jsonToTimeZoneInfo(value.toObject());
        m_timeZones.insert(info.id, info);
    }

    qDebug() << "Loaded" << m_timeZones.size() << "time zones from file";
    return true;
}

bool TimeZoneManager::saveToFile(const QString &filePath) {
    QJsonArray tzArray;
    for (const auto &info : m_timeZones.values()) {
        tzArray.append(timeZoneInfoToJson(info));
    }

    QJsonObject root;
    root["timezones"] = tzArray;
    root["savedAt"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(root);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to write to file:" << filePath;
        return false;
    }

    file.write(doc.toJson());
    file.close();

    qDebug() << "Saved time zones to file";
    return true;
}

void TimeZoneManager::initializeWithDefaults() {
    clearAllTimeZones();
    
    for (auto it = AppConstants::DEFAULT_TIMEZONES.begin(); 
         it != AppConstants::DEFAULT_TIMEZONES.end(); ++it) {
        addTimeZone(it.key(), it.value());
        setTimeZoneSelected(it.key(), true);
    }
    
    qDebug() << "Initialized with default time zones";
}

QString TimeZoneManager::getSystemTimeZone() {
    return QTimeZone::systemTimeZone().id();
}

QStringList TimeZoneManager::getAvailableTimeZones() {
    QStringList zones;
    for (const auto &id : QTimeZone::availableTimeZoneIds()) {
        zones.append(QString::fromUtf8(id));
    }
    return zones;
}

QDateTime TimeZoneManager::convertUtcToZone(const QDateTime &utcTime, const QString &tzId) {
    QTimeZone tz(tzId.toUtf8());
    if (!tz.isValid()) {
        return QDateTime();
    }
    return utcTime.toTimeZone(tz);
}

QString TimeZoneManager::getFormattedTime(const QString &tzId, const QString &format) {
    QDateTime time = getTimeInZone(tzId);
    return time.toString(format);
}

QString TimeZoneManager::getFormattedInfo(const QString &tzId) {
    if (!m_timeZones.contains(tzId)) {
        return "";
    }

    TimeZoneInfo info = m_timeZones[tzId];
    QString timeStr = getFormattedTime(tzId, "hh:mm:ss");
    return QString("%1  %2").arg(info.name, timeStr);
}

TimeZoneManager::TimeZoneInfo TimeZoneManager::createTimeZoneInfo(
    const QString &tzId, const QString &displayName) {
    
    QTimeZone tz(tzId.toUtf8());
    TimeZoneInfo info;
    info.id = tzId;
    info.name = displayName;
    info.utcOffset = tz.standardTimeOffset(QDateTime::currentDateTime());
    info.displayName = QString("%1 (UTC%2%3")
        .arg(displayName)
        .arg(info.utcOffset / 3600 > 0 ? "+" : "")
        .arg(info.utcOffset / 3600);
    info.selected = false;
    
    return info;
}

TimeZoneManager::TimeZoneInfo TimeZoneManager::jsonToTimeZoneInfo(
    const QJsonObject &obj) {
    
    TimeZoneInfo info;
    info.id = obj["id"].toString();
    info.name = obj["name"].toString();
    info.displayName = obj["displayName"].toString();
    info.utcOffset = obj["utcOffset"].toInt();
    info.selected = obj["selected"].toBool();
    
    return info;
}

QJsonObject TimeZoneManager::timeZoneInfoToJson(const TimeZoneInfo &info) {
    QJsonObject obj;
    obj["id"] = info.id;
    obj["name"] = info.name;
    obj["displayName"] = info.displayName;
    obj["utcOffset"] = info.utcOffset;
    obj["selected"] = info.selected;
    
    return obj;
}