/**
 * @file Dynamics.hpp
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

#ifndef DEVS_DYNAMICS
#define DEVS_DYNAMICS 1

#include <devs/Message.hpp>
#include <devs/Time.hpp>

#include <limits>
#include <string>
#include <vector>

namespace paradevs {

class Message;
class Messages;

class Dynamics
{
public:
    Dynamics(const std::string& name);
    virtual ~Dynamics();

    virtual void dint(const Time& /* t */)
    { }
    virtual void dext(const Time& /* e */, const Message& /* msg */)
    { }
    virtual Time start()
    { return std::numeric_limits < double >::max(); }
    virtual Time ta() const
    { return std::numeric_limits < double >::max(); }
    virtual Messages lambda() const;
    virtual void observation(std::ostream& /* file */) const
    { }

    const std::string& get_name() const
    { return _name; }

private:
    std::string _name;
};

} // namespace paradevs

#endif
