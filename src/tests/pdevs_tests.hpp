/**
 * @file pdevs_examples.hpp
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

#include <common/Time.hpp>

#include <pdevs/Dynamics.hpp>

#include <limits>

namespace paradevs { namespace pdevs {

template < typename T >
struct Limits
{
    static constexpr T negative_infinity =
        -std::numeric_limits < T >::infinity();
    static constexpr T positive_infinity =
        std::numeric_limits < T >::infinity();
    static constexpr T null = 0;
};

typedef paradevs::common::Time < double, Limits < double > > MyTime;

class A : public Dynamics < MyTime >
{
public:
    A(const std::string& name) : Dynamics < MyTime >(name)
    { }
    virtual ~A()
    { }

    virtual void dint(typename MyTime::type /* t */);
    virtual void dext(typename MyTime::type /* t */,
                      typename MyTime::type /* e */,
                      const common::Bag < MyTime >& /* msgs */);
    virtual void dconf(typename MyTime::type /* t */,
                       typename MyTime::type /* e */,
                       const common::Bag < MyTime >& /* msgs */);
    virtual typename MyTime::type start(typename MyTime::type /* t */);
    virtual typename MyTime::type ta(typename MyTime::type /* t */) const;
    virtual common::Bag < MyTime > lambda(typename MyTime::type /* t */) const;
    virtual void observation(std::ostream& /* file */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class B : public Dynamics < MyTime >
{
public:
    B(const std::string& name) : Dynamics < MyTime >(name)
    { }
    virtual ~B()
    { }

    virtual void dint(typename MyTime::type /* t */);
    virtual void dext(typename MyTime::type /* t */,
                      typename MyTime::type /* e */,
                      const common::Bag < MyTime >& /* msgs */);
    virtual void dconf(typename MyTime::type /* t */,
                       typename MyTime::type /* e */,
                       const common::Bag < MyTime >& /* msgs */);
    virtual typename MyTime::type start(typename MyTime::type /* t */);
    virtual typename MyTime::type ta(typename MyTime::type /* t */) const;
    virtual common::Bag < MyTime > lambda(typename MyTime::type /* t */) const;
    virtual void observation(std::ostream& /* file */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

} } // namespace paradevs pdevs
