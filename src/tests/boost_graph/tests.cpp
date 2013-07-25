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

#include <boost/timer.hpp>

#include <common/RootCoordinator.hpp>

#include <tests/boost_graph/models.hpp>
#include <tests/boost_graph/graph_builder.hpp>
#include <tests/boost_graph/graph_manager.hpp>
#include <tests/boost_graph/graph_partitioning.hpp>

using namespace paradevs::common;
using namespace paradevs::common::scheduler;
using namespace paradevs::pdevs;
using namespace paradevs::tests::boost_graph;

void flat_test()
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            SchedulerType,
            SchedulerHandle,
            InBuildFlatGraphManager <
                SchedulerHandle,
                FlatGraphBuilder >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
    > rc(0, 100000, "root", NoParameters(), NoParameters());

    rc.run();
}

void hierarchical_test()
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            SchedulerType,
            SchedulerHandle,
            HierarchicalGraphManager <
                SchedulerHandle,
                HierarchicalGraphBuilder >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
        > rc(0, 100, "root", NoParameters(), NoParameters());

    rc.run();
}

void partitionning_test()
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            SchedulerType,
            SchedulerHandle,
            HierarchicalGraphManager <
                SchedulerHandle,
                PartitioningGraphBuilder >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
        > rc(0, 100000, "root", NoParameters(), NoParameters());

    rc.run();
}

int main()
{
    boost::timer t;

    std::cout << "flat graph ..." << std::endl;
    flat_test();

    double t2 = t.elapsed();

    std::cout << "... OK -> " << t2 << std::endl;

    // hierarchical_test();

    std::cout << "partitioning graph ..." << std::endl;
    partitionning_test();

    double t3 = t.elapsed();

    std::cout << "... OK -> " << (t3 - t2) << std::endl;
    return 0;
}
