/**
 * @file tests/mixed/models.hpp
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

#ifndef TESTS_MIXED_MODELS_HPP
#define TESTS_MIXED_MODELS_HPP 1

#include <common/Time.hpp>
#include <common/Trace.hpp>

#include <dtss/Dynamics.hpp>

#include <pdevs/Dynamics.hpp>

namespace paradevs { namespace tests { namespace mixed {

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
class A1 : public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                              paradevs::common::NoParameters >
{
public:
    A1(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                    paradevs::common::NoParameters >(
                                        name, parameters)
    { }
    virtual ~A1()
    { }

    void dint(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace() <<
            common::TraceElement < MyTime >(get_name(), t,
                                            common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();
#endif

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif
    }

    typename MyTime::type start(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
   common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();
#endif
        _phase = WAIT;
        return 0;
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {
#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::TA);
        common::Trace < MyTime >::trace().flush();
#endif
        if (_phase == WAIT) {
            return 1;
        } else {
            return 0;
        }
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif

        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < MyTime, SchedulerHandle >(
                           "out", 0.));

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

template < class SchedulerHandle>
class B1 : public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                              paradevs::common::NoParameters >
{
public:
    B1(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                    paradevs::common::NoParameters >(
                                        name, parameters)
    { }
    virtual ~B1()
    { }

    void dint(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();
#endif

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
   (void)t;
   (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

    }

    typename MyTime::type start(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();
#endif

        _phase = WAIT;
        return std::numeric_limits < double >::max();
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::TA);
        common::Trace < MyTime >::trace().flush();
#endif

        if (_phase == WAIT) {
            return std::numeric_limits < double >::max();
        } else {
            return 0;
        }
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < MyTime, SchedulerHandle >(
                           "out", t));

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

template < class SchedulerHandle >
class A2 : public paradevs::dtss::Dynamics < MyTime, SchedulerHandle >
{
public:
    A2(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics <
           MyTime, SchedulerHandle,
           paradevs::common::NoParameters >(name, parameters)
    { }
    virtual ~A2()
    { }

    void transition(
        const common::Bag < MyTime, SchedulerHandle >& x,
            typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)x;
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

    }

    typename MyTime::type start(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();
#endif

        return 0;
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(
            common::ExternalEvent < MyTime, SchedulerHandle >( "out", 0.));

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        return msgs;
    }
};

template < class SchedulerHandle >
class B2 : public paradevs::dtss::Dynamics < MyTime, SchedulerHandle >
{
public:
    B2(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics <
           MyTime, SchedulerHandle,
           paradevs::common::NoParameters >(name, parameters)
    { }
    virtual ~B2()
    { }

    void transition(
        const common::Bag < MyTime, SchedulerHandle >& x,
            typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)x;
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

    }

    typename MyTime::type start(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();
#endif

        return 0;
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(
            common::ExternalEvent < MyTime, SchedulerHandle >("out", 0.));

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        return msgs;
    }
};

template < class SchedulerHandle>
class Beep : public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                                paradevs::common::NoParameters >
{
public:
    Beep(const std::string& name,
         const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                    paradevs::common::NoParameters >(name,
                                                                     parameters)
    { }
    virtual ~Beep()
    { }

    void dint(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace() <<
            common::TraceElement < MyTime >(get_name(), t,
                                            common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();
#endif

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

    }

    typename MyTime::type start(typename MyTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();
#endif

        _phase = WAIT;
        return 0;
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::TA);
        common::Trace < MyTime >::trace().flush();
#endif

        if (_phase == WAIT) {
            return (rand() % 100) / 10.;
        } else {
            return 0;
        }
    }

    common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < MyTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < MyTime, SchedulerHandle >(
                           "out", 0.));

#ifdef WITH_TRACE
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();
#endif

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

} } } // namespace paradevs tests mixed

#endif
