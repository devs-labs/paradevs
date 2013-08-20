/**
 * @file tests/boost_graph/partitioning/main.cpp
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

#include <tests/boost_graph/partitioning/gggp.hpp>
#include <tests/boost_graph/partitioning/graph_build.hpp>

#include <boost/timer.hpp>

#include <iostream>

using namespace paradevs::tests::boost_graph;

UnorientedGraph::vertex_iterator vertexIt, vertexEnd;
UnorientedGraph::adjacency_iterator neighbourIt, neighbourEnd;

OrientedGraph::vertex_iterator vertexIto, vertexEndo;
OrientedGraph::adjacency_iterator neighbourIto, neighbourEndo;

int main()
{
    boost::timer t;

    srand((unsigned)time(NULL));

    UnorientedGraph* g = new UnorientedGraph();
    OrientedGraph* go = new OrientedGraph();
    UnorientedGraph* graph_origin = new UnorientedGraph();
    OrientedGraph* gop = new OrientedGraph();

    build_graph(*g, *go);
    build_graph(*graph_origin, *gop);

    delete gop;

    int nbr_parties = 4;

    /*EntiersEntiers Partition = Random_partitioning(g,nbr_parties);

    for(uint i = 0; i < Partition.size(); i++){
    	for(uint j = 0; j < Partition.at(i)->size(); j++){
    		std::cout<<Partition.at(i)->at(j)<<std::endl;
    	}
    	std::cout<<std::endl;
    }

    std::cout<<Partition.size()<<std::endl;*/

    Edges edge_partie;
    OutputEdgeList outputedgeslist(nbr_parties);
    InputEdgeList inputedgelist;
    Connections connections;

    std::cout<<num_vertices(*g)/4<<std::endl;

    OrientedGraphs graphs = Multiniveau(num_vertices(*g)/2, g, graph_origin, go, nbr_parties,"rand", "gggp_pond",
                                        "cut_norm", "norm", edge_partie ,
                                        outputedgeslist, inputedgelist,
                                        connections);

    std::cout << std::endl;
    std::cout << "Sous Graphes :" << std::endl;
    for (uint i = 0; i< graphs.size(); i++) {
        tie(vertexIto, vertexEndo) = vertices(graphs[i]);
        for (; vertexIto != vertexEndo; ++vertexIto) {
            std::cout << graphs[i][*vertexIto]._index
                      << " est connecté avec ";
            tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,
                                                                 graphs[i]);
            for (; neighbourIto != neighbourEndo; ++neighbourIto)
                std::cout << graphs[i][*neighbourIto]._index << " ";
            std::cout << " et son poids est de "
                      << graphs[i][*vertexIto]._weight<<std::endl;
        }
        std::cout << std::endl;
    }

    std::clog << "OutputEdgeList :" << std::endl;
    for (uint i = 0; i < outputedgeslist.size(); i++) {
        for (uint j = 0; j < outputedgeslist.at(i).size(); j++){
            std::cout << outputedgeslist.at(i).at(j).first << " "
                      << outputedgeslist.at(i).at(j).second << std::endl;
        }
    }
    std::cout << std::endl;

    std::clog << "InputEdgeList :" << std::endl;
    for (uint i = 0; i < inputedgelist.size(); i++) {
        for (uint j = 0; j < inputedgelist.at(i).size(); j++){
            std::cout << inputedgelist.at(i).at(j).first << " "
                      << inputedgelist.at(i).at(j).second << std::endl;
        }
    }
    std::cout << std::endl;

    std::clog << "Connections :" << std::endl;
    for (uint i = 0; i < connections.size(); i++) {
        std::cout << "(" << connections.at(i).first.first << ","
                  << connections.at(i).first.second << ") -> ("
                  << connections.at(i).second.first << ","
                  << connections.at(i).second.second << ")"
                  << std::endl;
    }

	delete graph_origin;
	delete go;

    std::cout << "Duration : " << t.elapsed() << " seconds" << std::endl;

}
