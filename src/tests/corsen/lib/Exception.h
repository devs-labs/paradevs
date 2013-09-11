/*!
 * \file Exception.h
 * \brief Exceptions du programme Corsen.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 4 juin 2013
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

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>
#include <string>
#include <stdexcept>

/*! \class FileNotFound
 * \brief Exception - Fichier non trouvé.
 *
 *   Déclenché par le programme pour vous signifier que le fichier recherché n'a pas été trouvé.
 */

class FileNotFound : public std::runtime_error
{
public:
	FileNotFound(const std::string& argv = std::string()) :
        std::runtime_error(argv)
    { }
};

/*! \class ReadError
 * \brief Exception - Erreur de lecture.
 *
 * Déclenché par le programme pour vous signifier qu'une erreur de lecture dans un fichier a été rencontrée.
 */

class ReadError : public std::runtime_error
{
public :
	ReadError(const std::string& argv = std::string()):
		std::runtime_error(argv)
	{ }
};

/*! \class InvalidFileFormat
 * \brief Exception - Format de fichier invalide.
 *
 * Déclenché par le programme pour vous signifier que le format du fichier ne peut pas être interprété par les méthodes de la bibliothèque.
 */

class InvalidFileFormat : public std::runtime_error
{
public :
	InvalidFileFormat(const std::string& argv = std::string()):
		std::runtime_error(argv)
	{ }
};


#endif /* EXCEPTION_H_ */
