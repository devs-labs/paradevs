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

#include <dtss/Dynamics.hpp>
#include <common/Time.hpp>

namespace paradevs { namespace dtss {

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
    A(const std::string& name) : Dynamics(name)
    { }
    virtual ~A()
    { }

    virtual void transition(const common::Bag < MyTime >& /* x */,
                            MyTime::type /* t */);
    virtual MyTime::type start(MyTime::type /* t */);
    virtual common::Bag < MyTime > lambda(MyTime::type /* t */) const;
};

class B : public Dynamics < MyTime >
{
public:
    B(const std::string& name) : Dynamics(name)
    { }
    virtual ~B()
    { }

    virtual void transition(const common::Bag < MyTime >& /* x */,
                            MyTime::type /* t */);
    virtual MyTime::type start(MyTime::type /* t */);
    virtual common::Bag < MyTime > lambda(MyTime::type /* t */) const;
};

} } // namespace paradevs dtss
