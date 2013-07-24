/**
 * @file app/main.cpp
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

#include <kernel/pdevs/Coordinator.hpp>

#include <tests/mixed/models.hpp>
#include <tests/mixed/graph_manager.hpp>

using namespace paradevs::tests::mixed;

template < int size >
void run_flat_with_heap()
{
    boost::timer t;

    std::cout << "run_flat_with_heap [" << size << "] ..." << std::endl;

    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                paradevs::common::DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            LinearGraphManager < size, SchedulerHandle > >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();

    std::cout << "... OK -> " << t.elapsed() << std::endl;
}

template < int size >
void run_flat_with_vector()
{
    boost::timer t;

    std::cout << "run_flat_with_vector [" << size << "] ..." << std::endl;

    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::VectorScheduler <
                paradevs::common::DoubleTime >,
            paradevs::common::scheduler::NoSchedulerHandle,
            LinearGraphManager <
                size, paradevs::common::scheduler::NoSchedulerHandle > >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();

    std::cout << "... OK -> " << t.elapsed() << std::endl;
}

void run_hierarchic_with_heap()
{
    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                paradevs::common::DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            Root2GraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();
}

void run_hierarchic_with_vector()
{
    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::VectorScheduler <
                paradevs::common::DoubleTime >,
            paradevs::common::scheduler::NoSchedulerHandle,
            Root3GraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
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

// #include <condition_variable>
// #include <iostream>
// #include <mutex>
// #include <thread>
// #include <unistd.h>

// struct _sb
// {
//     std::condition_variable wait_cv;
//     std::mutex              wait_lk;
//     int                     runners;
// };

// class Barrier
// {
// public:
//     Barrier(int count)
//     {
//         maxcnt = count;
//         CurrentSb = &sb[0];
//         for (int i = 0; i < 2; ++i) {
//             _sb *CurrentSb = &sb[i];

//             CurrentSb->runners = count;
//         }
//     }

//     virtual ~Barrier()
//     { }

//     int wait()
//     {
//         _sb *TempSb = CurrentSb;

//         std::unique_lock < std::mutex > lck(TempSb->wait_lk);

//         if (TempSb->runners == 1) {
//             if (maxcnt != 1) {
//                 TempSb->runners = maxcnt;
//                 CurrentSb = (CurrentSb == &sb[0]) ? &sb[1] : &sb[0];
//                 TempSb->wait_cv.notify_all();
//             }
//         } else {
//             TempSb->runners--;
//             while (TempSb->runners != maxcnt)
//                 TempSb->wait_cv.wait(lck);
//         }
//         return 0;
//     }

// private:
//     int maxcnt;
//     _sb sb[2];
//     _sb *CurrentSb;
// };

// Barrier ba(2);

// void f1()
// {
//     for (unsigned int i = 1; i < 20; ++i) {
//         std::cout << "*";
//         usleep(50);
//     }
//     ba.wait();
//     std::cout << std::endl;
//     for (unsigned int i = 1; i < 20; ++i) {
//         std::cout << "x";
//         usleep(50);
//     }
//     std::cout << std::endl;
// }

// void f2()
// {
//     for (unsigned int i = 1; i < 20; ++i) {
//         std::cout << "O";
//         usleep(10);
//     }
//     ba.wait();
//     std::cout << std::endl;
//     for (unsigned int i = 1; i < 20; ++i) {
//         std::cout << "o";
//         usleep(10);
//     }
//     std::cout << std::endl;
// }

// int main()
// {
//     std::thread th1(f1);
//     std::thread th2(f2);

//     th1.join();
//     th2.join();

//     return 0;
// }
