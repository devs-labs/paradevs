/*!
 * \file Parameters.h
 * \brief paramètres du programme et du bassin versant.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 12 juin 2013
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

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <iostream>
#include <sstream>

/*! \class Parameters
 *
 * \brief Regroupe les paramètres du programme et du bassin versant.
 *
 */

class Parameters
{
public :
	int _gap;
	bool _meshMode;
	int _riverLevel;
	int _displaySea;
	int _nodesPerLine;
	int _nodesPerColumn;
	int _linesNumber;
	int _columnsNumber;
	float _meshSize;
	float _horizontalMeshStep;
	float _verticalMeshStep;
	float _meshArea;
	float _colorColumnsNumber;
	int _charColumnsNumber;
	float lx0;
	float ly0;
	float lx1;
	float ly1;
	float lx2;
	float ly2;
	float lx3;
	float ly3;
	bool _lambertCadre;

	/*!
	 * \brief Transformer en chaîne.
	 *
	 * Représentation chaînée de l'objet.
	 *
	 * \param void
	 * \return string
	 */

	const std::string toString() const
	{
		std::stringstream s;

		s << "\n - trou " <<((_gap == 0 ) ? "non" : "oui")<<"\n - modeMaille "<<((_meshMode == false ) ? "non" : "oui")<<"\n - afficherMer "<<((_displaySea == 0 ) ? "non" : "oui") <<"\n - nbNoeudLig "<<_nodesPerLine<<"\n - nbNoeudCol "<<_nodesPerColumn
				<<"\n - nbLig "<<_linesNumber<<"\n - nbCol "<<_columnsNumber<<"\n - tailleMaille "<<_meshSize<<"\n - pasMailleX "<<_horizontalMeshStep<<"\n - pasMailleY "<<_verticalMeshStep<<"\n - aireMaille "<<_meshArea<<
				"\n - colorColumnsNumber "<<_colorColumnsNumber<<"\n - nbColCar "<<_charColumnsNumber<<"\n - lx0 "<<lx0<<"\n - ly0 "<<ly0<<"\n - lx1 "<<lx1<<"\n - ly1 "<<ly1<<"\n - lx2 "<<lx2<<"\n - ly2 "<<ly2<<"\n - lx3 "<<lx3<<"\n - ly3 "<<ly3<<"\n - cadreLambert "<<((_lambertCadre == false ) ? "non" : "oui");
		return s.str();
	}
};


#endif /* PARAMETERS_H_ */
