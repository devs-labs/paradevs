/**
 * @file GraphManager.hpp
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

#ifndef DTSS_GRAPH_MANANGER
#define DTSS_GRAPH_MANANGER 1

#include <common/Coordinator.hpp>
#include <common/Links.hpp>
#include <common/Model.hpp>

namespace paradevs { namespace dtss {

class GraphManager
{
public:
    GraphManager(common::Coordinator* coordinator);
    virtual ~GraphManager();

    virtual void add_child(common::Model* child);
    virtual void add_link(common::Model* out_model, const std::string& out_port_name,
                          common::Model* in_model, const std::string& in_port_name);
    const common::Models& children() const
    { return _child_list; }
    const common::Links& links() const
    { return _link_list; }

private:
    common::Links        _link_list;
    common::Models       _child_list;
    common::Coordinator* _coordinator;
};

} } // namespace paradevs dtss

#endif
