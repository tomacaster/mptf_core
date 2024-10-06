#pragma once

#include <string_view>

#include <spdlog/logger.h>

#include "IFileSystem.h"
#include "FileSystemCommon.h"

#include "Logger.h"
#include "Memory/DataObject.h"

namespace Memory::Storage
{
    /// @brief Helper class based on std::filesystem
    class FileSystemCommon : public IFileSystem
    {
        public:
            FileSystemCommon();
            ~FileSystemCommon();

            std::shared_ptr<DataObject> Open(std::string_view path) override;
            bool Write(std::string_view filePath, const std::shared_ptr<DataObject>& dataObject) override;

        private:
            std::shared_ptr<spdlog::logger> logger_;
    };
}
