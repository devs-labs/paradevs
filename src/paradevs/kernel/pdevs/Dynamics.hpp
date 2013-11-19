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

#ifndef PDEVS_DYNAMICS
#define PDEVS_DYNAMICS 1

#include <paradevs/common/Bag.hpp>
#include <paradevs/common/ExternalEvent.hpp>
#include <paradevs/common/Parameters.hpp>

#include <string>
#include <vector>

namespace paradevs { namespace pdevs {

template < class Time, class SchedulerHandle,
           class Parameters = common::NoParameters >
class Dynamics
{
public:
    Dynamics(const std::string& name, const Parameters& /* parameters */) :
        _name(name)
    { }

    virtual ~Dynamics()
    { }

    virtual void dconf(typename Time::type /* t */,
                       typename Time::type /* e */,
                       const common::Bag < Time, SchedulerHandle >& /* bag */)
    { }

    virtual void dint(typename Time::type /* t */)
    { }

    virtual void dext(typename Time::type /* t */,
                      typename Time::type /* e */,
                      const common::Bag < Time, SchedulerHandle >& /* bag */)
    { }

    virtual typename Time::type start(typename Time::type /* time */)
    { return Time::infinity; }

    virtual typename Time::type ta(typename Time::type /* time */) const
    { return Time::infinity; }

    virtual common::Bag < Time, SchedulerHandle > lambda(
        typename Time::type /* time */) const
    { return common::Bag < Time, SchedulerHandle >(); }

    virtual void observation(std::ostream& /* file */) const
    { }

    const std::string& get_name() const
    { return _name; }

private:
    std::string _name;
};

} } // namespace paradevs pdevs

#endif
