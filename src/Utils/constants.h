#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QMap>

// 应用程序常量
namespace AppConstants {
    
    // 应用名称和版本
    const QString APP_NAME = "SmartDesktopHelper";
    const QString APP_VERSION = "1.0.0";
    const QString APP_TITLE = "智能桌面生活助手系统";
    
    // 数据文件路径
    const QString DATA_DIR = "./data";
    const QString TASKS_FILE = "./data/tasks.json";
    const QString NOTES_FILE = "./data/notes.json";
    const QString SETTINGS_FILE = "./data/settings.json";
    const QString TIMEZONES_FILE = "./data/timezones.json";
    
    // 窗口默认大小
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    const int MIN_WINDOW_WIDTH = 800;
    const int MIN_WINDOW_HEIGHT = 600;
    
    // 时钟更新间隔（毫秒）
    const int CLOCK_UPDATE_INTERVAL = 1000;  // 1秒
    
    // 默认时区列表
    const QMap<QString, QString> DEFAULT_TIMEZONES = {
        {"Asia/Shanghai", "北京 (Beijing)"},
        {"America/New_York", "纽约 (New York)"},
        {"Europe/London", "伦敦 (London)"},
        {"Asia/Tokyo", "东京 (Tokyo)"},
        {"Australia/Sydney", "悉尼 (Sydney)"}
    };
    
    // 字体设置
    const QString FONT_NAME = "Microsoft YaHei";
    const int FONT_SIZE_NORMAL = 11;
    const int FONT_SIZE_LARGE = 14;
    const int FONT_SIZE_TITLE = 16;
    const int FONT_SIZE_CLOCK = 48;
    
    // 颜色设置
    const QString COLOR_BACKGROUND = "#f5f5f5";
    const QString COLOR_TEXT = "#333333";
    const QString COLOR_BORDER = "#cccccc";
    const QString COLOR_HIGHLIGHT = "#0078d7";
    const QString COLOR_ERROR = "#d32f2f";
    const QString COLOR_SUCCESS = "#388e3c";
    
    // 按钮大小
    const int BUTTON_WIDTH = 120;
    const int BUTTON_HEIGHT = 40;
    
    // 状态栏消息显示时间（毫秒）
    const int STATUS_MESSAGE_DURATION = 3000;
}

#endif // CONSTANTS_H