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

template < class GraphBuilder >
void flat_heap_test(double duration)
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            SchedulerType,
            SchedulerHandle,
            InBuildFlatGraphManager <
                SchedulerHandle,
                GraphBuilder >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
    > rc(0, duration, "root", NoParameters(), NoParameters());

    rc.run();
}

template < class GraphBuilder >
void flat_vector_test(double duration)
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::VectorScheduler <
                paradevs::common::DoubleTime >,
            paradevs::common::scheduler::NoSchedulerHandle,
            InBuildFlatGraphManager <
                paradevs::common::scheduler::NoSchedulerHandle,
                GraphBuilder >,
            paradevs::common::NoParameters,
            paradevs::common::NoParameters >
    > rc(0, duration, "root", NoParameters(), NoParameters());

    rc.run();
}

void hierarchical_test()
{
    // RootCoordinator <
    //     DoubleTime,
    //     paradevs::pdevs::Coordinator <
    //         DoubleTime,
    //         SchedulerType,
    //         SchedulerHandle,
    //         HierarchicalGraphManager <
    //             SchedulerHandle,
    //             HierarchicalGraphBuilder >,
    //         paradevs::common::NoParameters,
    //         paradevs::common::NoParameters >
    //     > rc(0, 100, "root", NoParameters(), NoParameters());

    // rc.run();
}

void parallel_partitionning_heap_test(double duration,
                                      int cluster_number,
                                      std::string partitioning_method_name,
                                      int contraction_coef,
                                      bool contraction_coef_flag)
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::multithreading::Coordinator <
            DoubleTime,
            SchedulerType,
            SchedulerHandle,
            ParallelHeapHierarchicalGraphManager <
                SchedulerHandle,
                PartitioningGraphBuilder >,
            paradevs::common::NoParameters,
            PartitioningParameters >
        > rc(0, duration, "root", NoParameters(),
             PartitioningParameters(cluster_number, partitioning_method_name,
                                    contraction_coef, contraction_coef_flag));

    rc.run();
}

void partitionning_heap_test(double duration,
                             int cluster_number,
                             std::string partitioning_method_name,
                             int contraction_coef,
                             bool contraction_coef_flag)
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            SchedulerType,
            SchedulerHandle,
            HeapHierarchicalGraphManager <
                SchedulerHandle,
                PartitioningGraphBuilder >,
            paradevs::common::NoParameters,
            PartitioningParameters >
        > rc(0, duration, "root", NoParameters(),
             PartitioningParameters(cluster_number, partitioning_method_name,
                                    contraction_coef, contraction_coef_flag));

    rc.run();
}

void partitionning_vector_test(double duration,
                               int cluster_number,
                               std::string partitioning_method_name,
                               int contraction_coef,
                               bool contraction_coef_flag)
{
    RootCoordinator <
        DoubleTime,
        paradevs::pdevs::Coordinator <
            DoubleTime,
            paradevs::common::scheduler::VectorScheduler <
                paradevs::common::DoubleTime >,
            paradevs::common::scheduler::NoSchedulerHandle,
            VectorHierarchicalGraphManager <
                paradevs::common::scheduler::NoSchedulerHandle,
                PartitioningGraphBuilder >,
            paradevs::common::NoParameters,
            PartitioningParameters >
        > rc(0, duration, "root", NoParameters(),
             PartitioningParameters(cluster_number, partitioning_method_name,
                                    contraction_coef, contraction_coef_flag));

    rc.run();
}

void test(double duration, std::string partitioning_method_name,
          unsigned int min, unsigned int max, unsigned int step,
          bool vector, bool heap,
          int contraction_coef,
          bool contraction_coef_flag)
{
    boost::timer t;

    std::cout << "==== " << partitioning_method_name << " with ";
    if (contraction_coef_flag) {
        std::cout << "/";
    }
    std::cout << contraction_coef << " ===" << std::endl;
    std::cout << "n";
    if (heap) {
        std::cout << "\t heap";
    }
    if (vector) {
        std::cout << "\t vector";
    }
    std::cout << std::endl;

    if (contraction_coef_flag) {
        for (unsigned int n = min; n <= max; n += step) {
            std::cout << n << "\t";
            if (heap) {
                double t1 = t.elapsed();

                for (unsigned int i = 0; i < 20; ++i) {
                    partitionning_heap_test(duration, n,
                                            partitioning_method_name,
                                            contraction_coef,
                                            contraction_coef_flag);
                }

                double t2 = t.elapsed();

                std::cout << (t2 - t1) / 20 << "\t";
            }
            if (vector) {
                double t1 = t.elapsed();

                for (unsigned int i = 0; i < 20; ++i) {
                    partitionning_vector_test(duration, n,
                                              partitioning_method_name,
                                              contraction_coef,
                                              contraction_coef_flag);
                }

                double t2 = t.elapsed();

                std::cout << (t2 - t1) / 20 << std::endl;
            } else {
                std::cout << std::endl;
            }

        }
    } else {
        std::cout << contraction_coef << "\t";
        if (heap) {
            double t1 = t.elapsed();

            for (unsigned int i = 0; i < 20; ++i) {
                partitionning_heap_test(duration, contraction_coef,
                                        partitioning_method_name,
                                        contraction_coef,
                                        contraction_coef_flag);
            }

            double t2 = t.elapsed();

            std::cout << (t2 - t1) / 20 << "\t";
        }
        if (vector) {
            double t1 = t.elapsed();

            for (unsigned int i = 0; i < 20; ++i) {
                partitionning_vector_test(duration, contraction_coef,
                                          partitioning_method_name,
                                          contraction_coef,
                                          contraction_coef_flag);
                }

            double t2 = t.elapsed();

            std::cout << (t2 - t1) / 20 << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
}

void test_flat_38()
{
    boost::timer t;

    std::cout << "== 38 nodes ==" << std::endl;
    std::cout << "flat graph with heap = ";
    for (unsigned int i = 0; i < 20; ++i) {
        flat_heap_test< FlatGraphBuilder >(10000);
    }

    double t2 = t.elapsed();

    std::cout << t2 / 20 << std::endl;

    std::cout << "flat graph with vector = ";
    for (unsigned int i = 0; i < 20; ++i) {
        flat_vector_test< FlatGraphBuilder >(10000);
    }

    double t3 = t.elapsed();

    std::cout << (t3 - t2) / 20 << std::endl;
}

const double duration_38 = -1;

void test_partiotining_38()
{
    for (int i = 1; i <= 2; ++i) {
        test(duration_38, "ggp", 2, 16, 2, true, true, i, true);
        test(duration_38, "gggp_pond", 2, 16, 2, true, true, i, true);
        test(duration_38, "random", 2, 16, 2, true, true, i, true);
    }

    for (int i = 2; i <= 8; i += 2) {
        test(duration_38, "gggp_pond", 0, 0, 0, true, true, i, false);
    }
}

const double corsen_duration = 20;

void test_flat_corsen()
{
    boost::timer t;

    std::cout << "== CORSEN == " << std::endl;
    std::cout << "flat graph with heap = ";
    for (unsigned int i = 0; i < 20; ++i) {
        flat_heap_test< CorsenFlatGraphBuilder >(corsen_duration);
    }

    double t2 = t.elapsed();

    std::cout << t2 / 20 << std::endl;

    // std::cout << "flat graph with vector = ";
    // for (unsigned int i = 0; i < 20; ++i) {
    //     flat_vector_test< CorsenFlatGraphBuilder >(corsen_duration);
    // }

    // double t3 = t.elapsed();

    // std::cout << (t3 - t2) / 20 << std::endl;
}

void test_partitioning_corsen()
{
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 10, true);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 20, true);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 40, true);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 80, true);
    test(corsen_duration, "gggp_pond", 2, 22, 2, false, true, 200, true);

    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 30, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 40, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 50, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 60, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 70, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 80, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 90, false);
    test(corsen_duration, "gggp_pond", 2, 32, 2, false, true, 100, false);

    test(corsen_duration, "ggp", 2, 32, 2, false, true, 10, true);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 20, true);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 40, true);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 80, true);
    test(corsen_duration, "ggp", 2, 22, 2, false, true, 200, true);

    test(corsen_duration, "ggp", 2, 32, 2, false, true, 30, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 40, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 50, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 60, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 70, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 80, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 90, false);
    test(corsen_duration, "ggp", 2, 32, 2, false, true, 100, false);

    test(corsen_duration, "random", 2, 32, 2, false, true, 10, true);
    test(corsen_duration, "random", 2, 32, 2, false, true, 20, true);
    test(corsen_duration, "random", 2, 32, 2, false, true, 40, true);
    test(corsen_duration, "random", 2, 32, 2, false, true, 80, true);
    test(corsen_duration, "random", 2, 22, 2, false, true, 200, true);
}

int main()
{
    srand(7262);

    // test_flat_38();
    // test_partiotining_38();

    test_flat_corsen();
    test_partitioning_corsen();

    return 0;
}
