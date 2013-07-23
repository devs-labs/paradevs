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
#include <common/Trace.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

namespace paradevs { namespace tests { namespace pdevs {

struct SchedulerHandle;

typedef typename paradevs::common::scheduler::HeapScheduler <
    common::DoubleTime, SchedulerHandle >::type SchedulerType;

struct SchedulerHandle
{
    SchedulerHandle()
    { }

    SchedulerHandle(const SchedulerType::handle_type& handle)
        : _handle(handle)
    { }

    const SchedulerHandle& handle() const
    { return *this; }

    void handle(const SchedulerHandle& handle)
    { _handle = handle._handle; }

    SchedulerType::handle_type _handle;
};

template < class SchedulerHandle >
class S1GraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle >
{
public:
    S1GraphManager(common::Coordinator < common::DoubleTime,
                                         SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        SchedulerHandle >(coordinator,
                                                          parameters),
        a("a1", common::NoParameters()), b("b1", common::NoParameters())
    {
        S1GraphManager < SchedulerHandle >::add_child(&a);
        S1GraphManager < SchedulerHandle >::add_child(&b);

        a.add_out_port("out");
        b.add_in_port("in");
        b.add_out_port("out");
        coordinator->add_out_port("out");

        S1GraphManager < SchedulerHandle >::add_link(&a, "out", &b, "in");
        S1GraphManager < SchedulerHandle >::add_link(&b, "out",
                                                     coordinator, "out");
    }

    virtual ~S1GraphManager()
    { }

private:
    paradevs::pdevs::Simulator < common::DoubleTime, A < SchedulerHandle >,
                                 SchedulerHandle > a;
    paradevs::pdevs::Simulator < common::DoubleTime, B < SchedulerHandle >,
                                 SchedulerHandle > b;
};

template < class SchedulerHandle >
class S2GraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle >
{
public:
    S2GraphManager(common::Coordinator < common::DoubleTime,
                                         SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        SchedulerHandle >(coordinator,
                                                          parameters),
        a("a2", common::NoParameters()), b("b2", common::NoParameters())
    {
        S2GraphManager < SchedulerHandle >::add_child(&a);
        S2GraphManager < SchedulerHandle >::add_child(&b);

        a.add_in_port("in");
        a.add_out_port("out");
        b.add_in_port("in");
        coordinator->add_in_port("in");

        S2GraphManager < SchedulerHandle >::add_link(&a, "out", &b, "in");
        S2GraphManager < SchedulerHandle >::add_link(coordinator, "in",
                                                     &a, "in");
    }

    virtual ~S2GraphManager()
    { }

private:
    paradevs::pdevs::Simulator < common::DoubleTime, A < SchedulerHandle >,
                                 SchedulerHandle > a;
    paradevs::pdevs::Simulator < common::DoubleTime, B < SchedulerHandle >,
                                 SchedulerHandle > b;
};

class RootGraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle >
{
public:
    RootGraphManager(
        common::Coordinator < common::DoubleTime,
                              SchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime, SchedulerHandle >(
                                            coordinator, parameters),
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
        common::DoubleTime,
        SchedulerType,
        SchedulerHandle,
        S1GraphManager < SchedulerHandle > > S1;
    paradevs::pdevs::Coordinator <
        common::DoubleTime,
        SchedulerType,
        SchedulerHandle,
        S2GraphManager < SchedulerHandle > > S2;
};

template < class SchedulerHandle >
class OnlyOneGraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle >
{
public:
    OnlyOneGraphManager(common::Coordinator < common::DoubleTime,
                                              SchedulerHandle >* coordinator,
                        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        SchedulerHandle >(coordinator,
                                                          parameters),
        a("a", common::NoParameters())
    {
        OnlyOneGraphManager < SchedulerHandle >::add_child(&a);
    }

    virtual ~OnlyOneGraphManager()
    { }

private:
    paradevs::pdevs::Simulator < common::DoubleTime, A < SchedulerHandle >,
                                 SchedulerHandle > a;
};

template < class SchedulerHandle >
class FlatGraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle >
{
public:
    FlatGraphManager(common::Coordinator < common::DoubleTime,
                                           SchedulerHandle >* coordinator,
                     const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        SchedulerHandle >(coordinator,
                                                          parameters),
        a1("a1", common::NoParameters()), b1("b1", common::NoParameters()),
        a2("a2", common::NoParameters()), b2("b2", common::NoParameters())
    {
        FlatGraphManager < SchedulerHandle >::add_child(&a1);
        FlatGraphManager < SchedulerHandle >::add_child(&b1);
        FlatGraphManager < SchedulerHandle >::add_child(&a2);
        FlatGraphManager < SchedulerHandle >::add_child(&b2);

        a1.add_out_port("out");
        b1.add_in_port("in");
        b1.add_out_port("out");
        a2.add_in_port("in");
        a2.add_out_port("out");
        b2.add_in_port("in");

        FlatGraphManager < SchedulerHandle >::add_link(&a1, "out", &b1, "in");
        FlatGraphManager < SchedulerHandle >::add_link(&b1, "out", &a2, "in");
        FlatGraphManager < SchedulerHandle >::add_link(&a2, "out", &b2, "in");
    }

    virtual ~FlatGraphManager()
    { }

private:
    paradevs::pdevs::Simulator < common::DoubleTime, A < SchedulerHandle >,
                                 SchedulerHandle > a1;
    paradevs::pdevs::Simulator < common::DoubleTime, B < SchedulerHandle >,
                                 SchedulerHandle > b1;
    paradevs::pdevs::Simulator < common::DoubleTime, A < SchedulerHandle >,
                                 SchedulerHandle > a2;
    paradevs::pdevs::Simulator < common::DoubleTime, B < SchedulerHandle >,
                                 SchedulerHandle > b2;
};

} } } // namespace paradevs tests pdevs

#endif
