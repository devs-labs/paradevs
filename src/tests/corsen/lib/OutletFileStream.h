/*!
 * \file OutletFileStream.h
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

#ifndef OUTLETFILESTREAM_H_
#define OUTLETFILESTREAM_H_

#include "FileStream.h"
#include "Outlet.h"
#include "Coordinates.h"
#include <list>

/*! \class OutletFileStream
 *
 * \brief gère un flux binaire en lecture et écriture sur le fichier contenant l'arborescence de MntSurf.
 */

class OutletFileStream : public FileStream<corsenContainers::listS,Outlet *>
{
public :
	enum returnTypeTree {recursiveOff, recursiveOn , eof};
	OutletFileStream(std::string & filePath) : FileStream<corsenContainers::listS,Outlet *>(filePath) { }
	~OutletFileStream() {}

	returnType * read() const throw (FileNotFound, ReadError, InvalidFileFormat, std::bad_alloc)
	{
		std::ifstream outletFile(_filePath.c_str(),std::ios::binary);

		if(not outletFile)
			throw FileNotFound("Exception opening file\n: "+ _filePath);

		if(_format.compare("") == 0)
			return readStandardFormat(outletFile);

		throw InvalidFileFormat("Exception Unknown file format "+_filePath+"\n");

	}

	void write(const returnType & object, const std::string & extension) const
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

	void fillMap(Node * n, std::map<Coordinates, Node *> & tmpNodes) const
	{
		if (n != NULL)
		{
			tmpNodes[n->getCoord()] = n;
			fillMap(n->getChild(),tmpNodes);
			fillMap(n->getBrother(),tmpNodes);
		}
	}


	returnType * readStandardFormat(std::ifstream & file) const throw(ReadError, std::bad_alloc)
	{
		try
		{
			std::list<Outlet *> * tmp = new std::list<Outlet *>();
			std::map<Coordinates, Node *> tmpNodes;
			Outlet * olt = NULL;
			short ligne, colonne;
			int outletsNum = 100000 ;

			do
			{
				outletsNum -= 1 ;
				file.read(reinterpret_cast<char *>(&ligne), sizeof(short));
				file.read(reinterpret_cast<char *>(&colonne), sizeof(short));
				olt = new Outlet(Coordinates(ligne,colonne),0,outletsNum);

				if (readTree(file, olt, NULL) == eof)
				{
					delete olt;
					break;
				}

				fillMap(olt->getChild(), tmpNodes);
				olt->setNodes(tmpNodes);
				tmpNodes.clear();
				(*tmp).push_front(olt);
			}
			while(file.good());
			if(file.bad() or not file.eof())
			{
				file.close();
				throw ReadError("Exception reading file "+ _filePath);
			}

			file.close();
			return tmp;
		}
		catch(std::bad_alloc & e)
		{
			throw;
		}

	}

	/*!
	 *  \brief Lecture arbre
	 *
	 *  - Lit le fichier arbre.
	 *  - Stocke dans une liste les exutoires de réseau de drainage,
	 *  chaque exutoire contient la racine d'un arbre binaire.
	 *
	 *  \param file : fichier ou est stocké l'arborescence du réseau de drainage.
	 *  \param n : Noeud fils
	 *  \param p : Noeud père
	 *  \return recursiveoff : arrêt du parcours de l'arbre ou de la branche.
	 *  		recursiveon  : continuer parcours des branches de l'arbre.
	 *  		eof : fin du fichier atteinte.
	 */


	returnTypeTree readTree(std::ifstream & file, Node * n, Node * p) const
	{
		char c;

		file.read(reinterpret_cast<char *>(&c),sizeof(char));

		if(file.eof())
			return eof;

		switch (c)
		{
		case '(' :

			file.read(reinterpret_cast<char *>(&c),sizeof(char));

			if (c == ')')
				return recursiveOff ;

			n->setChild(new Node(Coordinates(n->getCoord(), c), n));

			if (readTree(file, (n->getChild()), n) == recursiveOn)
				return (readTree(file, n, p));

			break ;

		case ')' :
			n->setBrother(NULL);
			if (p->getFather() !=NULL)
				return recursiveOn ;
			else
				return recursiveOff ;

		default :
			n->setBrother(new Node(Coordinates(p->getCoord(),c), p));
			return (readTree(file, n->getBrother(), p)) ;
		}

		return recursiveOn;
	}


	void writeStandardFormat(std::ofstream & file, const returnType & object) const
	{

#ifdef DEBUG
		std::cout<<"Sauvegarde de l'arbre.\n";
#endif
		if (object.size() == 0)
			return ;

		for (returnType::const_reverse_iterator it = object.rbegin(); it!=object.rend() ; it++)
		{
			Coordinates outletCoordinates((*it)->getCoord());
			outletCoordinates.toBinaryFile(file);

			file.put('(');

			if ((*it)->getChild() != NULL)
				writeTree(file, *it, (*it)->getChild()) ;
			else
				file.put(')') ;
		}

		file.close();
	}

	void writeTree(std::ofstream & file, const Node * father, const Node * child) const
	{
		if(child != NULL)
		{
			file.put(father->getNeighbourId(child));

			if (child->getChild() !=NULL)
			{
				file.put('(') ;
				writeTree(file, child, child->getChild()) ;
			}

			if (child->getBrother() != NULL)
				writeTree(file, father, child->getBrother());
			else
				file.put(')');
		}

	}

};




#endif /* OUTLETFILESTREAM_H_ */
