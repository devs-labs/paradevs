/**
 * @file tests/multithreading/graph_manager.cpp
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

#ifndef TESTS_PDEVS_MULTITHREADING_GRAPH_MANAGER_HPP
#define TESTS_PDEVS_MULTITHREADING_GRAPH_MANAGER_HPP 1

#include <tests/pdevs/models.hpp>
#include <tests/pdevs/graph_manager.hpp>

#include <kernel/pdevs/multithreading/Coordinator.hpp>
#include <kernel/pdevs/GraphManager.hpp>
#include <kernel/pdevs/Simulator.hpp>

namespace paradevs { namespace tests { namespace multithreading {

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

    void init()
    { }

    void start(common::DoubleTime::type /* t */)
    { }

    void transition(
        const common::Models < common::DoubleTime,
                               pdevs::SchedulerHandle >& /* receivers */,
        common::DoubleTime::type /* t */)
    { }

    virtual ~S1GraphManager()
    { }

private:
    paradevs::pdevs::Simulator < common::DoubleTime,
                                 pdevs::A < SchedulerHandle >,
                                 SchedulerHandle > a;
    paradevs::pdevs::Simulator < common::DoubleTime,
                                 pdevs::B < SchedulerHandle >,
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

    void init()
    { }

    void start(common::DoubleTime::type /* t */)
    { }

    void transition(
        const common::Models < common::DoubleTime,
                               pdevs::SchedulerHandle >& /* receivers */,
        common::DoubleTime::type /* t */)
    { }

    virtual ~S2GraphManager()
    { }

private:
    paradevs::pdevs::Simulator < common::DoubleTime,
                                 pdevs::A < SchedulerHandle >,
                                 SchedulerHandle > a;
    paradevs::pdevs::Simulator < common::DoubleTime,
                                 pdevs::B < SchedulerHandle >,
                                 SchedulerHandle > b;
};

class RootGraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               pdevs::SchedulerHandle >
{
public:
    RootGraphManager(
        common::Coordinator < common::DoubleTime,
                              pdevs::SchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        pdevs::SchedulerHandle >(
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

    void init()
    {
        S1.set_sender(
            dynamic_cast < paradevs::pdevs::multithreading::Coordinator <
                common::DoubleTime,
                paradevs::common::scheduler::HeapScheduler <
                    common::DoubleTime, pdevs::SchedulerHandle >,
                pdevs::SchedulerHandle,
                paradevs::tests::multithreading::RootGraphManager >*
            >(get_coordinator())->get_sender());
        S2.set_sender(
            dynamic_cast < paradevs::pdevs::multithreading::Coordinator <
                common::DoubleTime,
                paradevs::common::scheduler::HeapScheduler <
                    common::DoubleTime, pdevs::SchedulerHandle >,
                pdevs::SchedulerHandle,
                paradevs::tests::multithreading::RootGraphManager >*
            >(get_coordinator())->get_sender());
    }

    void start(common::DoubleTime::type t)
    {
        S1.get_sender().send(
            paradevs::pdevs::multithreading::start_message <
                common::DoubleTime >(t));
        S2.get_sender().send(
            paradevs::pdevs::multithreading::start_message <
                common::DoubleTime >(t));
    }

    void transition(const common::Models < common::DoubleTime,
                                           pdevs::SchedulerHandle >& receivers,
                    common::DoubleTime::type t)
    {
        if (std::find(receivers.begin(), receivers.end(),
                      &S1) != receivers.end()) {
            S1.get_sender().send(
                paradevs::pdevs::multithreading::transition_message <
                    common::DoubleTime >(t));
        }
        if (std::find(receivers.begin(), receivers.end(),
                      &S2) != receivers.end()) {
            S2.get_sender().send(
                paradevs::pdevs::multithreading::transition_message <
                    common::DoubleTime >(t));
        }
    }

    virtual ~RootGraphManager()
    { }

private:
    paradevs::pdevs::multithreading::Coordinator <
        common::DoubleTime,
        pdevs::SchedulerType,
        pdevs::SchedulerHandle,
        S1GraphManager < pdevs::SchedulerHandle > > S1;
    paradevs::pdevs::multithreading::Coordinator <
        common::DoubleTime,
        pdevs::SchedulerType,
        pdevs::SchedulerHandle,
        S2GraphManager < pdevs::SchedulerHandle > > S2;
};

template < class SchedulerHandle >
class S3GraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle >
{
public:
    S3GraphManager(common::Coordinator < common::DoubleTime,
                                         SchedulerHandle >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        SchedulerHandle >(coordinator,
                                                          parameters)
    {
        coordinator->add_out_port("out");
        for (unsigned int i = 0; i < 10; ++i) {
            std::ostringstream ss;
            simulator_type* s = new simulator_type(ss.str(),
                                                   common::NoParameters());

            ss << "a" << (i + 1);
            _simulators.push_back(s);
            S3GraphManager < SchedulerHandle >::add_child(s);
            s->add_out_port("out");
        }
    }

    void init()
    { }

    void start(common::DoubleTime::type /* t */)
    { }

    void transition(
        const common::Models < common::DoubleTime,
                               pdevs::SchedulerHandle >& /* receivers */,
        common::DoubleTime::type /* t */)
    { }

    virtual ~S3GraphManager()
    {
        for (typename std::vector < simulator_type* >::const_iterator it =
                 _simulators.begin(); it != _simulators.end(); ++it) {
            delete *it;
        }
    }

private:
    typedef paradevs::pdevs::Simulator < common::DoubleTime,
                                         pdevs::A < SchedulerHandle >,
                                         SchedulerHandle > simulator_type;

    std::vector < simulator_type* > _simulators;
};

class Root2GraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               pdevs::SchedulerHandle >
{
public:
    Root2GraphManager(
        common::Coordinator < common::DoubleTime,
                              pdevs::SchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        pdevs::SchedulerHandle >(
                                            coordinator, parameters),
        S1("S1", paradevs::common::NoParameters(),
           paradevs::common::NoParameters()),
        S2("S2", paradevs::common::NoParameters(),
           paradevs::common::NoParameters())
    {
        add_child(&S1);
        add_child(&S2);
    }

    void init()
    {
        S1.set_sender(
            dynamic_cast < paradevs::pdevs::multithreading::Coordinator <
                common::DoubleTime,
                paradevs::common::scheduler::HeapScheduler <
                    common::DoubleTime, pdevs::SchedulerHandle >,
                pdevs::SchedulerHandle,
                paradevs::tests::multithreading::Root2GraphManager >*
            >(get_coordinator())->get_sender());
        S2.set_sender(
            dynamic_cast < paradevs::pdevs::multithreading::Coordinator <
                common::DoubleTime,
                paradevs::common::scheduler::HeapScheduler <
                    common::DoubleTime, pdevs::SchedulerHandle >,
                pdevs::SchedulerHandle,
                paradevs::tests::multithreading::Root2GraphManager >*
            >(get_coordinator())->get_sender());
    }

    void start(common::DoubleTime::type t)
    {
        S1.get_sender().send(
            paradevs::pdevs::multithreading::start_message <
                common::DoubleTime >(t));
        S2.get_sender().send(
            paradevs::pdevs::multithreading::start_message <
                common::DoubleTime >(t));
    }

    void transition(const common::Models < common::DoubleTime,
                                           pdevs::SchedulerHandle >& receivers,
                    common::DoubleTime::type t)
    {
        if (std::find(receivers.begin(), receivers.end(),
                      &S1) != receivers.end()) {
            S1.get_sender().send(
                paradevs::pdevs::multithreading::transition_message <
                    common::DoubleTime >(t));
        }
        if (std::find(receivers.begin(), receivers.end(),
                      &S2) != receivers.end()) {
            S2.get_sender().send(
                paradevs::pdevs::multithreading::transition_message <
                    common::DoubleTime >(t));
        }
    }

    virtual ~Root2GraphManager()
    { }

private:
    paradevs::pdevs::multithreading::Coordinator <
        common::DoubleTime,
        pdevs::SchedulerType,
        pdevs::SchedulerHandle,
        S3GraphManager < pdevs::SchedulerHandle > > S1;
    paradevs::pdevs::multithreading::Coordinator <
        common::DoubleTime,
        pdevs::SchedulerType,
        pdevs::SchedulerHandle,
        S3GraphManager < pdevs::SchedulerHandle > > S2;
};

class Root3GraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               pdevs::SchedulerHandle >
{
public:
    Root3GraphManager(
        common::Coordinator < common::DoubleTime,
                              pdevs::SchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime,
                                        pdevs::SchedulerHandle >(
                                            coordinator, parameters),
        S1("S1", paradevs::common::NoParameters(),
           paradevs::common::NoParameters()),
        S2("S2", paradevs::common::NoParameters(),
           paradevs::common::NoParameters())
    {
        add_child(&S1);
        add_child(&S2);
    }

    virtual ~Root3GraphManager()
    { }

private:
    paradevs::pdevs::Coordinator <
        common::DoubleTime,
        pdevs::SchedulerType,
        pdevs::SchedulerHandle,
        S3GraphManager < pdevs::SchedulerHandle > > S1;
    paradevs::pdevs::Coordinator <
        common::DoubleTime,
        pdevs::SchedulerType,
        pdevs::SchedulerHandle,
        S3GraphManager < pdevs::SchedulerHandle > > S2;
};

} } } // namespace paradevs tests multithreading

#endif
