/**
 * @file Value.hpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013-2015 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_VALUE
#define COMMON_VALUE 1

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/array.hpp>

#include <cstring>
#include <typeinfo>

namespace paradevs { namespace common {

class Value
{
public:
    Value() : _content(nullptr), _size(0)
    { }

    template < typename T >
    Value(T value)
    { assign(&value, sizeof(T), typeid(T).hash_code()); }

    Value(void* content, size_t size)
    { assign(content, size, typeid(void*).hash_code()); }

    Value(const char* value, unsigned int size)
    { assign(value, size * sizeof(char), typeid(char*).hash_code()); }

    virtual ~Value()
    { /* if (_content) delete[] _content; */ }

    bool empty() const
    { return _content == nullptr; }

    template < typename T >
    T get_content() const
    {
        assert(_type_id == typeid(T).hash_code());

        return *(T*)(_content);
    }

    std::string to_string() const
    {
        return std::string();
    }

private:
    void assign(const void* content, size_t size, size_t type_id)
    {
        _content = new char[size];
        std::memcpy(_content, content, size);
        _size = size;
        _type_id = type_id;
    }

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        (void) version;

        ar & _size;
        if (Archive::is_loading::value) {
            assert(_content == nullptr);
            _content = new char[_size];
        }
        ar & boost::serialization::make_array < char >(_content, _size);
        ar & _type_id;
    }

    char*  _content;
    size_t _size;
    size_t _type_id;
};

} } // namespace paradevs common

#endif
