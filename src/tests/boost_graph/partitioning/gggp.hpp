/**
 * @file tests/boost_graph/partitioning/gggp.hpp
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

#ifndef TESTS_BOOST_GRAPH_PARTITIONING_GGGP_H
#define TESTS_BOOST_GRAPH_PARTITIONING_GGGP_H 1

#include <tests/boost_graph/partitioning/utils.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

void gggp(UnorientedGraph *g, Entiers *sommetsSource,
          Entiers *sommetsDestination, EntiersEntiers &Partition);

void gggp_pond(UnorientedGraph *g, Entiers *sommetsSource,
               Entiers *sommetsDestination, EntiersEntiers &Partition);

void Iter_2l(EntiersEntiers &part, int nbr_parties, UnorientedGraph *g,
             const std::string &nom);

void bissectionRec(UnorientedGraph *g, EntiersEntiers &Partition,
                   int nbr_parties, const std::string &nom);

void Pseudo_random_partitioning(UnorientedGraph *g, EntiersEntiers &Partition,
                                uint nbr_parties);

OrientedGraphs Multiniveau(uint niveau_contraction, UnorientedGraph *g,
                           OrientedGraph *go, int nbr_parties,
                           std::string type_methode,
                           std::string choix_affinage,
                           std::string type_cut,
                           Edges &edge_partie,
                           OutputEdgeList &outputedgeslist,
                           InputEdgeList &inputedgelist,
                           Connections &connections);

} } } // namespace paradevs tests boost_graph

#endif
