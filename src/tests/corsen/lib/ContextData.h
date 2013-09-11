/*!
 * \file ContextData.h
 * \brief Stocke les données du fichier context.
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

#ifndef CONTEXTDATA_H_
#define CONTEXTDATA_H_

#include <string>
#include "Singleton.h"

/*! \class ContextData
 *
 * \brief regroupe les données du fichier context.
 *
 */

class ContextData : public Singleton<ContextData>
{
	friend class Singleton<ContextData>;

public :

	/**
	 * \struct mesh_chrono_t
	 * \brief structure pour gestion des sorties.
	 */
	struct mesh_chrono_t
	{
		int line;       /*!< numéro de ligne */
		int column;       /*!< numéro de colonne */
		FILE * ptf;  /*!< pointeur vers fichier sorties */

		mesh_chrono_t() : line(0), column(0), ptf(NULL) {}
	};


	typedef int day_t ;

	/**
	 * \struct date_t
	 * \brief structure pour représentation des dates.
	 */
	struct date_t
	{
		unsigned day; /*!< numéro jour */
		unsigned month; /*!< numéro mois */
		unsigned year; /*!< numéro année */

		date_t():day(0), month(0),year(0) {}
	};

	std::string _pathToData; /*!< chemin vers le répertoire contenant les fichiers de données */
	int _soilNumber; /*!< numéro de la couche sur laquelle on travaille */
	char * _absolutePath; /*!< chemin absolu vers le répertoire principal d'un projet TNT */
	double _defaultNetworkSlope; /*!< pente par défaut du réseau */
	std::string _soilFileName; /*!< nom du fichier de couches */
	double _pptionAccess; /*!< prop_acces_eau */
	mesh_chrono_t _outletsCoordinates[15]; /*!< Coordonnées exutoire */
	day_t _numberDays; /*!< Durée en jours de la simulation */
	date_t _simulationStartDate; /*!< Date du premier jour */

private :

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe ContextData.
	 *
	 *  Initialise les attributs.
	 *
	 */

	ContextData()
{
		_soilNumber = 0;
		_absolutePath = NULL;
		_defaultNetworkSlope = 0.;
		_pptionAccess = 0.;
		_numberDays = 0;
}
	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe ContextData
	 */

	~ContextData(){}
};

#endif /* CONTEXTDATA_H_ */
