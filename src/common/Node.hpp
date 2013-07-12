/**
 * @file Node.hpp
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

#ifndef COMMON_NODE
#define COMMON_NODE 1

#include <common/Model.hpp>

#include <string>

namespace paradevs { namespace common {

class Model;

class Node
{
public :
    Node(Model* model, const std::string& port_name);
    Node(const Node& other);
    virtual ~Node();

    Model* get_model() const;
    const std::string& get_port_name() const;

    virtual bool operator<(const Node& e) const;
    virtual bool operator==(const Node& other) const;

private :
    Model*      _model;
    std::string _port_name;
};

} } // namespace paradevs common

#endif
