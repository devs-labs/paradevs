/**
 * @file Model.hpp
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

#ifndef COMMON_MODEL
#define COMMON_MODEL 1

#include <paradevs/common/Bag.hpp>
#include <paradevs/common/ExternalEvent.hpp>
#include <paradevs/common/InternalEvent.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

namespace paradevs { namespace common {

template < class Time, class SchedulerHandle >
class ExternalEvent;

template < class Time, class SchedulerHandle >
class InternalEvent;

template < class Tim, class SchedulerHandlee >
class Bag;

typedef std::string Port;
typedef std::vector < Port > Ports;

template < class Time, class SchedulerHandle >
class Model
{
public:
    Model(const std::string& name) :
        _tl(0), _tn(0), _parent(0), _name(name), _inputs(0)
    { }

    virtual ~Model()
    {
        if (_inputs) {
            delete _inputs;
        }
    }

    // structure
    void add_in_port(const std::string& port_name)
    {
        assert(not exist_in_port(port_name));

        _in_ports.push_back(port_name);
    }

    void add_out_port(const std::string& port_name)
    {
        assert(not exist_out_port(port_name));

        _out_ports.push_back(port_name);
    }

    void delete_in_port(const std::string& port_name)
    {
        assert(not exist_in_port(port_name));

        _in_ports.erase(std::find(_in_ports.begin(), _in_ports.end(),
                                  port_name));
    }

    void delete_out_port(const std::string& port_name)
    {
        assert(not exist_out_port(port_name));

        _out_ports.erase(std::find(_out_ports.begin(), _out_ports.end(),
                                   port_name));
    }

    bool exist_in_port(const std::string& port_name)
    {
        return std::find(_in_ports.begin(), _in_ports.end(),
                         port_name) != _in_ports.end();
    }

    bool exist_out_port(const std::string& port_name)
    {
        return std::find(_out_ports.begin(), _out_ports.end(),
                         port_name) != _out_ports.end();
    }

    const std::string& get_name() const
    { return _name; }

    Model < Time, SchedulerHandle >* get_parent() const
    { return _parent; }

    virtual bool is_atomic() const = 0;

    void set_parent(Model < Time, SchedulerHandle >* parent)
    { _parent = parent; }

    virtual std::string to_string(int /* level */) const =0;

    // event
    void add_event(const common::ExternalEvent < Time, SchedulerHandle >&
                   message)
    {
        if (_inputs == 0) {
            _inputs = new Bag < Time, SchedulerHandle >;
        }
        _inputs->push_back(message);
    }

    void clear_bag()
    {
        if (_inputs) {
            delete _inputs;
            _inputs = 0;
        }
    }

    unsigned int event_number() const
    {
        if (_inputs) {
            return _inputs->size();
        } else {
            return 0;
        }
    }

    const common::Bag < Time, SchedulerHandle >& get_bag()
    {
        if (_inputs == 0) {
            _inputs = new Bag < Time, SchedulerHandle >;
        }
        return *_inputs;
    }

    // time
    typename Time::type get_tl() const
    { return _tl; }

    typename Time::type get_tn() const
    { return _tn; }

    // devs methods
    virtual void observation(std::ostream& file) const =0;
    virtual void output(typename Time::type t) =0;
    virtual void post_event(typename Time::type t,
                            const common::ExternalEvent < Time,
                                                          SchedulerHandle >&
                            event) = 0;
    virtual typename Time::type start(typename Time::type t) =0;
    virtual typename Time::type transition(typename Time::type t) =0;

    // scheduler
    void handle(SchedulerHandle handle)
    { _handle.handle(handle); }

    const SchedulerHandle& handle() const
    { return _handle.handle(); }

protected:
    typename Time::type _tl;
    typename Time::type _tn;

private :
    Model < Time, SchedulerHandle >* _parent;
    std::string                      _name;
    Ports                            _in_ports;
    Ports                            _out_ports;

    Bag < Time, SchedulerHandle >*   _inputs;
    SchedulerHandle                  _handle;
};

template < class Time, class SchedulerHandle >
class Models : public std::vector < Model < Time, SchedulerHandle >* >
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

} } // namespace paradevs common

#endif
