#pragma once

#include <memory>
#include <string_view>

#include "Memory/DataObject.h"

namespace Memory::Storage
{
    class IFileSystem
    {
    public:
        virtual ~IFileSystem() = default;

        virtual DataObject Open(std::string_view path, bool createIf = false) = 0;
        virtual bool Write(std::string_view filePath, const std::shared_ptr<DataObject>& dataObject) = 0;
        virtual bool WriteText(std::string_view filePath, const std::string_view content) = 0;
        virtual bool Exists(std::string_view path) const = 0;
        virtual bool Remove(std::string_view path) = 0;
        virtual bool CreateDirectory(std::string_view path) = 0;
        virtual bool RemoveDirectory(std::string_view path) = 0;
        virtual std::string_view GetHomeDir() const = 0;
    };
}