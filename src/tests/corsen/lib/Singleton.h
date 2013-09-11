/*!
 * \file Singleton.h
 * \brief modèle de singleton applicable à n'importe quelle classe.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 6 juin 2013
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

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <iostream>
#include "Constantes.h"

/*! \class Singleton
 *
 * \brief est un design pattern dont l'objet est de restreindre l'instanciation d'une classe à un seul objet.
 */

template <typename T>
class Singleton
{
protected:

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Singleton.
	 *  \param void
	 *  \return void
	 *
	 */

	Singleton () { }

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Singleton.
	 */

	~Singleton ()
	{
#ifdef DEBUG
		std::cout << "destroying singleton." << std::endl;
#endif
	}

public:

	/*!
	 *  \brief Retourner instance.
	 *
	 *  Méthode qui crée l'unique instance de la classe si elle n'existe pas encore puis la retourne.
	 *
	 * \param void
	 * \return Singleton
	 */

	static T * getInstance ()
	{
		if (NULL == _instance)
		{
#ifdef DEBUG
			std::cout << "creating singleton." << std::endl;
#endif
			_instance = new T;
		}
		else
		{
#ifdef DEBUG
			std::cout << "singleton already created!" << std::endl;
#endif
		}

		return (static_cast<T*> (_instance));
	}

	/*!
	 *  \brief Supprimer instance.
	 *
	 *  Méthode qui supprime l'unique instance de la classe si elle existe.
	 *
	 * \param void
	 * \return void
	 */

	static void kill ()
	{
		if (_instance != NULL)
		{
			delete _instance;
			_instance = NULL;
		}
	}

private:
	static T *_instance; /*!< Unique instance */
};

template <typename T>
T *Singleton<T>::_instance = NULL;


#endif /* SINGLETON_H_ */
