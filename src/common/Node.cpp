/**
 * @file Node.cpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013 ULCO http://www.univ-litoral.fr
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

#include <common/Node.hpp>

namespace paradevs { namespace common {

Node::Node(const std::string& port_name, Model* model)
    : _port_name(port_name), _model(model)
{ }

Node::Node(const Node& other)
    : _port_name(other._port_name), _model(other._model)
{ }

Node::~Node()
{ }

bool Node::operator<(const Node& o) const
{
    if (o._model == _model) {
        return o._port_name < _port_name;
    } else {
        return o._model < _model;
    }
}

bool Node::operator==(const Node& o) const
{
    return (o._port_name == _port_name and o._model == _model);
}

const std::string& Node::get_port_name() const
{ return _port_name; }

Model* Node::get_model() const
{ return _model; }

} } // namespace paradevs common
