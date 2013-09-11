/**
 * @file tests/boost_graph/partitioning/defs.hpp
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

#ifndef TESTS_BOOST_GRAPH_PARTITIONING_DEFS_H
#define TESTS_BOOST_GRAPH_PARTITIONING_DEFS_H 1

#include <list>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#include <tests/boost_graph/graph_defs.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

typedef unsigned int uint;

typedef std::vector < int > Entiers;

typedef std::vector < Entiers* > EntiersEntiers;
typedef std::vector < EntiersEntiers > EntiersEntiersEntiers;
typedef std::list < int > List;
typedef std::list < EntiersEntiers* > ListEntiersEntiers;

typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS,
                                VertexProperties,
                                EdgeProperties> UnorientedGraph;

typedef std::vector < UnorientedGraph* > Base_Graph;

typedef boost::graph_traits < UnorientedGraph >::vertex_descriptor vertex_t;
typedef boost::graph_traits < UnorientedGraph >::edge_descriptor edge_t;

typedef OrientedGraph::vertex_descriptor vertex_to;
typedef OrientedGraph::edge_descriptor edge_to;

template < class G >
struct VertexAndEdgeListGraphConcept
{
    void constraints() {
        boost::function_requires < boost::VertexListGraphConcept < G > >();
        boost::function_requires < boost::EdgeListGraphConcept < G > >();
    }
};

} } } // namespace paradevs tests boost_graph

#endif
