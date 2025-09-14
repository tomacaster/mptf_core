#pragma once

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger
{
    public:
        static void InitLogger(const std::string &logsDir = std::string());
        static const std::string DEFAULT_LOGGER_PATTERN;
        static std::shared_ptr<spdlog::logger> GetClassLogger(const std::string& name);        
        Logger();
        ~Logger();
    private:
        
        static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _consoleSink;
        static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> _fileSink;
};
