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
#include <pdevs/Coordinator.hpp>
#include <pdevs/RootCoordinator.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace paradevs { namespace pdevs {

void A::dint(const common::Time& t)
{

    std::cout << "[ model " << get_name() << " ] dint at " << t << std::endl;

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A::dext(const common::Time& /* e */, const common::Messages& msgs)
{

    std::cout << "[ model " << get_name() << " ] dext: "
              << msgs.to_string() << std::endl;

    _phase = SEND;
}

common::Time A::start()
{

    std::cout << "[ model " << get_name() << " ] start" << std::endl;

    _phase = WAIT;
    return 0;
}

common::Time A::ta() const
{
    if (_phase == WAIT) {
        return 1;
    } else {
        return 0;
    }
}

common::Messages A::lambda() const
{

    std::cout << "[ model " << get_name() << " ] lambda" << std::endl;

    common::Messages msgs;

    msgs.push_back(common::Message("out", 0, true));
    return msgs;
}

void A::observation(std::ostream& /* file */) const
{ }

void B::dint(const common::Time& t)
{

    std::cout << "[ model " << get_name() << " ] dint at " << t
              << std::endl;

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void B::dext(const common::Time& /* e */, const common::Messages& msgs)
{

    std::cout << "[ model " << get_name() << " ] dext: "
              << msgs.to_string() << std::endl;

    _phase = SEND;
}

common::Time B::start()
{

    std::cout << "[ model " << get_name() << " ] start" << std::endl;

    _phase = WAIT;
    return 0;
}

common::Time B::ta() const
{
    if (_phase == WAIT) {
        return std::numeric_limits < double >::max();
    } else {
        return 0;
    }
}

common::Messages B::lambda() const
{

    std::cout << "[ model " << get_name() << " ] lambda" << std::endl;

    common::Messages msgs;

    msgs.push_back(common::Message("out", 0, true));
    return msgs;
}

void B::observation(std::ostream& /* file */) const
{ }

common::Model* HierachicalBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");

    pdevs::Coordinator* S1 = new pdevs::Coordinator("S1");
    {
        pdevs::Simulator* a = new pdevs::Simulator(new A("a1"));
        pdevs::Simulator* b = new pdevs::Simulator(new B("b1"));

        S1->add_child(a);
        S1->add_child(b);
        S1->add_link(common::Node("out", a), common::Node("in", b));
        S1->add_link(common::Node("out", b), common::Node("out", S1));
    }

    pdevs::Coordinator* S2 = new pdevs::Coordinator("S2");
    {
        pdevs::Simulator* a = new pdevs::Simulator(new A("a2"));
        pdevs::Simulator* b = new pdevs::Simulator(new B("b2"));

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

common::Model* OnlyOneBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");
    pdevs::Simulator* a = new pdevs::Simulator(new A("a"));

    root->add_child(a);
    return root;
}

common::Model* FlatBuilder::build() const
{
    pdevs::Coordinator* root = new pdevs::Coordinator("root");
    pdevs::Simulator* a1 = new pdevs::Simulator(new A("a1"));
    pdevs::Simulator* b1 = new pdevs::Simulator(new B("b1"));
    pdevs::Simulator* a2 = new pdevs::Simulator(new A("a2"));
    pdevs::Simulator* b2 = new pdevs::Simulator(new B("b2"));

    root->add_child(a1);
    root->add_child(b1);
    root->add_child(a2);
    root->add_child(b2);
    root->add_link(common::Node("out", a1), common::Node("in", b1));
    root->add_link(common::Node("out", b1), common::Node("in", a2));
    root->add_link(common::Node("out", a2), common::Node("in", b2));
    return root;
}

} } // namespace paradevs pdevs

// TEST_CASE("pdevs/only_one", "run")
// {
//     paradevs::pdevs::OnlyOneBuilder builder;
//     paradevs::pdevs::RootCoordinator rc(0, 10, builder);

//     rc.run();
//     REQUIRE(true);
// }

TEST_CASE("pdevs/flat", "run")
{
    paradevs::pdevs::FlatBuilder builder;
    paradevs::pdevs::RootCoordinator rc(0, 10, builder);

    rc.run();
    REQUIRE(true);
}

// TEST_CASE("pdevs/hierachical", "run")
// {
//     paradevs::pdevs::HierachicalBuilder builder;
//     paradevs::pdevs::RootCoordinator rc(0, 10, builder);

//     rc.run();
//     REQUIRE(true);
// }
