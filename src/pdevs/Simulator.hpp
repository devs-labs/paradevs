/**
 * @file Simulator.hpp
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

#include <common/Coordinator.hpp>
#include <common/Simulator.hpp>
#include <common/Trace.hpp>

#include <cassert>

namespace paradevs { namespace pdevs {

template < class Time, class Dynamics >
class Simulator : public common::Simulator < Time >
{
public :
    Simulator(const std::string& name) :
        common::Simulator < Time >(name), _dynamics(name)
    { }

    ~Simulator()
    { }

/*************************************************
 * when i-message(t)
 *   tl = t - e
 *   tn = tl + ta(s)
 *************************************************/
    typename Time::type start(typename Time::type t)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::I_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Simulator < Time, Dynamics >::_tl
            << " ; tn = " << Simulator < Time, Dynamics >::_tn;
        common::Trace < Time >::trace().flush();
#endif

        Simulator < Time, Dynamics >::_tl = t;
        Simulator < Time, Dynamics >::_tn =
            Simulator < Time, Dynamics >::_tl + _dynamics.start(t);

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::I_MESSAGE)
            << ": AFTER => "
            << "tl = " << Simulator < Time, Dynamics >::_tl
            << " ; tn = " << Simulator < Time, Dynamics >::_tn;
        common::Trace < Time >::trace().flush();
#endif

        return Simulator < Time, Dynamics >::_tn;
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
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::OUTPUT)
            << ": BEFORE";
        common::Trace < Time >::trace().flush();
#endif

        if(t == Simulator < Time, Dynamics >::_tn) {
            common::Bag < Time > bag = _dynamics.lambda(t);

            if (not bag.empty()) {
                for (auto & event : bag) {
                    event.set_model(this);
                }
                dynamic_cast < common::Coordinator < Time >* >(
                    Simulator < Time, Dynamics >::get_parent())
                    ->dispatch_events(bag, t);
            }
        }

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::OUTPUT)
            << ": AFTER";
        common::Trace < Time >::trace().flush();
#endif

    }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time >& event)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::POST_EVENT)
            << ": BEFORE => " << event.to_string();
        common::Trace < Time >::trace().flush();
#endif

        Simulator < Time, Dynamics >::add_event(event);

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
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
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::S_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Simulator < Time, Dynamics >::_tl
            << " ; tn = " << Simulator < Time, Dynamics >::_tn;
        common::Trace < Time >::trace().flush();
#endif

        // assert(Simulator < Time, Dynamics >::_tl <= t and t <= Simulator < Time, Dynamics >::_tn);

        if(t == Simulator < Time, Dynamics >::_tn) {
            if (Simulator < Time, Dynamics >::event_number() == 0) {
                _dynamics.dint(t);
            } else {
                _dynamics.dconf(t, t - Simulator < Time, Dynamics >::_tl,
                                Simulator < Time, Dynamics >::get_bag());
            }
        } else {
            _dynamics.dext(t, t - Simulator < Time, Dynamics >::_tl,
                           Simulator < Time, Dynamics >::get_bag());
        }
        Simulator < Time, Dynamics >::_tn = t + _dynamics.ta(t);
        Simulator < Time, Dynamics >::_tl = t;
        Simulator < Time, Dynamics >::clear_bag();

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Simulator < Time, Dynamics >::get_name(), t,
                common::S_MESSAGE)
            << ": AFTER => "
            << "tl = " << Simulator < Time, Dynamics >::_tl
            << " ; tn = " << Simulator < Time, Dynamics >::_tn;
        common::Trace < Time >::trace().flush();
#endif

        return Simulator < Time, Dynamics >::_tn;
    }

private :
    Dynamics _dynamics;
};

} } // namespace paradevs pdevs

#endif
