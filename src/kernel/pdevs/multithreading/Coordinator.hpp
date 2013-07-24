/**
 * @file kernel/pdevs/multithreading/Coordinator.hpp
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

#ifndef PDEVS_MULTITHREADING_COORDINATOR
#define PDEVS_MULTITHREADING_COORDINATOR 1

#include <kernel/pdevs/Coordinator.hpp>

#include <future>

namespace paradevs { namespace pdevs { namespace multithreading {

class Barrier
{
    struct SubBarrier
    {
        std::condition_variable _cv;
        std::mutex              _lck;
        int                     _runners;
    };

public:
    Barrier(int count) : _max(count)
    {
        _current = &_sub_barriers[0];
        for (int i = 0; i < 2; ++i) {
            _sub_barriers[i]._runners = count;
        }
    }

    virtual ~Barrier()
    { }

    int wait()
    {
        SubBarrier *sub_barrier = _current;

        std::unique_lock < std::mutex > lck(sub_barrier->_lck);

        if (sub_barrier->_runners == 1) {
            if (_max != 1) {
                sub_barrier->_runners = _max;
                _current = (_current == &_sub_barriers[0]) ? &_sub_barriers[1] :
                    &_sub_barriers[0];
                sub_barrier->_cv.notify_all();
            }
        } else {
            sub_barrier->_runners--;
            while (sub_barrier->_runners != _max)
                sub_barrier->_cv.wait(lck);
        }
        return 0;
    }

private:
    int         _max;
    SubBarrier  _sub_barriers[2];
    SubBarrier* _current;
};

template < class Time,
           class Scheduler,
           class SchedulerHandle,
           class GraphManager,
           class Parameters = common::NoParameters,
           class GraphParameters = common::NoParameters >
class Coordinator : public pdevs::Coordinator < Time, Scheduler,
                                                SchedulerHandle, GraphManager,
                                                Parameters, GraphParameters >
{
    typedef pdevs::Coordinator < Time, Scheduler, SchedulerHandle, GraphManager,
                                 Parameters, GraphParameters > parent_type;
    typedef Coordinator < Time, Scheduler, SchedulerHandle, GraphManager,
                          Parameters, GraphParameters > type;

public:
    Coordinator(const std::string& name,
                const Parameters& parameters,
                const GraphParameters& graph_parameters) :
        pdevs::Coordinator < Time, Scheduler, SchedulerHandle, GraphManager,
                             Parameters, GraphParameters >(name, parameters,
                                                           graph_parameters)
    {
        for (auto & child : parent_type::_graph_manager.children()) {
            if (not child->is_atomic()) {
                type* coordinator = dynamic_cast < type* >(child);

                _threads.push_back(std::thread([&]{ coordinator->loop(); }));
            }
        }
    }

    virtual ~Coordinator()
    { }

    void loop()
    {
        bool stop = false;

        while (not stop) {

        }
    }

    typename Time::type start(typename Time::type t)
    {
        for (auto & child : parent_type::_graph_manager.children()) {
            if (child->is_atomic()) {
                type::_event_table.init(child->start(type::_tn), child);
            } else {

            }
        }
        type::_tl = t;
        type::_tn = type::_event_table.get_current_time();
        return type::_tn;
    }

    void output(typename Time::type t)
    {
        parent_type::output(t);
    }

    typename Time::type transition(typename Time::type t)
    {
        return parent_type::transition(t);
    }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time,
                                                  SchedulerHandle >& event)
    {
         parent_type::post_event(t, event);
    }

    typename Time::type dispatch_events(
        common::Bag < Time, SchedulerHandle > bag, typename Time::type t)
    {
        return parent_type::dispatch_events(bag, t);
    }

private:
    typedef std::vector < std::thread > Threads;

    Threads _threads;
};

} } } // namespace paradevs pdevs multithreading

#endif
