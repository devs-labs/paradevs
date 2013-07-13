/**
 * @file GraphManager.cpp
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

#include <dtss/GraphManager.hpp>

namespace paradevs { namespace dtss {

GraphManager::GraphManager(common::Coordinator* coordinator) :
    _coordinator(coordinator)
{ }

GraphManager::~GraphManager()
{
    for (auto & child : _child_list) {
        delete child;
    }
}

void GraphManager::add_child(common::Model* child)
{
    _child_list.push_back(child);
    child->set_parent(_coordinator);
}

void GraphManager::add_link(common::Model* out_model, const std::string& out_port_name,
                            common::Model* in_model, const std::string& in_port_name)
{
    _link_list.add(out_model, out_port_name, in_model, in_port_name);
}

} } // namespace paradevs dtss
