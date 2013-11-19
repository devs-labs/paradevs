/**
 * @file kernel/pdevs/Simulator.hpp
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

#ifndef PDEVS_SIMULATOR
#define PDEVS_SIMULATOR 1

#include <paradevs/common/Coordinator.hpp>
#include <paradevs/common/Parameters.hpp>
#include <paradevs/common/Simulator.hpp>
#include <paradevs/common/utils/String.hpp>
#include <paradevs/common/utils/Trace.hpp>

#include <cassert>

namespace paradevs { namespace pdevs {

template < class Time, class Dynamics, class SchedulerHandle,
           class Parameters = common::NoParameters >
class Simulator : public common::Simulator < Time, SchedulerHandle >
{
    typedef Simulator < Time, Dynamics, SchedulerHandle, Parameters > type;

public :
    Simulator(const std::string& name, const Parameters& parameters) :
        common::Simulator < Time, SchedulerHandle >(name),
        _dynamics(name, parameters)
    { }

    ~Simulator()
    { }

    virtual std::string to_string(int level) const
    {
        std::ostringstream ss;

        ss << common::spaces(level * 2) << "p-devs simulator \""
           << type::get_name() << "\""<< std::endl;
        return ss.str();
    }

/*************************************************
 * when i-message(t)
 *   tl = t - e
 *   tn = tl + ta(s)
 *************************************************/
    typename Time::type start(typename Time::type t)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::I_MESSAGE)
            << ": BEFORE => " << "tl = " << type::_tl << " ; tn = "
            << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

        type::_tl = t;
        type::_tn =
            type::_tl + _dynamics.start(t);

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::I_MESSAGE)
            << ": AFTER => " << "tl = " << type::_tl << " ; tn = "
            << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

        return type::_tn;
    }

    void observation(std::ostream &file) const
    {
        _dynamics.observation(file);
    }

/*************************************************
 * when *-message(t)
 *   if (t = tn) then
 *     y = lambda(s)
 *     send y-message(y,t) to parent
 *************************************************/
    void output(typename Time::type t)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::OUTPUT) << ": BEFORE";
        common::Trace < Time >::trace().flush();
#endif

        if(t == type::_tn) {
            common::Bag < Time, SchedulerHandle > bag = _dynamics.lambda(t);

            if (not bag.empty()) {
                for (auto & event : bag) {
                    event.set_model(this);
                }
                dynamic_cast < common::Coordinator < Time, SchedulerHandle >* >(
                    type::get_parent())->dispatch_events(bag, t);
            }
        }

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::OUTPUT) << ": AFTER";
        common::Trace < Time >::trace().flush();
#endif

    }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time,
                                                  SchedulerHandle >& event)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::POST_EVENT)
            << ": BEFORE => " << event.to_string();
        common::Trace < Time >::trace().flush();
#endif

        type::add_event(event);

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::POST_EVENT)
            << ": AFTER => " << event.to_string();
        common::Trace < Time >::trace().flush();
#endif

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
    typename Time::type transition(typename Time::type t)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::S_MESSAGE)
            << ": BEFORE => " << "tl = " << type::_tl << " ; tn = "
            << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

        assert(type::_tl <= t and t <= type::_tn);

        if(t == type::_tn) {
            if (type::event_number() == 0) {
                _dynamics.dint(t);
            } else {
                _dynamics.dconf(t, t - type::_tl, type::get_bag());
            }
        } else {
            _dynamics.dext(t, t - type::_tl, type::get_bag());
        }
        type::_tn = t + _dynamics.ta(t);
        type::_tl = t;
        type::clear_bag();

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::S_MESSAGE)
            << ": AFTER => " << "tl = " << type::_tl << " ; tn = " << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

        return type::_tn;
    }

private :
    Dynamics _dynamics;
};

} } // namespace paradevs pdevs

#endif
