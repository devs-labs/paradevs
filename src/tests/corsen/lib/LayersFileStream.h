/*!
 * \file LayersFileStream.h
 * \brief Flux binaire sur le fichier de couches.
 * \author The VLE Development Team
 *  See the AUTHORS or Authors.txt file
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

#ifndef LAYERSFILESTREAM_H_
#define LAYERSFILESTREAM_H_

#include <sstream>
#include "FileStream.h"
#include "Parameters.h"

/*! \class LayersFileStream
 *
 * \brief gère un flux en lecture et écriture sur le fichier de couches.
 *
 */

class LayersFileStream : public FileStream<corsenContainers::CType,unsigned char>
{
private :
	Parameters * _param;


public :
	LayersFileStream(const std::string & filePath, Parameters * param) : FileStream<corsenContainers::CType,unsigned char>(filePath)
	{
		_param = param;

	}

	returnType * read() const throw (FileNotFound, ReadError, InvalidFileFormat, std::bad_alloc)
	{

		std::ifstream layersFile(_filePath.c_str() ,std::ios::binary);
		if(!layersFile)
			throw FileNotFound("Exception opening File : "+_filePath);

		if(_format.compare("") == 0 )
			return readStandardFormat(layersFile);

		throw InvalidFileFormat("Exception Unknown file format "+ _filePath +"\n");
	}

	void write(const returnType & /* object */,
		   const std::string & /* extension */) const
	{

	}

	virtual ~LayersFileStream()
	{

	}


private :
	returnType * readStandardFormat(std::ifstream & file) const throw (ReadError, std::bad_alloc)
	{
		unsigned char * c;
		try
		{
			c = new unsigned char[_param->_linesNumber * _param->_charColumnsNumber + 1];
		}
		catch(std::bad_alloc & e)
		{
			throw;
		}
		int i =0;
		do
		{
			file.read(reinterpret_cast<char *>(&c[i]),sizeof(unsigned char));
			i++;
		}
		while(i != (_param->_linesNumber * _param->_charColumnsNumber));

		if(file.bad() /*or not file.eof()*/)
		{
			std::stringstream ss;
			ss << file.gcount();
			file.close();
			throw ReadError("Exception Reading data only "+ss.str()+" could be read "+_filePath);
		}
#ifdef DEBUG
		std::cout << "LayersFileStream : all characters read successfully.\n";
#endif
		file.close();
		c[_param->_linesNumber * _param->_charColumnsNumber] = '\0';
		return c;
	}

	void writeStandardFormat(std::ofstream & /* file */,
				 const returnType & /* object */) const
	{

	}
};


#endif /* LAYERSFILESTREAM_H_ */
