/**
 * @file EventTable.hpp
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

#ifndef COMMON_EVENT_TABLE
#define COMMON_EVENT_TABLE 1

#include <common/InternalEvent.hpp>

#include <algorithm>
#include <sstream>

namespace paradevs { namespace common {

template < class Time >
class EventTable : protected std::vector < InternalEvent < Time > >
{
public:
    EventTable()
    { }
    virtual ~EventTable()
    { }

    Model < Time >* get_current_model()
    {
        return EventTable < Time >::back().get_model();
    }

    Models < Time > get_current_models(typename Time::type time) const
    {
        Models < Time > models;
        bool found = true;

        for (typename EventTable < Time >::const_reverse_iterator it =
                 EventTable < Time >::rbegin();
             found and it != EventTable < Time >::rend(); ++it) {
            if (it->get_time() == time) {
                models.push_back(it->get_model());
            } else {
                found = false;
            }
        }
        return models;
    }

    typename Time::type get_current_time() const
    { return EventTable < Time >::back().get_time(); }

    void init(typename Time::type time, Model < Time >* model)
    {
        EventTable < Time >::push_back(InternalEvent < Time >(time, model));
        std::sort(EventTable < Time >::begin(), EventTable < Time >::end());
    }

    void put(typename Time::type time, Model < Time >* model)
    {
        remove(model);
        EventTable < Time >::push_back(InternalEvent < Time >(time, model));
        std::sort(EventTable < Time >::begin(), EventTable < Time >::end());
    }

    std::string to_string() const
    {
        std::stringstream ss;

        ss << "EventTable = { ";
        for (typename EventTable < Time >::const_iterator it =
                 EventTable < Time >::begin();
             it != EventTable < Time >::end(); ++it) {
            ss << "(" << it->get_time() << " -> " << it->get_model()->get_name()
               << ") ";
        }
        ss << "}";
        return ss.str();
    }

private:
    void remove(Model < Time >* model)
    {
        typename EventTable < Time >::iterator jt =
            EventTable < Time >::begin();

        while (jt != EventTable < Time >::end()) {
            if (jt->get_model() == model) {
                jt = EventTable < Time >::erase(jt);
            } else {
                ++jt;
            }
        }
    }
};

} } // namespace paradevs common

#endif
