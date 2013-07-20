/**
 * @file tests/mixed/tests.cpp
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

#include <tests/mixed/graph_manager.hpp>
#include <tests/mixed/models.hpp>

#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>

using namespace paradevs::tests::mixed;

TEST_CASE("mixed/hierachical", "run")
{
    paradevs::common::RootCoordinator <
        MyTime, paradevs::pdevs::Coordinator <
            MyTime, paradevs::common::scheduler::VectorScheduler <
                MyTime >, RootGraphManager > > rc(0, 100, "root");

    paradevs::common::Trace < MyTime >::trace().clear();
    rc.run();

    REQUIRE(paradevs::common::Trace < MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace < MyTime >::trace().elements().
            filter_model_name("b1").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace < MyTime >::trace().elements().
            filter_model_name("a2").
            filter_type(paradevs::common::START).size() == 1);
    REQUIRE(paradevs::common::Trace < MyTime >::trace().elements().
            filter_model_name("b2").
            filter_type(paradevs::common::START).size() == 1);

    REQUIRE(paradevs::common::Trace < MyTime >::trace().elements().
            filter_model_name("a1").
            filter_type(paradevs::common::DELTA_EXT).size() == 0);
    for (double t = 0; t <= 100; ++t) {
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("a1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 1);
    }

    for (double t = 0; t <= 100; ++t) {
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::TA).size() == 2);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("b1").filter_time(t).
                filter_type(paradevs::common::DELTA_EXT).size() == 1);
    }

    for (unsigned int t = 0; t <= 100; t += 20) {
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("a2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
    }

    for (unsigned int t = 0; t <= 100; t += 20) {
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::LAMBDA).size() == 1);
        REQUIRE(paradevs::common::Trace <
                    MyTime >::trace().elements().
                filter_model_name("b2").filter_time(t).
                filter_type(paradevs::common::DELTA_INT).size() == 1);
    }
}
