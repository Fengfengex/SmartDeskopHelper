#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

/**
 * @class FileManager
 * @brief 文件管理器 - 处理本地数据的读写操作
 * 
 * 功能：
 * - JSON文件的读取和写入
 * - 数据目录的创建和管理
 * - 文件存在性检查
 */
class FileManager {
public:
    FileManager();
    ~FileManager();

    /**
     * @brief 创建数据目录（如果不存在）
     * @param dirPath 目录路径
     * @return 是否成功
     */
    static bool ensureDataDirectory(const QString &dirPath);

    /**
     * @brief 读取JSON文件
     * @param filePath 文件路径
     * @return JSON文档
     */
    static QJsonDocument readJsonFile(const QString &filePath);

    /**
     * @brief 写入JSON文件
     * @param filePath 文件路径
     * @param doc JSON文档
     * @return 是否成功
     */
    static bool writeJsonFile(const QString &filePath, const QJsonDocument &doc);

    /**
     * @brief 检查文件是否存在
     * @param filePath 文件路径
     * @return 是否存在
     */
    static bool fileExists(const QString &filePath);

    /**
     * @brief 删除文件
     * @param filePath 文件路径
     * @return 是否成功
     */
    static bool deleteFile(const QString &filePath);

    /**
     * @brief 清空文件内容
     * @param filePath 文件路径
     * @return 是否成功
     */
    static bool clearFile(const QString &filePath);

    /**
     * @brief 获取文件大小
     * @param filePath 文件路径
     * @return 文件大小（字节）
     */
    static qint64 getFileSize(const QString &filePath);

    /**
     * @brief 初始化所有数据目录和文件
     * @return 是否成功
     */
    static bool initializeDataStructure();
};

#endif // FILEMANAGER_H