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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs { namespace pdevs {

void A::dint(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT);
    common::Trace::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A::dext(common::Time t, common::Time /* e */, const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_EXT)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    _phase = SEND;
}

void A::dconf(common::Time t, common::Time /* e */,
              const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_CONF)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

}

common::Time A::start(common::Time t)
{
    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    _phase = WAIT;
    return 0;
}

common::Time A::ta(common::Time t) const
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

void A::observation(std::ostream& /* file */) const
{ }

void B::dint(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_INT);
    common::Trace::trace().flush();

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void B::dext(common::Time t, common::Time /* e */, const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_EXT)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

    _phase = SEND;
}

void B::dconf(common::Time t, common::Time /* e */,
              const common::Bag& msgs)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::DELTA_CONF)
                           << "messages = " << msgs.to_string();
    common::Trace::trace().flush();

}

common::Time B::start(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::START);
    common::Trace::trace().flush();

    _phase = WAIT;
    return std::numeric_limits < double >::max();
}

common::Time B::ta(common::Time t) const
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

void B::observation(std::ostream& /* file */) const
{ }

common::Model* HierachicalBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");

    pdevs::Coordinator* S1 = new pdevs::Coordinator("S1");
    {
        pdevs::Simulator < A >* a = new pdevs::Simulator < A >("a1");
        pdevs::Simulator < B >* b = new pdevs::Simulator < B >("b1");

        S1->add_child(a);
        S1->add_child(b);
        S1->add_link(a, "out", b, "in");
        S1->add_link(b, "out", S1, "out");
    }

    pdevs::Coordinator* S2 = new pdevs::Coordinator("S2");
    {
        pdevs::Simulator < A >* a = new pdevs::Simulator < A >("a2");
        pdevs::Simulator < B >* b = new pdevs::Simulator < B >("b2");

        S2->add_child(a);
        S2->add_child(b);
        S2->add_link(a, "out", b, "in");
        S2->add_link(S2, "in", a, "in");
    }
    root->add_child(S1);
    root->add_child(S2);
    root->add_link(S1, "out", S2, "in");
    return root;
}

common::Model* OnlyOneBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");
    pdevs::Simulator < A >* a = new pdevs::Simulator < A >("a");

    root->add_child(a);
    return root;
}

common::Model* FlatBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");
    pdevs::Simulator < A >* a1 = new pdevs::Simulator < A >("a1");
    pdevs::Simulator < B >* b1 = new pdevs::Simulator < B >("b1");
    pdevs::Simulator < A >* a2 = new pdevs::Simulator < A >("a2");
    pdevs::Simulator < B >* b2 = new pdevs::Simulator < B >("b2");

    root->add_child(a1);
    root->add_child(b1);
    root->add_child(a2);
    root->add_child(b2);
    root->add_link(a1, "out", b1, "in");
    root->add_link(b1, "out", a2, "in");
    root->add_link(a2, "out", b2, "in");
    return root;
}

} } // namespace paradevs pdevs

TEST_CASE("pdevs/only_one", "run")
{
    paradevs::pdevs::OnlyOneBuilder builder;
    paradevs::common::RootCoordinator rc(0, 10, builder);

    paradevs::common::Trace::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    REQUIRE(paradevs::common::Trace::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::DELTA_CONF).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}

TEST_CASE("pdevs/flat", "run")
{
    paradevs::pdevs::FlatBuilder builder;
    paradevs::common::RootCoordinator rc(0, 10, builder);

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
    for (unsigned int t = 0; t <= 10; ++t) {
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

    for (unsigned int t = 0; t <= 10; ++t) {
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

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 3);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_CONF).size() == 0);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 4);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 2);
    }
}

TEST_CASE("pdevs/hierachical", "run")
{
    paradevs::pdevs::HierachicalBuilder builder;
    paradevs::common::RootCoordinator rc(0, 10, builder);

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
    for (unsigned int t = 0; t <= 10; ++t) {
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

    for (unsigned int t = 0; t <= 10; ++t) {
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

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 3);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_CONF).size() == 0);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 4);
        REQUIRE(paradevs::common::Trace::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 2);
    }
}
