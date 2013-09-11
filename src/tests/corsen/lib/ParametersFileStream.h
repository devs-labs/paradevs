/*!
 * \file ParametersFileStream.h
 * \brief Flux texte sur le fichier de paramètres du programme et du bassin versant.
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

#ifndef PARAMETERSFILESTREAM_H_
#define PARAMETERSFILESTREAM_H_

#include "FileStream.h"
#include "Parameters.h"
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

/*! \class ParametersFileStream
 *
 * \brief gère un flux texte en lecture et écriture sur le fichier de paramètres.
 */

class ParametersFileStream : public FileStream<corsenContainers::CType, Parameters>
{
public:
	std::string _modeFilePath;
	std::string _modeFileFormat;

	ParametersFileStream(std::string & parametersFilePath, std::string & modeFilePath) : FileStream<corsenContainers::CType, Parameters>(parametersFilePath)
	{
		_modeFilePath = modeFilePath;
		_modeFileFormat = findFormat(modeFilePath);
	}

	virtual ~ParametersFileStream(){}

	returnType * read() const throw (FileNotFound, InvalidFileFormat)
	{
		std::ifstream parFile(_filePath.c_str(),std::ios::in);
		std::ifstream modeFile(_modeFilePath.c_str(),std::ios::in);
		Parameters * p = NULL;

		if(not parFile)
			throw FileNotFound("Exception opening file : "+ _filePath);

		if(not modeFile)
			throw FileNotFound("Exception opening file : "+ _modeFilePath);

		if(_format.compare(".txt") == 0)
			p = readStandardFormat(parFile);
		else if(_format.compare(".def") == 0)
			p = readDefaultValues(parFile);
		else
			throw InvalidFileFormat("Exception Unknown file format "+_format+"\n");

		if(_modeFileFormat.compare("") == 0)
			readStandardModeFormat(modeFile, p);
		else
		{
			if(p != NULL)
				delete p;

			throw InvalidFileFormat("Exception Unknown file format "+_modeFileFormat+"\n");
		}

		return p;
	}


	void write(const returnType & object, const std::string & /* extension */) const throw (FileNotFound, InvalidFileFormat)
	{
		std::ofstream parFile(_filePath.c_str(), std::ios::trunc) ;

		if(not parFile)
			throw FileNotFound("Exception opening file: "+ _filePath);

		if(_format.compare(".txt") == 0)
			return writeStandardFormat(parFile, object);

		throw InvalidFileFormat("Exception Unknown file format "+_filePath+"\n");
	}

private :

	void readStandardModeFormat(std::ifstream & file, Parameters * p) const throw (FileNotFound, boost::bad_lexical_cast)
	{
		using boost::lexical_cast;
		std::string line;
		std::vector<std::string> parameters;

		std::getline(file, line);
		boost::split(parameters,line,boost::is_any_of(" "));
		p->_meshMode = lexical_cast<bool>(parameters.at(0));
		p->_gap = lexical_cast<int>(parameters.at(1));

		file.close();
	}

	returnType * readDefaultValues(std::ifstream & file) const throw (ReadError)
	{
		Parameters * param = new Parameters();
		file.read(reinterpret_cast<char *>(&(param->_riverLevel)), sizeof(int));
		file.read(reinterpret_cast<char *>(&(param->_displaySea)), sizeof(int));
		if(file.bad() or not file.eof())
		{
			file.close();
			throw ReadError("Exception reading file "+ _filePath);
		}
#ifdef DEBUG
		std::cout<<"Seuil de rivière: "<<param->_riverLevel<<" ha"<<std::endl;
		std::cout<<"Afficher la  mer: "<<param->_displaySea<<std::endl
#endif
		file.close();
		return param;
}

	returnType * readStandardFormat(std::ifstream & file) const
	{
		using boost::lexical_cast;
		using boost::bad_lexical_cast ;
		Parameters * param = new Parameters();
		std::string line;
		std::vector<std::string> parameters;

		std::getline(file,line);
		boost::split(parameters, line, boost::is_any_of(" "));
		try
		{
			param->_nodesPerLine = lexical_cast<int>(parameters.at(0));
			param->_nodesPerColumn = lexical_cast <int>(parameters.at(1));

			if(param->_meshMode)
			{
				param->_linesNumber = param->_nodesPerLine;
				param->_columnsNumber = param->_nodesPerColumn;
			}
			else
			{
				param->_linesNumber = param->_nodesPerLine - 1 ;
				param->_columnsNumber = param->_nodesPerColumn - 1 ;
			}
#ifdef DEBUG
			std::cout<<"Matrice Altitude : "<<param->_linesNumber<<" lignes et "<<param->_columnsNumber<<" colonnes \n"<<"mnt "<<param->_nodesPerLine<<" X "<<param->_nodesPerColumn<<std::endl;
#endif
		}
		catch (const bad_lexical_cast & e)
		{
			std::cerr<<e.what();
		}
		if(parameters.size() >= 3)
		{
			param->_horizontalMeshStep = lexical_cast<double>(parameters.at(2));

			if (parameters.size() >=4 )
			{
				param->_verticalMeshStep = lexical_cast<double>(parameters.at(3));
				param->_lambertCadre = false ;

				if (parameters.size() == 12)
				{
					param->_lambertCadre = true ;
					param->lx0 = lexical_cast<double>(parameters.at(4));
					param->ly0 = lexical_cast<double>(parameters.at(5));
					param->lx1 = lexical_cast<double>(parameters.at(6));
					param->ly1 = lexical_cast<double>(parameters.at(7));
					param->lx2 = lexical_cast<double>(parameters.at(8));
					param->ly2 = lexical_cast<double>(parameters.at(9));
					param->lx3 = lexical_cast<double>(parameters.at(10));
					param->ly3 = lexical_cast<double>(parameters.at(11));
				}

			}
			else
				param->_verticalMeshStep = param->_horizontalMeshStep;

			param->_meshSize = param->_horizontalMeshStep  ;

		}
		else
		{
			param->_horizontalMeshStep =  50. ;
			param->_verticalMeshStep = 50.;
			param->_meshSize = 50.;
		}

		param->_meshArea = param->_horizontalMeshStep * param->_verticalMeshStep ;
		param->_colorColumnsNumber = (( param->_columnsNumber / 32 ) + 1 ) * 32 ;
		param->_charColumnsNumber = (int) ceil ( (double) param->_columnsNumber / 8. ) ;

#ifdef DEBUG
		std::cout<<"Pas de la maille en x : "<<param->_horizontalMeshStep<<" mètres \n" ;
		std::cout<<"Pas de la maille en y : "<<param->_verticalMeshStep<<" mètres \n\n";
		std::cout<<param->_colorColumnsNumber<<" colonnes couleur\n\n";
		std::cout<<param->_charColumnsNumber<<" colonnes caractère (codage binaire)\n\n";
#endif
		if(not param->_lambertCadre)
		{
			param->lx0 = 0. ;
			param->ly0 = 0. ;
			param->lx1 = 0. ;
			param->ly1 = param->_verticalMeshStep * param->_nodesPerColumn / 1000. ;
			param->lx2 = param->_verticalMeshStep * param->_nodesPerLine / 1000. ;
			param->ly2 = 0. ;
			param->lx3 = param->_verticalMeshStep * param->_nodesPerLine / 1000. ;
			param->ly3 = param->_verticalMeshStep * param->_nodesPerColumn / 1000. ;
			param->_lambertCadre = true ;
		}

		file.close();
		return param;
	}

	void writeStandardFormat(std::ofstream & file, const returnType & object) const throw (FileNotFound)
	{
		std::ofstream modeFile(_modeFilePath, std::ios::trunc);
		if(not modeFile)
			throw FileNotFound("Exception opening file: "+ _modeFilePath);

		modeFile<<object._meshMode<<" "<<object._gap;;
		modeFile.close();

		file<<object._linesNumber<<" ";
		file<<object._columnsNumber<<" ";
		file<<object._horizontalMeshStep<<" ";
		file<<object._verticalMeshStep<<" ";
		file<<object.lx0<<" ";
		file<<object.ly0<<" ";
		file<<object.lx1<<" ";
		file<<object.ly1<<" ";
		file<<object.lx2<<" ";
		file<<object._charColumnsNumber<<" ";
		file<<object.lx3<<" ";
		file<<object.ly3<<"\n";
		file.close();
	}
};

#endif /* PARAMETERSFILESTREAM_H_ */
