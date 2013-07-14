/**
 * @file examples.cpp
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

#include <tests/mixed_tests.hpp>

#include <common/RootCoordinator.hpp>
#include <common/Trace.hpp>

#include <dtss/Coordinator.hpp>
#include <dtss/GraphManager.hpp>
#include <dtss/Simulator.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs {

void A1::dint(typename MyTime::type t)
{

    common::Trace < MyTime >::trace() <<
        common::TraceElement < MyTime >(get_name(), t,
                                        common::DELTA_INT);
    common::Trace < MyTime >::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A1::dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_EXT)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

    _phase = SEND;
}

void A1::dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_CONF)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

}

typename MyTime::type A1::start(typename MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    _phase = WAIT;
    return 0;
}

typename MyTime::type A1::ta(typename MyTime::type t) const
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

common::Bag < MyTime > A1::lambda(typename MyTime::type t) const
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

void B1::dint(typename MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_INT);
    common::Trace < MyTime >::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void B1::dext(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_EXT)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

    _phase = SEND;
}

void B1::dconf(typename MyTime::type t, typename MyTime::type /* e */,
               const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_CONF)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

}

typename MyTime::type B1::start(typename MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    _phase = WAIT;
    return std::numeric_limits < double >::max();
}

typename MyTime::type B1::ta(typename MyTime::type t) const
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

common::Bag < MyTime > B1::lambda(typename MyTime::type t) const
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

void A2::transition(const common::Bag < MyTime >& x, typename MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_INT)
        << "x = " << x.to_string();
    common::Trace < MyTime >::trace().flush();
}

typename MyTime::type A2::start(typename MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    return 0;
}

common::Bag < MyTime > A2::lambda(typename MyTime::type t) const
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

void B2::transition(const common::Bag < MyTime >& x, typename MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                                   common::DELTA_INT)
                           << "x = " << x.to_string();
    common::Trace < MyTime >::trace().flush();
}

typename MyTime::type B2::start(typename MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    return 0;
}

common::Bag < MyTime > B2::lambda(typename MyTime::type t) const
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
    pdevs::Coordinator < MyTime, S1GraphManager > S1;
    dtss::Coordinator < MyTime, LastBagPolicy, S2GraphManager > S2;
};

} // namespace paradevs

TEST_CASE("mixed/hierachical", "run")
{
    paradevs::common::RootCoordinator <
        paradevs::MyTime,  paradevs::pdevs::Coordinator <
            paradevs::MyTime, paradevs::RootGraphManager >
        > rc(0, 100, "root", paradevs::pdevs::Parameters());

    paradevs::common::Trace < paradevs::MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace < paradevs::MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace < paradevs::MyTime >::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace < paradevs::MyTime >::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace < paradevs::MyTime >::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace < paradevs::MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (double t = 0; t <= 100; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (double t = 0; t <= 100; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 100; t += 20) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
    }

    for (unsigned int t = 0; t <= 100; t += 20) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
    }
}
