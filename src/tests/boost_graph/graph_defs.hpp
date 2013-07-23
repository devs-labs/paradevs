/**
 * @file tests/boost_graph/graph_defs.hpp
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

#ifndef __TESTS_BOOST_GRAPH_GRAPH_DEFS_HPP
#define __TESTS_BOOST_GRAPH_GRAPH_DEFS_HPP 1

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

} } } // namespace paradevs tests boost_graph

#endif
