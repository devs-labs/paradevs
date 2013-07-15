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

#include <common/RootCoordinator.hpp>
#include <common/scheduler/VectorScheduler.hpp>
#include <common/scheduler/HeapScheduler.hpp>

#include <tests/mixed_tests.hpp>

void run_with_heap()
{
    paradevs::common::RootCoordinator <
        paradevs::MyTime, paradevs::pdevs::Coordinator <
            paradevs::MyTime,
            paradevs::common::scheduler::HeapScheduler < paradevs::MyTime >,
            paradevs::RootGraphManager >
        > rc(0, 10000, "root", paradevs::pdevs::Parameters());

    paradevs::common::Trace < paradevs::MyTime >::trace().clear();
    rc.run();
}

void run_with_vector()
{
    paradevs::common::RootCoordinator <
        paradevs::MyTime, paradevs::pdevs::Coordinator <
            paradevs::MyTime,
            paradevs::common::scheduler::VectorScheduler < paradevs::MyTime >,
            paradevs::RootGraphManager >
        > rc(0, 10000, "root", paradevs::pdevs::Parameters());

    paradevs::common::Trace < paradevs::MyTime >::trace().clear();
    rc.run();
}

int main()
{
    std::cout << "run_with_heap ..." << std::endl;
    run_with_heap();
    std::cout << "... OK" << std::endl;
    std::cout << "run_with_vector ..." << std::endl;
    run_with_vector();
    std::cout << "... OK" << std::endl;
    return 0;
}
