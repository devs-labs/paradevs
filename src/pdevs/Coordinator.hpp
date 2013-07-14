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

#ifndef PDEVS_COORDINATOR
#define PDEVS_COORDINATOR 1

#include <common/Coordinator.hpp>
#include <common/EventTable.hpp>
#include <common/Trace.hpp>

#include <cassert>
#include <iostream>

namespace paradevs { namespace pdevs {

class Parameters
{
public:
    Parameters()
    { }
};

template < class Time, class GraphManager >
class Coordinator : public common::Coordinator < Time >
{
public:
    typedef Parameters parameters_type;

    Coordinator(const std::string& name, const Parameters& /* parameters */) :
        common::Coordinator < Time >(name), _graph_manager(this)
    { }

    virtual ~Coordinator()
    { }

    typename Time::type start(typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::I_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        assert(_graph_manager.children().size() > 0);

        for (auto & child : _graph_manager.children()) {
            _event_table.init(child->start(
                                  Coordinator < Time, GraphManager >::_tn),
                              child);
        }
        Coordinator < Time, GraphManager >::_tl = t;
        Coordinator < Time, GraphManager >::_tn =
            _event_table.get_current_time();

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::I_MESSAGE)
            << ": AFTER => "
            << "tl = " << Coordinator < Time, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        return Coordinator < Time, GraphManager >::_tn;
    }

/**************************************************
 * when *-message(t)
 *   calculate IMM (models with tn = t in scheduler
 *   calculate INF from IMM
 *   for each e in IMM U INF
 *     calculate influencer
 *   ...
 *  send done to parent
 **************************************************/
    void output(typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::OUTPUT)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, GraphManager >::_tn
            << " ; scheduler = " << _event_table.to_string();
        common::Trace < Time >::trace().flush();

        // assert(t == Coordinator < Time, GraphManager >::_tn);

        common::Models < Time > IMM = _event_table.get_current_models(t);

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::OUTPUT)
            << ": IMM = " << IMM.to_string();
        common::Trace < Time >::trace().flush();

        for (auto & model : IMM) {
            model->output(t);
        }

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::OUTPUT)
            << ": AFTER => "
            << "tl = " << Coordinator < Time, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, GraphManager >::_tn
            << " ; scheduler = " << _event_table.to_string();
        common::Trace < Time >::trace().flush();

    }

/*******************************************************************
 * when x-message(t)
 *   receivers = { r | r in children, N in Ir, Z(N,r)(x) isn't empty
 *   for each r in receivers
 *     send x-message(Z(N,r)(x), t) with input value Z(N,r)(x) to r
 *   for each r in IMM and not in receivers
 *     send x-message(empty, t) to r
 *   sort event list acocrding to tn
 *   tl = t
 *   tn = min(tn_d | d in D)
 *******************************************************************/
    typename Time::type transition(typename Time::type t)
    {

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::S_MESSAGE)
            << ": BEFORE => "
            << "tl = " << Coordinator < Time, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, GraphManager >::_tn
            << " ; scheduler = " << _event_table.to_string();
        common::Trace < Time >::trace().flush();

        // assert(t >= Coordinator < Time, GraphManager >::_tl and t <= Coordinator < Time, GraphManager >::_tn);

        common::Models < Time > receivers = _event_table.get_current_models(t);

        add_models_with_inputs(receivers);

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::S_MESSAGE)
            << ": receivers = " << receivers.to_string();
        common::Trace < Time >::trace().flush();

        for (auto & model : receivers) {
            _event_table.put(model->transition(t), model);
        }
        update_event_table(t);
        Coordinator < Time, GraphManager >::_tl = t;
        Coordinator < Time, GraphManager >::_tn =
            _event_table.get_current_time();
        Coordinator < Time, GraphManager >::clear_bag();

        common::Trace < Time >::trace()
            << common::TraceElement < Time >(
                Coordinator < Time, GraphManager >::get_name(), t,
                common::S_MESSAGE)
            << ": AFTER => "
            << "tl = " << Coordinator < Time, GraphManager >::_tl
            << " ; tn = " << Coordinator < Time, GraphManager >::_tn
            << " ; scheduler = " << _event_table.to_string();
        common::Trace < Time >::trace().flush();

        return Coordinator < Time, GraphManager >::_tn;
    }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time >& event)
    {

        common::Trace < Time >::trace() << common::TraceElement < Time >(Coordinator < Time, GraphManager >::get_name(), t,
                                                       common::POST_EVENT)
                               << ": BEFORE => " << event.to_string();
        common::Trace < Time >::trace().flush();

        Coordinator < Time, GraphManager >::add_event(event);
        _graph_manager.post_event(t, event);
        update_event_table(t);
        Coordinator < Time, GraphManager >::_tn = _event_table.get_current_time();

        common::Trace < Time >::trace() << common::TraceElement < Time >(Coordinator < Time, GraphManager >::get_name(), t,
                                                       common::POST_EVENT)
                               << ": AFTER => " << event.to_string();
        common::Trace < Time >::trace().flush();

    }

/*******************************************************************
 * when y-message(y_d, t) with output y_d from d
 *******************************************************************/
    typename Time::type dispatch_events(common::Bag < Time > bag, typename Time::type t)
    {

        common::Trace < Time >::trace() << common::TraceElement < Time >(Coordinator < Time, GraphManager >::get_name(), t,
                                                       common::Y_MESSAGE)
                               << ": BEFORE => "
                               << "tl = " << Coordinator < Time, GraphManager >::_tl << " ; tn = " << Coordinator < Time, GraphManager >::_tn
                               << " ; bag = " << bag.to_string();
        common::Trace < Time >::trace().flush();

        _graph_manager.dispatch_events(bag, t);

        common::Trace < Time >::trace() << common::TraceElement < Time >(Coordinator < Time, GraphManager >::get_name(), t,
                                                       common::Y_MESSAGE)
                               << ": BEFORE => "
                               << "tl = " << Coordinator < Time, GraphManager >::_tl << " ; tn = " << Coordinator < Time, GraphManager >::_tn;
        common::Trace < Time >::trace().flush();

        return Coordinator < Time, GraphManager >::_tn;
    }

    void observation(std::ostream& file) const
    {
        for (auto & child : _graph_manager.children()) {
            child->observation(file);
        }
    }

    void add_models_with_inputs(common::Models < Time >& receivers)
    {
        for (auto & model : _graph_manager.children()) {
            if (model->event_number() > 0) {
                if (std::find(receivers.begin(), receivers.end(), model) ==
                    receivers.end()) {
                    receivers.push_back(model);
                }
            }
        }
    }

    void update_event_table(typename Time::type t)
    {
        for (auto & model : _graph_manager.children()) {
            if (model->event_number() > 0) {
                _event_table.put(t, model);
            }
        }
    }

private:
    GraphManager                _graph_manager;
    common::EventTable < Time > _event_table;
};

} } // namespace paradevs pdevs

#endif
