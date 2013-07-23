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
#include <common/Trace.hpp>

#include <dtss/Coordinator.hpp>
#include <dtss/GraphManager.hpp>
#include <dtss/Simulator.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

#include <tests/mixed/models.hpp>

namespace paradevs { namespace tests { namespace mixed {

struct SchedulerHandle;

typedef typename paradevs::common::scheduler::HeapScheduler <
    MyTime, SchedulerHandle >::type SchedulerType;

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
    const common::Bag < MyTime, SchedulerHandle >& bag() const
    { return _bag; }

    virtual void operator()(
        typename MyTime::type /* t */,
        const common::ExternalEvent < MyTime, SchedulerHandle >& event,
        typename MyTime::type /* tl */,
        typename MyTime::type /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag < MyTime, SchedulerHandle > _bag;
};

template < class SchedulerHandle >
struct IgnorePolicy
{
    const common::Bag < MyTime, SchedulerHandle >& bag() const
    { return _bag; }

    virtual void operator()(
        typename MyTime::type /* t */,
        const common::ExternalEvent < MyTime, SchedulerHandle >& /* event */,
        typename MyTime::type /* tl */,
        typename MyTime::type /* tn */)
    { }

private:
    common::Bag < MyTime, SchedulerHandle > _bag;
};

template < class SchedulerHandle >
class S1GraphManager :
        public pdevs::GraphManager < MyTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    S1GraphManager(common::Coordinator < MyTime, SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime, SchedulerHandle,
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
    pdevs::Simulator < MyTime, A1 < SchedulerHandle >, SchedulerHandle,
                       paradevs::common::NoParameters > a;
    pdevs::Simulator < MyTime, B1 < SchedulerHandle >, SchedulerHandle,
                       paradevs::common::NoParameters > b;
};

template < class SchedulerHandle >
class S2GraphManager : public dtss::GraphManager < MyTime, SchedulerHandle >
{
public:
    S2GraphManager(common::Coordinator < MyTime, SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        dtss::GraphManager < MyTime, SchedulerHandle >(coordinator, parameters),
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
    dtss::Simulator < MyTime, A2 < SchedulerHandle >, SchedulerHandle > a;
    dtss::Simulator < MyTime, B2 < SchedulerHandle >, SchedulerHandle > b;
};

class RootGraphManager :
        public pdevs::GraphManager < MyTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    RootGraphManager(common::Coordinator < MyTime,
                                           SchedulerHandle >* coordinator,
                     const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters),
        S1("S1", paradevs::common::NoParameters(),
           paradevs::common::NoParameters()),
        S2("S2", paradevs::dtss::Parameters < MyTime >(20),
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
        MyTime,
        SchedulerType,
        SchedulerHandle,
        S1GraphManager < SchedulerHandle > > S1;
    paradevs::dtss::Coordinator <
        MyTime,
        LastBagPolicy < SchedulerHandle >,
        S2GraphManager < SchedulerHandle >,
        SchedulerHandle,
        paradevs::dtss::Parameters < MyTime > > S2;
};

template < int size, class SchedulerHandle >
class LinearGraphManager :
        public pdevs::GraphManager < MyTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    LinearGraphManager(common::Coordinator < MyTime,
                                             SchedulerHandle >* coordinator,
                       const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters)
    {
        for (unsigned int i = 1; i <= size; ++i) {
            std::ostringstream ss;

            ss << "a" << i;
            _models.push_back(
                new pdevs::Simulator < MyTime, Beep < SchedulerHandle >,
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
    pdevs::Simulator < MyTime, Beep < SchedulerHandle >, SchedulerHandle,
                       paradevs::common::NoParameters >* > _models;
};

template < class SchedulerHandle >
class Linear2GraphManager :
        public pdevs::GraphManager < MyTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    Linear2GraphManager(common::Coordinator < MyTime,
                                              SchedulerHandle >* coordinator,
                        const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime, SchedulerHandle,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters)
    {
        for (unsigned int i = 1; i <= 100; ++i) {
            std::ostringstream ss;

            ss << "a" << i;
            _models.push_back(
                new pdevs::Simulator < MyTime,
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
        pdevs::Simulator < MyTime, Beep < SchedulerHandle >,
                           SchedulerHandle,
                           paradevs::common::NoParameters >* > _models;
};

class Root2GraphManager :
        public pdevs::GraphManager < MyTime, SchedulerHandle,
                                     paradevs::common::NoParameters >
{
public:
    Root2GraphManager(common::Coordinator < MyTime,
                                            SchedulerHandle >* coordinator,
                      const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime, SchedulerHandle,
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
        MyTime,
        SchedulerType,
        SchedulerHandle,
        Linear2GraphManager < SchedulerHandle > > S1;
    paradevs::pdevs::Coordinator <
        MyTime,
        SchedulerType,
        SchedulerHandle,
        Linear2GraphManager < SchedulerHandle > > S2;
};

class Root3GraphManager :
        public pdevs::GraphManager <
            MyTime,
            paradevs::common::scheduler::NoSchedulerHandle,
            paradevs::common::NoParameters >
{
public:
    Root3GraphManager(
        common::Coordinator <
            MyTime,
            paradevs::common::scheduler::NoSchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
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
        MyTime,
        paradevs::common::scheduler::VectorScheduler < MyTime >,
        paradevs::common::scheduler::NoSchedulerHandle,
        Linear2GraphManager < paradevs::common::scheduler::NoSchedulerHandle >
    > S1;
    pdevs::Coordinator <
        MyTime,
        paradevs::common::scheduler::VectorScheduler < MyTime >,
        paradevs::common::scheduler::NoSchedulerHandle,
        Linear2GraphManager < paradevs::common::scheduler::NoSchedulerHandle >
    > S2;
};

} } } // namespace paradevs tests mixed

#endif
