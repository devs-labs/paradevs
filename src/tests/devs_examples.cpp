/**
 * @file devs_examples.cpp
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

#include <tests/devs_examples.hpp>
#include <devs/Coordinator.hpp>

namespace paradevs { namespace devs {

void A::dint(const common::Time& t)
{

    std::cout << "[ model " << get_name() << " ] dint at " << t << std::endl;

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A::dext(const common::Time& /* e */, const common::Message& msg)
{

    std::cout << "[ model " << get_name() << " ] dext: "
              << msg.get_content()
              << " on " << msg.get_port_name() << std::endl;

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

void B::dext(const common::Time& /* e */, const common::Message& msg)
{

    std::cout << "[ model " << get_name() << " ] dext: "
              << msg.get_content()
              << " on " << msg.get_port_name() << std::endl;

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

common::Model* MyBuilder::build() const
{
    devs::Coordinator* root = new devs::Coordinator("root");

    devs::Coordinator* S1 = new devs::Coordinator("S1");
    {
        devs::Simulator* a = new devs::Simulator(new A("a1"));
        devs::Simulator* b = new devs::Simulator(new B("b1"));

        S1->add_child(a);
        S1->add_child(b);
        S1->add_link(common::Node("out", a), common::Node("in", b));
        S1->add_link(common::Node("out", b), common::Node("out", S1));
    }

    devs::Coordinator* S2 = new devs::Coordinator("S2");
    {
        devs::Simulator* a = new devs::Simulator(new A("a2"));
        devs::Simulator* b = new devs::Simulator(new B("b2"));

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

} } // namespace paradevs devs
