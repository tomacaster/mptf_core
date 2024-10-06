#pragma once

#include <memory>
#include <string_view>

namespace Memory::Storage
{
    class DataObject;

    class IFileSystem
    {
    public:
        virtual ~IFileSystem() = default;

        virtual std::shared_ptr<DataObject> Open(std::string_view path) = 0;
        virtual bool Write(std::string_view filePath, const std::shared_ptr<DataObject>& dataObject) = 0;
    };
}