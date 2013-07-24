/**
 * @file tests/boost_graph/partitioning/graph_build.cpp
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

#include <tests/boost_graph/partitioning/graph_build.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

void build_graph(UnorientedGraph& ug, OrientedGraph& og)
{

    /*
     * construction graphe Oriente
     */
    vertex_to v0 = boost::add_vertex(og);
    vertex_to v1 = boost::add_vertex(og);
    vertex_to v2 = boost::add_vertex(og);
    vertex_to v3 = boost::add_vertex(og);
    vertex_to v4 = boost::add_vertex(og);
    vertex_to v5 = boost::add_vertex(og);
    vertex_to v6 = boost::add_vertex(og);
    vertex_to v7 = boost::add_vertex(og);
    vertex_to v8 = boost::add_vertex(og);
    vertex_to v9 = boost::add_vertex(og);
    vertex_to v10 = boost::add_vertex(og);

    add_edge(v1, v0, EdgeProperties(1.), og);
    add_edge(v2, v0, EdgeProperties(1.), og);
    add_edge(v3, v0, EdgeProperties(1.), og);
    add_edge(v1, v2, EdgeProperties(1.), og);
    add_edge(v4, v1, EdgeProperties(1.), og);
    add_edge(v5, v1, EdgeProperties(1.), og);
    add_edge(v6, v1, EdgeProperties(1.), og);
    add_edge(v6, v2, EdgeProperties(1.), og);
    add_edge(v2, v3, EdgeProperties(1.), og);
    add_edge(v9, v3, EdgeProperties(1.), og);
    add_edge(v10, v3, EdgeProperties(1.), og);
    add_edge(v4, v5, EdgeProperties(1.), og);
    add_edge(v5, v6, EdgeProperties(1.), og);
    add_edge(v7, v4, EdgeProperties(1.), og);
    add_edge(v8, v4, EdgeProperties(1.), og);
    add_edge(v7, v8, EdgeProperties(1.), og);
    add_edge(v9, v10, EdgeProperties(1.), og);

    og[v6] = VertexProperties(6, 1.5, TOP_PIXEL);
    og[v8] = VertexProperties(8, 1., TOP_PIXEL);
    og[v10] = VertexProperties(10, 1.5, TOP_PIXEL);
    og[v0] = VertexProperties(0, 3, NORMAL_PIXEL);
    og[v1] = VertexProperties(1, 2, NORMAL_PIXEL);
    og[v2] = VertexProperties(2, 2, NORMAL_PIXEL);
    og[v3] = VertexProperties(3, 2, NORMAL_PIXEL);
    og[v4] = VertexProperties(4, 1.5, NORMAL_PIXEL);
    og[v5] = VertexProperties(5, 1.5, NORMAL_PIXEL);
    og[v7] = VertexProperties(7, 1., NORMAL_PIXEL);
    og[v9] = VertexProperties(9, 1.5, NORMAL_PIXEL);

    /*
     * construction graphe Non Oriente
     */

    vertex_t v01 = boost::add_vertex(ug);
    vertex_t v11 = boost::add_vertex(ug);
    vertex_t v21 = boost::add_vertex(ug);
    vertex_t v31 = boost::add_vertex(ug);
    vertex_t v41 = boost::add_vertex(ug);
    vertex_t v51 = boost::add_vertex(ug);
    vertex_t v61 = boost::add_vertex(ug);
    vertex_t v71 = boost::add_vertex(ug);
    vertex_t v81 = boost::add_vertex(ug);
    vertex_t v91 = boost::add_vertex(ug);
    vertex_t v101 = boost::add_vertex(ug);

    boost::add_edge(v01, v11, EdgeProperties(1.), ug);
    boost::add_edge(v01, v21, EdgeProperties(1.), ug);
    boost::add_edge(v01, v31, EdgeProperties(1.), ug);
    boost::add_edge(v11, v21, EdgeProperties(1.), ug);
    boost::add_edge(v11, v41, EdgeProperties(1.), ug);
    boost::add_edge(v11, v51, EdgeProperties(1.), ug);
    boost::add_edge(v11, v61, EdgeProperties(1.), ug);
    boost::add_edge(v21, v61, EdgeProperties(1.), ug);
    boost::add_edge(v21, v31, EdgeProperties(1.), ug);
    boost::add_edge(v31, v91, EdgeProperties(1.), ug);
    boost::add_edge(v31, v101, EdgeProperties(1.), ug);
    boost::add_edge(v41, v51, EdgeProperties(1.), ug);
    boost::add_edge(v51, v61, EdgeProperties(1.), ug);
    boost::add_edge(v41, v71, EdgeProperties(1.), ug);
    boost::add_edge(v41, v81, EdgeProperties(1.), ug);
    boost::add_edge(v71, v81, EdgeProperties(1.), ug);
    boost::add_edge(v91, v101, EdgeProperties(1.), ug);

    ug[v61] = VertexProperties(60, 1.5, TOP_PIXEL);
    ug[v81] = VertexProperties(80, 1, TOP_PIXEL);
    ug[v101] = VertexProperties(100, 1.5, TOP_PIXEL);
    ug[v01] = VertexProperties(0, 3, NORMAL_PIXEL);
    ug[v11] = VertexProperties(10, 2, NORMAL_PIXEL);
    ug[v21] = VertexProperties(20, 2, NORMAL_PIXEL);
    ug[v31] = VertexProperties(30, 2, NORMAL_PIXEL);
    ug[v41] = VertexProperties(40, 1.5, NORMAL_PIXEL);
    ug[v51] = VertexProperties(50, 1.5, NORMAL_PIXEL);
    ug[v71] = VertexProperties(70, 1, NORMAL_PIXEL);
    ug[v91] = VertexProperties(90, 1.5, NORMAL_PIXEL);

    /* property_map<UnorientedGraph,vertex_degree_t>::type
     * poids_sommets=get(vertex_degree_t(),*g);

     add_edge(0,1,1,*g);
     add_edge(0,2,1,*g);
     add_edge(0,3,1,*g);
     add_edge(1,2,1,*g);
     add_edge(1,4,1,*g);
     add_edge(1,5,1,*g);
     add_edge(1,6,1,*g);
     add_edge(2,6,1,*g);
     add_edge(2,3,1,*g);
     add_edge(3,18,1,*g);
     add_edge(3,21,1,*g);
     add_edge(4,5,1,*g);
     add_edge(4,7,1,*g);
     add_edge(4,8,1,*g);
     add_edge(4,9,1,*g);
     add_edge(5,6,1,*g);
     add_edge(6,15,1,*g);
     add_edge(6,16,1,*g);
     add_edge(6,17,1,*g);
     add_edge(7,8,1,*g);
     add_edge(7,10,1,*g);
     add_edge(7,11,1,*g);
     add_edge(8,9,1,*g);
     add_edge(8,11,1,*g);
     add_edge(8,12,1,*g);
     add_edge(9,13,1,*g);
     add_edge(9,14,1,*g);
     add_edge(10,11,1,*g);
     add_edge(11,12,1,*g);
     add_edge(13,14,1,*g);
     add_edge(15,16,1,*g);
     add_edge(16,17,1,*g);
     add_edge(17,19,1,*g);
     add_edge(19,20,1,*g);
     add_edge(22,23,1,*g);
     add_edge(18,17,1,*g);
     add_edge(18,19,1,*g);
     add_edge(18,20,1,*g);
     add_edge(18,21,1,*g);
     add_edge(21,22,1,*g);
     add_edge(21,23,1,*g);

     put(poids_sommets,0,3);

     for(int i=1;i<4;i++)
     put(poids_sommets,i,2.5);
     for(int i=4;i<7;i++)
     put(poids_sommets,i,2);
     put(poids_sommets,18,2);
     put(poids_sommets,21,2);
     for(int i=7;i<10;i++)
     put(poids_sommets,i,1.5);
     for(int i=15;i<18;i++)
     put(poids_sommets,i,1.5);
     put(poids_sommets,19,1.5);
     put(poids_sommets,20,1.5);
     put(poids_sommets,22,1.5);
     put(poids_sommets,23,1.5);
     for(int i=10;i<15;i++)
     put(poids_sommets,i,1);

     tie(vertexIt, vertexEnd) = vertices(*g);
     for (; vertexIt != vertexEnd; ++vertexIt)
     {
     std::cout << *vertexIt << " est connecté avec ";
     tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, *g);
     for (; neighbourIt != neighbourEnd; ++neighbourIt)
     std::cout << *neighbourIt << " ";
     std::cout<<" et son poids est de "<< poids_sommets[*vertexIt];
     std::cout << "\n";
     }*/
}

} } } // namespace paradevs tests boost_graph
