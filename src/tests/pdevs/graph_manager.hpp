/**
 * @file tests/pdevs/graph_manager.cpp
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

#ifndef TESTS_PDEVS_GRAPH_MANAGER_HPP
#define TESTS_PDEVS_GRAPH_MANAGER_HPP 1

#include <tests/pdevs/models.hpp>

#include <common/scheduler/HeapScheduler.hpp>
#include <common/scheduler/VectorScheduler.hpp>
#include <common/Trace.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

namespace paradevs { namespace tests { namespace pdevs {

class S1GraphManager :
        public paradevs::pdevs::GraphManager < MyTime >
{
public:
    S1GraphManager(common::Coordinator < MyTime >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime >(coordinator, parameters),
        a("a1", common::NoParameters()), b("b1", common::NoParameters())
    {
        add_child(&a);
        add_child(&b);

        a.add_out_port("out");
        b.add_in_port("in");
        b.add_out_port("out");
        coordinator->add_out_port("out");

        add_link(&a, "out", &b, "in");
        add_link(&b, "out", coordinator, "out");
    }

    virtual ~S1GraphManager()
    { }

private:
    paradevs::pdevs::Simulator < MyTime, A > a;
    paradevs::pdevs::Simulator < MyTime, B > b;
};

class S2GraphManager :
        public paradevs::pdevs::GraphManager < MyTime >
{
public:
    S2GraphManager(common::Coordinator < MyTime >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime >(coordinator, parameters),
        a("a2", common::NoParameters()), b("b2", common::NoParameters())
    {
        add_child(&a);
        add_child(&b);

        a.add_in_port("in");
        a.add_out_port("out");
        b.add_in_port("in");
        coordinator->add_in_port("in");

        add_link(&a, "out", &b, "in");
        add_link(coordinator, "in", &a, "in");
    }

    virtual ~S2GraphManager()
    { }

private:
    paradevs::pdevs::Simulator < MyTime, A > a;
    paradevs::pdevs::Simulator < MyTime, B > b;
};

class RootGraphManager :
        public paradevs::pdevs::GraphManager < MyTime >
{
public:
    RootGraphManager(common::Coordinator < MyTime >* coordinator,
                     const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime >(coordinator, parameters),
        S1("S1", paradevs::common::NoParameters(),
           paradevs::common::NoParameters()),
        S2("S2", paradevs::common::NoParameters(),
           paradevs::common::NoParameters())
    {
        add_child(&S1);
        add_child(&S2);

        add_link(&S1, "out", &S2, "in");
    }

    virtual ~RootGraphManager()
    { }

private:
    paradevs::pdevs::Coordinator <
    MyTime, paradevs::common::scheduler::HeapScheduler < MyTime >,
    S1GraphManager > S1;
    paradevs::pdevs::Coordinator <
        MyTime, paradevs::common::scheduler::HeapScheduler < MyTime >,
        S2GraphManager > S2;
};

class OnlyOneGraphManager :
        public paradevs::pdevs::GraphManager < MyTime >
{
public:
    OnlyOneGraphManager(common::Coordinator < MyTime >* coordinator,
                        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime >(coordinator, parameters),
        a("a", common::NoParameters())
    {
        add_child(&a);
    }

    virtual ~OnlyOneGraphManager()
    { }

private:
    paradevs::pdevs::Simulator < MyTime, A > a;
};

class FlatGraphManager :
        public paradevs::pdevs::GraphManager < MyTime >
{
public:
    FlatGraphManager(common::Coordinator < MyTime >* coordinator,
                     const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime >(coordinator, parameters),
        a1("a1", common::NoParameters()), b1("b1", common::NoParameters()),
        a2("a2", common::NoParameters()), b2("b2", common::NoParameters())
    {
        add_child(&a1);
        add_child(&b1);
        add_child(&a2);
        add_child(&b2);
        a1.add_out_port("out");
        b1.add_in_port("in");
        b1.add_out_port("out");
        a2.add_in_port("in");
        a2.add_out_port("out");
        b2.add_in_port("in");
        add_link(&a1, "out", &b1, "in");
        add_link(&b1, "out", &a2, "in");
        add_link(&a2, "out", &b2, "in");
    }

    virtual ~FlatGraphManager()
    { }

private:
    paradevs::pdevs::Simulator < MyTime, A > a1;
    paradevs::pdevs::Simulator < MyTime, B > b1;
    paradevs::pdevs::Simulator < MyTime, A > a2;
    paradevs::pdevs::Simulator < MyTime, B > b2;
};

} } } // namespace paradevs tests pdevs

#endif
