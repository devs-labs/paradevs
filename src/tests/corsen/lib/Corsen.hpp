/*!
 * \file Corsen.h
 * \brief Charge les différents fichiers en mémoire et lance la génération du graphe.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
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
#ifndef CORSEN_H_
#define CORSEN_H_
#define BOOST_TEST_DYN_LINK

#include <fstream>
#include <sstream>
#include <cstdio>
#include <stack>
#include <boost/foreach.hpp>
#include "ElevationFileStream.h"
#include "ParametersFileStream.h"
#include "LayersFileStream.h"
#include "OutletFileStream.h"
#include "SlopeFileStream.h"
#include "SoilFileStream.h"
#include "DrainFileStream.h"
#include "LayersTextFileStream.h"
#include "ContextFileReader.h"
#include "ContextData.h"
#include "Constantes.h"
#include "Functions.h"
#include "Graph.hpp"

/*! \class Corsen
 * \brief est la classe centrale de la bibliothèque.
 *
 *  La classe gère la lecture, l'ecriture des différents fichiers de données
 *  pour un bassin versant. Elle génère le boost graph correspondant aux
 *  données.
 */

class Corsen
{
public:
  /*!
   *  \brief Constructeur
   *
   *  Constructeur de la classe Corsen.
   */
  Corsen();

  /*!
   *  \brief Lecture
   *
   *  Lecture des fichiers de données du bassin versant.
   *
   *  \param files : liste des fichiers à lire.
   *  \param absolutePath : emplacement des fichiers à lire.
   */
  void read(std::vector<std::string* >& files,
	    std::string& absolutePath) throw (FileNotFound, ReadError,
					      InvalidFileFormat,
					      std::invalid_argument);

  /*!
   *  \brief Construire graphe
   *
   *	génère le boostGraph
   */
  void buildGraph();

  /*!
   *  \brief Affichage
   *
   *  Affiche le contenu des attributs.
   */
  void display();

  const std::vector<float> * getElevationMatrix() const
  {
    return _elevationMatrix;
  }

  const Graph& getGraph() const {
    return _graph;
  }

  const std::vector<Layer> * getLayers() const {
    return _layers;
  }

  const std::list<Outlet*> * getOutlets() const {
    return _outlets;
  }

  const Parameters * getParam() const {
    return _param;
  }

  const Node * getExutoire() const {
    return _outlet;
  }

  const std::vector<float> * getGradientMatrix() const {
    return _gradientMatrix;
  }

  const std::vector<float> * getSoilMatrix() const {
    return _soilMatrix;
  }

  const std::vector<float> * getElevationMatrixBv() const {
    return _elevationMatrixBv;
  }

  /*!
   *  \brief Destructeur
   *
   *  Destructeur de la classe Corsen
   */
  virtual ~Corsen();

private:

	Graph _graph;
	ParametersFileStream * _pfs; /*!< Flux fichier paramètres */
	ElevationFileStream * _efs; /*!< Flux fichier des données d'altitudes */
	OutletFileStream * _ofs; /*!< Flux fichier des arbres de drainage */
	SlopeFileStream * _gfs; /*!< Flux fichier des pentes */
	SoilFileStream * _sfs;
	LayersFileStream * _lfs; /*!< Flux fichier des couches*/
	DrainFileStream<corsenContainers::vecS, float> * _dfs;
	std::vector<float> * _gradientMatrix ;/*!< données pentes */
	std::vector<float> * _soilMatrix;
	std::vector<float> * _elevationMatrix;/*!< données altitudes */
	std::list<Outlet *> * _outlets;/*!< liste des exutoires */
	std::vector<Layer> *  _layers; /*!< liste des couches */
	Parameters * _param; /*!< paramètres du programme */
	Node * _outlet; /*!< noeud exutoire */
	std::vector<float> * _elevationMatrixBv;
};

#endif /* CORSEN_H_ */
