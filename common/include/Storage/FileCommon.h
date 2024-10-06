#pragma once

#include <string_view>

#include <spdlog/logger.h>

#include "FileSystemCommon.h"
#include "Logger.h"
#include "DataObject.h"

namespace Memory::Storage
{

    /// @brief Helper that you can use as file object. It's inherrites FileSystemCommon
    class FileCommon : private FileSystemCommon
    {
        public:
            FileCommon(std::string_view path);
            ~FileCommon();

            std::shared_ptr<DataObject> Open();
            bool Write(const std::shared_ptr<DataObject>& data);
        private:
            std::shared_ptr<spdlog::logger> logger_;
    }
}