/**
 * @file tests/common/scheduler/tests.cpp
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

#include <common/scheduler/HeapScheduler.hpp>
#include <common/time/DoubleTime.hpp>

#include <kernel/pdevs/Dynamics.hpp>
#include <kernel/pdevs/Simulator.hpp>

#include <chrono>

#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>

using namespace paradevs::common;
using namespace paradevs::common::scheduler;

using namespace paradevs::pdevs;

using namespace std::chrono;

struct SchedulerHandle;

typedef typename HeapScheduler < DoubleTime,
                                 SchedulerHandle >::type SchedulerType;

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

typedef Dynamics < DoubleTime, SchedulerHandle > MyDynamics;
typedef paradevs::pdevs::Simulator < DoubleTime, MyDynamics,
                                     SchedulerHandle > MySimulator;
typedef std::vector < MySimulator* > MySimulators;

const int simulator_number = 5000;
const double simulation_duration = 1000;
const int sample_number = 20;

double unit_test(unsigned int n)
{
    MySimulators simulators;
    HeapScheduler < DoubleTime, SchedulerHandle > scheduler;

    for (unsigned int i = 0; i < simulator_number; ++i) {
        std::ostringstream ss;

        ss << "a" << (i + 1);
        simulators.push_back(new MySimulator(ss.str(), NoParameters()));
    }

    std::vector < std::vector < unsigned int > > lists;

    for (unsigned int t = 1; t < simulation_duration; ++t) {
        std::vector < unsigned int > list;
        std::vector < unsigned int > list2;

        for (unsigned int i = 0; i < n; ++i) {
            list2.push_back(i);
        }
        for (unsigned int i = 0; i < n; ++i) {
            unsigned int j = rand() % list2.size();
            unsigned int index = list2[j];
            std::vector < unsigned int >::iterator it =
                std::find(list2.begin(), list2.end(), index);

            list.push_back(index);
            list2.erase(it);
        }
        lists.push_back(list);
    }

    steady_clock::time_point t1 = steady_clock::now();

    for (unsigned int i = 0; i < n; ++i) {
        scheduler.init(0., simulators[i]);
    }

    for (unsigned int t = 1; t < simulation_duration; ++t) {
        for (unsigned int i = 0; i < n; ++i) {
            scheduler.put((double)t, simulators[lists[t - 1][i]]);
        }
    }

    steady_clock::time_point t2 = steady_clock::now();

    duration < double > time_span = duration_cast <
        duration < double > >(t2 - t1);

    for (MySimulators::const_iterator it = simulators.begin();
         it != simulators.end(); ++it) {
        delete *it;
    }

    return time_span.count();
}

void test(unsigned int n, unsigned int r)
{
    std::vector < double > t;

    for (unsigned int i = 0; i < sample_number; ++i) {
        t.push_back(unit_test(n));
    }

    double a = 0;

    for (unsigned int i = 0; i < sample_number; ++i) {
        a += t[i];
    }
    a /= sample_number;

    double sd = 0;

    for (unsigned int i = 0; i < sample_number; ++i) {
        sd += (t[i] - a)*(t[i] - a);
    }
    sd /= sample_number;
    sd = sqrt(sd);

    std::cout << n << "\t" << a << "\t" << (a * r) << "\t"
              << sd << "\t" << (sd * r) << std::endl;
}

TEST_CASE("common/scheduler/heap", "run")
{
    for (unsigned int i = 1; i <= 200; i+= 5) {
        test(simulator_number / i, i);
    }
}
