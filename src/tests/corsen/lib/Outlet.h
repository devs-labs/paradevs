/*!
 * \file Outlet.h
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

#ifndef OUTLET_H_
#define OUTLET_H_

#include "Node.h"
#include <vector>
#include <map>


class Outlet : public Node
{

public :
	short getFlag() const {
		return _flag;
	}

	short getMx() const {
		return _mx;
	}

	short getGmx() const {
		return _Mx;
	}

	short getMy() const {
		return _my;
	}

	short getGmy() const {
		return _My;
	}

	int getNumber() const {
		return _number;
	}

	short getOrder() const {
		return _order;
	}

	void setFlag(short flag)
	{
		_flag = flag;
	}

	void setMx(short mx)
	{
		_mx = mx;
	}

	void setGMx(short mx)
	{
		_Mx = mx;
	}

	void setMy(short my)
	{
		_my = my;
	}

	void setGMy(short my)
	{
		_My = my;
	}

	void setNumber(int number)
	{
		_number = number;
	}

	void setOrder(short order)
	{
		_order = order;
	}

	Outlet() : Node()
	{
		_flag = 0;
		_order = 0;
		_mx = 0;
		_my = 0;
		_Mx = 0;
		_My = 0;
		_number = 0;
	}

	Outlet(const Outlet & o) : Node(o.getCoord(), o.getFather())
	{
		_father = o.getFather();
		_brother = o.getBrother();
		_child = o.getChild();
		_flag = o.getFlag();
		_number = o.getNumber() ;
		_order = o.getOrder();
		_mx = o.getMx();
		_my = o.getMy();
		_Mx = o.getGmx();
		_My = o.getGmy();

	}

	Outlet(const Coordinates & c, short flag, int outletsNumber) : Node(c, NULL)
	{
		_child = NULL;
		_brother = NULL;
		_flag = flag;
		_number = outletsNumber ;
		_order = 0;
		_mx = 0;
		_my = 0;
		_Mx = 0;
		_My = 0;

	}
	~Outlet()
	{
		for(std::map<Coordinates, Node *>::iterator it = _childrenNodes.begin(); it!=_childrenNodes.end();it++)
			delete it->second;
	}

	void setNodes(const std::map<Coordinates, Node*>& nodes)
	{
		this->_childrenNodes = nodes;
	}

	const std::string toString() const
	{
		std::stringstream ss;
		ss<<"Outlet : "<<_coord.toString()<<"flag "<<_flag<<" numero "<<_number<<std::endl;

		ss <<"All nodes : \n";
		for(std::map<Coordinates, Node *>::const_iterator it = _childrenNodes.begin(); it!=_childrenNodes.end();it++)
			ss << it->second->toString()<<"\n:";

		return ss.str();
	}

	 Node * searchChildNode(const Coordinates & coord) const
	{
		if(_childrenNodes.count(coord))
			return _childrenNodes.find(coord)->second;

		return NULL;
	}

private :
	std::map<Coordinates, Node *>_childrenNodes;
	short _flag;
	short _order;
	short _mx, _my, _Mx, _My ;
	int _number ;
};

#endif /* OUTLET_H_ */
