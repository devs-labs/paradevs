/**
 * @file HeapScheduler.hpp
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

#ifndef COMMON_SCHEDULER_HEAP_SCHEDULER_HPP
#define COMMON_SCHEDULER_HEAP_SCHEDULER_HPP 1

#include <common/InternalEvent.hpp>

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/binomial_heap.hpp>

#include <cmath>
#include <sstream>

namespace paradevs { namespace common { namespace scheduler {

template < typename Time >
struct Heap
{
    typedef boost::heap::fibonacci_heap <
        InternalEvent < Time >, boost::heap::compare <
                       EventCompare < InternalEvent < Time > > > > Type;

    typedef typename boost::heap::fibonacci_heap <
        InternalEvent < Time >, boost::heap::compare <
                       EventCompare < InternalEvent <
                                          Time > > > >::handle_type Handle;
};

template < class Time >
class HeapScheduler
{
    typedef boost::heap::fibonacci_heap < InternalEvent < Time >,
                                          boost::heap::compare <
                                              EventCompare <
                                                  InternalEvent < Time > > >
                                          > Heap;

public:
    HeapScheduler()
    { }
    virtual ~HeapScheduler()
    { }

    Model < Time >* get_current_model()
    {
        return _heap.top().get_model();
    }

    Models < Time > get_current_models(typename Time::type time) const
    {
        Models < Time > models;

        for (typename Heap::ordered_iterator it = _heap.ordered_begin();
             it != _heap.ordered_end() and it->get_time() == time; ++it) {
            models.push_back(it->get_model());
        }
        return models;
    }

    typename Time::type get_current_time() const
    {
        return _heap.top().get_time();
    }

    void init(typename Time::type time, Model < Time >* model)
    {
        model->heap_id(_heap.push(InternalEvent < Time >(time, model)));
    }

    void put(typename Time::type time, Model < Time >* model)
    {
        typename Time::type previous_time = (*model->heap_id()).get_time();

        (*model->heap_id()).set_time(time);
        if (previous_time < time) {
            _heap.decrease(model->heap_id());
        } else if (previous_time > time) {
            _heap.increase(model->heap_id());
        }
    }

    std::string to_string() const
    {
        std::stringstream ss;

        ss << "Scheduler = { ";
        for (typename Heap::ordered_iterator it = _heap.ordered_begin();
             it != _heap.ordered_end(); ++it) {
            ss << "(" << it->get_time() << " -> " << it->get_model()->get_name()
               << ") ";
        }
        ss << "}";
        return ss.str();
    }

private:
    Heap _heap;
};

} } } // namespace paradevs common scheduler

#endif
