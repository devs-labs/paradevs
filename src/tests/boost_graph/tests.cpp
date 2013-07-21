/**
 * @file tests/boost_graph/tests.cpp
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

#include <common/RootCoordinator.hpp>

#include <tests/boost_graph/models.hpp>
#include <tests/boost_graph/graph_manager.hpp>

using namespace paradevs::common;
using namespace paradevs::common::scheduler;
using namespace paradevs::pdevs;
using namespace paradevs::tests::boost_graph;

void flat_test()
{
    RootCoordinator < MyTime, paradevs::pdevs::Coordinator <
        MyTime, VectorScheduler < MyTime >, InBuildFlatGraphManager <
            FlatGraphBuilder >, paradevs::common::NoParameters,
        paradevs::common::NoParameters >
    > rc(0, 100, "root", NoParameters(), NoParameters());

    rc.run();
}

void hierarchical_test()
{
    RootCoordinator < MyTime, paradevs::pdevs::Coordinator <
        MyTime, VectorScheduler < MyTime >, HierarchicalGraphManager <
            HierarchicalGraphBuilder >, paradevs::common::NoParameters,
        paradevs::common::NoParameters > > rc(0, 100, "root",
                                              NoParameters(), NoParameters());

    rc.run();
}

int main()
{
    // flat_test();
    hierarchical_test();
    return 0;
}
