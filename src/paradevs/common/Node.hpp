/**
 * @file Node.hpp
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

#ifndef COMMON_NODE
#define COMMON_NODE 1

#include <paradevs/common/Model.hpp>

#include <string>

namespace paradevs { namespace common {

template < class Time >
class Model;

template < class Time >
class Node
{
public :
    Node(Model < Time >* model, const std::string& port_name)
        : _model(model), _port_name(port_name)
    { }

    Node(const Node < Time >& other)
    : _model(other._model), _port_name(other._port_name)
    { }

    virtual ~Node()
    { }

    bool operator<(const Node < Time >& o) const
    {
        if (o._model == _model) {
            return o._port_name < _port_name;
        } else {
            return o._model < _model;
        }
    }

    bool operator==(const Node < Time >& o) const
    {
        return (o._port_name == _port_name and o._model == _model);
    }

    const std::string& get_port_name() const
    { return _port_name; }

    Model < Time >* get_model() const
    { return _model; }

private :
    Model < Time >* _model;
    std::string     _port_name;
};

} } // namespace paradevs common

#endif
