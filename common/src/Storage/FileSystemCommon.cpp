#include "Storage/FileSystemCommon.h"

#include <fstream>
#include <iostream>
#include <filesystem>

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

    DataObject FileSystemCommon::Open(std::string_view path, bool createIf)
    {
        if (fs::exists(path))
        {
            std::ifstream stream(path.data(), std::ios::binary | std::ios::ate);
            if (stream.is_open())
            {
                std::streamsize size = stream.tellg(); // Get the size of the file

                if (size <= 0)
                {
                    logger_->error("File size is zero or negative.");
                    throw std::runtime_error("Invalid file size.");
                }

                stream.seekg(0, std::ios::beg); // Rewind to the beginning of the file

                std::vector<char> buffer(static_cast<size_t>(size));
                if (stream.read(buffer.data(), size))
                {
                    logger_->debug("Read {}kb", size);
                    return DataObject(buffer); // RVO, Move Semantics
                }
                else
                {
                    logger_->error("Error during reading file");
                    throw std::runtime_error("Error during reading file");
                }
            }
            else
            {
                logger_->error("Cannot open file.");
                throw std::runtime_error("Cannot open file.");
            }
        } 
        else if (createIf) {
            DataObject data;
            if (data.LoadFromStream((std::ifstream(fs::path(path))))) {
                return data;
            }
        } 

        throw std::runtime_error("Unknown errror");
    }

    bool FileSystemCommon::Write(std::string_view filePath, const std::shared_ptr<DataObject> &file)
    {
        if (Exists(filePath))
        {
           auto file = Open(filePath, false); 

           file.GetData();
        }
        return false;
    }

    bool Memory::Storage::FileSystemCommon::WriteText(std::string_view filePath, const std::string_view content)
    {
        return false;
    }

    bool Memory::Storage::FileSystemCommon::Exists(std::string_view path) const
    {
        fs::path::
        return false;
    }

    bool Memory::Storage::FileSystemCommon::Remove(std::string_view path)
    {
        return false;
    }

    bool Memory::Storage::FileSystemCommon::CreateDirectory(std::string_view path)
    {
        return false;
    }

    bool Memory::Storage::FileSystemCommon::RemoveDirectory(std::string_view path)
    {
        return false;
    }

    std::string_view Memory::Storage::FileSystemCommon::GetHomeDir() const
    {
        return std::string_view();
    }

}

