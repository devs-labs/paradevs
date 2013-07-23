/**
 * @file tests/pdevs/models.hpp
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

#ifndef TESTS_PDEVS_MODELS_HPP
#define TESTS_PDEVS_MODELS_HPP 1

#include <common/Time.hpp>
#include <common/Trace.hpp>

#include <pdevs/Dynamics.hpp>

#include <limits>

namespace paradevs { namespace tests { namespace pdevs {

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

template < class SchedulerHandle>
class A : public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle >
{
public:
    A(const std::string& name, const common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle >(name, parameters)
    { }
    virtual ~A()
    { }

    void dint(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                A < SchedulerHandle >::get_name(), t,
                common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                A < SchedulerHandle >::get_name(), t,
                common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                A < SchedulerHandle >::get_name(), t,
                common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

    }

    typename MyTime::type start(typename MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                A < SchedulerHandle >::get_name(), t,
                common::START);
        common::Trace < MyTime >::trace().flush();

        _phase = WAIT;
        return 0;
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                A < SchedulerHandle >::get_name(), t,
                common::TA);
        common::Trace < MyTime >::trace().flush();

        if (_phase == WAIT) {
            return 1;
        } else {
            return 0;
        }
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {
        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < MyTime, SchedulerHandle >(
                           "out", 0.));

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                A < SchedulerHandle >::get_name(), t,
                common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        return msgs;
    }

    void observation(std::ostream& /* file */) const
    { }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

template < class SchedulerHandle >
class B : public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle >
{
public:
    B(const std::string& name, const common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle >(name, parameters)
    { }
    virtual ~B()
    { }

    void dint(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                B < SchedulerHandle >::get_name(), t,
                common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                B < SchedulerHandle >::get_name(), t,
                common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                B < SchedulerHandle >::get_name(), t,
                common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

    }

    typename MyTime::type start(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                B < SchedulerHandle >::get_name(), t,
                common::START);
        common::Trace < MyTime >::trace().flush();

        _phase = WAIT;
        return std::numeric_limits < double >::max();
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                B < SchedulerHandle >::get_name(), t,
                common::TA);
        common::Trace < MyTime >::trace().flush();

        if (_phase == WAIT) {
            return std::numeric_limits < double >::max();
        } else {
            return 0;
        }
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {
        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < MyTime, SchedulerHandle >(
                           "out", 0.));

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(
                B < SchedulerHandle >::get_name(), t,
                common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        return msgs;
    }

    void observation(std::ostream& /* file */) const
    { }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

} } } // namespace paradevs tests pdevs

#endif
