/**
 * @file kernel/sss/Model.hpp
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

#ifndef SSS_MODEL
#define SSS_MODEL 1

#include <paradevs/common/Model.hpp>

namespace paradevs { namespace sss {

template < class Time, class SchedulerHandle >
class Model : public virtual common::Model < Time, SchedulerHandle >
{
public:
    Model(const std::string& name) :
        common::Model < Time, SchedulerHandle >(name)
    {
        assigned = 0;
        _mark = false;
        _send = false;
    }

    virtual ~Model()
    { }

    virtual void update_buffer(typename Time::type /* time */) = 0;

    void add_event(const common::ExternalEvent < Time, SchedulerHandle >&
                   message)
    {
        common::Model < Time, SchedulerHandle >::add_event(message);
        std::map < std::string, bool >::iterator it =
            port_assigned.find(message.get_port_name());

        if (it != port_assigned.end() and not it->second) {
            port_assigned[message.get_port_name()] = true;
            ++assigned;
        }
    }

    void add_in_port(const std::string& port_name, bool sync)
    {
        common::Model < Time, SchedulerHandle >::add_in_port(port_name);
        if (sync) {
            port_assigned[port_name] = false;
        }
    }

    bool all_ports_are_assigned() const
    { return assigned == port_assigned.size(); }

    void clear_bag()
    {
        common::Model < Time, SchedulerHandle >::clear_bag();

        for (auto & p: port_assigned) {
            p.second = false;
        }
        assigned = 0;
    }

    bool is_marked() const
    { return _mark; }

    bool is_send() const
    { return _send; }

    void mark()
    { _mark = true; }

    void send()
    { _send = true; }

    void unmark()
    { _mark = false; }

    void unsend()
    { _send = false; }

private:
    std::map < std::string, bool > port_assigned;
    unsigned int assigned;
    bool _mark;
    bool _send;
};

template < class Time, class SchedulerHandle >
class Models : public std::vector < sss::Model < Time, SchedulerHandle >* >
{
public:
    Models()
    { }
    virtual ~Models()
    { }

    std::string to_string() const
    {
        std::ostringstream ss;

        ss << "{ ";
        for (typename Models < Time, SchedulerHandle >::const_iterator it =
                 Models < Time, SchedulerHandle >::begin();
             it != Models < Time, SchedulerHandle >::end(); ++it) {
            ss << (*it)->get_name() << " ";
        }
        ss << "}";
        return ss.str();
    }
};

} } // namespace paradevs sss

#endif
