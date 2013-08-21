/**
 * @file tests/multithreading/tests.cpp
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

#include <tests/multithreading/graph_manager.hpp>
#include <tests/pdevs/graph_manager.hpp>

#include <common/RootCoordinator.hpp>

#include <chrono>

#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>

using namespace paradevs::tests::pdevs;
using namespace paradevs::tests::multithreading;
using namespace paradevs::common;
using namespace std::chrono;

TEST_CASE("pdevs/multithreading/hierachical", "run")
{
    steady_clock::time_point t1 = steady_clock::now();

    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::multithreading::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            paradevs::tests::multithreading::RootGraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    rc.run();

    steady_clock::time_point t2 = steady_clock::now();

    duration < double > time_span = duration_cast <
        duration < double > >(t2 - t1);

    std::cout << "multithreading/dependant -> " << time_span.count()
              << std::endl;
}

TEST_CASE("pdevs/classic/hierachical", "run")
{
    steady_clock::time_point t1 = steady_clock::now();

    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            paradevs::tests::pdevs::RootGraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    rc.run();

    steady_clock::time_point t2 = steady_clock::now();

    duration < double > time_span = duration_cast <
        duration < double > >(t2 - t1);

    std::cout << "classic/dependant -> " << time_span.count() << std::endl;
}

TEST_CASE("pdevs/multithreading/independant", "run")
{
    steady_clock::time_point t1 = steady_clock::now();

    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::multithreading::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            paradevs::tests::multithreading::Root2GraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    rc.run();

    steady_clock::time_point t2 = steady_clock::now();

    duration < double > time_span = duration_cast <
        duration < double > >(t2 - t1);

    std::cout << "multithreading/independant -> " << time_span.count()
              << std::endl;
}

TEST_CASE("pdevs/classic/independant", "run")
{
    steady_clock::time_point t1 = steady_clock::now();

    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            paradevs::tests::multithreading::Root3GraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    rc.run();

    steady_clock::time_point t2 = steady_clock::now();

    duration < double > time_span = duration_cast <
        duration < double > >(t2 - t1);

    std::cout << "classic/independant -> " << time_span.count() << std::endl;
}

