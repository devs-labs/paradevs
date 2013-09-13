/**
 * @file tests/boost_graph/graph_partitioning.hpp
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

#ifndef __TESTS_BOOST_GRAPH_GRAPH_PARTITIONING_HPP
#define __TESTS_BOOST_GRAPH_GRAPH_PARTITIONING_HPP 1

#include <tests/boost_graph/graph_defs.hpp>
#include <tests/boost_graph/partitioning/graph_build.hpp>
#include <tests/boost_graph/partitioning/gggp.hpp>

#include <boost/graph/copy.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

class PartitioningGraphBuilder
{
public:
    PartitioningGraphBuilder(int cn, std::string pmn, int cc, bool ccf) :
        cluster_number(cn), partitioning_method_name(pmn),
        contraction_coef(cc), contraction_coef_flag(ccf)
    { }

    void build(OrientedGraphs& graphs,
               InputEdgeList& input_edges,
               OutputEdgeList& output_edges,
               Connections& parent_connections)
    {
        UnorientedGraph* g = new UnorientedGraph();
        OrientedGraph go;
        UnorientedGraph graph_origin;

        // internal examples
        {
            build_graph(*g, go);
            boost::copy_graph(*g, graph_origin);
        }

        // corsen examples
        // {
        //     build_corsen_graph(go);
        //     make_unoriented_graph(go, *g);
        //     boost::copy_graph(*g, graph_origin);
        // }

        Edges edge_partie;
        Connections connections;

        output_edges = OutputEdgeList(cluster_number);

        if (contraction_coef_flag) {
            graphs = Multiniveau(num_vertices(*g) / contraction_coef,
                                 g, &graph_origin, &go,
                                 cluster_number, "HEM",
                                 partitioning_method_name,
                                 "cut_norm", "norm", edge_partie ,
                                 output_edges, input_edges,
                                 parent_connections);
        } else {
            graphs = Multiniveau(contraction_coef, g, &graph_origin, &go,
                                 cluster_number, "HEM",
                                 partitioning_method_name,
                                 "cut_norm", "norm", edge_partie ,
                                 output_edges, input_edges,
                                 parent_connections);
        }

        std::cout << "*********************************" << std::endl;
        std::cout << "Graphs:" << std::endl;
        for (unsigned int i = 0; i < graphs.size(); ++i) {
            std::cout << "graph[" << i << "]:" << std::endl;
            const OrientedGraph& og = graphs[i];
            OrientedGraph::vertex_iterator it_og, end_og;

            tie(it_og, end_og) = vertices(og);
            for (; it_og != end_og; ++it_og) {
                OrientedGraph::adjacency_iterator neighbour_it, neighbour_end;

                std::cout << og[*it_og]._index << " -> { ";
                tie(neighbour_it, neighbour_end) = adjacent_vertices(*it_og,
                                                                     og);
                for (; neighbour_it != neighbour_end; ++neighbour_it) {
                    std::cout << og[*neighbour_it]._index << " ";
                }
                std::cout << "}" << std::endl;
            }
        }
        {
            unsigned int i = 0;

            std::cout << "Input edges:" << std::endl;
            for (InputEdgeList::const_iterator it = input_edges.begin();
                 it != input_edges.end(); ++it, ++i) {
                std::cout << "S" << i << " = {";
                for (InputEdges::const_iterator it2 = it->begin();
                     it2 != it->end(); ++it2) {
                    std::cout << " ( " << it2->first << " -> " << it2->second
                              << " )";
                }
                std::cout << " }" << std::endl;;
            }
        }
        {
            unsigned int i = 0;

            std::cout << "Output edges:" << std::endl;
            for (OutputEdgeList::const_iterator it = output_edges.begin();
                 it != output_edges.end(); ++it, ++i) {
                std::cout << "S" << i << " = {";
                for (OutputEdges::const_iterator it2 = it->begin();
                     it2 != it->end(); ++it2) {
                    std::cout << " ( " << it2->first << " -> " << it2->second
                              << " )";
                }
                std::cout << " }" << std::endl;;
            }
        }

        std::cout << "*********************************" << std::endl;

    }

private:
    int cluster_number;
    std::string partitioning_method_name;
    int contraction_coef;
    bool contraction_coef_flag;
};

class CorsenFlatGraphBuilder
{
public:
    CorsenFlatGraphBuilder()
    { }

    void build(OrientedGraphs& graphs, InputEdgeList& /* input_edges */,
               OutputEdgeList& /* output_edges */,
               Connections& /* parent_connections */)
    {
        OrientedGraph graph;

        build_corsen_graph(graph);
        graphs.push_back(graph);
    }
};

} } } // namespace paradevs tests boost_graph

#endif
