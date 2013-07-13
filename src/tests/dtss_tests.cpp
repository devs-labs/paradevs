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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs { namespace dtss {

void A::transition(const common::Bag& /* x */, common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT);
    common::Trace::trace().flush();
}

common::Time A::start(common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    return 0;
}

common::Bag A::lambda(common::Time t) const
{
    common::Bag msgs;

    msgs.push_back(common::ExternalEvent("out", 0.));

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::LAMBDA)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    return msgs;
}

void B::transition(const common::Bag& x, common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT)
                           << "x = " << x.to_string();
    common::Trace::trace().flush();
}

common::Time B::start(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    return 0;
}

common::Bag B::lambda(common::Time t) const
{
    common::Bag msgs;

    msgs.push_back(common::ExternalEvent("out", 0.));

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::LAMBDA)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    return msgs;
}

struct Policy
{
    const common::Bag& bag() const
    { return _bag; }

    virtual void operator()(common::Time /* t */,
                            const common::ExternalEvent& event,
                            common::Time /* tl */,
                            common::Time /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag _bag;
};

class OnlyOneGraphManager : public dtss::GraphManager
{
public:
    OnlyOneGraphManager(common::Coordinator* coordinator) :
        dtss::GraphManager(coordinator)
    {
        dtss::Simulator < A >* a = new dtss::Simulator < A >("a", 1);

        add_child(a);
    }

    virtual ~OnlyOneGraphManager()
    { }
};

class TwoGraphManager : public dtss::GraphManager
{
public:
    TwoGraphManager(common::Coordinator* coordinator) :
        dtss::GraphManager(coordinator)
    {
        dtss::Simulator < A >* a = new dtss::Simulator < A >("a", 1);
        dtss::Simulator < B >* b = new dtss::Simulator < B >("b", 1);

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
        paradevs::dtss::Coordinator < paradevs::dtss::Policy,
                                      paradevs::dtss::OnlyOneGraphManager >
        > rc(0, 10, "root", paradevs::dtss::Parameters(1));

    paradevs::common::Trace::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}

TEST_CASE("dtss/two", "run")
{
    paradevs::common::RootCoordinator <
        paradevs::dtss::Coordinator < paradevs::dtss::Policy,
                                      paradevs::dtss::TwoGraphManager >
        > rc(0, 10, "root", paradevs::dtss::Parameters(1));

    paradevs::common::Trace::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }

    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("b").
            filter_type(paradevs::common::START).size() == 1);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}
