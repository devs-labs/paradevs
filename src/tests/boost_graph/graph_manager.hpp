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

#include <boost/graph/adjacency_list.hpp>

#include <common/scheduler/HeapScheduler.hpp>
#include <common/scheduler/VectorScheduler.hpp>

#include <pdevs/Coordinator.hpp>
#include <pdevs/GraphManager.hpp>
#include <pdevs/Simulator.hpp>

#include <tests/boost_graph/models.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

struct VertexProperties
{
    int          _index;
    double       _weight;
    DynamicsType _type;

    VertexProperties() : _index(0), _weight(0), _type(NORMAL_PIXEL)
    { }
    VertexProperties(int index, double weight, DynamicsType type) :
        _index(index), _weight(weight), _type(type)
    { }
};

struct EdgeProperties
{
    double       _weight;

    EdgeProperties() : _weight(0)
    { }
    EdgeProperties(double weight) : _weight(weight)
    { }
};

typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS,
                                VertexProperties, EdgeProperties> Graph;
typedef std::vector < Graph > Graphs;

typedef std::pair < int, int > Edge;
typedef std::vector < Edge > Edges;
typedef Edges OutputEdges;
typedef Edges InputEdges;
typedef std::vector < OutputEdges > OutputEdgeList;
typedef std::vector < InputEdges > InputEdgeList;

typedef std::pair < int, int > Port;
typedef std::pair < Port, Port > Connection;
typedef std::vector < Connection > Connections;

struct GraphParameters
{
    Graph       _graph;
    InputEdges  _input_edges;
    OutputEdges _output_edges;

    GraphParameters(const Graph& graph,
                    const InputEdges& input_edges,
                    const OutputEdges& output_edges) :
        _graph(graph), _input_edges(input_edges), _output_edges(output_edges)
    { }
};

template < class Parameters >
class FlatGraphManager :
    public paradevs::pdevs::GraphManager < MyTime, Parameters >
{
public:
    FlatGraphManager(common::Coordinator < MyTime >* coordinator,
        const Parameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime, Parameters >(
            coordinator, parameters)
    { }

    virtual ~FlatGraphManager()
    {
        for (TopSimulators::const_iterator it = _top_simulators.begin();
             it != _top_simulators.end(); ++it) {
            delete it->second;
        }
        for (NormalSimulators::const_iterator it = _normal_simulators.begin();
             it != _normal_simulators.end(); ++it) {
            delete it->second;
        }
    }

    void build_flat_graph(const Graph& g)
    {
        Graph::vertex_iterator vertexIt, vertexEnd;

        boost::tie(vertexIt, vertexEnd) = boost::vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
            std::ostringstream ss;

            ss << "a" << g[*vertexIt]._index;
            switch (g[*vertexIt]._type) {
            case TOP_PIXEL:
                _top_simulators[g[*vertexIt]._index] =
                    new pdevs::Simulator <
                        MyTime, TopPixel, TopPixelParameters >(
                            ss.str(), TopPixelParameters());
                FlatGraphManager < Parameters >::add_child(
                    _top_simulators[g[*vertexIt]._index]);
                break;
            case NORMAL_PIXEL:
                unsigned int n = 0;
                Graph::adjacency_iterator neighbourIt, neighbourEnd;

                boost::tie(neighbourIt, neighbourEnd) =
                    boost::adjacent_vertices(*vertexIt, g);
                for (; neighbourIt != neighbourEnd; ++neighbourIt) {
                    ++n;
                }
                _normal_simulators[g[*vertexIt]._index] =
                    new pdevs::Simulator <
                        MyTime, NormalPixel, NormalPixelParameters >(
                            ss.str(), NormalPixelParameters(n));
                FlatGraphManager < Parameters >::add_child(
                        _normal_simulators[g[*vertexIt]._index]);
                break;
            };
        }

        boost::tie(vertexIt, vertexEnd) = boost::vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
            Graph::adjacency_iterator neighbourIt, neighbourEnd;

            boost::tie(neighbourIt, neighbourEnd) =
                boost::adjacent_vertices(*vertexIt, g);
            for (; neighbourIt != neighbourEnd; ++neighbourIt) {
                paradevs::common::Model < MyTime >* a = 0;
                paradevs::common::Model < MyTime >* b = 0;

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
                FlatGraphManager < Parameters >::add_link(b, "out", a, "in");
            }
	}
    }

protected:
    typedef std::map < int, pdevs::Simulator <
                                MyTime, TopPixel,
                                TopPixelParameters >* > TopSimulators;
    typedef std::map < int, pdevs::Simulator <
                                MyTime, NormalPixel,
                                NormalPixelParameters>* > NormalSimulators;

    TopSimulators    _top_simulators;
    NormalSimulators _normal_simulators;
};

class BuiltFlatGraphManager :
    public FlatGraphManager < GraphParameters >
{
public:
    BuiltFlatGraphManager(common::Coordinator < MyTime >* coordinator,
                          const GraphParameters& parameters) :
        FlatGraphManager < GraphParameters >(
            coordinator, parameters)
    {
        build_flat_graph(parameters._graph);
        // input
        for (Edges::const_iterator it = parameters._input_edges.begin();
             it != parameters._input_edges.end(); ++it) {
            std::ostringstream ss_in;

            ss_in << "in_" << it->first;
            BuiltFlatGraphManager::add_link(coordinator, ss_in.str(),
                                            _normal_simulators[it->second],
                                            "in");
        }
        // output
        for (Edges::const_iterator it = parameters._output_edges.begin();
             it != parameters._output_edges.end(); ++it) {
            std::ostringstream ss_out;

            ss_out << "out_" << it->second;
            BuiltFlatGraphManager::add_link(_normal_simulators[it->first],
                                            "out", coordinator, ss_out.str());
        }
    }

    virtual ~BuiltFlatGraphManager()
    { }
};

template < class GraphBuilder >
class InBuildFlatGraphManager :
    public FlatGraphManager < paradevs::common::NoParameters >
{
public:
    InBuildFlatGraphManager(common::Coordinator < MyTime >* coordinator,
                            const paradevs::common::NoParameters& parameters) :
        FlatGraphManager < paradevs::common::NoParameters >(
            coordinator, parameters)
    {
        GraphBuilder   builder;
        Graphs         graphs;
        InputEdgeList  input_edges;
        OutputEdgeList output_edges;
        Connections    parent_connections;

        builder.build(graphs, input_edges, output_edges, parent_connections);
        build_flat_graph(graphs.front());
    }

    virtual ~InBuildFlatGraphManager()
    { }
};

class FlatGraphBuilder
{
public:
    FlatGraphBuilder()
    { }

    void build(Graphs& graphs, InputEdgeList& /* input_edges */,
               OutputEdgeList& /* output_edges */,
               Connections& /* parent_connections */)
    {
        Graph graph;

        Graph::vertex_descriptor v0 = boost::add_vertex(graph);
        Graph::vertex_descriptor v1 = boost::add_vertex(graph);
        Graph::vertex_descriptor v2 = boost::add_vertex(graph);
        Graph::vertex_descriptor v3 = boost::add_vertex(graph);
        Graph::vertex_descriptor v4 = boost::add_vertex(graph);
        Graph::vertex_descriptor v5 = boost::add_vertex(graph);
        Graph::vertex_descriptor v6 = boost::add_vertex(graph);
        Graph::vertex_descriptor v7 = boost::add_vertex(graph);
        Graph::vertex_descriptor v8 = boost::add_vertex(graph);
        Graph::vertex_descriptor v9 = boost::add_vertex(graph);
        Graph::vertex_descriptor v10 = boost::add_vertex(graph);

        boost::add_edge(v0, v1, 1, graph);
	boost::add_edge(v0, v2, 1, graph);
	boost::add_edge(v0, v3, 1, graph);
	boost::add_edge(v1, v2, 1, graph);
	boost::add_edge(v1, v4, 1, graph);
	boost::add_edge(v1, v5, 1, graph);
	boost::add_edge(v1, v6, 1, graph);
	boost::add_edge(v2, v6, 1, graph);
	boost::add_edge(v2, v3, 1, graph);
	boost::add_edge(v3, v9, 1, graph);
	boost::add_edge(v3, v10, 1, graph);
	boost::add_edge(v4, v5, 1, graph);
	boost::add_edge(v5, v6, 1, graph);
	boost::add_edge(v4, v7, 1, graph);
	boost::add_edge(v4, v8, 1, graph);
	boost::add_edge(v7, v8, 1, graph);
	boost::add_edge(v9, v10, 1, graph);

        graph[v6] = VertexProperties(6, 1, TOP_PIXEL);
        graph[v8] = VertexProperties(8, 1, TOP_PIXEL);
        graph[v10] = VertexProperties(10, 1, TOP_PIXEL);
        graph[v0] = VertexProperties(0, 1, NORMAL_PIXEL);
        graph[v1] = VertexProperties(1, 1, NORMAL_PIXEL);
        graph[v2] = VertexProperties(2, 1, NORMAL_PIXEL);
        graph[v3] = VertexProperties(3, 1, NORMAL_PIXEL);
        graph[v4] = VertexProperties(4, 1, NORMAL_PIXEL);
        graph[v5] = VertexProperties(5, 1, NORMAL_PIXEL);
        graph[v7] = VertexProperties(7, 1, NORMAL_PIXEL);
        graph[v9] = VertexProperties(9, 1, NORMAL_PIXEL);

        graphs.push_back(graph);
    }
};

template < class GraphBuilder >
class HierarchicalGraphManager :
    public paradevs::pdevs::GraphManager < MyTime,
                                           paradevs::common::NoParameters >
{
public:
    HierarchicalGraphManager(common::Coordinator < MyTime >* coordinator,
                             const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::GraphManager < MyTime,
                                        paradevs::common::NoParameters >(
                                            coordinator, parameters)
    {
        GraphBuilder   graph_builder;
        Graphs         graphs;
        InputEdgeList  input_edges;
        OutputEdgeList output_edges;
        Connections    parent_connections;

        graph_builder.build(graphs, input_edges, output_edges,
                            parent_connections);

        // build coordinators (graphs)
        for (unsigned int i = 0; i < graphs.size(); ++i) {
            Coordinator* coordinator = 0;
            std::ostringstream ss;

            ss << "S" << i;
            coordinator =
                new Coordinator(ss.str(), paradevs::common::NoParameters(),
                                GraphParameters(graphs[i], input_edges[i],
                                                output_edges[i]));
            _coordinators.push_back(coordinator);
            HierarchicalGraphManager < GraphBuilder >::add_child(
                coordinator);

        }

        // builds internal connections (edges)
        for (Connections::const_iterator it = parent_connections.begin();
             it != parent_connections.end(); ++it) {
            const Connection& connection = *it;
            std::ostringstream ss_out;
            std::ostringstream ss_in;

            ss_out << "out_" << connection.first.second;
            ss_in << "in_" << connection.second.second;
            HierarchicalGraphManager < GraphBuilder >::add_link(
                _coordinators[connection.first.first], ss_out.str(),
                _coordinators[connection.second.first], ss_in.str());
        }
    }

    virtual ~HierarchicalGraphManager()
    {
        for (Coordinators::const_iterator it = _coordinators.begin();
             it != _coordinators.end(); ++it) {
            delete *it;
        }
    }

private:
    typedef paradevs::pdevs::Coordinator < MyTime,
                                           common::scheduler::VectorScheduler <
                                               MyTime >,
                                           BuiltFlatGraphManager,
                                           common::NoParameters,
                                           GraphParameters > Coordinator;
    typedef std::vector < Coordinator* > Coordinators;

    Coordinators _coordinators;
};

class HierarchicalGraphBuilder
{
public:
    HierarchicalGraphBuilder()
    { }

    void build(Graphs& graphs, InputEdgeList& input_edges,
               OutputEdgeList& output_edges, Connections& parent_connections)
    {
        // S1
        {
            Graph graph;

            Graph::vertex_descriptor v1 = boost::add_vertex(graph);
            Graph::vertex_descriptor v2 = boost::add_vertex(graph);
            Graph::vertex_descriptor v4 = boost::add_vertex(graph);
            Graph::vertex_descriptor v5 = boost::add_vertex(graph);
            Graph::vertex_descriptor v6 = boost::add_vertex(graph);
            Graph::vertex_descriptor v7 = boost::add_vertex(graph);
            Graph::vertex_descriptor v8 = boost::add_vertex(graph);

            boost::add_edge(v1, v2, 1, graph);
            boost::add_edge(v1, v4, 1, graph);
            boost::add_edge(v1, v5, 1, graph);
            boost::add_edge(v1, v6, 1, graph);
            boost::add_edge(v2, v6, 1, graph);
            boost::add_edge(v4, v5, 1, graph);
            boost::add_edge(v5, v6, 1, graph);
            boost::add_edge(v4, v7, 1, graph);
            boost::add_edge(v4, v8, 1, graph);
            boost::add_edge(v7, v8, 1, graph);

            graph[v6] = VertexProperties(6, 1, TOP_PIXEL);
            graph[v8] = VertexProperties(8, 1, TOP_PIXEL);
            graph[v1] = VertexProperties(1, 1, NORMAL_PIXEL);
            graph[v2] = VertexProperties(2, 1, NORMAL_PIXEL);
            graph[v4] = VertexProperties(4, 1, NORMAL_PIXEL);
            graph[v5] = VertexProperties(5, 1, NORMAL_PIXEL);
            graph[v7] = VertexProperties(7, 1, NORMAL_PIXEL);

            graphs.push_back(graph);
        }
        // S2
        {
            Graph graph;

            Graph::vertex_descriptor v0 = boost::add_vertex(graph);
            Graph::vertex_descriptor v3 = boost::add_vertex(graph);
            Graph::vertex_descriptor v9 = boost::add_vertex(graph);
            Graph::vertex_descriptor v10 = boost::add_vertex(graph);

            boost::add_edge(v0, v3, 1, graph);
            boost::add_edge(v3, v10, 1, graph);
            boost::add_edge(v9, v10, 1, graph);
            boost::add_edge(v3, v9, 1, graph);

            graph[v10] = VertexProperties(10, 1, TOP_PIXEL);
            graph[v0] = VertexProperties(0, 1, NORMAL_PIXEL);
            graph[v3] = VertexProperties(3, 1, NORMAL_PIXEL);
            graph[v9] = VertexProperties(9, 1, NORMAL_PIXEL);

            graphs.push_back(graph);
        }
        {
            // input S1
            input_edges.push_back(InputEdges());
            input_edges[0].push_back(Edge(3, 2));
            // input S2
            input_edges.push_back(InputEdges());
            input_edges[0].push_back(Edge(1, 0));
            input_edges[0].push_back(Edge(2, 0));

            // output S1
            output_edges.push_back(OutputEdges());
            output_edges[0].push_back(Edge(1, 0));
            output_edges[0].push_back(Edge(2, 0));
            // output S2
            output_edges.push_back(OutputEdges());
            output_edges[0].push_back(Edge(3, 2));

            // parent
            parent_connections.push_back(Connection(Port(1,1),Port(2,0)));
            parent_connections.push_back(Connection(Port(1,2),Port(2,0)));
            parent_connections.push_back(Connection(Port(2,3),Port(1,2)));
        }
    }
};

} } } // namespace paradevs tests boost_graph

#endif
