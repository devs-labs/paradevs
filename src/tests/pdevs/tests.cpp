/**
 * @file tests/pdevs/tests.cpp
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

#include <tests/pdevs/graph_manager.hpp>
#include <tests/pdevs/models.hpp>

#include <common/RootCoordinator.hpp>

#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>

using namespace paradevs::tests::pdevs;
using namespace paradevs::common;

TEST_CASE("pdevs/only_one", "run")
{
    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            OnlyOneGraphManager < SchedulerHandle > >
        > rc(0, 10, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < DoubleTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a").
            filter_type(paradevs::common::DELTA_CONF).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
    }
}

TEST_CASE("pdevs/flat", "run")
{
    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            FlatGraphManager < SchedulerHandle> >
        > rc(0, 10, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < DoubleTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 3);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_CONF).size() == 0);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 4);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 2);
    }
}

TEST_CASE("pdevs/hierachical", "run")
{
    paradevs::common::RootCoordinator <
        DoubleTime, paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            RootGraphManager >
        > rc(0, 10, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < DoubleTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace <
                DoubleTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 3);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_CONF).size() == 0);
    }

    for (unsigned int t = 0; t <= 10; ++t) {
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::TA).size() == 4);
        REQUIRE(paradevs::common::Trace <
                    DoubleTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 2);
    }
}
