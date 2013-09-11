/*!
 * \file Node.h
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
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

#ifndef NODE_H_
#define NODE_H_

#include "Coordinates.h"
#include <list>
class Node
{
protected :
	Coordinates _coord;
	Node * _father;
	Node * _child;
	Node * _brother;

public :

	Node(): _coord()
{
		_father = NULL;
		_child = NULL;
		_brother = NULL;
}

	Node(const Node & n)
	{
		_coord = n.getCoord();
		_father = n.getFather();
		_child = n.getChild();
		_brother = n.getBrother();
	}

	Node(const Coordinates & c, Node * father) :_coord(c)
	{
		_father = father;
		_child = NULL;
		_brother = NULL;
	}

	virtual ~Node(){}

	void setPere(Node * pere)
	{
		_father = pere;
	}

	void setCoord(const Coordinates& coord)
	{
		_coord = coord;
	}

	const Coordinates& getCoord() const
	{
		return _coord;
	}

	Node * getChild() const
	{
		return _child;
	}

	Node * getBrother() const
	{
		return _brother;
	}

	Node * getFather() const
	{
		return _father;
	}

	void setChild(Node *  child)
	{
		_child = child;
	}

	void setBrother(Node *  brother)
	{
		_brother = brother;
	}

	const std::string toString() const
	{
		std::stringstream ss;

		ss <<"coordonnes du noeud : "<<_coord.toString()<<"\n";

		if(_child !=NULL)
			ss<<"coordonnes du fils : "<<_child->getCoord().toString()<<"\n";

		if(_brother !=NULL)
			ss<<"coordonnes du frere : "<<_brother->getCoord().toString()<<"\n";

		return ss.str();
	}

	char getNeighbourId(const Node * n) const
	{
		char c ='X';
		short diffi = _coord.getLine() - n->getCoord().getLine() ;
		short diffj = _coord.getColumn() - n->getCoord().getColumn();

		if (diffi == 1 && diffj == 0)
			c ='1';
		else if (diffi == 1 && diffj == -1)
			c = '2' ;
		else if(diffi == 0 && diffj == -1)
			c = '3' ;
		else if (diffi == -1 && diffj == -1)
			c = '4' ;
		else if (diffi == -1 && diffj == 0)
			c = '5' ;
		else if (diffi == -1 && diffj == 1)
			c = '6' ;
		else if (diffi == 0 && diffj == 1)
			c = '7' ;
		else if (diffi == 1 && diffj == 1)
			c = '8' ;

		return c;
	}


};

#endif /* NODE_H_ */
