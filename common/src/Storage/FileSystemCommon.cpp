#include "Storage/FileSystemCommon.h"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace Memory::Storage
{
    fs::path path_;

    FileSystemCommon::FileSystemCommon()
    {
        logger_ = Logger::GetClassLogger("FileManager");
    }

    FileSystemCommon::~FileSystemCommon()
    {
    }

DataObject FileSystemCommon::Open(std::string_view path, bool createIf)
{
    path_ = path;

    if (fs::exists(path_))
    {
        std::ifstream stream(path_, std::ios::binary | std::ios::ate);
        if (stream.is_open())
        {
            std::streamsize size = stream.tellg(); // Pobieramy rozmiar pliku
            stream.seekg(0, std::ios::beg); // Przemieszczamy wskaźnik na początek pliku

            if (size <= 0)
            {
                logger_->error("File size is zero or negative.");
                throw std::runtime_error("Invalid file size.");
            }

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
    throw std::runtime_error("File does not exist.");
}

    bool FileSystemCommon::Write(std::string_view filePath, const std::shared_ptr<DataObject> &file)
    {
        return false;
    }
}
