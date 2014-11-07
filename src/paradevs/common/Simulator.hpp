/**
 * @file Simulator.hpp
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

#ifndef COMMON_SIMULATOR
#define COMMON_SIMULATOR 1

#include <paradevs/common/Model.hpp>

#include <sstream>

namespace paradevs { namespace common {

template < class Time >
class Simulator : public virtual Model < Time >
{
public :
    Simulator(const std::string& name) : Model < Time >(name)
    { }
    virtual ~Simulator()
    { }

    virtual bool is_atomic() const
    { return true; }

    virtual std::string to_string(int /* level */) const
    {
        std::ostringstream ss;

        ss << "Simulator " << Simulator < Time >::get_name();
        return ss.str();
    }

// DEVS methods
    virtual void observation(std::ostream& file) const =0;
    virtual void output(typename Time::type t) =0;
    virtual void post_event(typename Time::type t,
                            const common::ExternalEvent < Time >& event) = 0;
    virtual typename Time::type start(typename Time::type t) =0;
    virtual typename Time::type transition(typename Time::type t) =0;
};

} } // namespace paradevs common

#endif
