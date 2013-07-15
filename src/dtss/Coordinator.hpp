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

#include <common/Coordinator.hpp>

#include <cassert>
#include <iostream>

namespace paradevs { namespace dtss {

template < class Time >
class Parameters
{
public:
    Parameters(typename Time::type time_step) : _time_step(time_step)
    { }

    typename Time::type _time_step;
};

template < class Time, class Policy, class GraphManager >
class Coordinator : public common::Coordinator < Time >
{
public:
    typedef Parameters < Time > parameters_type;

    Coordinator(const std::string& name,
                const Parameters < Time >& parameters) :
        common::Coordinator < Time >(name), _graph_manager(this),
        _time_step(parameters._time_step)
    { }

    virtual ~Coordinator()
    { }

    typename Time::type start(typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::I_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        assert(_graph_manager.children().size() > 0);

        for (auto & child : _graph_manager.children()) {
            child->start(Coordinator < Time, Policy, GraphManager >::_tn);
        }
        Coordinator < Time, Policy, GraphManager >::_tl = t;
        Coordinator < Time, Policy, GraphManager >::_tn = t;

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::I_MESSAGE)
            << ": AFTER => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        return Coordinator < Time, Policy, GraphManager >::_tn;
    }

    typename Time::type dispatch_events(common::Bag < Time > bag,
                                        typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::Y_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn
            << " ; bag = " << bag.to_string();
        common::Trace < Time >::trace().flush();

        _graph_manager.dispatch_events(bag, t);

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::Y_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        return Coordinator < Time, Policy, GraphManager >::_tn;
    }

    void observation(std::ostream& file) const
    {
        for (auto & child : _graph_manager.children()) {
            child->observation(file);
        }
    }

    void output(typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::OUTPUT)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        if (t == Coordinator < Time, Policy, GraphManager >::_tn) {
            for (auto & model : _graph_manager.children()) {
                model->output(t);
            }
        }

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::OUTPUT)
            << ": AFTER => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

    }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time >& event)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::POST_EVENT)
            << ": BEFORE => " << event.to_string();
        common::Trace < Time >::trace().flush();

        if (t == Coordinator < Time, Policy, GraphManager >::_tn) {
            _graph_manager.post_event(t, event);
        } else {
            _policy(t, event, Coordinator < Time, Policy, GraphManager >::_tl,
                    Coordinator < Time, Policy, GraphManager >::_tn);
        }

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::POST_EVENT)
            << ": AFTER => " << event.to_string();
        common::Trace < Time >::trace().flush();

    }

    typename Time::type transition(typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::S_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        if (t == Coordinator < Time, Policy, GraphManager >::_tn) {
            for (auto & event : _policy.bag()) {
                post_event(t, event);
            }
            for (auto & model : _graph_manager.children()) {
                model->transition(t);
            }
            Coordinator < Time, Policy, GraphManager >::_tl = t;
            Coordinator < Time, Policy, GraphManager >::_tn = t + _time_step;
        }
        Coordinator < Time, Policy, GraphManager >::clear_bag();

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, Policy, GraphManager >::get_name(), t,
                common::S_MESSAGE)
            << ": AFTER => "
            << "tl = " << Coordinator < Time, Policy, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, Policy, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        return Coordinator < Time, Policy, GraphManager >::_tn;
    }

private:
    GraphManager        _graph_manager;
    typename Time::type _time_step;
    Policy              _policy;
};

} } // namespace paradevs dtss

#endif
