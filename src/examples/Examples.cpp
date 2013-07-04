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

#include <examples/Examples.hpp>

namespace paradevs {

void A::dint(const Time& t)
{

    std::cout << "[ model " << get_name() << " ] dint at " << t << std::endl;

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void A::dext(const Time& /* e */, const Message& msg)
{

    std::cout << "[ model " << get_name() << " ] dext: "
              << msg.get_content()
              << " on " << msg.get_port_name() << std::endl;

    _phase = SEND;
}

Time A::start()
{

    std::cout << "[ model " << get_name() << " ] start" << std::endl;

    _phase = WAIT;
    return 0;
}

Time A::ta() const
{
    if (_phase == WAIT) {
        return 1;
    } else {
        return 0;
    }
}

Messages A::lambda() const
{

    std::cout << "[ model " << get_name() << " ] lambda" << std::endl;

    Messages msgs;

    msgs.push_back(Message("out", 0, true));
    return msgs;
}

void A::observation(std::ostream& /* file */) const
{ }

void B::dint(const Time& t)
{

    std::cout << "[ model " << get_name() << " ] dint at " << t
              << std::endl;

    if (_phase == SEND) {
        _phase = WAIT;
    }
}

void B::dext(const Time& /* e */, const Message& msg)
{

    std::cout << "[ model " << get_name() << " ] dext: "
              << msg.get_content()
              << " on " << msg.get_port_name() << std::endl;

    _phase = SEND;
}

Time B::start()
{

    std::cout << "[ model " << get_name() << " ] start" << std::endl;

    _phase = WAIT;
    return 0;
}

Time B::ta() const
{
    if (_phase == WAIT) {
        return std::numeric_limits < double >::max();
    } else {
        return 0;
    }
}

Messages B::lambda() const
{

    std::cout << "[ model " << get_name() << " ] lambda" << std::endl;

    Messages msgs;

    msgs.push_back(Message("out", 0, true));
    return msgs;
}

void B::observation(std::ostream& /* file */) const
{ }

Coordinator* MyBuilder::build() const
{
    Coordinator* root = new Coordinator("root");

    Coordinator* S1 = new Coordinator("S1");
    {
        Simulator* a = new Simulator(new A("a1"));
        Simulator* b = new Simulator(new B("b1"));

        S1->add_child(a);
        S1->add_child(b);
        S1->add_link(Node("out", a), Node("in", b));
        S1->add_link(Node("out", b), Node("out", S1));
    }

    Coordinator* S2 = new Coordinator("S2");
    {
        Simulator* a = new Simulator(new A("a2"));
        Simulator* b = new Simulator(new B("b2"));

        S2->add_child(a);
        S2->add_child(b);
        S2->add_link(Node("out", a), Node("in", b));
        S2->add_link(Node("in", S2), Node("in", a));
    }
    root->add_child(S1);
    root->add_child(S2);
    root->add_link(Node("out", S1), Node("in", S2));
    return root;
}

} // namespace paradevs
