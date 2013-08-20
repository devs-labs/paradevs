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

#include <tests/boost_graph/graph_defs.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

class FlatGraphBuilder
{
public:
    FlatGraphBuilder()
    { }

    void build(OrientedGraphs& graphs, InputEdgeList& /* input_edges */,
               OutputEdgeList& /* output_edges */,
               Connections& /* parent_connections */)
    {
        OrientedGraph graph;

        OrientedGraph::vertex_descriptor v0 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v1 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v2 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v3 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v4 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v5 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v6 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v7 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v8 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v9 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v10 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v11 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v12 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v13 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v14 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v15 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v16 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v17 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v18 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v19 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v20 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v21 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v22 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v23 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v24 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v25 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v26 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v27 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v28 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v29 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v30 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v31 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v32 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v33 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v34 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v35 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v36 = boost::add_vertex(graph);
        OrientedGraph::vertex_descriptor v37 = boost::add_vertex(graph);

        boost::add_edge(v1, v0, 1., graph);
        boost::add_edge(v2, v0, 1., graph);
        boost::add_edge(v3, v0, 1., graph);
        boost::add_edge(v1, v2, 1., graph);
        boost::add_edge(v4, v1, 1., graph);
        boost::add_edge(v5, v1, 1., graph);
        boost::add_edge(v6, v1, 1., graph);
        boost::add_edge(v6, v2, 1., graph);
        boost::add_edge(v2, v3, 1., graph);
        boost::add_edge(v9, v3, 1., graph);
        boost::add_edge(v10, v3 , 1., graph);
        boost::add_edge(v4, v5, 1., graph);
        boost::add_edge(v5, v6, 1., graph);
        boost::add_edge(v7, v4, 1., graph);
        boost::add_edge(v8, v4, 1., graph);
        boost::add_edge(v7, v8, 1., graph);
        boost::add_edge(v9, v10 , 1., graph);
        boost::add_edge(v8, v11, 1., graph);
        boost::add_edge(v11, v4, 1., graph);
        boost::add_edge(v12, v13, 1., graph);
        boost::add_edge(v12, v7, 1., graph);
        boost::add_edge(v13, v7, 1., graph);
        boost::add_edge(v14, v15, 1., graph);
        boost::add_edge(v14, v12, 1., graph);
        boost::add_edge(v15, v16, 1., graph);
        boost::add_edge(v15, v12, 1., graph);
        boost::add_edge(v16, v17, 1., graph);
        boost::add_edge(v16, v12, 1., graph);
        boost::add_edge(v17, v12, 1., graph);
        boost::add_edge(v18, v19, 1., graph);
        boost::add_edge(v18, v8, 1., graph);
        boost::add_edge(v19, v20, 1., graph);
        boost::add_edge(v19, v8, 1., graph);
        boost::add_edge(v20, v8, 1., graph);
        boost::add_edge(v21, v22, 1., graph);
        boost::add_edge(v21, v19, 1., graph);
        boost::add_edge(v22, v23, 1., graph);
        boost::add_edge(v22, v19, 1., graph);
        boost::add_edge(v23, v19, 1., graph);
        boost::add_edge(v24, v25, 1., graph);
        boost::add_edge(v24, v6, 1., graph);
        boost::add_edge(v25, v6, 1., graph);
        boost::add_edge(v26, v11, 1., graph);
        boost::add_edge(v26, v27, 1., graph);
        boost::add_edge(v26, v24, 1., graph);
        boost::add_edge(v27, v24, 1., graph);
        boost::add_edge(v28, v25, 1., graph);
        boost::add_edge(v29, v27, 1., graph);
        boost::add_edge(v29, v28, 1., graph);
        boost::add_edge(v30, v27, 1., graph);
        boost::add_edge(v30, v28, 1., graph);
        boost::add_edge(v31, v32, 1., graph);
        boost::add_edge(v31, v10, 1., graph);
        boost::add_edge(v32, v33, 1., graph);
        boost::add_edge(v32, v10, 1., graph);
        boost::add_edge(v33, v10, 1., graph);
        boost::add_edge(v34, v31, 1., graph);
        boost::add_edge(v34, v35, 1., graph);
        boost::add_edge(v35, v31, 1., graph);
        boost::add_edge(v35, v32, 1., graph);
        boost::add_edge(v36, v32, 1., graph);
        boost::add_edge(v36, v37, 1., graph);
        boost::add_edge(v36, v33, 1., graph);
        boost::add_edge(v37, v33, 1., graph);

        /*graph[v6] = VertexProperties(6, 1., NORMAL_PIXEL);
        graph[v8] = VertexProperties(8, 1., NORMAL_PIXEL);
        graph[v10] = VertexProperties(10, 1., NORMAL_PIXEL);
        graph[v0] = VertexProperties(0, 1., NORMAL_PIXEL);
        graph[v1] = VertexProperties(1, 1., NORMAL_PIXEL);
        graph[v2] = VertexProperties(2, 1., NORMAL_PIXEL);
        graph[v3] = VertexProperties(3, 1., NORMAL_PIXEL);
        graph[v4] = VertexProperties(4, 1., NORMAL_PIXEL);
        graph[v5] = VertexProperties(5, 1., NORMAL_PIXEL);
        graph[v7] = VertexProperties(7, 1., TOP_PIXEL);
        graph[v9] = VertexProperties(9, 1., TOP_PIXEL);*/

        graph[v6] = VertexProperties(6, 2.5, NORMAL_PIXEL);
        graph[v8] = VertexProperties(8, 2., NORMAL_PIXEL);
        graph[v10] = VertexProperties(10, 2.5, NORMAL_PIXEL);
        graph[v0] = VertexProperties(0, 4, NORMAL_PIXEL);
        graph[v1] = VertexProperties(1, 3, NORMAL_PIXEL);
        graph[v2] = VertexProperties(2, 3, NORMAL_PIXEL);
        graph[v3] = VertexProperties(3, 3, NORMAL_PIXEL);
        graph[v4] = VertexProperties(4, 2.5, NORMAL_PIXEL);
        graph[v5] = VertexProperties(5, 2.5, NORMAL_PIXEL);
        graph[v7] = VertexProperties(7, 2., NORMAL_PIXEL);
        graph[v9] = VertexProperties(9, 2.5, TOP_PIXEL);
        graph[v11] = VertexProperties(11, 2, NORMAL_PIXEL);
        graph[v12] = VertexProperties(12, 1.5, NORMAL_PIXEL);
        graph[v13] = VertexProperties(13, 1.5, NORMAL_PIXEL);
        graph[v14] = VertexProperties(14, 1, TOP_PIXEL);
        graph[v15] = VertexProperties(15, 1, NORMAL_PIXEL);
        graph[v16] = VertexProperties(16, 1, NORMAL_PIXEL);
        graph[v17] = VertexProperties(17, 1, NORMAL_PIXEL);
        graph[v18] = VertexProperties(18, 1.5, TOP_PIXEL);
        graph[v19] = VertexProperties(19, 1.5, NORMAL_PIXEL);
        graph[v20] = VertexProperties(20, 1.5, NORMAL_PIXEL);
        graph[v21] = VertexProperties(21, 1, TOP_PIXEL);
        graph[v22] = VertexProperties(22, 1, NORMAL_PIXEL);
        graph[v23] = VertexProperties(23, 1, NORMAL_PIXEL);
        graph[v24] = VertexProperties(24, 2, NORMAL_PIXEL);
        graph[v25] = VertexProperties(25, 2, NORMAL_PIXEL);
        graph[v26] = VertexProperties(26, 1.5, TOP_PIXEL);
        graph[v27] = VertexProperties(27, 1.5, NORMAL_PIXEL);
        graph[v28] = VertexProperties(28, 1.5, NORMAL_PIXEL);
        graph[v29] = VertexProperties(29, 1, TOP_PIXEL);
        graph[v30] = VertexProperties(30, 1, TOP_PIXEL);
        graph[v31] = VertexProperties(31, 2, NORMAL_PIXEL);
        graph[v32] = VertexProperties(32, 2, NORMAL_PIXEL);
        graph[v33] = VertexProperties(33, 2, NORMAL_PIXEL);
        graph[v34] = VertexProperties(34, 1.5, TOP_PIXEL);
        graph[v35] = VertexProperties(35, 1.5, NORMAL_PIXEL);
        graph[v36] = VertexProperties(36, 1.5, TOP_PIXEL);
        graph[v37] = VertexProperties(37, 1.5, NORMAL_PIXEL);


        graphs.push_back(graph);
    }
};

class HierarchicalGraphBuilder
{
public:
    HierarchicalGraphBuilder()
    { }

    void build(OrientedGraphs& graphs, InputEdgeList& input_edges,
               OutputEdgeList& output_edges, Connections& parent_connections)
    {
        // S1
        {
            OrientedGraph graph;

            OrientedGraph::vertex_descriptor v1 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v4 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v5 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v7 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v8 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v11 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v12 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v13 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v14 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v15 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v16 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v17 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v18 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v19 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v20 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v21 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v22 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v23 = boost::add_vertex(graph);

            boost::add_edge(v4, v1, 1., graph);
            boost::add_edge(v5, v1, 1., graph);
            boost::add_edge(v4, v5, 1., graph);
            boost::add_edge(v7, v4, 1., graph);
            boost::add_edge(v8, v4, 1., graph);
            boost::add_edge(v7, v8, 1., graph);
            boost::add_edge(v8, v11, 1., graph);
            boost::add_edge(v11, v4, 1., graph);
            boost::add_edge(v12, v13, 1., graph);
            boost::add_edge(v12, v7, 1., graph);
            boost::add_edge(v13, v7, 1., graph);
            boost::add_edge(v14, v15, 1., graph);
            boost::add_edge(v14, v12, 1., graph);
            boost::add_edge(v15, v16, 1., graph);
            boost::add_edge(v15, v12, 1., graph);
            boost::add_edge(v16, v17, 1., graph);
            boost::add_edge(v16, v12, 1., graph);
            boost::add_edge(v17, v12, 1., graph);
            boost::add_edge(v18, v19, 1., graph);
            boost::add_edge(v18, v8, 1., graph);
            boost::add_edge(v19, v20, 1., graph);
            boost::add_edge(v19, v8, 1., graph);
            boost::add_edge(v20, v8, 1., graph);
            boost::add_edge(v21, v22, 1., graph);
            boost::add_edge(v21, v19, 1., graph);
            boost::add_edge(v22, v23, 1., graph);
            boost::add_edge(v22, v19, 1., graph);
            boost::add_edge(v23, v19, 1., graph);

            graph[v8] = VertexProperties(8, 2., NORMAL_PIXEL);
            graph[v1] = VertexProperties(1, 3, NORMAL_PIXEL);
            graph[v4] = VertexProperties(4, 2.5, NORMAL_PIXEL);
            graph[v5] = VertexProperties(5, 2.5, NORMAL_PIXEL);
            graph[v7] = VertexProperties(7, 2., NORMAL_PIXEL);
            graph[v11] = VertexProperties(11, 2, NORMAL_PIXEL);
            graph[v12] = VertexProperties(12, 1.5, NORMAL_PIXEL);
            graph[v13] = VertexProperties(13, 1.5, NORMAL_PIXEL);
            graph[v14] = VertexProperties(14, 1, TOP_PIXEL);
            graph[v15] = VertexProperties(15, 1, NORMAL_PIXEL);
            graph[v16] = VertexProperties(16, 1, NORMAL_PIXEL);
            graph[v17] = VertexProperties(17, 1, NORMAL_PIXEL);
            graph[v18] = VertexProperties(18, 1.5, TOP_PIXEL);
            graph[v19] = VertexProperties(19, 1.5, NORMAL_PIXEL);
            graph[v20] = VertexProperties(20, 1.5, NORMAL_PIXEL);
            graph[v21] = VertexProperties(21, 1, TOP_PIXEL);
            graph[v22] = VertexProperties(22, 1, NORMAL_PIXEL);
            graph[v23] = VertexProperties(23, 1, NORMAL_PIXEL);


            /*OrientedGraph::vertex_descriptor v1 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v2 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v4 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v5 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v6 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v7 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v8 = boost::add_vertex(graph);

            boost::add_edge(v1, v2, 1., graph);
            boost::add_edge(v4, v1, 1., graph);
            boost::add_edge(v5, v1, 1., graph);
            boost::add_edge(v6, v1, 1., graph);
            boost::add_edge(v6, v2, 1., graph);
            boost::add_edge(v4, v5, 1., graph);
            boost::add_edge(v5, v6, 1., graph);
            boost::add_edge(v7, v4, 1., graph);
            boost::add_edge(v8, v4, 1., graph);
            boost::add_edge(v7, v8, 1., graph);

            graph[v6] = VertexProperties(6, 1., NORMAL_PIXEL);
            graph[v8] = VertexProperties(8, 1., NORMAL_PIXEL);
            graph[v1] = VertexProperties(1, 1., NORMAL_PIXEL);
            graph[v2] = VertexProperties(2, 1., NORMAL_PIXEL);
            graph[v4] = VertexProperties(4, 1., NORMAL_PIXEL);
            graph[v5] = VertexProperties(5, 1., NORMAL_PIXEL);
            graph[v7] = VertexProperties(7, 1., TOP_PIXEL);*/

            graphs.push_back(graph);
        }
        // S2
        {
            OrientedGraph graph;

            OrientedGraph::vertex_descriptor v0 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v2 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v3 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v6 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v9 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v10 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v24 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v25 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v26 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v27 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v28 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v29 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v30 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v31 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v32 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v33 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v34 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v35 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v36 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v37 = boost::add_vertex(graph);

            boost::add_edge(v2, v0, 1., graph);
            boost::add_edge(v3, v0, 1., graph);
            boost::add_edge(v6, v2, 1., graph);
            boost::add_edge(v2, v3, 1., graph);
            boost::add_edge(v9, v3, 1., graph);
            boost::add_edge(v10, v3 , 1., graph);
            boost::add_edge(v9, v10 , 1., graph);
            boost::add_edge(v24, v25, 1., graph);
            boost::add_edge(v24, v6, 1., graph);
            boost::add_edge(v25, v6, 1., graph);
            boost::add_edge(v26, v27, 1., graph);
            boost::add_edge(v26, v24, 1., graph);
            boost::add_edge(v27, v24, 1., graph);
            boost::add_edge(v28, v25, 1., graph);
            boost::add_edge(v29, v27, 1., graph);
            boost::add_edge(v29, v28, 1., graph);
            boost::add_edge(v30, v27, 1., graph);
            boost::add_edge(v31, v32, 1., graph);
            boost::add_edge(v31, v10, 1., graph);
            boost::add_edge(v32, v33, 1., graph);
            boost::add_edge(v32, v10, 1., graph);
            boost::add_edge(v33, v10, 1., graph);
            boost::add_edge(v34, v31, 1., graph);
            boost::add_edge(v34, v35, 1., graph);
            boost::add_edge(v35, v31, 1., graph);
            boost::add_edge(v35, v32, 1., graph);
            boost::add_edge(v36, v32, 1., graph);
            boost::add_edge(v36, v37, 1., graph);
            boost::add_edge(v36, v33, 1., graph);
            boost::add_edge(v37, v33, 1., graph);

            graph[v6] = VertexProperties(6, 2.5, NORMAL_PIXEL);
            graph[v10] = VertexProperties(10, 2.5, NORMAL_PIXEL);
            graph[v0] = VertexProperties(0, 4, NORMAL_PIXEL);
            graph[v2] = VertexProperties(2, 3, NORMAL_PIXEL);
            graph[v3] = VertexProperties(3, 3, NORMAL_PIXEL);
            graph[v9] = VertexProperties(9, 2.5, TOP_PIXEL);
            graph[v24] = VertexProperties(24, 2, NORMAL_PIXEL);
            graph[v25] = VertexProperties(25, 2, NORMAL_PIXEL);
            graph[v26] = VertexProperties(26, 1.5, TOP_PIXEL);
            graph[v27] = VertexProperties(27, 1.5, NORMAL_PIXEL);
            graph[v28] = VertexProperties(28, 1.5, NORMAL_PIXEL);
            graph[v29] = VertexProperties(29, 1, TOP_PIXEL);
            graph[v30] = VertexProperties(30, 1, TOP_PIXEL);
            graph[v31] = VertexProperties(31, 2, NORMAL_PIXEL);
            graph[v32] = VertexProperties(32, 2, NORMAL_PIXEL);
            graph[v33] = VertexProperties(33, 2, NORMAL_PIXEL);
            graph[v34] = VertexProperties(34, 1.5, TOP_PIXEL);
            graph[v35] = VertexProperties(35, 1.5, NORMAL_PIXEL);
            graph[v36] = VertexProperties(36, 1.5, TOP_PIXEL);
            graph[v37] = VertexProperties(37, 1.5, NORMAL_PIXEL);

            /*OrientedGraph::vertex_descriptor v0 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v3 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v9 = boost::add_vertex(graph);
            OrientedGraph::vertex_descriptor v10 = boost::add_vertex(graph);

            boost::add_edge(v3, v0, 1., graph);
            boost::add_edge(v10, v3, 1., graph);
            boost::add_edge(v9, v10, 1., graph);
            boost::add_edge(v9, v3, 1., graph);

            graph[v10] = VertexProperties(10, 1., NORMAL_PIXEL);
            graph[v0] = VertexProperties(0, 1., NORMAL_PIXEL);
            graph[v3] = VertexProperties(3, 1., NORMAL_PIXEL);
            graph[v9] = VertexProperties(9, 1., TOP_PIXEL);*/

            graphs.push_back(graph);
        }
        {

            /*// input S1
            input_edges.push_back(InputEdges());
            // input S2
            input_edges.push_back(InputEdges());
            input_edges[1].push_back(Edge(1, 0));
            input_edges[1].push_back(Edge(2, 0));
            input_edges[1].push_back(Edge(2, 3));

            // output S1
            output_edges.push_back(OutputEdges());
            output_edges[0].push_back(Edge(1, 0));
            output_edges[0].push_back(Edge(2, 0));
            output_edges[0].push_back(Edge(2, 3));
            // output S2
            output_edges.push_back(OutputEdges());

            // parent
            parent_connections.push_back(Connection(Port(1,1),Port(2,0)));
            parent_connections.push_back(Connection(Port(1,2),Port(2,0)));
            parent_connections.push_back(Connection(Port(1,2),Port(2,3)));*/


            // input S1
            input_edges.push_back(InputEdges());
            input_edges[0].push_back(Edge(6, 1));
            input_edges[0].push_back(Edge(26, 11));
            // input S2
            input_edges.push_back(InputEdges());
            input_edges[1].push_back(Edge(1, 0));
            input_edges[1].push_back(Edge(1, 2));
            input_edges[1].push_back(Edge(5, 6));

            // output S1
            output_edges.push_back(OutputEdges());
            output_edges[0].push_back(Edge(1, 0));
            output_edges[0].push_back(Edge(1, 2));
            output_edges[0].push_back(Edge(5, 6));
            // output S2
            output_edges.push_back(OutputEdges());
            output_edges[1].push_back(Edge(6, 1));
            output_edges[1].push_back(Edge(26, 11));

            // parent
            parent_connections.push_back(Connection(Port(1,1),Port(2,0)));
            parent_connections.push_back(Connection(Port(1,1),Port(2,2)));
            parent_connections.push_back(Connection(Port(1,5),Port(2,6)));
            parent_connections.push_back(Connection(Port(2,6),Port(1,1)));
            parent_connections.push_back(Connection(Port(2,26),Port(1,11)));
        }
    }
};

} } } // namespace paradevs tests boost_graph

#endif
