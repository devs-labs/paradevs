/**
 * @file tests/boost_graph/graph_manager.hpp
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

#ifndef __TESTS_BOOST_GRAPH_GRAPH_MANAGER_HPP
#define __TESTS_BOOST_GRAPH_GRAPH_MANAGER_HPP 1

#include <common/scheduler/HeapScheduler.hpp>
#include <common/scheduler/VectorScheduler.hpp>

#include <kernel/pdevs/Coordinator.hpp>
#include <kernel/pdevs/GraphManager.hpp>
#include <kernel/pdevs/Simulator.hpp>

#include <tests/boost_graph/models.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

struct SchedulerHandle;

typedef typename paradevs::common::scheduler::HeapScheduler <
    common::DoubleTime, SchedulerHandle >::type SchedulerType;

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

struct GraphParameters
{
    OrientedGraph _graph;
    InputEdges    _input_edges;
    OutputEdges   _output_edges;

    GraphParameters(const OrientedGraph& graph,
                    const InputEdges& input_edges,
                    const OutputEdges& output_edges) :
        _graph(graph), _input_edges(input_edges), _output_edges(output_edges)
    { }
};

template < class SchedulerHandle, class Parameters >
class FlatGraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle,
                                               Parameters >
{
public:
    FlatGraphManager(common::Coordinator < common::DoubleTime,
                                           SchedulerHandle >* coordinator,
        const Parameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                        Parameters >(
            coordinator, parameters)
    { }

    virtual ~FlatGraphManager()
    {
        for (typename TopSimulators::const_iterator it =
                 _top_simulators.begin(); it != _top_simulators.end();
             ++it) {
            delete it->second;
        }
        for (typename NormalSimulators::const_iterator it =
                 _normal_simulators.begin(); it != _normal_simulators.end();
             ++it) {
            delete it->second;
        }
    }

    void build_flat_graph(const OrientedGraph& g, const InputEdges& inputs)
    {
        OrientedGraph::vertex_iterator vertexIt, vertexEnd;

        boost::tie(vertexIt, vertexEnd) = boost::vertices(g);
        for (; vertexIt != vertexEnd; ++vertexIt) {
            std::ostringstream ss;

            ss << "a" << g[*vertexIt]._index;
            switch (g[*vertexIt]._type) {
            case TOP_PIXEL:
                _top_simulators[g[*vertexIt]._index] =
                    new pdevs::Simulator <
                        common::DoubleTime, TopPixel < SchedulerHandle >,
                        SchedulerHandle,
                        TopPixelParameters >(ss.str(), TopPixelParameters());
                _top_simulators[g[*vertexIt]._index]->add_out_port("out");
                FlatGraphManager < SchedulerHandle, Parameters >::add_child(
                    _top_simulators[g[*vertexIt]._index]);
                break;
            case NORMAL_PIXEL:
                unsigned int n = 0;
                OrientedGraph::vertex_iterator vertexIt2, vertexEnd2;

                boost::tie(vertexIt2, vertexEnd2) = boost::vertices(g);
                for (; vertexIt2 != vertexEnd2; ++vertexIt2) {
                    OrientedGraph::adjacency_iterator neighbourIt, neighbourEnd;

                    boost::tie(neighbourIt, neighbourEnd) =
                        boost::adjacent_vertices(*vertexIt2, g);
                    for (; neighbourIt != neighbourEnd; ++neighbourIt) {
                        if (g[*neighbourIt]._index == g[*vertexIt]._index) {
                            ++n;
                        }
                    }
                }

                for (InputEdges::const_iterator it = inputs.begin();
                     it != inputs.end(); ++it) {
                    if (g[*vertexIt]._index == it->second) {
                        ++n;
                    }
                }
                _normal_simulators[g[*vertexIt]._index] =
                    new pdevs::Simulator <
                        common::DoubleTime, NormalPixel < SchedulerHandle >,
                        SchedulerHandle, NormalPixelParameters >(
                            ss.str(), NormalPixelParameters(n));
                _normal_simulators[g[*vertexIt]._index]->add_in_port("in");
                _normal_simulators[g[*vertexIt]._index]->add_out_port("out");
                FlatGraphManager < SchedulerHandle, Parameters >::add_child(
                    _normal_simulators[g[*vertexIt]._index]);
                break;
            };
        }

        boost::tie(vertexIt, vertexEnd) = boost::vertices(g);
        for (; vertexIt != vertexEnd; ++vertexIt)
        {
            OrientedGraph::adjacency_iterator neighbourIt, neighbourEnd;

            boost::tie(neighbourIt, neighbourEnd) =
                boost::adjacent_vertices(*vertexIt, g);
            for (; neighbourIt != neighbourEnd; ++neighbourIt) {
                paradevs::common::Model < common::DoubleTime,
                                          SchedulerHandle >* a = 0;
                paradevs::common::Model < common::DoubleTime,
                                          SchedulerHandle >* b = 0;

                if (g[*vertexIt]._type == TOP_PIXEL) {
                    a = _top_simulators[g[*vertexIt]._index];
                } else {
                    a = _normal_simulators[g[*vertexIt]._index];
                }
                if (g[*neighbourIt]._type == TOP_PIXEL) {
                    b = _top_simulators[g[*neighbourIt]._index];
                } else {
                    b = _normal_simulators[g[*neighbourIt]._index];
                }
                FlatGraphManager < SchedulerHandle,
                                   Parameters >::add_link(a, "out",
                                                          b, "in");
            }
        }
    }

protected:
    typedef std::map < int, pdevs::Simulator <
                                common::DoubleTime,
                                TopPixel < SchedulerHandle >,
                                SchedulerHandle,
                                TopPixelParameters >* > TopSimulators;
    typedef std::map < int, pdevs::Simulator <
                                common::DoubleTime,
                                NormalPixel < SchedulerHandle >,
                                SchedulerHandle,
                                NormalPixelParameters >* > NormalSimulators;

    TopSimulators    _top_simulators;
    NormalSimulators _normal_simulators;
};

template < class SchedulerHandle >
class BuiltFlatGraphManager :
        public FlatGraphManager < SchedulerHandle, GraphParameters >
{
public:
    BuiltFlatGraphManager(
        common::Coordinator < common::DoubleTime,
                              SchedulerHandle >* coordinator,
        const GraphParameters& parameters) :
        FlatGraphManager < SchedulerHandle, GraphParameters >(
            coordinator, parameters)
    {
        BuiltFlatGraphManager < SchedulerHandle >::build_flat_graph(
            parameters._graph, parameters._input_edges);
        // input
        for (Edges::const_iterator it = parameters._input_edges.begin();
             it != parameters._input_edges.end(); ++it) {
            std::ostringstream ss_in;

            ss_in << "in_" << it->first;
            if (not coordinator->exist_in_port(ss_in.str())) {
                coordinator->add_in_port(ss_in.str());
            }
            BuiltFlatGraphManager < SchedulerHandle>::add_link(
                coordinator, ss_in.str(),
                BuiltFlatGraphManager <
                    SchedulerHandle >::_normal_simulators[it->second], "in");
        }
        // output
        for (Edges::const_iterator it = parameters._output_edges.begin();
             it != parameters._output_edges.end(); ++it) {
            std::ostringstream ss_out;

            ss_out << "out_" << it->first;
            if (not coordinator->exist_out_port(ss_out.str())) {
                coordinator->add_out_port(ss_out.str());
            }
            if (not BuiltFlatGraphManager < SchedulerHandle>::exist_link(
                BuiltFlatGraphManager <
                    SchedulerHandle >::_normal_simulators[it->first], "out",
                coordinator, ss_out.str())) {
                BuiltFlatGraphManager < SchedulerHandle>::add_link(
                    BuiltFlatGraphManager <
                        SchedulerHandle >::_normal_simulators[it->first], "out",
                    coordinator, ss_out.str());
            }
        }
    }

    virtual ~BuiltFlatGraphManager()
    { }
};

template < class SchedulerHandle, class GraphBuilder >
class InBuildFlatGraphManager :
        public FlatGraphManager < SchedulerHandle,
                                  paradevs::common::NoParameters >
{
public:
    InBuildFlatGraphManager(
        common::Coordinator < common::DoubleTime,
                              SchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        FlatGraphManager < SchedulerHandle, paradevs::common::NoParameters >(
            coordinator, parameters)
    {
        GraphBuilder   builder;
        OrientedGraphs graphs;
        InputEdgeList  input_edges;
        OutputEdgeList output_edges;
        Connections    parent_connections;

        builder.build(graphs, input_edges, output_edges, parent_connections);
        InBuildFlatGraphManager < SchedulerHandle,
                                  GraphBuilder >::build_flat_graph(
                                      graphs.front(), InputEdges());
    }

    virtual ~InBuildFlatGraphManager()
    { }
};

template < class SchedulerHandle, class GraphBuilder >
class HierarchicalGraphManager :
        public paradevs::pdevs::GraphManager < common::DoubleTime,
                                               SchedulerHandle,
                                               paradevs::common::NoParameters >
{
public:
    HierarchicalGraphManager(
        common::Coordinator < common::DoubleTime,
                              SchedulerHandle >* coordinator,
        const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < common::DoubleTime, SchedulerHandle,
                                        paradevs::common::NoParameters >(
                                            coordinator, parameters)
    {
        GraphBuilder   graph_builder;
        OrientedGraphs graphs;
        InputEdgeList  input_edges;
        OutputEdgeList output_edges;
        Connections    parent_connections;

        graph_builder.build(graphs, input_edges, output_edges,
                            parent_connections);

        // build coordinators (graphs)
        for (unsigned int i = 0; i < graphs.size(); ++i) {
            Coordinator* coordinator = 0;
            std::ostringstream ss;

            ss << "S" << (i + 1);
            coordinator =
                new Coordinator(ss.str(), paradevs::common::NoParameters(),
                                GraphParameters(graphs[i], input_edges[i],
                                                output_edges[i]));
            _coordinators.push_back(coordinator);
            HierarchicalGraphManager < SchedulerHandle,
                                       GraphBuilder >::add_child(coordinator);

        }

        // builds internal connections (edges)
        for (Connections::const_iterator it = parent_connections.begin();
             it != parent_connections.end(); ++it) {
            const Connection& connection = *it;
            std::ostringstream ss_out;
            std::ostringstream ss_in;

            ss_out << "out_" << connection.first.second;
            ss_in << "in_" << connection.first.second;

            if (not HierarchicalGraphManager <
                    SchedulerHandle, GraphBuilder >::exist_link(
                        _coordinators[connection.first.first - 1],
                        ss_out.str(),
                        _coordinators[connection.second.first - 1],
                        ss_in.str())) {
                HierarchicalGraphManager <
                    SchedulerHandle, GraphBuilder >::add_link(
                        _coordinators[connection.first.first - 1],
                        ss_out.str(),
                        _coordinators[connection.second.first - 1],
                        ss_in.str());
            }
        }
    }

    virtual ~HierarchicalGraphManager()
    {
        for (typename Coordinators::const_iterator it = _coordinators.begin();
             it != _coordinators.end(); ++it) {
            delete *it;
        }
    }

private:
    typedef paradevs::pdevs::Coordinator <
        common::DoubleTime,
        SchedulerType,
        SchedulerHandle,
        BuiltFlatGraphManager < SchedulerHandle >,
        common::NoParameters,
        GraphParameters > Coordinator;
    typedef std::vector < Coordinator* > Coordinators;

    Coordinators _coordinators;
};

} } } // namespace paradevs tests boost_graph

#endif
