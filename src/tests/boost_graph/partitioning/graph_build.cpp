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
    vertex_to v11 = boost::add_vertex(og);
    vertex_to v12 = boost::add_vertex(og);
    vertex_to v13 = boost::add_vertex(og);
    vertex_to v14 = boost::add_vertex(og);
    vertex_to v15 = boost::add_vertex(og);
    vertex_to v16 = boost::add_vertex(og);
    vertex_to v17 = boost::add_vertex(og);
    vertex_to v18 = boost::add_vertex(og);
    vertex_to v19 = boost::add_vertex(og);
    vertex_to v20 = boost::add_vertex(og);
    vertex_to v21 = boost::add_vertex(og);
    vertex_to v22 = boost::add_vertex(og);
    vertex_to v23 = boost::add_vertex(og);
    vertex_to v24 = boost::add_vertex(og);
    vertex_to v25 = boost::add_vertex(og);
    vertex_to v26 = boost::add_vertex(og);
    vertex_to v27 = boost::add_vertex(og);
    vertex_to v28 = boost::add_vertex(og);
    vertex_to v29 = boost::add_vertex(og);
    vertex_to v30 = boost::add_vertex(og);
    vertex_to v31 = boost::add_vertex(og);
    vertex_to v32 = boost::add_vertex(og);
    vertex_to v33 = boost::add_vertex(og);
    vertex_to v34 = boost::add_vertex(og);
    vertex_to v35 = boost::add_vertex(og);
    vertex_to v36 = boost::add_vertex(og);
    vertex_to v37 = boost::add_vertex(og);



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
    add_edge(v8, v11, EdgeProperties(1.), og);
    add_edge(v11, v4, EdgeProperties(1.), og);
    add_edge(v12, v13, EdgeProperties(1.), og);
    add_edge(v12, v7, EdgeProperties(1.), og);
    add_edge(v13, v7, EdgeProperties(1.), og);
    add_edge(v14, v15, EdgeProperties(1.), og);
    add_edge(v14, v12, EdgeProperties(1.), og);
    add_edge(v15, v16, EdgeProperties(1.), og);
    add_edge(v15, v12, EdgeProperties(1.), og);
    add_edge(v16, v17, EdgeProperties(1.), og);
    add_edge(v16, v12, EdgeProperties(1.), og);
    add_edge(v17, v12, EdgeProperties(1.), og);
    add_edge(v18, v19, EdgeProperties(1.), og);
    add_edge(v18, v8, EdgeProperties(1.), og);
    add_edge(v19, v20, EdgeProperties(1.), og);
    add_edge(v19, v8, EdgeProperties(1.), og);
    add_edge(v20, v8, EdgeProperties(1.), og);
    add_edge(v21, v22, EdgeProperties(1.), og);
    add_edge(v21, v19, EdgeProperties(1.), og);
    add_edge(v22, v23, EdgeProperties(1.), og);
    add_edge(v22, v19, EdgeProperties(1.), og);
    add_edge(v23, v19, EdgeProperties(1.), og);
    add_edge(v24, v25, EdgeProperties(1.), og);
    add_edge(v24, v6, EdgeProperties(1.), og);
    add_edge(v25, v6, EdgeProperties(1.), og);
    add_edge(v26, v11, EdgeProperties(1.), og);
    add_edge(v26, v27, EdgeProperties(1.), og);
    add_edge(v26, v24, EdgeProperties(1.), og);
    add_edge(v27, v24, EdgeProperties(1.), og);
    add_edge(v28, v25, EdgeProperties(1.), og);
    add_edge(v29, v27, EdgeProperties(1.), og);
    add_edge(v29, v28, EdgeProperties(1.), og);
    add_edge(v30, v27, EdgeProperties(1.), og);
    add_edge(v31, v32, EdgeProperties(1.), og);
    add_edge(v31, v10, EdgeProperties(1.), og);
    add_edge(v32, v33, EdgeProperties(1.), og);
    add_edge(v32, v10, EdgeProperties(1.), og);
    add_edge(v33, v10, EdgeProperties(1.), og);
    add_edge(v34, v31, EdgeProperties(1.), og);
    add_edge(v34, v35, EdgeProperties(1.), og);
    add_edge(v35, v31, EdgeProperties(1.), og);
    add_edge(v35, v32, EdgeProperties(1.), og);
    add_edge(v36, v32, EdgeProperties(1.), og);
    add_edge(v36, v37, EdgeProperties(1.), og);
    add_edge(v36, v33, EdgeProperties(1.), og);
    add_edge(v37, v33, EdgeProperties(1.), og);


    /*og[v6] = VertexProperties(6, 1.5, NORMAL_PIXEL);
    og[v8] = VertexProperties(8, 1., NORMAL_PIXEL);
    og[v10] = VertexProperties(10, 1.5, NORMAL_PIXEL);
    og[v0] = VertexProperties(0, 3, NORMAL_PIXEL);
    og[v1] = VertexProperties(1, 2, NORMAL_PIXEL);
    og[v2] = VertexProperties(2, 2, NORMAL_PIXEL);
    og[v3] = VertexProperties(3, 2, NORMAL_PIXEL);
    og[v4] = VertexProperties(4, 1.5, NORMAL_PIXEL);
    og[v5] = VertexProperties(5, 1.5, NORMAL_PIXEL);
    og[v7] = VertexProperties(7, 1., TOP_PIXEL);
    og[v9] = VertexProperties(9, 1.5, TOP_PIXEL);*/

    og[v6] = VertexProperties(6, 2.5, NORMAL_PIXEL);
    og[v8] = VertexProperties(8, 2., NORMAL_PIXEL);
    og[v10] = VertexProperties(10, 2.5, NORMAL_PIXEL);
    og[v0] = VertexProperties(0, 4, NORMAL_PIXEL);
    og[v1] = VertexProperties(1, 3, NORMAL_PIXEL);
    og[v2] = VertexProperties(2, 3, NORMAL_PIXEL);
    og[v3] = VertexProperties(3, 3, NORMAL_PIXEL);
    og[v4] = VertexProperties(4, 2.5, NORMAL_PIXEL);
    og[v5] = VertexProperties(5, 2.5, NORMAL_PIXEL);
    og[v7] = VertexProperties(7, 2., NORMAL_PIXEL);
    og[v9] = VertexProperties(9, 2.5, TOP_PIXEL);
    og[v11] = VertexProperties(11, 2, NORMAL_PIXEL);
    og[v12] = VertexProperties(12, 1.5, NORMAL_PIXEL);
    og[v13] = VertexProperties(13, 1.5, NORMAL_PIXEL);
    og[v14] = VertexProperties(14, 1, TOP_PIXEL);
    og[v15] = VertexProperties(15, 1, NORMAL_PIXEL);
    og[v16] = VertexProperties(16, 1, NORMAL_PIXEL);
    og[v17] = VertexProperties(17, 1, NORMAL_PIXEL);
    og[v18] = VertexProperties(18, 1.5, TOP_PIXEL);
    og[v19] = VertexProperties(19, 1.5, NORMAL_PIXEL);
    og[v20] = VertexProperties(20, 1.5, NORMAL_PIXEL);
    og[v21] = VertexProperties(21, 1, TOP_PIXEL);
    og[v22] = VertexProperties(22, 1, NORMAL_PIXEL);
    og[v23] = VertexProperties(23, 1, NORMAL_PIXEL);
    og[v24] = VertexProperties(24, 2, NORMAL_PIXEL);
    og[v25] = VertexProperties(25, 2, NORMAL_PIXEL);
    og[v26] = VertexProperties(26, 1.5, TOP_PIXEL);
    og[v27] = VertexProperties(27, 1.5, NORMAL_PIXEL);
    og[v28] = VertexProperties(28, 1.5, NORMAL_PIXEL);
    og[v29] = VertexProperties(29, 1, TOP_PIXEL);
    og[v30] = VertexProperties(30, 1, TOP_PIXEL);
    og[v31] = VertexProperties(31, 2, NORMAL_PIXEL);
    og[v32] = VertexProperties(32, 2, NORMAL_PIXEL);
    og[v33] = VertexProperties(33, 2, NORMAL_PIXEL);
    og[v34] = VertexProperties(34, 1.5, TOP_PIXEL);
    og[v35] = VertexProperties(35, 1.5, NORMAL_PIXEL);
    og[v36] = VertexProperties(36, 1.5, TOP_PIXEL);
    og[v37] = VertexProperties(37, 1.5, NORMAL_PIXEL);


    /*
     * construction graphe Non Oriente
     */

    vertex_t v01 = boost::add_vertex(ug);
    vertex_t v1r1 = boost::add_vertex(ug);
    vertex_t v2r1 = boost::add_vertex(ug);
    vertex_t v3r1 = boost::add_vertex(ug);
    vertex_t v41 = boost::add_vertex(ug);
    vertex_t v51 = boost::add_vertex(ug);
    vertex_t v61 = boost::add_vertex(ug);
    vertex_t v71 = boost::add_vertex(ug);
    vertex_t v81 = boost::add_vertex(ug);
    vertex_t v91 = boost::add_vertex(ug);
    vertex_t v101 = boost::add_vertex(ug);
    vertex_t v111 = boost::add_vertex(ug);
    vertex_t v121 = boost::add_vertex(ug);
    vertex_t v131 = boost::add_vertex(ug);
    vertex_t v141 = boost::add_vertex(ug);
    vertex_t v151 = boost::add_vertex(ug);
    vertex_t v161 = boost::add_vertex(ug);
    vertex_t v171 = boost::add_vertex(ug);
    vertex_t v181 = boost::add_vertex(ug);
    vertex_t v191 = boost::add_vertex(ug);
    vertex_t v201 = boost::add_vertex(ug);
    vertex_t v211 = boost::add_vertex(ug);
    vertex_t v221 = boost::add_vertex(ug);
    vertex_t v231 = boost::add_vertex(ug);
    vertex_t v241 = boost::add_vertex(ug);
    vertex_t v251 = boost::add_vertex(ug);
    vertex_t v261 = boost::add_vertex(ug);
    vertex_t v271 = boost::add_vertex(ug);
    vertex_t v281 = boost::add_vertex(ug);
    vertex_t v291 = boost::add_vertex(ug);
    vertex_t v301 = boost::add_vertex(ug);
    vertex_t v311 = boost::add_vertex(ug);
    vertex_t v321 = boost::add_vertex(ug);
    vertex_t v331 = boost::add_vertex(ug);
    vertex_t v341 = boost::add_vertex(ug);
    vertex_t v351 = boost::add_vertex(ug);
    vertex_t v361 = boost::add_vertex(ug);
    vertex_t v371 = boost::add_vertex(ug);

    boost::add_edge(v01, v1r1, EdgeProperties(1.), ug);
    boost::add_edge(v01, v2r1, EdgeProperties(1.), ug);
    boost::add_edge(v01, v3r1, EdgeProperties(1.), ug);
    boost::add_edge(v1r1, v2r1, EdgeProperties(1.), ug);
    boost::add_edge(v1r1, v41, EdgeProperties(1.), ug);
    boost::add_edge(v1r1, v51, EdgeProperties(1.), ug);
    boost::add_edge(v1r1, v61, EdgeProperties(1.), ug);
    boost::add_edge(v2r1, v61, EdgeProperties(1.), ug);
    boost::add_edge(v2r1, v3r1, EdgeProperties(1.), ug);
    boost::add_edge(v3r1, v91, EdgeProperties(1.), ug);
    boost::add_edge(v3r1, v101, EdgeProperties(1.), ug);
    boost::add_edge(v41, v51, EdgeProperties(1.), ug);
    boost::add_edge(v51, v61, EdgeProperties(1.), ug);
    boost::add_edge(v41, v71, EdgeProperties(1.), ug);
    boost::add_edge(v41, v81, EdgeProperties(1.), ug);
    boost::add_edge(v71, v81, EdgeProperties(1.), ug);
    boost::add_edge(v91, v101, EdgeProperties(1.), ug);
    boost::add_edge(v41, v111, EdgeProperties(1.), ug);
    boost::add_edge(v71, v121, EdgeProperties(1.), ug);
    boost::add_edge(v71, v131, EdgeProperties(1.), ug);
    boost::add_edge(v121, v131, EdgeProperties(1.), ug);
    boost::add_edge(v121, v141, EdgeProperties(1.), ug);
    boost::add_edge(v121, v151, EdgeProperties(1.), ug);
    boost::add_edge(v121, v161, EdgeProperties(1.), ug);
    boost::add_edge(v121, v171, EdgeProperties(1.), ug);
    boost::add_edge(v141, v151, EdgeProperties(1.), ug);
    boost::add_edge(v151, v161, EdgeProperties(1.), ug);
    boost::add_edge(v161, v171, EdgeProperties(1.), ug);
    boost::add_edge(v81, v111, EdgeProperties(1.), ug);
    boost::add_edge(v121, v131, EdgeProperties(1.), ug);
    boost::add_edge(v81, v181, EdgeProperties(1.), ug);
    boost::add_edge(v81, v191, EdgeProperties(1.), ug);
    boost::add_edge(v81, v201, EdgeProperties(1.), ug);
    boost::add_edge(v181, v191, EdgeProperties(1.), ug);
    boost::add_edge(v191, v201, EdgeProperties(1.), ug);
    boost::add_edge(v191, v211, EdgeProperties(1.), ug);
    boost::add_edge(v191, v221, EdgeProperties(1.), ug);
    boost::add_edge(v191, v231, EdgeProperties(1.), ug);
    boost::add_edge(v211, v221, EdgeProperties(1.), ug);
    boost::add_edge(v221, v231, EdgeProperties(1.), ug);
    boost::add_edge(v111, v261, EdgeProperties(1.), ug);
    boost::add_edge(v61, v241, EdgeProperties(1.), ug);
    boost::add_edge(v61, v251, EdgeProperties(1.), ug);
    boost::add_edge(v241, v251, EdgeProperties(1.), ug);
    boost::add_edge(v241, v261, EdgeProperties(1.), ug);
    boost::add_edge(v241, v271, EdgeProperties(1.), ug);
    boost::add_edge(v261, v271, EdgeProperties(1.), ug);
    boost::add_edge(v251, v281, EdgeProperties(1.), ug);
    boost::add_edge(v271, v291, EdgeProperties(1.), ug);
    boost::add_edge(v271, v301, EdgeProperties(1.), ug);
    boost::add_edge(v281, v291, EdgeProperties(1.), ug);
    boost::add_edge(v281, v301, EdgeProperties(1.), ug);
    boost::add_edge(v101, v311, EdgeProperties(1.), ug);
    boost::add_edge(v101, v321, EdgeProperties(1.), ug);
    boost::add_edge(v101, v331, EdgeProperties(1.), ug);
    boost::add_edge(v311, v321, EdgeProperties(1.), ug);
    boost::add_edge(v321, v331, EdgeProperties(1.), ug);
    boost::add_edge(v311, v341, EdgeProperties(1.), ug);
    boost::add_edge(v311, v351, EdgeProperties(1.), ug);
    boost::add_edge(v321, v351, EdgeProperties(1.), ug);
    boost::add_edge(v321, v361, EdgeProperties(1.), ug);
    boost::add_edge(v331, v361, EdgeProperties(1.), ug);
    boost::add_edge(v331, v371, EdgeProperties(1.), ug);
    boost::add_edge(v341, v351, EdgeProperties(1.), ug);
    boost::add_edge(v361, v371, EdgeProperties(1.), ug);

    /*ug[v61] = VertexProperties(60, 1.5, NORMAL_PIXEL);
    ug[v81] = VertexProperties(80, 1, NORMAL_PIXEL);
    ug[v101] = VertexProperties(100, 1.5, NORMAL_PIXEL);
    ug[v01] = VertexProperties(0, 3, NORMAL_PIXEL);
    ug[v1r1] = VertexProperties(10, 2, NORMAL_PIXEL);
    ug[v2r1] = VertexProperties(20, 2, NORMAL_PIXEL);
    ug[v3r1] = VertexProperties(30, 2, NORMAL_PIXEL);
    ug[v41] = VertexProperties(40, 1.5, NORMAL_PIXEL);
    ug[v51] = VertexProperties(50, 1.5, NORMAL_PIXEL);
    ug[v71] = VertexProperties(70, 1, TOP_PIXEL);
    ug[v91] = VertexProperties(90, 1.5, TOP_PIXEL);*/

    ug[v6] = VertexProperties(6, 2.5, NORMAL_PIXEL);
    ug[v8] = VertexProperties(8, 2., NORMAL_PIXEL);
    ug[v10] = VertexProperties(10, 2.5, NORMAL_PIXEL);
    ug[v0] = VertexProperties(0, 4, NORMAL_PIXEL);
    ug[v1] = VertexProperties(1, 3, NORMAL_PIXEL);
    ug[v2] = VertexProperties(2, 3, NORMAL_PIXEL);
    ug[v3] = VertexProperties(3, 3, NORMAL_PIXEL);
    ug[v4] = VertexProperties(4, 2.5, NORMAL_PIXEL);
    ug[v5] = VertexProperties(5, 2.5, NORMAL_PIXEL);
    ug[v7] = VertexProperties(7, 2., NORMAL_PIXEL);
    ug[v9] = VertexProperties(9, 2.5, TOP_PIXEL);
    ug[v11] = VertexProperties(11, 2, NORMAL_PIXEL);
    ug[v12] = VertexProperties(12, 1.5, NORMAL_PIXEL);
    ug[v13] = VertexProperties(13, 1.5, NORMAL_PIXEL);
    ug[v14] = VertexProperties(14, 1, TOP_PIXEL);
    ug[v15] = VertexProperties(15, 1, NORMAL_PIXEL);
    ug[v16] = VertexProperties(16, 1, NORMAL_PIXEL);
    ug[v17] = VertexProperties(17, 1, NORMAL_PIXEL);
    ug[v18] = VertexProperties(18, 1.5, TOP_PIXEL);
    ug[v19] = VertexProperties(19, 1.5, NORMAL_PIXEL);
    ug[v20] = VertexProperties(20, 1.5, NORMAL_PIXEL);
    ug[v21] = VertexProperties(21, 1, TOP_PIXEL);
    ug[v22] = VertexProperties(22, 1, NORMAL_PIXEL);
    ug[v23] = VertexProperties(23, 1, NORMAL_PIXEL);
    ug[v24] = VertexProperties(24, 2, NORMAL_PIXEL);
    ug[v25] = VertexProperties(25, 2, NORMAL_PIXEL);
    ug[v26] = VertexProperties(26, 1.5, TOP_PIXEL);
    ug[v27] = VertexProperties(27, 1.5, NORMAL_PIXEL);
    ug[v28] = VertexProperties(28, 1.5, NORMAL_PIXEL);
    ug[v29] = VertexProperties(29, 1, TOP_PIXEL);
    ug[v30] = VertexProperties(30, 1, TOP_PIXEL);
    ug[v31] = VertexProperties(31, 2, NORMAL_PIXEL);
    ug[v32] = VertexProperties(32, 2, NORMAL_PIXEL);
    ug[v33] = VertexProperties(33, 2, NORMAL_PIXEL);
    ug[v34] = VertexProperties(34, 1.5, TOP_PIXEL);
    ug[v35] = VertexProperties(35, 1.5, NORMAL_PIXEL);
    ug[v36] = VertexProperties(36, 1.5, TOP_PIXEL);
    ug[v37] = VertexProperties(37, 1.5, NORMAL_PIXEL);

}

} } } // namespace paradevs tests boost_graph
