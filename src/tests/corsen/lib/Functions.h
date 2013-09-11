/*!
 * \file Functions.h
 * \brief
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

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include "Parameters.h"
#include "Coordinates.h"

class Functions {

public :


	/*!
	 *  \brief Retourner un bit d'un entier.
	 *
	 * \param n : Entier ou chercher le bit .
	 * \param b : Nombre de décalage binaire à effectuer.
	 * \return la valeur du bit b du nombre n.
	 */

	static int getvalbit (int n, unsigned b)
	{
		return ((n>>b) & 1) ;
	}

	/*!
	 *  \brief Affecte la valeur 1 au bit b du nombre pointé par n.
	 *
	 * \param n : Entier à modifier .
	 * \param b : Nombre de décalage binaire à effectuer.
	 * \return void.
	 */

	static void valbiton (int * n, unsigned b)
	{
		*n |= 1<<b ;
	}

	/*!
	 *  \brief Affecte la valeur 0 au bit b du nombre pointé par n.
	 *
	 * \param n : Entier à modifier .
	 * \param b : Nombre de décalage binaire à effectuer.
	 * \return void.
	 */

	static void valbitoff (int *n, unsigned b)
	{
		*n &= ~(1<<b) ;
	}

	static void fatalError(const char* s, int erreurcode);
	//static void ignorelf(char *s);
	//static bool isComment(char *s);
	//static bool isNetwork(int lig, int col);
	//static FILE* openFile(const char *nom, const char *mode);
	//static void handleError(const char* s);

};

#endif /* FUNCTIONS_H_ */
