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
#include <pdevs/Coordinator.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs {

void A1::dint(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT);
    common::Trace::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A1::dext(common::Time t, common::Time /* e */, const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_EXT)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    _phase = SEND;
}

void A1::dconf(common::Time t, common::Time /* e */,
              const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_CONF)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

}

common::Time A1::start(common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    _phase = WAIT;
    return 0;
}

common::Time A1::ta(common::Time t) const
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::TA);
    common::Trace::trace().flush();

    if (_phase == WAIT) {
        return 1;
    } else {
        return 0;
    }
}

common::Bag A1::lambda(common::Time t) const
{
    common::Bag msgs;

    msgs.push_back(common::ExternalEvent("out", 0.));

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::LAMBDA)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    return msgs;
}

void B1::dint(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT);
    common::Trace::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void B1::dext(common::Time t, common::Time /* e */, const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_EXT)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    _phase = SEND;
}

void B1::dconf(common::Time t, common::Time /* e */,
              const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_CONF)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

}

common::Time B1::start(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    _phase = WAIT;
    return std::numeric_limits < double >::max();
}

common::Time B1::ta(common::Time t) const
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::TA);
    common::Trace::trace().flush();

    if (_phase == WAIT) {
        return std::numeric_limits < double >::max();
    } else {
        return 0;
    }
}

common::Bag B1::lambda(common::Time t) const
{
    common::Bag msgs;

    msgs.push_back(common::ExternalEvent("out", t));

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::LAMBDA)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    return msgs;
}

void A2::transition(const common::Bag& x, common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT)
                           << "x = " << x.to_string();
    common::Trace::trace().flush();
}

common::Time A2::start(common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    return 0;
}

common::Bag A2::lambda(common::Time t) const
{
    common::Bag msgs;

    msgs.push_back(common::ExternalEvent("out", 0, true));

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::LAMBDA)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    return msgs;
}

void B2::transition(const common::Bag& x, common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT)
                           << "x = " << x.to_string();
    common::Trace::trace().flush();
}

common::Time B2::start(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    return 0;
}

common::Bag B2::lambda(common::Time t) const
{
    common::Bag msgs;

    msgs.push_back(common::ExternalEvent("out", 0, true));

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::LAMBDA)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    return msgs;
}

struct LastBagPolicy
{
    const common::Bag& bag() const
    { return _bag; }

    virtual void operator()(common::Time /* t */, const common::ExternalEvent& event,
                            common::Time /* tl */, common::Time /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag _bag;
};

struct IgnorePolicy
{
    const common::Bag& bag() const
    { return _bag; }

    virtual void operator()(common::Time /* t */,
                            const common::ExternalEvent& /* event */,
                            common::Time /* tl */, common::Time /* tn */)
    { }

private:
    common::Bag _bag;
};

common::Model* HierachicalBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");

    pdevs::Coordinator* S1 = new pdevs::Coordinator("S1");
    {
        pdevs::Simulator* a = new pdevs::Simulator(new A1("a1"));
        pdevs::Simulator* b = new pdevs::Simulator(new B1("b1"));

        S1->add_child(a);
        S1->add_child(b);
        S1->add_link(common::Node("out", a), common::Node("in", b));
        S1->add_link(common::Node("out", b), common::Node("out", S1));
    }

    dtss::Coordinator < LastBagPolicy >* S2 =
        new dtss::Coordinator < LastBagPolicy >("S2", 20);
    {
        dtss::Simulator* a = new dtss::Simulator(new A2("a2"), 20);
        dtss::Simulator* b = new dtss::Simulator(new B2("b2"), 20);

        S2->add_child(a);
        S2->add_child(b);
        S2->add_link(common::Node("out", a), common::Node("in", b));
        S2->add_link(common::Node("in", S2), common::Node("in", a));
    }
    root->add_child(S1);
    root->add_child(S2);
    root->add_link(common::Node("out", S1), common::Node("in", S2));
    return root;
}

} // namespace paradevs

TEST_CASE("mixed/hierachical", "run")
{
    paradevs::HierachicalBuilder builder;
    paradevs::common::RootCoordinator rc(0, 100, builder);

    paradevs::common::Trace::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (double t = 0; t <= 100; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (double t = 0; t <= 100; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 100; t += 20) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
    }

    for (unsigned int t = 0; t <= 100; t += 20) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
    }
}
