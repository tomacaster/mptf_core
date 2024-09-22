// Memory/DataObject.h
#pragma once

#include <memory>
#include <cstddef>
#include <vector>

namespace Memory
{
    /// @brief Basic data object for streams, etc.
    /// Based on vector<char>
    class DataObject
    {
    public:
        DataObject();
        DataObject(std::shared_ptr<std::vector<char>> dataPtr);
        ~DataObject() = default;

        size_t SetData(std::shared_ptr<std::vector<char>> data);
        std::shared_ptr<std::vector<char>> GetData() const;
        void Allocate(size_t size);
        bool Resize(size_t size, bool force = false);
        size_t Size();

    private:
        std::shared_ptr<std::vector<char>> _data;
    };
}
