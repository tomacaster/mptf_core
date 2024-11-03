#include "Storage/FileCommon.h"

#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

namespace Memory::Storage
{
    struct FilesystemImpl
    {
        fs::path filePath;
    } FilesystemImpl;
    
    FileCommon::FileCommon(std::string_view path) : filePath_(path)
    {
        object_ = fileSystem_.Open(path, true);
        if ( object_.Size() == 0)
        {
            throw std::runtime_error("File does not exists.");
        }
    }

    FileCommon::~FileCommon()
    {
    }

    std::string_view FileCommon::GetPath() const
    {
        return filePath_;
    }

    std::shared_ptr<DataObject> FileCommon::Open()
    {
        return std::make_shared<DataObject>(object_);
    }

    bool Memory::Storage::FileCommon::Write(const std::shared_ptr<DataObject> &data)
    {
        return false;
    }
}