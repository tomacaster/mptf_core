#pragma once

#include <string_view>

#include <spdlog/logger.h>

#include "IFileSystem.h"

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

            DataObject Open(std::string_view path, bool createIf = false) override;
            bool Write(std::string_view filePath, const std::shared_ptr<DataObject>& dataObject) override;
            bool WriteText(std::string_view filePath, const std::string_view content) override;
            bool Exists(std::string_view path) const override;
            bool Remove(std::string_view path) override;
            bool CreateDirectory(std::string_view path) override;
            bool RemoveDirectory(std::string_view path) override;
            std::string_view GetHomeDir() const override;
        private:
            std::shared_ptr<spdlog::logger> logger_;
    };
}
