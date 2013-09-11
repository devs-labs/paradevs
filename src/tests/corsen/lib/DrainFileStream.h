/*!
 * \file DrainFileStream.h
 * \brief Flux binaire sur fichier contenant toutes les données de l'arborescence de MntSurf.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 13 juin 2013
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

#ifndef DRAINFILESTREAM_H_
#define DRAINFILESTREAM_H_

#include "FileStream.h"
#include "Coordinates.h"
#include <typeinfo>
#include <vector>

/*! \class DrainFileStream
 *
 * \brief gère un flux binaire en lecture et écriture sur le fichier de drain.
 */


template <class X, class Y, class T = FileStream<X,Y> >
class DrainFileStream : public T
{
public :
	DrainFileStream(std::string & filePath) : T(filePath)
	{


	}
	~DrainFileStream() {}

	typename T::returnType * read() const throw (FileNotFound, ReadError, InvalidFileFormat, std::bad_alloc)
	{
		std::ifstream drainFile(T::_filePath.c_str(),std::ios::binary);

		if(not drainFile)
			throw FileNotFound("Exception opening file\n: "+ T:: _filePath);

		if(T::_format.compare("") == 0)
			return readStandardFormat(drainFile);

		throw InvalidFileFormat("Exception Unknown file format "+T::_filePath+"\n");

	}

	void write(const typename T::returnType & object, const std::string & extension) const
	{
	/*	std::string filePath(_filePath);
		filePath.append(extension);
		std::ofstream drainFile(filePath.c_str(), std::ios::trunc);

		if(not drainFile)
			throw FileNotFound("Exception opening file "+ filePath +"\n");

		if(_format.compare("") == 0)
			return writeStandardFormat(drainFile, object);

		throw InvalidFileFormat("Exception Unknown file format "+ filePath +"\n");
*/
	}

private :

	typename T::returnType * readStandardFormat(std::ifstream & file) const throw(ReadError, std::bad_alloc)
	{
		try
		{
			typename T::returnType * tmpVec = new  typename T::returnType();
			Y tmp;
			do
			{
				file.read(reinterpret_cast<char *>(&tmp), sizeof(Y));
				if(not file.eof() and not file.bad())
					tmpVec->push_back(tmp);

			}
			while(file.good());
			if(file.bad() or not file.eof())
			{
				file.close();
				throw ReadError("Exception Reading data"+ T::_filePath);
			}
			file.close();
			return tmpVec;
		}
		catch(std::bad_alloc & e)
		{
			throw;
		}
	}


	void writeStandardFormat(std::ofstream & file, const typename T::returnType & object) const
	{
		Y tmp;
		for(int i  = 0; i < object.size() ; i++)
		{
			tmp = object.at(i);
			file.write(reinterpret_cast<char *>(&tmp), sizeof(Y));
		}
		file.close();
	}
};


#endif /* DRAINFILESTREAM_H_ */
