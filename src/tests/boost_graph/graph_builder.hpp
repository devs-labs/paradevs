/**
 * @file tests/boost_graph/graph_builder.hpp
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

#ifndef __TESTS_BOOST_GRAPH_GRAPH_BUILDER_HPP
#define __TESTS_BOOST_GRAPH_GRAPH_BUILDER_HPP 1

#include <boost/graph/adjacency_list.hpp>

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
            input_edges[1].push_back(Edge(1, 0));
            input_edges[1].push_back(Edge(2, 0));

            // output S1
            output_edges.push_back(OutputEdges());
            output_edges[0].push_back(Edge(1, 0));
            output_edges[0].push_back(Edge(2, 0));
            // output S2
            output_edges.push_back(OutputEdges());
            output_edges[1].push_back(Edge(3, 2));

            // parent
            parent_connections.push_back(Connection(Port(1,1),Port(2,0)));
            parent_connections.push_back(Connection(Port(1,2),Port(2,0)));
            parent_connections.push_back(Connection(Port(2,3),Port(1,2)));
        }
    }
};

} } } // namespace paradevs tests boost_graph

#endif
