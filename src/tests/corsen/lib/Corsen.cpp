/*!
 * \file Corsen.cpp
 * \brief Charge les différents fichiers en mémoire et lance la
 * génération du graphe.
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
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

#include "Corsen.hpp"

int Coordinates::_columnsNumber = 0;

Corsen::Corsen() : _graph()
{
    _pfs = NULL;
    _efs = NULL;
    _ofs = NULL;
    _gfs = NULL;
    _lfs = NULL;
    _sfs = NULL;
    _dfs = NULL;
    _elevationMatrixBv = NULL;
    _outlet = NULL;
    _soilMatrix = NULL;
    _gradientMatrix = NULL;
    _elevationMatrix = NULL;
    _outlets = NULL;
    _param = NULL;
    _layers = NULL;
}

void Corsen::read(std::vector < std::string* > & files,
                  std::string& absolutePath) throw (FileNotFound, ReadError,
                                                    InvalidFileFormat,
                                                    std::invalid_argument)
{
    std::stringstream ss;

    _pfs = new ParametersFileStream(*files.at(0), *files.at(1));
    _efs = new ElevationFileStream(*files.at(2));
    _ofs = new OutletFileStream(*files.at(3));
    _gfs = new SlopeFileStream(*files.at(4));
    _dfs = new DrainFileStream<corsenContainers::vecS, float>(*files.at(4));

    ContextData * ctxtD = ContextData::getInstance();

    ContextFileReader::read((*files.at(5)).c_str(), ctxtD->_numberDays,
                            ctxtD->_simulationStartDate,
                            ctxtD->_outletsCoordinates);
    _sfs = new SoilFileStream(absolutePath + ctxtD->_soilFileName);

    _layers = new std::vector<Layer>();
    _layers->push_back(Layer(std::string("Reseau Hydrographique"), 0, 0,
                             RESEAU_HYDRO, false));

    _param = _pfs->read();
    Coordinates::_columnsNumber = _param->_columnsNumber;

    _soilMatrix = _sfs->read();
    _gradientMatrix = _gfs->read();
    _elevationMatrix = _efs->read();
    _outlets = _ofs->read();

    int layerNumber = Layer::find(*_layers, RESEAU_HYDRO);

    if(layerNumber == -1)
        throw std::invalid_argument(
            "Impossible de trouver l'élément dans le tableau de couches");

    ss << *files.at(6) << layerNumber;
    _lfs = new LayersFileStream(ss.str(), _param);
    _layers->at(layerNumber).setData(_lfs->read());
}

void Corsen::buildGraph()
{
    Coordinates c(ContextData::getInstance()->_outletsCoordinates[0].line, ContextData::getInstance()->_outletsCoordinates[0].column);
    for(std::list<Outlet *>::const_iterator it = _outlets->begin(); it!=_outlets->end();it++)
    {
        if((*it)->getCoord() == c)
        {
            _outlet = *it;
            _outlet->setBrother(NULL);
            break;
        }
        _outlet = (*it)->searchChildNode(c);
        if (_outlet != NULL)
        {
            _outlet->setBrother(NULL);
            break;
        }
    }

    _layers->at(Layer::find(*_layers, RESEAU_HYDRO)).matbiton(_outlet->getCoord(), _param);

    _efs->write(*_elevationMatrix, std::string(".sav"));
    std::stack<Node *> stack;

    stack.push(_outlet);
    _elevationMatrixBv = new std::vector<float>(_elevationMatrix->size());

    while (not stack.empty())
    {
        Node * s = stack.top();
        unsigned int index = s->getCoord().getLine() * _param->_columnsNumber + s->getCoord().getColumn();

        _elevationMatrixBv->at(index) = _elevationMatrix->at(index);
        stack.pop();
        if (s->getBrother())
            stack.push(s->getBrother());
        if (s->getChild())
            stack.push(s->getChild());
    }

    _graph.build(_elevationMatrixBv, _param);
}

void Corsen::display()
{
    std::cout<<"Les paramètres du programme sont :"<<_param->toString()<<std::endl;
    std::cout<<"Liste d'adjacence :"<<std::endl;
    _graph.display();
#ifdef DEBUG
    std::cout<<"Tableau de couches :"<<std::endl;
    for(std::vector<Layer>::const_iterator it = _layers->begin(); it!=_layers->end(); it++)
        it->display(_param);
#endif

}

Corsen::~Corsen()
{
    if(_outlets !=NULL)
    {
        for(std::list<Outlet *>::iterator it = _outlets->begin(); it!=_outlets->end(); it++)
        {
            delete (*it);
            *it = NULL;
        }
    }

    if(_soilMatrix != NULL)
        delete _soilMatrix;
    if(_gradientMatrix !=NULL)
        delete _gradientMatrix;
    if(_param !=NULL)
        delete _param;
    if(_outlets !=NULL)
        delete _outlets;
    if(_elevationMatrix !=NULL)
        delete _elevationMatrix;
    if(_pfs != NULL)
        delete _pfs;
    if(_efs != NULL)
        delete _efs;
    if(_ofs != NULL)
        delete _ofs;
    if(_gfs != NULL)
        delete _gfs;
    if(_sfs != NULL)
        delete _sfs;
    if(_lfs != NULL)
        delete _lfs;
    if(_layers != NULL)
        delete _layers;
    if(_elevationMatrixBv != NULL)
        delete _elevationMatrixBv;
    if(_dfs != NULL)
        delete _dfs;
    ContextData::kill();
#ifdef DEBUG
    std::cout<<"destruction achevée \n";
#endif
}
