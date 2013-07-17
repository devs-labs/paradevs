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

#ifndef DTSS_SIMULATOR
#define DTSS_SIMULATOR 1

#include <common/Coordinator.hpp>
#include <common/Simulator.hpp>
#include <common/Trace.hpp>

#include <cassert>

namespace paradevs { namespace dtss {

template < class Time, class Dynamics >
class Simulator : public common::Simulator < Time >
{
public:
    Simulator(const std::string& name, typename Time::type time_step) :
        common::Simulator < Time >(name), _dynamics(name),
        _time_step(time_step)
    { }

    ~Simulator()
    {  }

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

        _dynamics.start(t);
        Simulator < Time, Dynamics >::_tl = t;
        Simulator < Time, Dynamics >::_tn = t;

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

        if (t == Simulator < Time, Dynamics >::_tn) {
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

        // assert(t == Simulator < Time, Dynamics >::_tn);

        _dynamics.transition(Simulator < Time, Dynamics >::get_bag(), t);
        Simulator < Time, Dynamics >::_tl = t;
        Simulator < Time, Dynamics >::_tn = t + _time_step;
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
    Dynamics            _dynamics;
    typename Time::type _time_step;
};

} } // namespace paradevs dtss

#endif
