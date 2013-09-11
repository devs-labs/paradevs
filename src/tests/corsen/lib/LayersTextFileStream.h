/**
 * \file LayersTextFileStream.h
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 3 juin 2013
 * \brief Flux texte sur fichier de couches.
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

#ifndef LAYERSTEXTFILESTREAM_H_
#define LAYERSTEXTFILESTREAM_H_

#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <stdbool.h>
#include <string>
#include <sstream>
#include "FileStream.h"
#include "Layer.h"
#include "Constantes.h"

/*! \class LayersTextFileStream
 *
 * \brief gère un flux texte en lecture et écriture sur le fichier de couches.
 */

class LayersTextFileStream : public FileStream<corsenContainers::vecS,Layer>
{

public :
	LayersTextFileStream(std::string & filePath)  : FileStream<corsenContainers::vecS,Layer>(filePath) {}
	virtual ~LayersTextFileStream() {}

public :

	/*!
	 * \brief Lecture
	 *
	 * Ouvre le fichier de couches et lance la méthode de lecture adaptée.
	 * \param void
	 * \return l'objet contenant les données lues.
	 */

	returnType * read() const throw (FileNotFound, InvalidFileFormat)
	{
		std::ifstream file(_filePath.c_str(),std::ios::in);

		if(not file)
			throw FileNotFound("Exception opening file\n "+_filePath);

		if(_format.compare("") == 0)
			return readStandardFormat(file);

		throw InvalidFileFormat("Exception Unknown file format "+_filePath+"\n");
	}

	/*!
	 * \brief Écriture
	 *  Ouvre le fichier de couches et lance la méthode d'écriture adaptée.
	 *  \param object : objet contenant les informations à écrire
	 *  \param extension : format du fichier pour la sauvegarde
	 *  \return void
	 */

	void write(const returnType & object, const std::string & extension) const throw (FileNotFound, InvalidFileFormat)
	{
		std::string filePath(_filePath);
		filePath.append(extension);
		std::ofstream file(filePath.c_str() ,std::ios::app);

		if(not file)
			throw ("Exception opening file\n "+ filePath);

		if(_format.compare("") == 0)
			return writeStandardFormat(file, object);

		throw InvalidFileFormat("Exception Unknown file format "+ filePath + "\n");
	}

private:

	/*!
	 * \brief Lecture au format standard
	 *
	 * Lit dans le fichier '_filePath' le label et la couleur des couches de segments raster.
	 * \param file fichier dans lequel lire les données.
	 * \return l'objet contenant les données lues.
	 */

	returnType * readStandardFormat(std::ifstream & file) const
	{
		std::string line;
		std::vector<Layer> * layers = new std::vector<Layer>();

		while(std::getline(file,line))
			layers->push_back(Layer(line));

		file.close();

		return layers;
	}

	/*!
	 * \brief Écriture au format standard
	 *
	 * Écrit dans le fichier '_filePath' le label et la la couleur des couches de segments raster.
	 * \param file fichier dans lequel écrire les données.
	 * \param object l'objet contenant les informations à écrire.
	 * \return void
	 */

	void writeStandardFormat(std::ofstream & file, const returnType & object) const
	{
		for (std::vector<Layer>::const_iterator it = object.begin(); it!= object.end(); it++)
			it->toTextFile(file);
	}

};


#endif /* LAYERSTEXTFILESTREAM_H_ */
