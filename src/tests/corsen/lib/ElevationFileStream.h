/*!
 * \file ElevationFileStream.h
 * \brief Flux sur le fichier d'altitudes.
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

#ifndef ELEVATIONFILESTREAM_H_
#define ELEVATIONFILESTREAM_H_

#include "FileStream.h"

/*! \class ElevationFileStream
 *
 * \brief gère un flux en lecture et écriture  sur le fichier d'altitudes.
 */

class ElevationFileStream: public FileStream<corsenContainers::vecS,float>
{
public :
	ElevationFileStream(const std::string & filePath) : FileStream<corsenContainers::vecS,float>(filePath) {}
	virtual ~ElevationFileStream(){}

	returnType * read() const throw (FileNotFound, ReadError, InvalidFileFormat, std::bad_alloc)
	{
		std::ifstream altFile(_filePath.c_str(),std::ios::binary);
		if(not altFile)
			throw FileNotFound("Exception opening file\n "+_filePath);

		if(_format.compare("") == 0)
			return readStandardFormat(altFile);

		throw InvalidFileFormat("Exception Unknown file format "+_filePath+"\n");
	}

	returnType * read(const std::string & extension) const throw (FileNotFound, ReadError, InvalidFileFormat, std::bad_alloc)
	{
		std::string filePath(_filePath);
		filePath.append(extension);

		std::ifstream altFile(filePath.c_str(),std::ios::binary);
		if(not altFile)
			throw FileNotFound("Exception opening file "+filePath+"\n");

		if(extension.compare(".sav") == 0)
			return readStandardFormat(altFile);

		throw InvalidFileFormat("Exception Unknown file format "+filePath+"\n");
	}


	void write(const returnType & object, const std::string & extension) const throw (FileNotFound, InvalidFileFormat)
	{
		std::string filePath(_filePath);
		filePath.append(extension);
		std::ofstream altFile(filePath.c_str(), std::ios::trunc);

		if(not altFile)
			throw FileNotFound("Exception opening file "+ filePath +"\n");

		if(_format.compare("") == 0)
			return writeStandardFormat(altFile, object);

		throw InvalidFileFormat("Exception Unknown file format "+ filePath +"\n");
	}

private :
	returnType * readStandardFormat(std::ifstream & file) const throw (ReadError, std::bad_alloc)
	{
		// get length of file:
		file.seekg (0, file.end);
		int length = file.tellg();
		file.seekg (0, file.beg);

		try
		{
			returnType * tmpVec = new returnType();
			/* double tailleeffective = static_cast<double>(length) / static_cast<double>(sizeof(float)); */
#ifdef DEBUG
			std::cout<<"------ ElevationFileStream --------- \n";
			std::cout<<"Taille en octets : "<<length <<"\nTaille du type de retour : "<<sizeof(float)<<"\nTaille du vec d'élévation : "<<length/sizeof(returnType)
										<<"\nTaille effective : "<< tailleeffective <<std::endl;
			std::cout<<"------ ElevationFileStream --------- \n";
#endif
			float tmp;
			do
			{
				file.read(reinterpret_cast<char *>(&tmp), sizeof(float));
				if(not file.eof() and not file.bad())
					tmpVec->push_back(tmp);

			}
			while(file.good());
			if(file.bad() or not file.eof())
			{
				file.close();
				throw ReadError("Exception Reading data"+ _filePath);
			}
			file.close();
			return tmpVec;
		}
		catch(std::bad_alloc & e)
		{
			throw;
		}

	}

	void writeStandardFormat(std::ofstream & file, const returnType & object) const throw (std::exception)
	{
		float tmp;
		for(returnType::const_iterator it = object.begin(); it!= object.end() ; ++it)
		{
			tmp = *it;
			file.write(reinterpret_cast<char *>(&tmp), sizeof(float));
		}
		file.close();
	}
};


#endif /* ELEVATIONFILESTREAM_H_ */
