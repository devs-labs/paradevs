/**
 * @file Model.hpp
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

#ifndef COMMON_MODEL
#define COMMON_MODEL 1

#include <common/Bag.hpp>
#include <common/ExternalEvent.hpp>

#include <iostream>
#include <sstream>
#include <vector>

namespace paradevs { namespace common {

template < class Time >
class ExternalEvent;

template < class Time >
class Bag;

template < class Time >
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

    void add_event(const common::ExternalEvent < Time >& message)
    {
        if (_inputs == 0) {
            _inputs = new Bag < Time >;
        }
        _inputs->push_back(message);
    }

    const common::Bag < Time >& get_bag()
    {
        if (_inputs == 0) {
            _inputs = new Bag < Time>;
        }
        return *_inputs;
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

    virtual void observation(std::ostream& file) const =0;
    virtual void output(typename Time::type t) =0;
    virtual void post_event(typename Time::type t,
                            const common::ExternalEvent < Time >& event) = 0;
    virtual typename Time::type start(typename Time::type t) =0;
    virtual typename Time::type transition(typename Time::type t) =0;

    virtual const std::string& get_name() const
    { return _name; }

    Model < Time >* get_parent() const
    { return _parent; }

    void set_parent(Model < Time >* parent)
    { _parent = parent; }

protected:
    typename Time::type _tl;
    typename Time::type _tn;

private :
    Model < Time >*     _parent;
    std::string         _name;
    Bag < Time >*       _inputs;
};

template < class Time >
class Models : public std::vector < Model < Time >* >
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
        for (typename Models < Time >::const_iterator it =
                 Models < Time >::begin(); it != Models < Time >::end(); ++it) {
            ss << (*it)->get_name() << " ";
        }
        ss << "}";
        return ss.str();
    }
};

} } // namespace paradevs common

#endif
