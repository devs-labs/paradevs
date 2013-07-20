/**
 * @file main.cpp
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
#include <common/scheduler/VectorScheduler.hpp>
#include <common/scheduler/HeapScheduler.hpp>

#include <pdevs/Coordinator.hpp>

#include <tests/mixed/models.hpp>
#include <tests/mixed/graph_manager.hpp>

using namespace paradevs::tests::mixed;

template < int size >
void run_flat_with_heap()
{
    boost::timer t;

    std::cout << "run_flat_with_heap [" << size << "] ..." << std::endl;

    paradevs::common::RootCoordinator <
        MyTime, paradevs::pdevs::Coordinator <
            MyTime,
            paradevs::common::scheduler::HeapScheduler < MyTime >,
            LinearGraphManager < size >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < MyTime >::trace().clear();
    rc.run();

    std::cout << "... OK -> " << t.elapsed() << std::endl;
}

template < int size >
void run_flat_with_vector()
{
    boost::timer t;

    std::cout << "run_flat_with_vector [" << size << "] ..." << std::endl;

    paradevs::common::RootCoordinator <
        MyTime, paradevs::pdevs::Coordinator <
            MyTime,
            paradevs::common::scheduler::VectorScheduler < MyTime >,
            LinearGraphManager < size >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < MyTime >::trace().clear();
    rc.run();

    std::cout << "... OK -> " << t.elapsed() << std::endl;
}

void run_hierarchic_with_heap()
{
    paradevs::common::RootCoordinator <
        MyTime, paradevs::pdevs::Coordinator <
            MyTime,
            paradevs::common::scheduler::HeapScheduler < MyTime >,
            Root2GraphManager,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < MyTime >::trace().clear();
    rc.run();
}

void run_hierarchic_with_vector()
{
    paradevs::common::RootCoordinator <
        MyTime, paradevs::pdevs::Coordinator <
            MyTime,
            paradevs::common::scheduler::VectorScheduler < MyTime >,
            Root3GraphManager,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < MyTime >::trace().clear();
    rc.run();
}

int main()
{
    boost::timer t;

    srand(108364);

    run_flat_with_heap < 10 >();
    run_flat_with_heap < 20 >();
    run_flat_with_heap < 30 >();
    run_flat_with_heap < 40 >();
    run_flat_with_heap < 50 >();
    run_flat_with_heap < 60 >();
    run_flat_with_heap < 70 >();
    run_flat_with_heap < 80 >();
    run_flat_with_heap < 90 >();
    run_flat_with_heap < 100 >();
    run_flat_with_heap < 200 >();

    run_flat_with_vector < 10 >();
    run_flat_with_vector < 20 >();
    run_flat_with_vector < 30 >();
    run_flat_with_vector < 40 >();
    run_flat_with_vector < 50 >();
    run_flat_with_vector < 60 >();
    run_flat_with_vector < 70 >();
    run_flat_with_vector < 80 >();
    run_flat_with_vector < 90 >();
    run_flat_with_vector < 100 >();
    run_flat_with_vector < 200 >();

    double t2 = t.elapsed();

    std::cout << "run_hierarchic_with_heap ..." << std::endl;
    run_hierarchic_with_heap();

    double t3 = t.elapsed();

    std::cout << "... OK -> " << (t3 - t2) << std::endl;
    std::cout << "run_hierarchic_with_vector ..." << std::endl;
    run_hierarchic_with_vector();

    double t4 = t.elapsed();

    std::cout << "... OK -> "  << (t4 - t3) << std::endl;
    return 0;
}
