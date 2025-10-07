// Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

// QilHost.cpp : Defines the entry point for the application.

#include "QilHost.h"

int main()
{
    // 将控制台的活动代码页由936 GBK设置为65001 UTF-8。
    system("chcp 65001");
    {
        // 创建一个控制台颜色输出器
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        {
            console_sink->set_pattern("%^[%H:%M:%S.%e] [%t] [%s-%#-%!] [%l] %v%$"); // 设置日志格式 %^ start color, %t thread id, %s source fileName, %# source fileLine, %! source funcName, #l log level, %v log text, %$ end color.
            console_sink->set_level(spdlog::level::trace); // 设置控制台日志级别
        }
        // 创建一个文件输出器，若为空文件夹则自动创建文件夹和文件，若存在文件及和文件则自动续写。
        std::string logPath;
        {
            int32_t intDate;
            {
                time_t systemTime = time(nullptr);
                tm localTime;
                localtime_s(&localTime, &systemTime);
                intDate = (localTime.tm_year + 1900) * 10000 + (localTime.tm_mon + 1) * 100 + localTime.tm_mday;
            }
            {
                char User_AppData_Local[MAX_PATH];
                SHGetSpecialFolderPathA(0, User_AppData_Local, CSIDL_LOCAL_APPDATA, 0);
                logPath = std::string { User_AppData_Local } + "\\.QIL\\SpLog\\" + std::to_string(intDate) + ".txt";
            }
        }
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath);
        {
            file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%s-%#-%!] [%l] %v"); // 设置日志格式 %t thread id, %s source fileName, %# source fileLine, %! source funcName, #l log level, %v log text.
            file_sink->set_level(spdlog::level::trace); // 设置文件日志级别
        }
        // 创建一个多态日志器，它将同时使用控制台和文件输出器
        std::vector<spdlog::sink_ptr> sinks { console_sink, file_sink };
        auto combined_logger = std::make_shared<spdlog::logger>("combined_logger", sinks.begin(), sinks.end());
        {
            spdlog::register_logger(combined_logger); // 注册多态日志器
            combined_logger->flush_on(spdlog::level::trace);
            combined_logger->set_level(spdlog::level::trace); // 设置多态日志器的级别
            spdlog::set_default_logger(combined_logger);
            spdlog::set_level(spdlog::level::trace);
        }
    }

    SPDLOG_INFO(std::string { "QilHost starts." });

    SPDLOG_INFO(std::string { "QilHost exits." });

    {
        // 清理并释放资源
        spdlog::drop_all(); // 释放所有资源
    }

    std::cout << "Hello QilHost CMake." << std::endl;
    return 0;
}
