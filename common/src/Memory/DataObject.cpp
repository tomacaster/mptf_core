// Memory/DataObject.cpp
#include "Memory/DataObject.h"

namespace Memory
{
    DataObject::DataObject(const std::vector<char> &dataPtr) : data_(dataPtr)
    {
    }

    DataObject::DataObject(std::vector<char> &&dataPtr) : data_(std::move(dataPtr))
    {
    }

    size_t DataObject::SetData(const std::vector<char>& data)
    {
        data_ = std::move(data);
        return data_.size();
    }

    std::shared_ptr<std::vector<char>> DataObject::GetData() const
    {
        return std::make_shared<std::vector<char>>(data_);
    }

    bool DataObject::Allocate(size_t size) 
    {
        if (data_.empty()) 
        {
            try 
            {
                data_.reserve(size);

                return true;
            } catch (const std::bad_alloc&) 
            {
                return false;
            }
        }
        return false;
    }

    bool DataObject::Resize(size_t size, bool force)
    {
        if (force || data_.size() != size) 
        {
            try 
            {
                data_.resize(size);
                
                return true;
            } catch (const std::bad_alloc&) 
            {
                return false;
            }
        }
        return true;
    }

    size_t DataObject::Size() const
    {   
        return data_.size();
    }
}
