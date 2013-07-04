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

#ifndef DEVS_CHILD
#define DEVS_CHILD 1

#include <devs/Dynamics.hpp>
#include <devs/Links.hpp>
#include <devs/Message.hpp>
#include <devs/Node.hpp>
#include <devs/Time.hpp>

#include <iostream>
#include <limits>
#include <vector>

namespace paradevs {

class Dynamics;
class Links;
class Message;
class Messages;
class Node;

class Model;
typedef std::vector < Model* > Models;

class Model
{
public:
    Model(const std::string& name);
    virtual ~Model();

    virtual Time i_message(Time /* t */) = 0;
    virtual Time s_message(Time /* t */) =0;
    virtual Time x_message(const Message& /* message */, Time /* t */) =0;
    // virtual Time y_message(Messages /* messages */, Time /* t */) =0;
    virtual void observation(std::ostream& file) const = 0;

    virtual const std::string& get_name() const
    { return _name; }

    virtual Model* get_parent() const;
    virtual void set_parent(Model* parent);

protected:
    Time        _tl;
    Time        _tn;

private :
    Model*      _parent;
    std::string _name;
};

} // namespace paradevs

#endif
