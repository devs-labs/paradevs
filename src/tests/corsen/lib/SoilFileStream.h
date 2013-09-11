/*!
 * \file SoilFileStream.h
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

#ifndef SOILFILESTREAM_H_
#define SOILFILESTREAM_H_

#include "FileStream.h"
#include <sstream>

class SoilFileStream : public FileStream<corsenContainers::vecS,float>
{
public :

	SoilFileStream(const std::string & filePath) : FileStream<corsenContainers::vecS,float>(filePath) {}
	virtual ~SoilFileStream(){}

	returnType * read() const throw (FileNotFound, ReadError, InvalidFileFormat)
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

private :
	returnType * readStandardFormat(std::ifstream & file) const throw (ReadError)
	{
			int i = 0;
			int tmp;
			returnType * soilVec = new returnType();
			do
			{
				file.read(reinterpret_cast<char *>(&tmp), sizeof(float));
				if(file.eof())
				{
					file.close();
#ifdef DEBUG
					std::cout << "SoilFileStream : all characters read successfully. \n";
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
					soilVec->push_back(tmp) ;
					i++;
				}
			}
			while(file.good());

			return soilVec;
	}

	void writeStandardFormat(std::ofstream & /* file */, const returnType & /* object */) const
	{
	}

};

#endif
