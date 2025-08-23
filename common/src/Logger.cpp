#include "Logger.h"
#include <iostream>
#include <spdlog/spdlog.h>

const std::string Logger::MAIN_LOGGER_PATTERN {"[%d-%m-%Y %H:%M:%S.%e] [%^%l%$] \033[90m%n\033[0m %v"};
std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> Logger::_consoleSink {nullptr};
std::shared_ptr<spdlog::sinks::basic_file_sink_mt> Logger::_fileSink {nullptr};

Logger::Logger()
{
   
}

void Logger::InitLogger(const std::string &logsDir)
{
    _consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    _consoleSink->set_level(spdlog::level::debug);
    _consoleSink->set_pattern(MAIN_LOGGER_PATTERN);

    std::shared_ptr<spdlog::logger> logger;

    if (!logsDir.empty())
    {
        _fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logsDir + "/logs/logs.log", true);
        _fileSink->set_level(spdlog::level::debug);
        _fileSink->set_pattern(MAIN_LOGGER_PATTERN);

        logger = std::make_shared<spdlog::logger>("defaultLogger", spdlog::sinks_init_list{_consoleSink, _fileSink});
    }
    else
    {
        logger = std::make_shared<spdlog::logger>("defaultLogger", spdlog::sinks_init_list{_consoleSink});
    }

    logger->set_level(spdlog::level::trace);
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
}


std::shared_ptr<spdlog::logger> Logger::GetClassLogger(const std::string& name)
{
    try
    {
        auto logger = spdlog::get(name);
        if (logger == nullptr)
        {
            auto new_logger = std::make_shared<spdlog::logger>(
                name,
                _fileSink ? spdlog::sinks_init_list{_consoleSink, _fileSink} 
                          : spdlog::sinks_init_list{_consoleSink}
            );

            new_logger->set_level(spdlog::level::trace);
            spdlog::register_logger(new_logger);

            return new_logger;
        }
        else
        {
            return logger;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return spdlog::default_logger();
    }
}

Logger::~Logger()
{
    spdlog::shutdown();
}
