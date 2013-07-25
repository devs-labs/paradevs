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

    og[v6] = VertexProperties(6, 1.5, NORMAL_PIXEL);
    og[v8] = VertexProperties(8, 1., NORMAL_PIXEL);
    og[v10] = VertexProperties(10, 1.5, NORMAL_PIXEL);
    og[v0] = VertexProperties(0, 3, NORMAL_PIXEL);
    og[v1] = VertexProperties(1, 2, NORMAL_PIXEL);
    og[v2] = VertexProperties(2, 2, NORMAL_PIXEL);
    og[v3] = VertexProperties(3, 2, NORMAL_PIXEL);
    og[v4] = VertexProperties(4, 1.5, NORMAL_PIXEL);
    og[v5] = VertexProperties(5, 1.5, NORMAL_PIXEL);
    og[v7] = VertexProperties(7, 1., TOP_PIXEL);
    og[v9] = VertexProperties(9, 1.5, TOP_PIXEL);

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

    ug[v61] = VertexProperties(60, 1.5, NORMAL_PIXEL);
    ug[v81] = VertexProperties(80, 1, NORMAL_PIXEL);
    ug[v101] = VertexProperties(100, 1.5, NORMAL_PIXEL);
    ug[v01] = VertexProperties(0, 3, NORMAL_PIXEL);
    ug[v11] = VertexProperties(10, 2, NORMAL_PIXEL);
    ug[v21] = VertexProperties(20, 2, NORMAL_PIXEL);
    ug[v31] = VertexProperties(30, 2, NORMAL_PIXEL);
    ug[v41] = VertexProperties(40, 1.5, NORMAL_PIXEL);
    ug[v51] = VertexProperties(50, 1.5, NORMAL_PIXEL);
    ug[v71] = VertexProperties(70, 1, TOP_PIXEL);
    ug[v91] = VertexProperties(90, 1.5, TOP_PIXEL);

}

} } } // namespace paradevs tests boost_graph
