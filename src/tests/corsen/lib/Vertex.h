/*!
 * \file Vertex.h
 * \brief les types de données nécessaires aux sommets.
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

#ifndef VERTEX_H_
#define VERTEX_H_

#include <sstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include "Parameters.h"
#include "Coordinates.h"
#include "Constantes.h"


/**
 * \struct VertexProperties
 * \brief structure représentant un sommet dans le boost::Graph.
 */
struct VertexProperties
{
	std::string name; /*!< nom du sommet*/
	int identifier; /*!< identifiant du sommet*/
	Coordinates c; /*!< Coordonnées du sommet*/
	VertexProperties() : name(""), identifier(0), c() {} /*!< Constructeur par defaut*/
	VertexProperties(std::string const& n, int i, const Coordinates & coord) : name(n), identifier(i), c(coord)  {} /*!< Constructeur avec paramètres*/
};

/**
 * \struct EdgeProperties
 * \brief structure représentant un arc dans le boost::Graph.
 */
struct EdgeProperties
{
	double weight;
	double distance;
	float pourcent;
	EdgeProperties() : weight(0.), distance(0.), pourcent(0.) {}
	EdgeProperties(double w, double d, float p) : weight(w), distance(d), pourcent(p) {}
};


typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, VertexProperties, EdgeProperties > DirectedGraph; /*!< Liste d'adjacence */

//Some typedefs for simplicity
typedef boost::graph_traits<DirectedGraph>::vertex_descriptor vertex_t; /*!< Simplification descripteur de sommet de la liste d'adjacence accessible via la classe de traits graph_traits */
typedef boost::graph_traits<DirectedGraph>::edge_descriptor edge_t; /*!< Simplification descripteur d'un arc de la liste d'adjacence accessible via la classe de traits graph_traits */


/*! \class Vertex
 * \brief représente un point du bassin versant.
 */

class Vertex
{
private :
	vertex_t _boostGraphIdentifier; /*!< identifiant boostGraph liant une instance de cette classe à un sommet du boostGraph */
	char _mp; /*!< Type */
	int _identifier; /*!< Identifiant*/
	Coordinates _coordinates; /*!< Coordonnées en 2D */
	float _elevation /*!< Altitude */;
	std::vector<Vertex *>_neighbours; /*!< liste voisins */
	float _derive; /*!< derive */

public :

	enum dataType {elevation, derive};

	/*!
	 *  \brief Constructeur par défaut
	 *
	 *  Constructeur de la classe Vertex
	 *
	 */

	Vertex() :_coordinates()
	{
		_mp = 'n';
		_identifier = 0;
		_elevation = 0.;
		_derive = 0.;
		_boostGraphIdentifier = 4294967295;
	}

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur avec paramètres de la classe Vertex
	 *
	 * \param id : identifiant
	 * \param c : Coordonnées
	 * \param elevation : altitude
	 */

	Vertex(int id, const Coordinates & c, float elevation)
	{
		_derive = -999999.0;
		_boostGraphIdentifier = 4294967295;
		_mp = 'n';
		_identifier = id;
		_coordinates = c;
		this->_elevation = elevation;
	}

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur par recopie de la classe Vertex
	 *
	 * \param v : sommet à copier.
	 */

	Vertex(const Vertex & v)
	{
		_mp = v.getMp();
		_identifier = v.getIdentifier();
		_coordinates = v.getCoord();
		_elevation = v.getElevation();
		_boostGraphIdentifier = v.getBoostGraphIdentifier();
		_derive = v.getDerive();
		_neighbours = v.getNeighbours();
	}

	virtual ~Vertex(){}

	const std::vector<Vertex*> & getNeighbours() const
			{
		return _neighbours;
			}

	void setNeighbours(const std::vector<Vertex*> & neighbours)
	{
		this->_neighbours = neighbours;
	}

	const Coordinates& getCoord() const
	{
		return _coordinates;
	}


	/*!
	 * \brief Transformer en chaîne.
	 *
	 * Représentation chaînée de l'objet
	 *
	 * \param void
	 * \return string
	 */


	const std::string toString() const
	{
		std::stringstream s;
		s <<"mp :"<<_mp <<" coordonnées : "<<_coordinates.toString()<<" altitude : "<<_elevation<<" identifiant : "<<_identifier<<" sommet : "<<_boostGraphIdentifier<<" derive : "<<_derive;
		return s.str();
	}


	float getElevation() const
	{
		return _elevation;
	}

	vertex_t getBoostGraphIdentifier() const
	{
		return _boostGraphIdentifier;
	}

	void setBoostGraphIdentifier(vertex_t vertex)
	{
		this->_boostGraphIdentifier = vertex;
	}

	int getIdentifier() const {
		return _identifier;
	}

	void setDerive(float derive) {
		this->_derive = derive;
	}

	float getDerive() const
	{
		return _derive;
	}

	/*!
	 *  \brief sigma
	 *  \param dt : précise l'attribut avec lequel effectuer le calcul.
	 *  \return la somme des poids des sommets voisins du sommet
	 */

	float sigma(dataType dt) const
	{
		float somme = 0. ;

		if(dt == elevation)
		{
			for(std::vector<Vertex *>::const_iterator itVoisins = _neighbours.begin();itVoisins!=_neighbours.end();itVoisins++)
			{
				if ((**itVoisins).getElevation() > ALTMER)
					somme += (*itVoisins)->tanBxL(getInstance(), elevation) ;
			}
		}
		else
		{
			for(std::vector<Vertex *>::const_iterator itVoisins = _neighbours.begin();itVoisins!=_neighbours.end();itVoisins++)
			{
				if ((**itVoisins).getDerive() > ALTMER)
					somme += (*itVoisins)->tanBxL(getInstance(), derive);
			}
		}
		return somme ;
	}

	/*!
	 * \brief teste la position de la maille.
	 * \return true si la maille testée se situe sur le bord_de_mer, faux sinon
	 */

	bool isOnSeaside()
	{
		for (std::vector<Vertex *>::const_iterator it = _neighbours.begin(); it !=_neighbours.end(); it++)
		{
			if ((*it)->getElevation() <= ALTMER)
				return true;
		}
		return false;
	}

	/*!
	 * \brief tanBxL
	 * \param v : le sommet avec laquelle effectuer le calcul.
	 * \param dt : précise l'attribut avec lequel effectuer le calcul.
	 * \return le poids du sommet dans la diffusion de la surface contributive vers la maille v.
	 */

	float tanBxL(const Vertex * v, dataType dt ) const
	{
		float delta;

		if(dt == elevation)
			delta = v->getElevation() -_elevation;
		else
			delta = v->getDerive() -_derive;

		if (delta > 0.)
			return ((_coordinates.isSameLine(v->getCoord()) || _coordinates.isSameColumn(v->getCoord())) ? delta*0.5 : delta*0.354) ;
		else
			return 0. ;
	}

	char getMp() const
	{
		return _mp;
	}

	void setMp(char mp)
	{
		this->_mp = mp;
	}

	const Vertex * getInstance() const
	{
		return this;
	}


};


#endif /* VERTEX_H_ */
