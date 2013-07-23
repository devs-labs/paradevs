/**
 * @file tests/mixed/graph_manager.hpp
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

#ifndef TESTS_MIXED_GRAPH_MANAGER_HPP
#define TESTS_MIXED_GRAPH_MANAGER_HPP 1

#include <common/scheduler/VectorScheduler.hpp>
#include <common/scheduler/HeapScheduler.hpp>

#include <kernel/dtss/Coordinator.hpp>
#include <kernel/dtss/GraphManager.hpp>
#include <kernel/dtss/Simulator.hpp>

#include <kernel/pdevs/Coordinator.hpp>
#include <kernel/pdevs/GraphManager.hpp>
#include <kernel/pdevs/Simulator.hpp>

#include <tests/mixed/models.hpp>

namespace paradevs { namespace tests { namespace mixed {

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
struct LastBagPolicy
{
    const common::Bag < common::DoubleTime, SchedulerHandle >& bag() const
    { return _bag; }

    virtual void operator()(
        typename common::DoubleTime::type /* t */,
        const common::ExternalEvent < common::DoubleTime,
                                      SchedulerHandle >& event,
        typename common::DoubleTime::type /* tl */,
        typename common::DoubleTime::type /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag < common::DoubleTime, SchedulerHandle > _bag;
};

template < class SchedulerHandle >
struct IgnorePolicy
{
    const common::Bag < common::DoubleTime, SchedulerHandle >& bag() const
    { return _bag; }

    virtual void operator()(
        typename common::DoubleTime::type /* t */,
        const common::ExternalEvent < common::DoubleTime,
                                      SchedulerHandle >& /* event */,
        typename common::DoubleTime::type /* tl */,
        typename common::DoubleTime::type /* tn */)
    { }

private:
    common::Bag < common::DoubleTime, SchedulerHandle > _bag;
};

template < class SchedulerHandle >
class S1GraphManager :
        public pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    S1GraphManager(common::Coordinator < common::DoubleTime,
                                         SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters),
        a("a1", paradevs::common::NoParameters()),
        b("b1", paradevs::common::NoParameters())
    {
        S1GraphManager < SchedulerHandle >::add_child(&a);
        S1GraphManager < SchedulerHandle >::add_child(&b);

        a.add_out_port("out");
        b.add_in_port("in");
        b.add_out_port("out");
        coordinator->add_out_port("out");

        S1GraphManager < SchedulerHandle >::add_link(&a, "out",
                                                     &b, "in");
        S1GraphManager < SchedulerHandle >::add_link(&b, "out",
                                                     coordinator, "out");
    }

    virtual ~S1GraphManager()
    { }

private:
    pdevs::Simulator < common::DoubleTime,
                       A1 < SchedulerHandle >,
                       SchedulerHandle,
                       paradevs::common::NoParameters > a;
    pdevs::Simulator < common::DoubleTime,
                       B1 < SchedulerHandle >,
                       SchedulerHandle,
                       paradevs::common::NoParameters > b;
};

template < class SchedulerHandle >
class S2GraphManager :
        public dtss::GraphManager < common::DoubleTime, SchedulerHandle >
{
public:
    S2GraphManager(common::Coordinator < common::DoubleTime,
                                         SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        dtss::GraphManager < common::DoubleTime,
                             SchedulerHandle >(coordinator, parameters),
        a("a2", 20, paradevs::common::NoParameters()),
        b("b2", 20, paradevs::common::NoParameters())
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
    dtss::Simulator < common::DoubleTime,
                      A2 < SchedulerHandle >,
                      SchedulerHandle > a;
    dtss::Simulator < common::DoubleTime,
                      B2 < SchedulerHandle >,
                      SchedulerHandle > b;
};

class RootGraphManager :
        public pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    RootGraphManager(common::Coordinator < common::DoubleTime,
                                           SchedulerHandle >* coordinator,
                     const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters),
        S1("S1", paradevs::common::NoParameters(),
           paradevs::common::NoParameters()),
        S2("S2", paradevs::dtss::Parameters < common::DoubleTime >(20),
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
    paradevs::dtss::Coordinator <
        common::DoubleTime,
        LastBagPolicy < SchedulerHandle >,
        S2GraphManager < SchedulerHandle >,
        SchedulerHandle,
        paradevs::dtss::Parameters < common::DoubleTime > > S2;
};

template < int size, class SchedulerHandle >
class LinearGraphManager :
        public pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    LinearGraphManager(common::Coordinator < common::DoubleTime,
                                             SchedulerHandle >* coordinator,
                       const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters)
    {
        for (unsigned int i = 1; i <= size; ++i) {
            std::ostringstream ss;

            ss << "a" << i;
            _models.push_back(
                new pdevs::Simulator < common::DoubleTime,
                                       Beep < SchedulerHandle >,
                                       SchedulerHandle,
                                       paradevs::common::NoParameters >(
                                           ss.str(),
                                           paradevs::common::NoParameters()));
        }
        for (unsigned int i = 0; i < size; ++i) {
            LinearGraphManager < size, SchedulerHandle >::add_child(_models[i]);

            _models[i]->add_in_port("in");
            _models[i]->add_out_port("out");
        }
        for (unsigned int i = 0; i < size - 1; ++i) {
            LinearGraphManager < size,
                                 SchedulerHandle >::add_link(_models[i],
                                                             "out",
                                                             _models[i + 1],
                                                             "in");
        }
    }

    virtual ~LinearGraphManager()
    {
        for (unsigned int i = 0; i < size; ++i) {
            delete _models[i];
        }
    }

private:
    std::vector <
    pdevs::Simulator < common::DoubleTime,
                       Beep < SchedulerHandle >,
                       SchedulerHandle,
                       paradevs::common::NoParameters >* > _models;
};

template < class SchedulerHandle >
class Linear2GraphManager :
        public pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    Linear2GraphManager(common::Coordinator < common::DoubleTime,
                                              SchedulerHandle >* coordinator,
                        const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters)
    {
        for (unsigned int i = 1; i <= 100; ++i) {
            std::ostringstream ss;

            ss << "a" << i;
            _models.push_back(
                new pdevs::Simulator < common::DoubleTime,
                                       Beep < SchedulerHandle >,
                                       SchedulerHandle,
                                       paradevs::common::NoParameters >(
                                           ss.str(),
                                           paradevs::common::NoParameters()));
        }
        for (unsigned int i = 0; i < 100; ++i) {
            Linear2GraphManager < SchedulerHandle >::add_child(_models[i]);

            _models[i]->add_in_port("in");
            _models[i]->add_out_port("out");
        }
        for (unsigned int i = 0; i < 99; ++i) {
            Linear2GraphManager < SchedulerHandle >::add_link(_models[i], "out",
                                                              _models[i + 1],
                                                              "in");
        }

        coordinator->add_in_port("in");
        coordinator->add_out_port("out");

        Linear2GraphManager < SchedulerHandle >::add_link(coordinator, "in",
                                                          _models[0], "in");
        Linear2GraphManager < SchedulerHandle >::add_link(_models[49], "out",
                                                          coordinator, "out");
    }

    virtual ~Linear2GraphManager()
    {
        for (unsigned int i = 0; i < 100; ++i) {
            delete _models[i];
        }
    }

private:
    std::vector <
        pdevs::Simulator < common::DoubleTime, Beep < SchedulerHandle >,
                           SchedulerHandle,
                           paradevs::common::NoParameters >* > _models;
};

class Root2GraphManager :
        public pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    Root2GraphManager(common::Coordinator < common::DoubleTime,
                                            SchedulerHandle >* coordinator,
                      const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
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

    virtual ~Root2GraphManager()
    { }

private:
    paradevs::pdevs::Coordinator <
        common::DoubleTime,
        SchedulerType,
        SchedulerHandle,
        Linear2GraphManager < SchedulerHandle > > S1;
    paradevs::pdevs::Coordinator <
        common::DoubleTime,
        SchedulerType,
        SchedulerHandle,
        Linear2GraphManager < SchedulerHandle > > S2;
};

class Root3GraphManager :
        public pdevs::GraphManager <
            common::DoubleTime,
            paradevs::common::scheduler::NoSchedulerHandle,
            paradevs::common::NoParameters >
{
public:
    Root3GraphManager(
        common::Coordinator <
            common::DoubleTime,
            paradevs::common::scheduler::NoSchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < common::DoubleTime,
                              paradevs::common::scheduler::NoSchedulerHandle,
                              paradevs::common::NoParameters >(
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

    virtual ~Root3GraphManager()
    { }

private:
    pdevs::Coordinator <
        common::DoubleTime,
        paradevs::common::scheduler::VectorScheduler < common::DoubleTime >,
        paradevs::common::scheduler::NoSchedulerHandle,
        Linear2GraphManager < paradevs::common::scheduler::NoSchedulerHandle >
    > S1;
    pdevs::Coordinator <
        common::DoubleTime,
        paradevs::common::scheduler::VectorScheduler < common::DoubleTime >,
        paradevs::common::scheduler::NoSchedulerHandle,
        Linear2GraphManager < paradevs::common::scheduler::NoSchedulerHandle >
    > S2;
};

} } } // namespace paradevs tests mixed

#endif
