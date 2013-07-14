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

#include <tests/pdevs_tests.hpp>

#include <common/RootCoordinator.hpp>
#include <common/Trace.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs { namespace pdevs {

void A::dint(typename MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_INT);
    common::Trace < MyTime >::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A::dext(typename MyTime::type t, typename MyTime::type /* e */,
             const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_EXT)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

    _phase = SEND;
}

void A::dconf(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_CONF)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

}

typename MyTime::type A::start(typename MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    _phase = WAIT;
    return 0;
}

typename MyTime::type A::ta(typename MyTime::type t) const
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

common::Bag < MyTime > A::lambda(typename MyTime::type t) const
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

void A::observation(std::ostream& /* file */) const
{ }

void B::dint(typename MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_INT);
    common::Trace < MyTime >::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void B::dext(typename MyTime::type t, typename MyTime::type /* e */,
             const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_EXT)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

    _phase = SEND;
}

void B::dconf(typename MyTime::type t, typename MyTime::type /* e */,
              const common::Bag < MyTime >& msgs)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_CONF)
        << "messages = " << msgs.to_string();
    common::Trace < MyTime >::trace().flush();

}

typename MyTime::type B::start(typename MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    _phase = WAIT;
    return std::numeric_limits < double >::max();
}

typename MyTime::type B::ta(typename MyTime::type t) const
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

common::Bag < MyTime > B::lambda(typename MyTime::type t) const
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

void B::observation(std::ostream& /* file */) const
{ }

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
    pdevs::Simulator < MyTime, A > a;
    pdevs::Simulator < MyTime, B > b;
};

class S2GraphManager : public pdevs::GraphManager < MyTime >
{
public:
    S2GraphManager(common::Coordinator < MyTime >* coordinator) :
        pdevs::GraphManager < MyTime >(coordinator), a("a2"), b("b2")
    {
        add_child(&a);
        add_child(&b);
        add_link(&a, "out", &b, "in");
        add_link(coordinator, "in", &a, "in");
    }

    virtual ~S2GraphManager()
    { }

private:
    pdevs::Simulator < MyTime, A > a;
    pdevs::Simulator < MyTime, B > b;
};

class RootGraphManager : public pdevs::GraphManager < MyTime >
{
public:
    RootGraphManager(common::Coordinator < MyTime >* coordinator) :
        pdevs::GraphManager < MyTime >(coordinator),
        S1("S1", Parameters()),
        S2("S2", Parameters())
    {
        add_child(&S1);
        add_child(&S2);
        add_link(&S1, "out", &S2, "in");
    }

    virtual ~RootGraphManager()
    { }

private:
    Coordinator < MyTime, S1GraphManager > S1;
    Coordinator < MyTime, S2GraphManager > S2;
};

class OnlyOneGraphManager : public pdevs::GraphManager < MyTime >
{
public:
    OnlyOneGraphManager(common::Coordinator < MyTime >* coordinator) :
        pdevs::GraphManager < MyTime >(coordinator), a("a")
    {
        add_child(&a);
    }

    virtual ~OnlyOneGraphManager()
    { }

private:
    pdevs::Simulator < MyTime, A > a;
};

class FlatGraphManager : public pdevs::GraphManager < MyTime >
{
public:
    FlatGraphManager(common::Coordinator < MyTime >* coordinator) :
        pdevs::GraphManager < MyTime >(coordinator),
        a1("a1"), b1("b1"), a2("a2"), b2("b2")
    {
        add_child(&a1);
        add_child(&b1);
        add_child(&a2);
        add_child(&b2);
        add_link(&a1, "out", &b1, "in");
        add_link(&b1, "out", &a2, "in");
        add_link(&a2, "out", &b2, "in");
    }

    virtual ~FlatGraphManager()
    { }

private:
    pdevs::Simulator < MyTime, A > a1;
    pdevs::Simulator < MyTime, B > b1;
    pdevs::Simulator < MyTime, A > a2;
    pdevs::Simulator < MyTime, B > b2;
};

} } // namespace paradevs pdevs

TEST_CASE("pdevs/only_one", "run")
{
    paradevs::common::RootCoordinator <
        paradevs::pdevs::MyTime, paradevs::pdevs::Coordinator <
            paradevs::pdevs::MyTime, paradevs::pdevs::OnlyOneGraphManager >
        > rc(0, 10, "root", paradevs::pdevs::Parameters());

    paradevs::common::Trace < paradevs::pdevs::MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::DELTA_CONF).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}

TEST_CASE("pdevs/flat", "run")
{
    paradevs::common::RootCoordinator <
        paradevs::pdevs::MyTime, paradevs::pdevs::Coordinator <
            paradevs::pdevs::MyTime, paradevs::pdevs::FlatGraphManager >
        > rc(0, 10, "root", paradevs::pdevs::Parameters());

    paradevs::common::Trace < paradevs::pdevs::MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 3);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_CONF).size() == 0);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 4);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 2);
    }
}

TEST_CASE("pdevs/hierachical", "run")
{
    paradevs::common::RootCoordinator <
        paradevs::pdevs::MyTime, paradevs::pdevs::Coordinator <
            paradevs::pdevs::MyTime, paradevs::pdevs::RootGraphManager >
        > rc(0, 10, "root", paradevs::pdevs::Parameters());

    paradevs::common::Trace < paradevs::pdevs::MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace <
                paradevs::pdevs::MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 3);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_CONF).size() == 0);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 4);
        REQUIRE(paradevs::common::Trace <
                    paradevs::pdevs::MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 2);
    }
}
