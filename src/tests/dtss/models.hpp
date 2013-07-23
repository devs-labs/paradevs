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

#include <common/time/DoubleTime.hpp>

namespace paradevs { namespace tests { namespace dtss {

template < class SchedulerHandle>
class A :
        public paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle,
                                          paradevs::common::NoParameters >
{
public:
    A(const std::string& name,
      const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle,
                                   paradevs::common::NoParameters >(name,
                                                                    parameters)
    { }
    virtual ~A()
    { }

    void transition(const common::Bag < common::DoubleTime,
                    SchedulerHandle >& /* x */,
                    common::DoubleTime::type t)
    {
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(
                A < SchedulerHandle >::get_name(), t,
                common::DELTA_INT);
        common::Trace < common::DoubleTime >::trace().flush();
    }

    common::DoubleTime::type start(common::DoubleTime::type t)
    {
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(
                A < SchedulerHandle >::get_name(), t,
                common::START);
        common::Trace < common::DoubleTime >::trace().flush();

        return 0;
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        common::DoubleTime::type t) const
    {
        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < common::DoubleTime,
                                               SchedulerHandle >("out", 0.));

        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(
                A < SchedulerHandle >::get_name(), t,
                common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();

        return msgs;
    }
};

template < class SchedulerHandle>
class B :
        public paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle,
                                          paradevs::common::NoParameters >
{
public:
    B(const std::string& name,
      const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle,
                                   paradevs::common::NoParameters >(name,
                                                                    parameters)
    { }
    virtual ~B()
    { }

    void transition(const common::Bag < common::DoubleTime,
                    SchedulerHandle >& x,
                    common::DoubleTime::type t)
    {
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(
                B < SchedulerHandle >::get_name(), t,
                common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
    }

    common::DoubleTime::type start(common::DoubleTime::type t)
    {

        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(
                B < SchedulerHandle >::get_name(), t,
                common::START);
        common::Trace < common::DoubleTime >::trace().flush();

        return 0;
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        common::DoubleTime::type t) const
    {
        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < common::DoubleTime,
                                               SchedulerHandle >("out", 0.));

        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(
                B < SchedulerHandle >::get_name(), t,
                common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();

        return msgs;
    }
};

} } } // namespace paradevs tests dtss

#endif
