/**
 * @file Coordinator.hpp
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

#ifndef DEVS_COORDINATOR
#define DEVS_COORDINATOR 1

#include <devs/Model.hpp>
#include <devs/EventTable.hpp>
#include <devs/Links.hpp>
#include <devs/Message.hpp>
#include <devs/Node.hpp>

#include <iostream>
#include <vector>
#include <map>

namespace paradevs {

class Coordinator : public Model
{
public :
    Coordinator(const std::string& name);
    virtual ~Coordinator();

// DEVS methods
    virtual Time i_message(Time /* t */);
    virtual Time s_message(Time /* t */);
    virtual Time x_message(const Message& /* message */, Time /* t */);
    virtual Time y_message(Messages /* messages */, Time /* t */);
    virtual void observation(std::ostream& file) const;

// graph methods
    virtual void add_child(Model* child);
    virtual void add_link(const Node& source, const Node& destination);

private :
    Links      _link_list;
    Models     _child_list;
    EventTable _event_table;
};

} // namespace paradevs

#endif
