/**
 * @file tests/dtss/graph_manager.hpp
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

#ifndef TESTS_DTSS_GRAPH_MANAGER_HPP
#define TESTS_DTSS_GRAPH_MANAGER_HPP 1

#include <dtss/Coordinator.hpp>
#include <dtss/GraphManager.hpp>
#include <dtss/Simulator.hpp>

#include <tests/dtss/models.hpp>

namespace paradevs { namespace tests { namespace dtss {

struct Policy
{
    const common::Bag < MyTime >& bag() const
    { return _bag; }

    virtual void operator()(MyTime::type /* t */,
                            const common::ExternalEvent < MyTime >& event,
                            MyTime::type /* tl */,
                            MyTime::type /* tn */)
    {
        _bag.clear();
        _bag.push_back(event);
    }

private:
    common::Bag < MyTime > _bag;
};

class OnlyOneGraphManager :
        public paradevs::dtss::GraphManager < MyTime,
                                              paradevs::common::NoParameters >
{
public:
    OnlyOneGraphManager(common::Coordinator < MyTime >* coordinator,
                        const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::GraphManager < MyTime,
                                       paradevs::common::NoParameters >(
                                           coordinator, parameters),
        a("a", 1, NoParameters())
    {
        add_child(&a);
    }

    virtual ~OnlyOneGraphManager()
    { }

private:
    paradevs::dtss::Simulator < MyTime, A, NoParameters > a;
};

class TwoGraphManager :
        public paradevs::dtss::GraphManager < MyTime,
                                              paradevs::common::NoParameters >
{
public:
    TwoGraphManager(common::Coordinator < MyTime >* coordinator,
                    const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::GraphManager < MyTime,
                                       paradevs::common::NoParameters >(
                                           coordinator, parameters),
        a("a", 1, NoParameters()), b("b", 1, NoParameters())
    {
        add_child(&a);
        add_child(&b);
        add_link(&a, "out", &b, "in");
    }

    virtual ~TwoGraphManager()
    { }

private:
    paradevs::dtss::Simulator < MyTime, A, NoParameters > a;
    paradevs::dtss::Simulator < MyTime, B, NoParameters > b;
};

} } } // namespace paradevs tests dtss

#endif
