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

#include <tests/dtss_tests.hpp>

#include <common/RootCoordinator.hpp>
#include <common/Trace.hpp>

#include <dtss/Coordinator.hpp>
#include <dtss/GraphManager.hpp>
#include <dtss/Simulator.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs { namespace dtss {

void A::transition(const common::Bag < MyTime >& /* x */, MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_INT);
    common::Trace < MyTime >::trace().flush();
}

MyTime::type A::start(MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    return 0;
}

common::Bag < MyTime > A::lambda(MyTime::type t) const
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

void B::transition(const common::Bag < MyTime >& x, MyTime::type t)
{
    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::DELTA_INT)
        << "x = " << x.to_string();
    common::Trace < MyTime >::trace().flush();
}

MyTime::type B::start(MyTime::type t)
{

    common::Trace < MyTime >::trace()
        << common::TraceElement < MyTime >(get_name(), t,
                                           common::START);
    common::Trace < MyTime >::trace().flush();

    return 0;
}

common::Bag < MyTime > B::lambda(MyTime::type t) const
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

struct Policy
{
    const common::Bag < MyTime >& bag() const
    { return _bag; }

    virtual void operator()(MyTime::type /* t */,
                            const common::ExternalEvent < MyTime >& event,
                            MyTime::type /* tl */,
                            MyTime::type /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag < MyTime > _bag;
};

class OnlyOneGraphManager : public dtss::GraphManager < MyTime >
{
public:
    OnlyOneGraphManager(common::Coordinator < MyTime >* coordinator) :
        dtss::GraphManager < MyTime >(coordinator)
    {
        dtss::Simulator < MyTime, A >* a =
            new dtss::Simulator < MyTime, A >("a", 1);

        add_child(a);
    }

    virtual ~OnlyOneGraphManager()
    { }
};

class TwoGraphManager : public dtss::GraphManager < MyTime >
{
public:
    TwoGraphManager(common::Coordinator < MyTime >* coordinator) :
        dtss::GraphManager < MyTime >(coordinator)
    {
        dtss::Simulator < MyTime, A >* a =
            new dtss::Simulator < MyTime, A >("a", 1);
        dtss::Simulator < MyTime, B >* b =
            new dtss::Simulator < MyTime, B >("b", 1);

        add_child(a);
        add_child(b);
        add_link(a, "out", b, "in");
    }

    virtual ~TwoGraphManager()
    { }
};

} } // namespace paradevs dtss

TEST_CASE("dtss/only_one", "run")
{

    paradevs::common::RootCoordinator <
        paradevs::dtss::MyTime, paradevs::dtss::Coordinator <
            paradevs::dtss::MyTime, paradevs::dtss::Policy,
            paradevs::dtss::OnlyOneGraphManager >
        > rc(0, 10, "root",
             paradevs::dtss::Parameters < paradevs::dtss::MyTime >(1));

    paradevs::common::Trace < paradevs::dtss::MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                paradevs::dtss::MyTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    for (double t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::dtss::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::dtss::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}

TEST_CASE("dtss/two", "run")
{
    paradevs::common::RootCoordinator <
        paradevs::dtss::MyTime, paradevs::dtss::Coordinator <
            paradevs::dtss::MyTime, paradevs::dtss::Policy,
            paradevs::dtss::TwoGraphManager >
        > rc(0, 10, "root",
             paradevs::dtss::Parameters < paradevs::dtss::MyTime >(1));

    paradevs::common::Trace < paradevs::dtss::MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                paradevs::dtss::MyTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::dtss::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::dtss::MyTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }

    REQUIRE(paradevs::common::Trace <
                paradevs::dtss::MyTime >::trace().elements().
            filter_model_name("b").
            filter_type(paradevs::common::START).size() == 1);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    paradevs::dtss::MyTime >::trace().elements().
                filter_model_name("b").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    paradevs::dtss::MyTime >::trace().elements().
                filter_model_name("b").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}
