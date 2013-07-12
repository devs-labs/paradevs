/**
 * @file Links.cpp
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

#include <common/Links.hpp>

#include <sstream>

namespace paradevs { namespace common {

void Links::add(Model* out_model, const std::string& out_port_name,
                Model* in_model, const std::string& in_port_name)
{
    insert(std::pair < Node, Node >(Node(out_model, out_port_name),
                                    Node(in_model, in_port_name)));
}

Links::Result Links::find(Model* out_model, const std::string& out_port_name)
{
    return equal_range(common::Node(out_model, out_port_name));
}

std::string Links::to_string() const
{
    std::stringstream ss;

    ss << "Graph = { ";
    for (const_iterator it = begin(); it != end(); ++it) {
        ss << "(" << it->first.get_model()->get_name() << ":"
           << it->first.get_port_name()
           << " -> "
           << it->second.get_model()->get_name() << ":"
           << it->second.get_port_name()
           << ") ";
    }
    ss << "}";
    return ss.str();
}

} } // namespace paradevs common
