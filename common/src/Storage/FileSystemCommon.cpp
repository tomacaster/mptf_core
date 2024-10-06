#include "Storage/FileSystemCommon.h"


namespace fs = std::filesystem;

namespace Memory::Storage
{
    FileSystemCommon::FileSystemCommon() 
    {
        logger_ = Logger::GetClassLogger("FileManager");
    }

    FileSystemCommon::~FileSystemCommon()
    {
    }

    std::shared_ptr<DataObject> FileSystemCommon::Open(std::string_view path)
    {
        DataObject data;

        return std::make_shared<DataObject>(data);
    }

    bool FileSystemCommon::Write(std::string_view filePath, const std::shared_ptr<DataObject> &file)
    {
        return false;
    }
}
