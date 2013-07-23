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

#ifndef COMMON_COORDINATOR
#define COMMON_COORDINATOR 1

#include <common/Bag.hpp>
#include <common/ExternalEvent.hpp>
#include <common/Links.hpp>
#include <common/Model.hpp>
#include <common/Node.hpp>

#include <iostream>

namespace paradevs { namespace common {

template < class Time, class SchedulerHandle >
class Model;

template < class Time, class SchedulerHandle >
class Coordinator : public Model < Time, SchedulerHandle >
{
public :
    Coordinator(const std::string& name) : Model < Time, SchedulerHandle >(name)
    { }

    virtual ~Coordinator()
    { }

// DEVS methods
    virtual void observation(std::ostream& file) const =0;
    virtual void output(typename Time::type t) =0;
    virtual void post_event(typename Time::type t,
                            const common::ExternalEvent < Time,
                                                          SchedulerHandle >&
                            event) =0;
    virtual typename Time::type dispatch_events(common::Bag < Time,
                                                              SchedulerHandle >
                                                bag,
                                                typename Time::type t) =0;
    virtual typename Time::type start(typename Time::type t) =0;
    virtual typename Time::type transition(typename Time::type t) =0;
};

} } // namespace paradevs common

#endif
