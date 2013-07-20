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

struct LastBagPolicy
{
    const common::Bag < MyTime >& bag() const
    { return _bag; }

    virtual void operator()(typename MyTime::type /* t */,
                            const common::ExternalEvent < MyTime >& event,
                            typename MyTime::type /* tl */,
                            typename MyTime::type /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag < MyTime > _bag;
};

struct IgnorePolicy
{
    const common::Bag < MyTime >& bag() const
    { return _bag; }

    virtual void operator()(typename MyTime::type /* t */,
                            const common::ExternalEvent < MyTime >& /* event */,
                            typename MyTime::type /* tl */,
                            typename MyTime::type /* tn */)
    { }

private:
    common::Bag < MyTime > _bag;
};

class S1GraphManager :
        public pdevs::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    S1GraphManager(common::Coordinator < MyTime >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters),
        a("a1", NoParameters()), b("b1", NoParameters())
    {
        add_child(&a);
        add_child(&b);
        add_link(&a, "out", &b, "in");
        add_link(&b, "out", coordinator, "out");
    }

    virtual ~S1GraphManager()
    { }

private:
    pdevs::Simulator < MyTime, A1, NoParameters > a;
    pdevs::Simulator < MyTime, B1, NoParameters > b;
};

class S2GraphManager :
        public dtss::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    S2GraphManager(common::Coordinator < MyTime >* coordinator,
                   const paradevs::common::NoParameters& parameters) :
        dtss::GraphManager < MyTime,
                             paradevs::common::NoParameters >(
                                 coordinator, parameters),
        a("a2", 20, NoParameters()), b("b2", 20, NoParameters())
    {
        add_child(&a);
        add_child(&b);
        add_link(&a, "out", &b, "in");
        add_link(coordinator, "in", &a, "in");
    }

    virtual ~S2GraphManager()
    { }

private:
    dtss::Simulator < MyTime, A2, NoParameters > a;
    dtss::Simulator < MyTime, B2, NoParameters > b;
};

class RootGraphManager :
    public pdevs::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    RootGraphManager(common::Coordinator < MyTime >* coordinator,
                     const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
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
    pdevs::Coordinator < MyTime,
                         paradevs::common::scheduler::VectorScheduler <
                             MyTime >,
                         S1GraphManager,
                         paradevs::common::NoParameters,
                         paradevs::common::NoParameters > S1;
    dtss::Coordinator < MyTime,
                        LastBagPolicy,
                        S2GraphManager,
                        paradevs::dtss::Parameters < MyTime >,
                        paradevs::common::NoParameters > S2;
};

template < int size >
class LinearGraphManager :
    public pdevs::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    LinearGraphManager(common::Coordinator < MyTime >* coordinator,
                       const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters)
    {
        for (unsigned int i = 1; i <= size; ++i) {
            std::ostringstream ss;

            ss << "a" << i;
            _models.push_back(
                new pdevs::Simulator < MyTime, Beep, NoParameters >(
                    ss.str(), NoParameters()));
        }
        for (unsigned int i = 0; i < size; ++i) {
            add_child(_models[i]);
        }
        for (unsigned int i = 0; i < size - 1; ++i) {
            add_link(_models[i], "out", _models[i + 1], "in");
        }
    }

    virtual ~LinearGraphManager()
    {
        for (unsigned int i = 0; i < size; ++i) {
            delete _models[i];
        }
    }

private:
    std::vector < pdevs::Simulator < MyTime, Beep, NoParameters >* > _models;
};

class Linear2GraphManager :
    public pdevs::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    Linear2GraphManager(common::Coordinator < MyTime >* coordinator,
                        const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
                              paradevs::common::NoParameters >(
                                  coordinator, parameters)
    {
        for (unsigned int i = 1; i <= 100; ++i) {
            std::ostringstream ss;

            ss << "a" << i;
            _models.push_back(
                new pdevs::Simulator < MyTime, Beep, NoParameters >(
                    ss.str(), NoParameters()));
        }
        for (unsigned int i = 0; i < 100; ++i) {
            add_child(_models[i]);
        }
        for (unsigned int i = 0; i < 99; ++i) {
            add_link(_models[i], "out", _models[i + 1], "in");
        }
        add_link(coordinator, "in", _models[0], "in");
        add_link(_models[49], "out", coordinator, "out");
    }

    virtual ~Linear2GraphManager()
    {
        for (unsigned int i = 0; i < 100; ++i) {
            delete _models[i];
        }
    }

private:
    std::vector < pdevs::Simulator < MyTime, Beep, NoParameters >* > _models;
};

class Root2GraphManager :
    public pdevs::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    Root2GraphManager(common::Coordinator < MyTime >* coordinator,
                      const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
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
    pdevs::Coordinator < MyTime,
                         paradevs::common::scheduler::HeapScheduler <
                             MyTime >,
                         Linear2GraphManager,
                         paradevs::common::NoParameters,
                         paradevs::common::NoParameters > S1;
    pdevs::Coordinator < MyTime,
                         paradevs::common::scheduler::HeapScheduler <
                             MyTime >,
                         Linear2GraphManager,
                         paradevs::common::NoParameters,
                         paradevs::common::NoParameters > S2;
};

class Root3GraphManager :
    public pdevs::GraphManager < MyTime, paradevs::common::NoParameters >
{
public:
    Root3GraphManager(common::Coordinator < MyTime >* coordinator,
                      const paradevs::common::NoParameters& parameters) :
        pdevs::GraphManager < MyTime,
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
    pdevs::Coordinator < MyTime,
                         paradevs::common::scheduler::VectorScheduler <
                             MyTime >,
                         Linear2GraphManager,
                         paradevs::common::NoParameters,
                         paradevs::common::NoParameters > S1;
    pdevs::Coordinator < MyTime,
                         paradevs::common::scheduler::VectorScheduler <
                             MyTime >,
                         Linear2GraphManager,
                         paradevs::common::NoParameters,
                         paradevs::common::NoParameters > S2;
};

} } } // namespace paradevs tests mixed

#endif
