/**
 * @file Simulator.cpp
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

#include <common/Trace.hpp>

#include <dtss/Coordinator.hpp>
#include <dtss/Simulator.hpp>

#include <cassert>
#include <stdexcept>

namespace paradevs { namespace dtss {

Simulator::Simulator(Dynamics* dynamics, common::Time time_step) :
    common::Simulator(dynamics->get_name()), _dynamics(dynamics),
    _time_step(time_step)
{ }

Simulator::~Simulator()
{ delete _dynamics; }

common::Time Simulator::start(common::Time t)
{
    _dynamics->start(t);
    _tn = t;
    return _tn;
}

void Simulator::observation(std::ostream &file) const
{ _dynamics->observation(file); }

void Simulator::output(common::Time t)
{
    if(t == _tn) {
        common::Bag bag = _dynamics->lambda(t);

        if (not bag.empty()) {
            for (common::Bag::iterator it = bag.begin(); it != bag.end();
                 ++it) {
                it->set_model(this);
            }
            dynamic_cast < Coordinator* >(get_parent())->dispatch_events(bag,
                                                                         t);
        }
    }
}

void Simulator::post_message(common::Time /* t */,
                             const common::ExternalEvent& event)
{ add_event(event); }

common::Time Simulator::transition(common::Time t)
{
    assert(t == _tn);

    _dynamics->transition(get_bag(), t);
    _tn = t + _time_step;
    clear_bag();
    return _tn;
}

} } // namespace paradevs dtss
