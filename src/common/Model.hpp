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
#include <common/Time.hpp>

#include <iostream>
#include <vector>

namespace paradevs { namespace common {

class Bag;
class ExternalEvent;

class Model
{
public:
    Model(const std::string& name);
    virtual ~Model();

    virtual void observation(std::ostream& file) const =0;
    virtual void output(common::Time t) =0;
    virtual void post_message(common::Time t,
                              const common::ExternalEvent& event) = 0;
    virtual common::Time start(common::Time t) =0;
    virtual common::Time transition(common::Time t) =0;

    virtual const std::string& get_name() const
    { return _name; }

    Model* get_parent() const
    { return _parent; }

    void set_parent(Model* parent)
    { _parent = parent; }

    void add_event(const common::ExternalEvent& event);
    void clear_bag();
    const common::Bag& get_bag() const;
    unsigned int event_number() const;

protected:
    Time        _tl;
    Time        _tn;

private :
    Model*      _parent;
    std::string _name;
    Bag*        _inputs;
};

class Models : public std::vector < Model* >
{
public:
    Models()
    { }
    virtual ~Models()
    { }

    std::string to_string() const;
};

} } // namespace paradevs common

#endif
