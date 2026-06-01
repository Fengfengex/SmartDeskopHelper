#ifndef TIMEZONEMANAGER_H
#define TIMEZONEMANAGER_H

#include <QString>
#include <QDateTime>
#include <QTimeZone>
#include <QMap>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

/**
 * @class TimeZoneManager
 * @brief 时区管理器 - 管理多个时区的时间获取和转换
 * 
 * 功能：
 * - 存储和管理多个时区信息
 * - 获取指定时区的当前时间
 * - 时区添加、删除、查询
 * - 时区配置的持久化存储
 */
class TimeZoneManager {
public:
    /**
     * @struct TimeZoneInfo
     * @brief 时区信息结构体
     */
    struct TimeZoneInfo {
        QString id;              // 时区ID（如 "Asia/Shanghai"）
        QString name;            // 时区显示名称（如 "北京"）
        QString displayName;     // 完整显示名称
        int utcOffset;          // UTC偏移量（秒）
        bool selected;          // 是否被选中显示
    };

    TimeZoneManager();
    ~TimeZoneManager();

    // 时区操作
    /**
     * @brief 添加时区
     * @param tzId 时区ID（如 "Asia/Shanghai"）
     * @param displayName 显示名称（如 "北京"）
     * @return 是否添加成功
     */
    bool addTimeZone(const QString &tzId, const QString &displayName);

    /**
     * @brief 移除时区
     * @param tzId 时区ID
     * @return 是否移除成功
     */
    bool removeTimeZone(const QString &tzId);

    /**
     * @brief 获取指定时区的当前时间
     * @param tzId 时区ID
     * @return 该时区的当前时间
     */
    QDateTime getTimeInZone(const QString &tzId);

    /**
     * @brief 获取指定时区的UTC偏移量
     * @param tzId 时区ID
     * @return UTC偏移量（小时）
     */
    int getUtcOffset(const QString &tzId);

    /**
     * @brief 获取指定时区的完整信息
     * @param tzId 时区ID
     * @return 时区信息结构体
     */
    TimeZoneInfo getTimeZoneInfo(const QString &tzId) const;

    // 时区列表操作
    /**
     * @brief 获取所有已添加的时区列表
     * @return 时区信息列表
     */
    QVector<TimeZoneInfo> getAllTimeZones() const;

    /**
     * @brief 获取所有已选中的时区列表
     * @return 选中的时区信息列表
     */
    QVector<TimeZoneInfo> getSelectedTimeZones() const;

    /**
     * @brief 设置时区是否显示
     * @param tzId 时区ID
     * @param selected 是否显示
     */
    void setTimeZoneSelected(const QString &tzId, bool selected);

    /**
     * @brief 检查时区是否存在
     * @param tzId 时区ID
     * @return 是否存在
     */
    bool hasTimeZone(const QString &tzId) const;

    /**
     * @brief 清空所有时区
     */
    void clearAllTimeZones();

    /**
     * @brief 获取时区总数
     * @return 时区数量
     */
    int timeZoneCount() const;

    // 文件操作
    /**
     * @brief 从JSON配置文件加载时区设置
     * @param filePath 配置文件路径
     * @return 是否加载成功
     */
    bool loadFromFile(const QString &filePath);

    /**
     * @brief 将时区设置保存到JSON配置文件
     * @param filePath 配置文件路径
     * @return 是否保存成功
     */
    bool saveToFile(const QString &filePath);

    // 初始化
    /**
     * @brief 使用默认时区初始化
     */
    void initializeWithDefaults();

    /**
     * @brief 获取本地系统时区
     * @return 系统时区ID
     */
    static QString getSystemTimeZone();

    /**
     * @brief 获取可用的所有时区列表
     * @return 可用时区ID列表
     */
    static QStringList getAvailableTimeZones();

    /**
     * @brief 将UTC时间转换到指定时区
     * @param utcTime UTC时间
     * @param tzId 目标时区ID
     * @return 转换后的时间
     */
    static QDateTime convertUtcToZone(const QDateTime &utcTime, const QString &tzId);

    /**
     * @brief 获取时区的格式化时间字符串
     * @param tzId 时区ID
     * @param format 格式字符串（如 "hh:mm:ss"）
     * @return 格式化的时间字符串
     */
    QString getFormattedTime(const QString &tzId, const QString &format = "hh:mm:ss");

    /**
     * @brief 获取时区的格式化完整信息
     * @param tzId 时区ID
     * @return 格式化字符串（如 "北京 14:30:45"）
     */
    QString getFormattedInfo(const QString &tzId);

private:
    QMap<QString, TimeZoneInfo> m_timeZones;  // 时区存储容器

    /**
     * @brief 根据时区ID创建TimeZoneInfo
     */
    TimeZoneInfo createTimeZoneInfo(const QString &tzId, const QString &displayName);

    /**
     * @brief 从JSON对象转换为TimeZoneInfo
     */
    TimeZoneInfo jsonToTimeZoneInfo(const QJsonObject &obj);

    /**
     * @brief 将TimeZoneInfo转换为JSON对象
     */
    QJsonObject timeZoneInfoToJson(const TimeZoneInfo &info);
};

#endif // TIMEZONEMANAGER_H