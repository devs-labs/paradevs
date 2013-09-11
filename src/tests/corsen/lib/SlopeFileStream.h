/*!
 * \file SlopeFileStream.h
 * \brief Flux binaire sur fichier de pentes.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 20 juin 2013
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

#ifndef SLOPEFILESTREAM_H_
#define SLOPEFILESTREAM_H_

// read a file and save it into memory

#include <sstream>
#include "FileStream.h"


/*! \class SlopeFileStream
 * \brief gère un flux binaire en lecture et écriture sur le fichier de pentes.
 *
 */

class SlopeFileStream: public FileStream<corsenContainers::vecS,float>
{
public :
	SlopeFileStream(const std::string & filePath) : FileStream<corsenContainers::vecS,float>(filePath) {}
	virtual ~SlopeFileStream(){}

	returnType * read() const throw (FileNotFound, ReadError, InvalidFileFormat, std::bad_alloc)
	{
		std::ifstream gradientFile(_filePath.c_str(),std::ios::binary);
		if(not gradientFile)
			throw FileNotFound("Exception opening file\n "+_filePath);

		if(_format.compare("") == 0)
			return readStandardFormat(gradientFile);

		throw InvalidFileFormat("Exception Unknown file format "+_filePath+"\n");
	}

	void write(const returnType & /* object */, const std::string & /* extension */) const
	{

	}

	returnType * readStandardFormat(std::ifstream & file) const throw (ReadError, std::bad_alloc)
	{
		int i = 0;
		float tmp;
		try
		{
			returnType *  gradientVec = new returnType();

			do
			{
				file.read(reinterpret_cast<char *>(&tmp), sizeof(float));
				if(file.eof())
				{
					file.close();
#ifdef DEBUG
					std::cout<<"SlopeFileStream : all characters read successfully.\n";
#endif
					break;
				}
				else if(file.bad())
				{
					file.close();
					std::stringstream ss;
					ss << i * sizeof(float);
					throw ReadError("Exception Reading file, only " + ss.str() + " bytes could be read");
				}
				else
				{
					gradientVec->push_back(tmp);
					i++;
				}
			}
			while(file.good());

			return gradientVec;
		}
		catch(std::bad_alloc & e)
		{
			throw;
		}
	}

	void writeStandardFormat(std::ofstream & /* file */,
				 const returnType & /* object */) const
	{
	}

};


#endif /* SLOPEFILESTREAM_H_ */
