#include "FileSystemCommon.h"

namespace fs = std::filesystem;

namespace Memory::Storage
{
    FileSystemCommon::FileSystemCommon() :
    path_()
    {
        logger_ = Logger::GetClassLogger("FileManager");
    }

    Memory::Storage::FileSystemCommon::FileSystemCommon(std::string_view path)
    {
        logger_ = Logger::GetClassLogger("FileManager");
        path_ = path;
    }

    FileSystemCommon::~FileSystemCommon()
    {
    }

    std::shared_ptr<DataObject> FileSystemCommon::Open()
    {
        return std::shared_ptr<DataObject>();
    }

    std::shared_ptr<DataObject> FileSystemCommon::Open(std::string_view path)
    {
        DataObject data;

        return std::make_shared<DataObject>(data);
    }

    bool FileSystemCommon::Write(const std::shared_ptr<DataObject> &data)
    {
        return false;
    }

    bool FileSystemCommon::Write(std::string_view filePath, const std::shared_ptr<DataObject> &file)
    {
        return false;
    }
}
