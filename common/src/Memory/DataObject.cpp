// Memory/DataObject.cpp
#include "Memory/DataObject.h"

namespace Memory
{
    DataObject::DataObject() : _data(std::make_shared<std::vector<char>>()) {}

    DataObject::DataObject(std::shared_ptr<std::vector<char>> dataPtr)
        : _data(std::move(dataPtr)) { }

    size_t DataObject::SetData(std::shared_ptr<std::vector<char>> data)
    {
        _data = std::move(data);
        return _data ? _data->size() : 0;
    }

    std::shared_ptr<std::vector<char>> DataObject::GetData() const
    {
        return _data;
    }

    void DataObject::Allocate(size_t size)
    {
        _data = std::make_shared<std::vector<char>>(size);
    }

    bool DataObject::Resize(size_t size, bool force)
    {
        if (!_data)
        {
            _data = std::make_shared<std::vector<char>>();
        }

        if(size <= _data->size() && !force)
        {
            return false;
        }
        else
        {
            _data->resize(size);
            return true;
        }
    }

    size_t DataObject::Size()
    {   
        return _data ? _data->size() : 0;
    }
}
