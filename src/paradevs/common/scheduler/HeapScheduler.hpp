/**
 * @file HeapScheduler.hpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013-2015 ULCO http://www.univ-litoral.fr
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

#include <paradevs/common/InternalEvent.hpp>

#include <boost/heap/fibonacci_heap.hpp>

#include <sstream>

namespace paradevs { namespace common { namespace scheduler {

template < class Time, class T >
class HeapScheduler :
        public boost::heap::fibonacci_heap <
    InternalEvent < Time, T >,
    boost::heap::compare <
        EventCompare < InternalEvent < Time, T > > > >
{
public:
    typedef HeapScheduler < Time, T > type;
    typedef Model < Time, T >         model_type;
    typedef Models < Time, T >        models_type;
    typedef InternalEvent < Time, T > internal_event_type;

    HeapScheduler()
    { }
    virtual ~HeapScheduler()
    { }

    model_type* get_current_model()
    {
        return type::top().get_model();
    }

    models_type get_current_models(typename Time::type time) const
    {
        models_type models;

        for (typename type::ordered_iterator it = type::ordered_begin();
             it != type::ordered_end() and it->get_time() == time; ++it) {
            models.push_back(it->get_model());
        }
        return models;
    }

    typename Time::type get_current_time() const
    {
        return type::top().get_time();
    }

    void init(typename Time::type time, model_type* model)
    {
        model->handle(T(type::push(internal_event_type(time, model))));
    }

    void put(typename Time::type time, model_type* model)
    {
        typename Time::type previous_time =
            (*model->handle()._handle).get_time();

        (*model->handle()._handle).set_time(time);
        if (previous_time < time) {
            type::decrease(model->handle()._handle);
        } else if (previous_time > time) {
            type::increase(model->handle()._handle);
        }
    }

    std::string to_string() const
    {
        std::stringstream ss;

        ss << "Scheduler = { ";
        for (typename type::ordered_iterator it = type::ordered_begin();
             it != type::ordered_end(); ++it) {
            ss << "(" << it->get_time() << " -> " << it->get_model()->get_name()
               << ") ";
        }
        ss << "}";
        return ss.str();
    }
};

} } } // namespace paradevs common scheduler

#endif
