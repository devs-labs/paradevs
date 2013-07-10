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

#include <pdevs/Coordinator.hpp>
#include <pdevs/Simulator.hpp>

#include <cassert>
#include <stdexcept>

namespace paradevs { namespace pdevs {

Simulator::Simulator(Dynamics* dynamics) :
    common::Simulator(dynamics->get_name()), _dynamics(dynamics)
{ }

Simulator::~Simulator()
{ delete _dynamics; }

/*************************************************
 * when i-message(t)
 *   tl = t - e
 *   tn = tl + ta(s)
 *************************************************/
common::Time Simulator::start(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    _tl = t;
    _tn = _tl + _dynamics->start(t);

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    return _tn;
}

void Simulator::observation(std::ostream &file) const
{
    _dynamics->observation(file);
}

/*************************************************
 * when *-message(t)
 *   if (t = tn) then
 *     y = lambda(s)
 *     send y-message(y,t) to parent
 *************************************************/
void Simulator::output(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::OUTPUT)
                           << ": BEFORE";
    common::Trace::trace().flush();

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

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::OUTPUT)
                           << ": AFTER";
    common::Trace::trace().flush();

}

void Simulator::post_message(common::Time t,
                             const common::ExternalEvent& message)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": BEFORE => " << message.to_string();
    common::Trace::trace().flush();

    add_event(message);

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": AFTER => " << message.to_string();
    common::Trace::trace().flush();

}

/*************************************************
 * when x-message(t)
 *   if (x is empty and t = tn) then
 *       s = delta_int(s)
 *  else if (x isn't empty and t = tn)
 *       s = delta_conf(s,x)
 *  else if (x isn't empty and t < tn)
 *    e = t - tl
 *    s = delta_ext(s,e,x)
 *  tn = t + ta(s)
 *  tl = t
 *************************************************/
common::Time Simulator::transition(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    assert(_tl <= t and t <= _tn);

    if(t == _tn) {
        if (event_number() == 0) {
            _dynamics->dint(t);
        } else {
            _dynamics->dconf(t, t - _tl, get_bag());
        }
    } else {
        _dynamics->dext(t, t - _tl, get_bag());
    }
    _tn = t + _dynamics->ta(t);
    _tl = t;
    clear_bag();

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    return _tn;
}

} } // namespace paradevs pdevs
