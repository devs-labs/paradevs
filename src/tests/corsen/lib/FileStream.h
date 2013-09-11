/*!
 * \file FileStream.h
 * \brief modèle de flux sur fichiers applicable à n'importe quelle classe.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 11 juin 2013
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

#ifndef FILESTREAM_H_
#define FILESTREAM_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "Exception.h"
#include "Constantes.h"


namespace corsenContainers
{
struct vecS{};
struct listS{};
struct CType {};
template <class Selector, class ValueType>
struct container_gen { };

template <class ValueType>
struct container_gen<vecS, ValueType> {
	typedef std::vector<ValueType> type;
};
template <class ValueType>
struct container_gen<CType, ValueType> {
	typedef ValueType type;
};
template <class ValueType>
struct container_gen<listS, ValueType> {
	typedef std::list<ValueType> type;
};
}

template<class container, class valuetype>

/*! \class FileStream
 *
 * \brief est une classe abstraite, elle sert de modèle aux différents lecteurs de fichiers.
 *
 *  La classe gère la lecture et l'ecriture au format standard.
 */

class FileStream
{
protected :
	std::string _filePath; /*!< chemin du fichier*/
	std::string _format; /*!< format du fichier*/
public :

	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe FileReader, analyse le chemin du fichier afin de déterminer son format.
	 *
	 *  \param filePath : chemin du fichier.
	 *  \return void
	 */

	FileStream(const std::string & filePath)
{
		_filePath = filePath;
		_format = findFormat(filePath);
}
	typedef typename corsenContainers::container_gen<container,valuetype>::type returnType;

	/*!
	 *  \brief Lecture
	 *
	 *  Analyse le format du fichier et lance la méthode de lecture adaptée.
	 *
	 *  \return un objet contenant les informations lues.
	 */
	virtual returnType * read() const = 0;

	/*!
	 *  \brief écriture
	 *
	 *  Analyse le format du fichier et lance la méthode d'écriture adaptée.
	 *
	 *   \param object : objet contenant les informations à écrire
	 *   \param extension : format du fichier pour la sauvegarde
	 *   \return void
	 */

	virtual void write(const returnType & object, const std::string & extension) const = 0;

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe FileStream
	 */
	virtual ~FileStream(){}

	const std::string& getFilePath() const
	{
		return _filePath;
	}

	void setFilePath(const std::string& filePath)
	{
		_filePath = filePath;
		_format = findFormat(filePath);
	}

protected :

	const std::string findFormat(const std::string & filePath) const
	{
		std::string format("");

		std::vector<std::string>Vec;
		std::string reversefilePath(filePath.rbegin(), filePath.rend());
		boost::split(Vec,reversefilePath,boost::is_any_of("\\/"));
		if(Vec.size() !=0)
		{
			std::string filePathEnd(Vec.at(0).rbegin(),Vec.at(0).rend());
			Vec.clear();
			boost::split(Vec, filePathEnd, boost::is_any_of("."));
			if(isHiddenFile(filePathEnd))
			{
				for(unsigned int i = 2; i<Vec.size();i++)
					format+="."+Vec.at(i);
			}
			else
			{
				for(unsigned int i = 1; i<Vec.size();i++)
					format+="."+Vec.at(i);
			}
		}
		else
		{
			boost::split(Vec, _filePath, boost::is_any_of("."));
			if(isHiddenFile(_filePath))
			{
				for(unsigned int i = 2; i<Vec.size();i++)
					format+="."+Vec.at(i);
			}
			else
			{
				for(unsigned int i = 1; i<Vec.size();i++)
					format+="."+Vec.at(i);
			}
		}

		return format;
	}

	bool isHiddenFile(const std::string & filePath) const
	{
		if(filePath.substr(0,1).compare(".") == 0)
			return true;

		return false;
	}

private:


	/*!
	 *  \brief Lecture au format standard
	 *
	 *  Lecture des données du fichier selon un formatage particulier .
	 *
	 * \param file fichier dans lequel lire les données.
	 *  \return l'objet contenant les informations lues.
	 */

	virtual returnType * readStandardFormat(std::ifstream & file) const = 0;
	/*!
	 *  \brief écriture au format standard
	 *
	 *  Écriture des données dans le fichier selon un formatage particulier.
	 *
	 *  \param file fichier dans lequel écrire les données.
	 *  \param object l'objet contenant les informations à écrire.
	 *  \return void
	 */

	virtual void writeStandardFormat(std::ofstream & file, const returnType & object) const = 0;

};


#endif /* FILESTREAM_H_ */
