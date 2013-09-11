/**
 *
 * \file Layer.h
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

#ifndef LAYER_H_
#define LAYER_H_

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "Constantes.h"
#include "Exception.h"
#include "Functions.h"

class Layer
{
private :

	std::string _label ;
	int _color ;
	int _active ;
	int _type ;
	bool _modified ;
	unsigned char * _data; /*!< données sur couches */

public :
	Layer():_label(""),_color(0),_active(0),_type(0),_modified(0), _data(NULL){}
	Layer(std::string label, int color,int active,int type, bool modified)
	{
		_label = label;
		_color = color;
		_active = active;
		_type = type;
		_modified = modified;
		_data = NULL;
	}

	Layer(std::string & label, int color,int active,int type, bool modified)
	{
		_label = label;
		_color = color;
		_active = active;
		_type = type;
		_modified = modified;
		_data = NULL;
	}
	Layer(const Layer & c)
	{
		_label = c.getLabel();
		_color = c.getColor();
		_active = c.getActive();
		_type = c.getType();
		_modified = c.isModified();
		_data = c.getData();
	}
	/*!
	 *
	 * \brief Constructeur
	 *
	 * Constructeur avec paramètres de la classe Layer, remplit les attributs de la classe avec les données de 'ligne'.
	 *
	 * \param ligne : chaîne de caractères contenant des informations pour la classe
	 * \return void
	 */

	Layer(const std::string & line)
	{
		_data = NULL ;

		using boost::lexical_cast ;
		using boost::bad_lexical_cast ;

		boost::char_separator<char> sep("\"");
		boost::tokenizer <boost::char_separator<char> >tokens(line,sep);

		boost::tokenizer<boost::char_separator<char> >::iterator it = tokens.begin();
		_label = *it;
		++it;

		try
		{
			_color = lexical_cast<int>(*it);
			_active =  lexical_cast<int>(*it);
			_type = lexical_cast<int>(*it);
		}

		catch(const bad_lexical_cast & e)
		{
			std::cerr<<e.what();
		}

		_modified = false ;
	}

	bool operator==(const Layer& layer) const
							{ return (_type == layer.getType() and (_type == CONTOUR_BASSIN or _type == RESEAU_HYDRO or _type == EXUTOIRES));}

	void toTextFile(std::ofstream & file) const
	{
		file<<"\""<<_label<<"\""<<" "<<_color<<" "<<_active<<" "<<_type<<"\n";
	}

	~Layer()
	{
		if(_data !=NULL)
			delete [] _data;
	}

	int getActive() const
	{
		return _active;
	}

	int getColor() const
	{
		return _color;
	}

	const std::string& getLabel() const
	{
		return _label;
	}

	bool isModified() const
	{
		return _modified;
	}

	int getType() const
	{
		return _type;
	}

	void setLabel(const std::string& label) {
		_label = label;
	}

	void setColor(int couleur) {
#ifdef IHM
		_color = couleur;
#endif
	}

	void setActive(int active)
	{
		_active = active;
	}

	void setType(int type)
	{
		_type = type;
	}

	static void fill(std::vector<Layer> & layers)
	{
		layers.push_back(Layer(std::string("Reseau Hydrographique"), 0,0,RESEAU_HYDRO,false));
		layers.push_back(Layer(std::string("Contour des Bassins Versants"), 0,0,CONTOUR_BASSIN,false));
		layers.push_back(Layer(std::string(""), 0,0,CONTOUR_IMAGE_BINAIRE,false));
		layers.push_back(Layer(std::string("Exutoires du Reseau Hydro"), 0,0,EXUTOIRES,false));
	}

	static int find(std::vector<Layer> & layers, int type)
	{
		for(unsigned short int  i = 0; i < layers.size(); i++)
		{
			if(layers.at(i).getType() == type && (type == CONTOUR_BASSIN || type == RESEAU_HYDRO || type == EXUTOIRES))
				return i;
		}

		return -1 ;
	}

	const std::string toString() const
	{
		std::stringstream ss;
		ss <<"label "<<_label <<" couleur "<<_color<<" active "<<_active<<" type"<<_type;
		return ss.str();
	}

	void display(Parameters * p) const
	{
		std::cout<<toString()<<std::endl;

		std::cout<<"Données Couches "<<std::endl;

		for(int i = 0; i< p->_linesNumber; i++)
		{
			for(int j = 0; j< p->_columnsNumber; j++)
			{
				std::cout<<isNetwork(Coordinates(p->_linesNumber - 1 - i , j),p )<<std::endl;
			}
			std::cout<<"\n";
		}
	}

	unsigned char* getData() const
	{
		return _data;
	}

	void setData(unsigned char* data)
	{
		_data = data;
	}

	/*!
	 *  \brief Retourner le bit de coordonnées i, j d'une matrice
	 *
	 * \param m : matrice des couches.
	 * \param c : Coordonnées 2D afin de se situer dans la matrice.
	 * \param p : Paramètres du bassin versant.
	 * \return la valeur du bit correspondant au pixel i, j dans la matrice m.
	 */

	bool getmatbit (const Coordinates & c, const Parameters * p) const
	{
		return (((*( _data + (c.getLine() *p->_charColumnsNumber+(c.getColumn()>>3))))>>(c.getColumn()&7)) & 1);
	}

	/*!
	 *  \brief Affecte la valeur 1 au bit correspondant au pixel i, j dans la matrice m.
	 *
	 * \param m : Matrice des couches.
	 * \param c : Coordonnées 2D afin de se situer dans la matrice.
	 * \param p : Paramètres du bassin versant.
	 * \return void.
	 */

	void matbiton (const Coordinates & c, const Parameters * p)
	{
		*(_data + (c.getLine() * p->_charColumnsNumber +(c.getColumn()>>3))) |= 1<<(c.getColumn()&7);
	}


	/*!
	 *  \brief Affecte la valeur 0 au bit correspondant au pixel i, j dans la matrice m.
	 *
	 * \param m : Matrice des couches.
	 * \param c : Coordonnées 2D afin de se situer dans la matrice.
	 * \param p : Paramètres du bassin versant.
	 * \return void.
	 */

	void matbitoff (Coordinates &c, const Parameters * p)
	{
		*(_data + (c.getLine() * p->_charColumnsNumber + (c.getColumn()>>3))) &= ~(1<<(c.getColumn()&7)) ;
	}


	bool isNetwork(const Coordinates & c, const Parameters * p) const
	{
		return getmatbit(c, p);
	}
};



#endif /* LAYER_H_ */
