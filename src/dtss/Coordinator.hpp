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

#ifndef DTSS_COORDINATOR
#define DTSS_COORDINATOR 1

#include <common/Bag.hpp>
#include <common/Coordinator.hpp>
#include <common/EventTable.hpp>
#include <common/Links.hpp>
#include <common/ExternalEvent.hpp>
#include <common/Node.hpp>

#include <iostream>

namespace paradevs { namespace dtss {

class Coordinator : public common::Coordinator
{
public:
    Coordinator(const std::string& name, common::Time time_step);
    virtual ~Coordinator();

// DEVS methods
    virtual void output(common::Time /* t */);
    virtual void post_message(common::Time /* t */,
                              const common::ExternalEvent& /* message */);
    virtual common::Time dispatch_events(common::Bag /* bag */,
                                         common::Time /* t */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Time transition(common::Time /* t */);
    virtual void observation(std::ostream& file) const;

// graph methods
    virtual void add_child(Model* child);
    virtual void add_link(const common::Node& source,
                          const common::Node& destination);

private:
    common::Links  _link_list;
    common::Models _child_list;
    common::Time   _time_step;
};

} } // namespace paradevs dtss

#endif
