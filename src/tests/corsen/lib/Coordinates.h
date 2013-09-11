/*!
 * \file Coordinates.h
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 3 juin 2013
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

#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include "Parameters.h"

/*! \class Coordinates
 * \brief représente les coordonnées en 2D d'un point du bassin versant.
 */

class Coordinates
{
private :
	short _line; /*!< numéro de ligne */
	short _column; /*!< numéro de colonne */

public :
	static int _columnsNumber; /*!< nombre de colonnes */
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur par défaut de la classe Coordinates.
	 *  Initialise les attributs à 0.
	 *
	 *  \return void.
	 */

	Coordinates(): _line(0), _column(0) {};

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur avec paramètres de la classe Coordinates.
	 *
	 *  \param line : numéro de la ligne.
	 *  \param column : : numéro de la colonne.
	 *  \return void.
	 */

	Coordinates(short line, short column) : _line(line),_column(column) {}

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur par copie de la classe Coordinates.
	 *
	 *  \param c : Instance de la classe Coordonnées à copier.
	 *  \return void.
	 */

	Coordinates(const Coordinates &c): _line(c.getLine()), _column(c.getColumn()){}

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur avec paramètres de la classe Coordinates.
	 *
	 *  \param nodeCoordinates : Coordonnées de base indispensable pour le calcul de la coordonnée voisine.
	 *  \param identifiantVoisin : détermine la position du voisin par rapport à la coordonnées de base.
	 *  \return void.
	 */

	Coordinates(const Coordinates & nodeCoordinates, char identifiantVoisin)
	{
		switch (identifiantVoisin)
		{
		case '1' :
			_line = nodeCoordinates.getLine() - 1 ;
			_column = nodeCoordinates.getColumn() ;
			break ;
		case '2' :
			_line = nodeCoordinates.getLine() - 1 ;
			_column = nodeCoordinates.getColumn() + 1 ;
			break ;

		case '3':
			_line = nodeCoordinates.getLine() ;
			_column = nodeCoordinates.getColumn() + 1 ;
			break ;

		case '4' :
			_line = nodeCoordinates.getLine() + 1 ;
			_column = nodeCoordinates.getColumn() + 1 ;
			break ;

		case '5' :
			_line = nodeCoordinates.getLine() + 1 ;
			_column = nodeCoordinates.getColumn() ;
			break ;

		case '6' :
			_line = nodeCoordinates.getLine() + 1 ;
			_column = nodeCoordinates.getColumn() - 1 ;
			break ;

		case '7' :
			_line = nodeCoordinates.getLine() ;
			_column = nodeCoordinates.getColumn() - 1 ;
			break ;

		case '8' :
			_line = nodeCoordinates.getLine() - 1 ;
			_column = nodeCoordinates.getColumn() - 1 ;
			break ;
		}
	}


	void operator = (const Coordinates& c)
	{
		_line = c.getLine();
		_column = c.getColumn();
	}

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Coordinates
	 */

	virtual ~Coordinates()
	{

	}

	short getColumn() const
	{
		return _column;
	}

	void setColumn(short colonne)
	{
		this->_column = colonne;
	}

	short getLine() const
	{
		return _line;
	}

	void setLine(int ligne)
	{
		this->_line = ligne;
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
		std::stringstream ss;
		ss<<"Ligne "<<_line<<" Colonne "<<_column<<" ";
		return ss.str();
	}

	/*!
	 * \brief clé.
	 *
	 * Génère un identifiant unique (sans doublons) en fonction du numéro de la ligne et de la colonne et du nombre de colonnes.
	 *
	 * \param void
	 * \return identifiant de la coordonnées.
	 *
	 */
	int key() const
	{ return (_line * _columnsNumber + _column); }

	virtual bool operator==(const Coordinates& coordinates) const
					{ return key() == coordinates.key(); }

	virtual bool operator!=(const Coordinates& coordinates) const
					{return key() != coordinates.key();}

	virtual bool operator<(const Coordinates& coordinates) const
	{ return key() < coordinates.key(); }

	/*!
	 * \brief est valide ?
	 *
	 * Vérifie que la coordonnées correspond bien à un point du bassin versant.
	 * \param p : paramètres du programme et du bassin versant.
	 * \return true si elle est située dans le bassin versant, false sinon.
	 *
	 */

	bool isValid (Parameters * p)
	{
		return (_line>=0 && _line <p->_linesNumber && _column>=0 && _column < p->_columnsNumber) ;
	}

	/*!
	 * \brief est sur la même ligne ?
	 *
	 * Vérifie que si les lignes sont identiques.
	 * \param line : numéro de la ligne.
	 * \return true si elles sont identiques, false sinon.
	 *
	 */

	bool isSameLine(short line) const
	{
		return (_line == line);
	}

	/*!
	 * \brief est sur la même colonne ?
	 *
	 * Vérifie que si les colonnes sont identiques.
	 * \param column : numéro de la colonne.
	 * \return true si elles sont identiques, false sinon.
	 *
	 */
	bool isSameColumn(short column) const
	{
		return (_column == column);
	}

	/*!
	 * \brief est sur la même ligne ?
	 *
	 * Vérifie que si les lignes sont identiques.
	 * \param c : Coordonnées à tester.
	 * \return true si elles sont identiques, false sinon.
	 *
	 */

	bool isSameLine(const Coordinates & c) const
	{
		return (_line == c.getLine());
	}

	/*!
	 * \brief est sur la même colonne ?
	 *
	 * Vérifie que si les colonnes sont identiques.
	 * \param c : Coordonnées à tester.
	 * \return true si elles sont identiques, false sinon.
	 *
	 */

	bool isSameColumn(const Coordinates & c) const
	{
		return (_column == c.getColumn());
	}

	/*!
	 * \brief est sur le contour ?
	 *
	 * Vérifie si la coordonnées se situe sur le contour du bassin versant.
	 * \param p : paramètres du programme et du bassin versant.
	 * \return true si elle est située sur le contour du bassin versant, false sinon.
	 *
	 */
	bool isOnShore(const Parameters * p) const
	{
		if (_line == 0)
			return true;
		else if( _column == 0)
			return true;
		else if(_line == p->_linesNumber - 1)
			return true;
		else if (_column == p->_columnsNumber - 1)
			return true;
		else
			return false;
	}

	/*!
	 * \brief Envoyer vers fichier binaire
	 *
	 * Écrit l'objet dans un fichier binaire.
	 * \param file : fichier ou écrire les données.
	 * \return void.
	 *
	 */


	void toBinaryFile(std::ofstream & file)
	{
		file.write(reinterpret_cast<char *>(&_line),sizeof(short));
		file.write(reinterpret_cast<char *>(&_column),sizeof(short));
	}

};

#endif /* COORDINATES_H_ */
