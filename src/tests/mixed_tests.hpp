/**
 * @file mixed_examples.hpp
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

#include <common/RootCoordinator.hpp>
#include <common/scheduler/VectorScheduler.hpp>
#include <common/scheduler/HeapScheduler.hpp>
#include <common/Time.hpp>
#include <common/Trace.hpp>

#include <dtss/Coordinator.hpp>
#include <dtss/Dynamics.hpp>
#include <dtss/GraphManager.hpp>
#include <dtss/Simulator.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/Dynamics.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

namespace paradevs {

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

class A1 : public paradevs::pdevs::Dynamics < MyTime >
{
public:
    A1(const std::string& name) : paradevs::pdevs::Dynamics < MyTime >(name)
    { }
    virtual ~A1()
    { }

    void dint(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace() <<
            common::TraceElement < MyTime >(get_name(), t,
                                            common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

    }

    typename MyTime::type start(typename MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();

        _phase = WAIT;
        return 0;
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::TA);
        common::Trace < MyTime >::trace().flush();

        if (_phase == WAIT) {
            return 1;
        } else {
            return 0;
        }
    }

    common::Bag < MyTime > lambda(typename MyTime::type t) const
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

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class B1 : public paradevs::pdevs::Dynamics < MyTime >
{
public:
    B1(const std::string& name) : paradevs::pdevs::Dynamics < MyTime >(name)
    { }
    virtual ~B1()
    { }

    void dint(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT);
        common::Trace < MyTime >::trace().flush();

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        _phase = SEND;
    }

    void dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime >& msgs)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

    }

    typename MyTime::type start(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();

        _phase = WAIT;
        return std::numeric_limits < double >::max();
    }

    typename MyTime::type ta(typename MyTime::type t) const
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::TA);
        common::Trace < MyTime >::trace().flush();

        if (_phase == WAIT) {
            return std::numeric_limits < double >::max();
        } else {
            return 0;
        }
    }

    common::Bag < MyTime > lambda(typename MyTime::type t) const
    {
        common::Bag < MyTime > msgs;

        msgs.push_back(common::ExternalEvent < MyTime >("out", t));

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < MyTime >::trace().flush();

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class A2 : public paradevs::dtss::Dynamics < MyTime >
{
public:
    A2(const std::string& name) : paradevs::dtss::Dynamics < MyTime >(name)
    { }
    virtual ~A2()
    { }

    void transition(const common::Bag < MyTime >& x, typename MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < MyTime >::trace().flush();
    }

    typename MyTime::type start(typename MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();

        return 0;
    }

    common::Bag < MyTime > lambda(typename MyTime::type t) const
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

class B2 : public paradevs::dtss::Dynamics < MyTime >
{
public:
    B2(const std::string& name) : paradevs::dtss::Dynamics < MyTime >(name)
    { }
    virtual ~B2()
    { }

    void transition(const common::Bag < MyTime >& x, typename MyTime::type t)
    {
        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < MyTime >::trace().flush();
    }

    typename MyTime::type start(typename MyTime::type t)
    {

        common::Trace < MyTime >::trace()
            << common::TraceElement < MyTime >(get_name(), t,
                                               common::START);
        common::Trace < MyTime >::trace().flush();

        return 0;
    }

    common::Bag < MyTime > lambda(typename MyTime::type t) const
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

struct LastBagPolicy
{
    const common::Bag < MyTime >& bag() const
    { return _bag; }

    virtual void operator()(typename MyTime::type /* t */,
                            const common::ExternalEvent < MyTime >& event,
                            typename MyTime::type /* tl */,
                            typename MyTime::type /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag < MyTime > _bag;
};

struct IgnorePolicy
{
    const common::Bag < MyTime >& bag() const
    { return _bag; }

    virtual void operator()(typename MyTime::type /* t */,
                            const common::ExternalEvent < MyTime >& /* event */,
                            typename MyTime::type /* tl */,
                            typename MyTime::type /* tn */)
    { }

private:
    common::Bag < MyTime > _bag;
};

class S1GraphManager : public pdevs::GraphManager < MyTime >
{
public:
    S1GraphManager(common::Coordinator < MyTime >* coordinator) :
        pdevs::GraphManager < MyTime >(coordinator), a("a1"), b("b1")
    {
        add_child(&a);
        add_child(&b);
        add_link(&a, "out", &b, "in");
        add_link(&b, "out", coordinator, "out");
    }

    virtual ~S1GraphManager()
    { }

private:
    pdevs::Simulator < MyTime, A1 > a;
    pdevs::Simulator < MyTime, B1 > b;
};

class S2GraphManager : public dtss::GraphManager < MyTime >
{
public:
    S2GraphManager(common::Coordinator < MyTime >* coordinator) :
        dtss::GraphManager < MyTime >(coordinator), a("a2", 20), b("b2", 20)
    {
        add_child(&a);
        add_child(&b);
        add_link(&a, "out", &b, "in");
        add_link(coordinator, "in", &a, "in");
    }

    virtual ~S2GraphManager()
    { }

private:
    dtss::Simulator < MyTime, A2 > a;
    dtss::Simulator < MyTime, B2 > b;
};

class RootGraphManager : public pdevs::GraphManager < MyTime >
{
public:
    RootGraphManager(common::Coordinator < MyTime >* coordinator) :
        pdevs::GraphManager < MyTime >(coordinator),
        S1("S1", paradevs::pdevs::Parameters()),
        S2("S2", paradevs::dtss::Parameters < MyTime >(20))
    {
        add_child(&S1);
        add_child(&S2);
        add_link(&S1, "out", &S2, "in");
    }

    virtual ~RootGraphManager()
    { }

private:
    pdevs::Coordinator < MyTime,
                         paradevs::common::scheduler::HeapScheduler <
                             MyTime >,
                         S1GraphManager > S1;
    dtss::Coordinator < MyTime, LastBagPolicy, S2GraphManager > S2;
};

} // namespace paradevs
