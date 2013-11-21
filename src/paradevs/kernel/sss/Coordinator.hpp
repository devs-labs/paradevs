/**
 * @file kernel/sss/Coordinator.hpp
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

#ifndef SSS_COORDINATOR
#define SSS_COORDINATOR 1

#include <paradevs/common/Coordinator.hpp>
#include <paradevs/common/Parameters.hpp>
#include <paradevs/common/utils/Trace.hpp>

#include <paradevs/kernel/sss/Model.hpp>

#include <cassert>
#include <iostream>

namespace paradevs { namespace sss {

template < class Time >
class Parameters
{
public:
    Parameters(typename Time::type time_step) : _time_step(time_step)
    { }

    typename Time::type _time_step;
};

template < class Time, class Policy, class GraphManager,
           class SchedulerHandle, class Parameters = Parameters < Time >,
           class GraphParameters = common::NoParameters >
class Coordinator : public common::Coordinator < Time, SchedulerHandle >,
                    public sss::Model < Time, SchedulerHandle >
{
    typedef Coordinator < Time, Policy, GraphManager, SchedulerHandle,
                          Parameters, GraphParameters > type;

public:
    typedef Parameters parameters_type;
    typedef GraphParameters graph_parameters_type;

    Coordinator(const std::string& name,
                const Parameters& parameters,
                const GraphParameters& graph_paramaters) :
        common::Model < Time, SchedulerHandle >(name),
        common::Coordinator < Time, SchedulerHandle >(name),
        sss::Model < Time, SchedulerHandle >(name),
        _graph_manager(this, graph_paramaters),
        _time_step(parameters._time_step)
    { }

    virtual ~Coordinator()
    { }

    virtual bool is_atomic() const
    { return common::Coordinator < Time, SchedulerHandle >::is_atomic(); }

    virtual std::string to_string(int level) const
    { return common::Coordinator < Time, SchedulerHandle >::to_string(level); }

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

        assert(_graph_manager.children().size() > 0);

        type::_tl = t;
        type::_tn = t;
        for (auto & child : _graph_manager.children()) {
            child->start(t);
        }

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

    typename Time::type dispatch_events(common::Bag < Time,
                                                      SchedulerHandle > bag,
                                        typename Time::type t)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::Y_MESSAGE)
            << ": BEFORE => " << "tl = " << type::_tl << " ; tn = "
            << type::_tn << " ; bag = " << bag.to_string();
        common::Trace < Time >::trace().flush();
#endif

        _graph_manager.dispatch_events(bag, t);

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::Y_MESSAGE)
            << ": BEFORE => " << "tl = " << type::_tl << " ; tn = "
            << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

        return type::_tn;
    }

    void observation(std::ostream& file) const
    {
        for (auto & child : _graph_manager.children()) {
            child->observation(file);
        }
    }

    void output(typename Time::type t)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::OUTPUT)
            << ": BEFORE => " << "tl = " << type::_tl << " ; tn = "
            << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

        if (t == type::_tn) {
            for (auto & model : _graph_manager.children()) {
                model->update_buffer(t);
            }
            for (auto & model : _graph_manager.children()) {
                if (not model->is_send() && model->is_marked()) {
                    model->output(t);
                    model->send();
                }
            }
        }

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::OUTPUT)
            << ": AFTER => " << "tl = " << type::_tl << " ; tn = " << type::_tn;
        common::Trace < Time >::trace().flush();
#endif

    }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time,
                                                  SchedulerHandle >& event)
    {

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::POST_EVENT)
            << ": BEFORE => " << event.to_string();
        common::Trace < Time >::trace().flush();
#endif

        if (t == type::_tn) {
            _graph_manager.post_event(t, event);
        } else {
            _policy(t, event, type::_tl, type::_tn);
        }

#ifdef WITH_TRACE
        common::Trace < Time >::trace()
            << common::TraceElement < Time >(type::get_name(), t,
                                             common::POST_EVENT)
            << ": AFTER => " << event.to_string();
        common::Trace < Time >::trace().flush();
#endif

    }

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

        if (t == type::_tn) {
            bool end = true;

            for (auto & event : _policy.bag()) {
                post_event(t, event);
            }
            for (auto & model : _graph_manager.children()) {
                if (not model->is_marked()) {
                    if (model->all_ports_are_assigned()) {
                        model->transition(t);
                        model->mark();
                        end = false;
                    } else {
                        end = false;
                    }
                } else {
                    if (not model->is_send()) {
                        end = false;
                    } else {
                        if (t == model->get_tn()) {
                            model->transition(t);
                        }
                    }
                }
            }

            if (end) {
                for (auto & model : _graph_manager.children()) {
                    model->unmark();
                    model->unsend();
                }
                type::_tl = t;
                type::_tn = t + _time_step;
            }
        }
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

    virtual void update_buffer(typename Time::type /* time */)
    { }

private:
    GraphManager        _graph_manager;
    typename Time::type _time_step;
    Policy              _policy;
};

} } // namespace paradevs sss

#endif
