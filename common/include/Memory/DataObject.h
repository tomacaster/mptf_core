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
        DataObject() = default;
        explicit DataObject(const std::vector<char>& dataPtr);
        explicit DataObject(std::vector<char>&& dataPtr);
        ~DataObject() = default;

        size_t SetData(const std::vector<char>& data);
        std::shared_ptr<std::vector<char>> GetData() const;
        /// @brief Preallocate space for data only if data is empty
        /// @param size 
        /// @return true on succes; otherwise false
        bool Allocate(size_t size);
        bool Resize(size_t size, bool force = false);
        size_t Size() const;
        bool LoadFromStream(std::istream& is);
        bool SaveToStream(std::ostream& os) const;

    private:
        std::vector<char> data_;
    };
}
