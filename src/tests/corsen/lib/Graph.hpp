/**
 *
 * \file Graph.hpp
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 30 mai 2013
 * \brief Générateur du graphe représentant un bassin versant.
 */

/*
 * Copyright (C) 2012-2013 ULCO http://www.univ-littoral.fr
 * Copyright (C) 2012-2013 INRA http://www.inra.fr
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

#ifndef GRAPH_HPP_
#define GRAPH_HPP_ 1

#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
#include <unistd.h>
#include <cstdio>
#include <iterator>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <boost/array.hpp>
#include <boost/format.hpp>
#include "boost/graph/topological_sort.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/version.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include "Constantes.h"
#include "Vertex.h"
#include "Exception.h"
#include "Parameters.h"

/*! \class Graph
 * \brief représente un bassin versant sous forme de graphe.
 *
 *  La classe détermine le maillage du bassin versant. Pour effectuer
 *  cela, la classe crée un objet de type boost::graph et le complète
 *  en y ajoutant des sommets et des arcs.
 */

class Graph
{
public:

    /*!
     *  \brief Constructeur
     *
     *  initialisation de certains attributs.
     */
    Graph();

    virtual ~Graph()
    { }

    /*!
     *  \brief Construction du graphe.
     *
     *  Méthode qui crée les sommets et génère le boost::graph en fonction des
     *  données contenues dans ceux-ci.
     *
     *  \param elevationMatrix : données d'altitudes du bassin versant
     *  \param p : paramètres du programme.
     */
    void build(std::vector<float> * elevationMatrix, Parameters * p);

    const DirectedGraph& graph() const
    { return _go; }

    /*!
     * \brief Afficher
     *
     *  Affiche les sommets, les arêtes et les arêtes incidentes.
     */
    void display();

private:

    /*!
     * \brief Créer arc.
     *
     * Crée un nouvel arc entre deux sommets, il sera ajouté au
     * vecteur d'arcs du boost Graph.
     * \param Source : arc sortant
     * \param Dest : arc entrant
     * \param pourcent : ratio entre le poids du sommet et la somme
     * des poids de ses sommets voisins.
     */
    void createEdge(Vertex * src , Vertex & dst, float pourcent)
    {
        boost::add_edge(src->getBoostGraphIdentifier(),
                        dst.getBoostGraphIdentifier(),
                        EdgeProperties(0., 0., pourcent),_go);
    }

    /*!
     * \brief Créer sommet.
     *
     * Crée un nouveau sommet si inexistant, il sera ajouté au vecteur
     * de sommets du boost Graph.
     *
     */
    void createVertex(Vertex & m)
    {
        if (m.getBoostGraphIdentifier() == 4294967295)
            m.setBoostGraphIdentifier(
                boost::add_vertex(VertexProperties(
                                      (boost::format("p_%1%") %
                                       (m.getIdentifier())).str(),
                                      m.getIdentifier(),
                                      m.getCoord()),_go));
    }

    /*!
     * \brief Construire maillage.
     *
     * 	Classement des sommets du bassin versant selon leur dénivellation.
     * 	Ajout d'arcs au graphe selon plusieurs critères :
     * 	 - La positionnement des sommets.
     * 	 - La dénivellation entre les sommets.
     */
    void buildMesh();

    /*!
     * \brief Construire maillages plateaux
     *
     * Ajout d'arcs au graphe selon plusieurs critères :
     *  - Le positionnement des sommets.
     * 	- L'absence ou la faible dénivellation entre les sommets.
     */
    void buildTablelandsMeshes();

    /*!
     * \brief Rechercher exutoire
     *
     * Ajout dans la liste les sommets dits 'exutoire' du plateau étudié.
     *
     */
    void searchOutlet(Vertex & m, int nbi);

    /*!
     * \brief Calculer géodésique.
     *
     *  Calcule le chemin le plus court, ou l'un des plus courts
     *  chemins s'il en existe plusieurs, entre deux sommets du bassin versant.
     */

    void computeGeodesic();

    /*!
     * \brief Ajouter des arcs au maillage plateau.
     *
     * Ajout d'arcs au graphe reliant les sommets entre eux selon
     * plusieurs critères :
     *  - Leur positionnement.
     * 	- L'absence ou la faible dénivellation entre eux.
     */

    void addTablelandsEdges();

    DirectedGraph            _go; /*!< Graphe Orienté */
    std::map < int, Vertex > _vertices; /*!< Sommets du bassin versant */
    std::vector < Vertex* >  _tablelandVertices; /*!< Ensemble de
                                                  * sommets du bassin
                                                  * versant qui une
                                                  * fois reliés forme
                                                  * un maillage 'plateau' */
    int                      _isolatedVertices; /*!< Nombre de sommets sans
                                                 * exutoire du bassin versant */
    const Parameters*        _param; /*!< Paramètres du programme */
};

#endif /* GRAPHE_HPP_ */
