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

namespace paradevs { namespace tests { namespace boost_graph {

class PartitioningGraphBuilder
{
public:
    PartitioningGraphBuilder()
    { }

    void build(OrientedGraphs& graphs,
               InputEdgeList& input_edges,
               OutputEdgeList& output_edges,
               Connections& parent_connections)
    {
        srand(7266);

        UnorientedGraph* g = new UnorientedGraph();
        OrientedGraph* go = new OrientedGraph();
        UnorientedGraph* graph_origin = new UnorientedGraph();
        OrientedGraph* gop = new OrientedGraph();

        build_graph(*g, *go);
        build_graph(*graph_origin, *gop);

        delete gop;

        int nbr_parties = 8;
        Edges edge_partie;
        Connections connections;

        /*
         * teste sur la fonction gggp_pond amélioration + validation complete
         * sur un nombre de parties supérieur à 6. Recherche de l'origine de
         * l'erreur de segmentation et la corriger
         */

        output_edges = OutputEdgeList(nbr_parties);

        graphs = Multiniveau(num_vertices(*g)/4, g, graph_origin, go, nbr_parties,"rand", "gggp_pond",
                             "cut_norm", "norm", edge_partie ,
                             output_edges, input_edges,
                             parent_connections);
        //std::cout<<"Sorti ! "<<std::endl;

        delete graph_origin;

    }
};

} } } // namespace paradevs tests boost_graph

#endif
