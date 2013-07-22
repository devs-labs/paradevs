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
    // hierarchical_test();

    class M;

    struct A
    {
        double time;
        M*     model;

        A(double _time, M* _model)
        {
            time = _time;
            model = _model;
        }
    };

    struct ACompare
        : std::binary_function < A, A, bool >
    {
        bool operator()(const A &left, const A &right) const
        { return left.time > right.time; }
    };

    typedef boost::heap::fibonacci_heap < A, boost::heap::compare <
        ACompare > > Heap;

    typedef Heap::handle_type HeapHandle;

    class M
    {
    public:
        M(int a)
        {
            _a = a;
        }

        int a() const
        { return _a; }

        HeapHandle heap_id() const
        { return _heap_id; }

        void heap_id(HeapHandle id)
        { _heap_id = id; }

    private:
        int _a;
        HeapHandle _heap_id;
    };

    Heap heap;
    M* m1 = new M(1);
    M* m2 = new M(2);

    m1->heap_id(heap.push(A(0, m1)));
    m2->heap_id(heap.push(A(0, m2)));

    (*m1->heap_id()).time = 1;
    heap.decrease(m1->heap_id());
    (*m2->heap_id()).time = 1;
    heap.decrease(m2->heap_id());

    std::cout << "Scheduler = { ";
    while (not heap.empty()) {
        std::cout << "(" << heap.top().time << "," << heap.top().model->a()
                  << ") ";
        heap.pop();
    }
    std::cout << "}" << std::endl;



    return 0;
}
