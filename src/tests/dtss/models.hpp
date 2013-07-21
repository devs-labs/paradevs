/**
 * @file tests/dtss/models.hpp
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

#ifndef TESTS_DTSS_MODELS_HPP
#define TESTS_DTSS_MODELS_HPP 1

#include <dtss/Dynamics.hpp>
#include <common/Time.hpp>

namespace paradevs { namespace tests { namespace dtss {

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

class A :
        public paradevs::dtss::Dynamics < MyTime,
                                          paradevs::common::NoParameters >
{
public:
    A(const std::string& name,
      const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics < MyTime,
                                   paradevs::common::NoParameters >(name,
                                                                    parameters)
    { }
    virtual ~A()
    { }

    void transition(const common::Bag < MyTime >& /* x */, MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();
    }

    MyTime::type start(MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();

        return 0;
    }

    common::Bag < MyTime > lambda(MyTime::type t) const
    {
        common::Bag < MyTime > msgs;

        msgs.push_back(common::ExternalEvent < MyTime >("out", 0.));

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        return msgs;
    }
};

class B :
        public paradevs::dtss::Dynamics < MyTime,
                                          paradevs::common::NoParameters >
{
public:
    B(const std::string& name,
      const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics < MyTime,
                                   paradevs::common::NoParameters >(name,
                                                                    parameters)
    { }
    virtual ~B()
    { }

    void transition(const common::Bag < MyTime >& x, MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < MyTime >::trace().flush();
    }

    MyTime::type start(MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();

        return 0;
    }

    common::Bag < MyTime > lambda(MyTime::type t) const
    {
        common::Bag < MyTime > msgs;

        msgs.push_back(common::ExternalEvent < MyTime >("out", 0.));

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        return msgs;
    }
};

} } } // namespace paradevs tests dtss

#endif
