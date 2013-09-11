/**
 *
 * \file Graph.cpp
 * \author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 * \version 2.0
 * \date 30 mai 2013
 * \brief Générateur du graphe représentant un bassin versant.
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

#include "Graph.hpp"

Graph::Graph(): _isolatedVertices(0), _param(NULL)
{ }

void Graph::build(std::vector<float> * elevationMatrix, Parameters * p)
{
    _param = p;

    int counter = 0;
    for (int i = 0 ; i < p->_linesNumber; i++) {
        for (int j = 0 ; j < p->_columnsNumber ; j++) {
            if (elevationMatrix->at(i*p->_columnsNumber+j) > ALTMER) {
                _vertices[i * p->_columnsNumber + j] =
                    Vertex(i * p->_columnsNumber + j,
                           Coordinates(i, j),
                           elevationMatrix->at(i * p->_columnsNumber + j));
                counter++;
            }
        }
    }

    std::vector < Vertex* > tmpVertices;

    for(std::map < int, Vertex >::iterator it = _vertices.begin();
        it!=_vertices.end(); it++) {
        for (int i = it->second.getCoord().getLine() - 1 ;
             i <= it->second.getCoord().getLine() +1 ; i++) {
            for (int j = it->second.getCoord().getColumn() - 1 ;
                 j <= it->second.getCoord().getColumn()  + 1 ; j++) {
                if (Coordinates(i,j).isValid(p) &&
                    (not it->second.getCoord().isSameLine(i) ||
                     not it->second.getCoord().isSameColumn(j))) {
                    tmpVertices.push_back(
                        &_vertices[i * p->_columnsNumber + j]);
                }
            }
        }
        it->second.setNeighbours(tmpVertices);
        tmpVertices.clear();
    }
    buildMesh();
    buildTablelandsMeshes() ;
}

void Graph::display()
{
    //const char* name = "ABCDEF";
    int tablelandsCounter = 0;

    //std::cout << "vertex set: ";
    //boost::print_vertices(_gno, name);
    //std::cout << std::endl;
    //
    //std::cout << "edge set: ";
    //boost::print_edges(_gno, name);
    //std::cout << std::endl;
    //
    //std::cout << "incident edges: " << std::endl;
    //boost::print_graph(_gno, name);
    //std::cout << std::endl;

    for (std::map < int, Vertex >::iterator it = _vertices.begin();
         it != _vertices.end(); it++) {
        if (it->second.getMp() == 'v')
            tablelandsCounter++ ;
    }

    DirectedGraph::vertex_iterator beginV, endV;
    DirectedGraph::adjacency_iterator beginA, endA;

    std::cout << "edge set: \n";
    boost::tie(beginV, endV) = boost::vertices(_go);
    for(; beginV!=endV; beginV++)
    {
        std::cout<<*beginV<<" -> ";
        boost::tie(beginA,endA) = boost::adjacent_vertices(*beginV,_go);
        for(; beginA!=endA; beginA++)
        {
            std::cout<<*beginA<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"vertices number : "<<boost::num_vertices(_go)<<"\n";
    std::cout<<"edges number : "<<boost::num_edges(_go)<<"\n";
    std::cout<<"meshes number of tableland type :"<<tablelandsCounter<<std::endl;
}

void Graph::buildMesh()
{
    std::vector<Vertex *>tmpNeighbours;

    for(std::map<int,Vertex>::iterator it = _vertices.begin(); it!=_vertices.end();it++)
    {
        if(it->second.getElevation() > ALTMER)
        {
            if(it->second.sigma(Vertex::elevation) <= EPSALT && not it->second.getCoord().isOnShore(_param) && not it->second.isOnSeaside())
                it->second.setMp('p');
            else
            {
                createVertex(it->second);
                tmpNeighbours = it->second.getNeighbours();
                for(std::vector<Vertex *>::iterator itNeighbours = tmpNeighbours.begin(); itNeighbours != tmpNeighbours.end(); itNeighbours++)
                {
                    if ((*itNeighbours)->getElevation() > ALTMER && ((it->second.getElevation() - (*itNeighbours)->getElevation()) > EPSALT))
                    {
                        createVertex(**itNeighbours);
                        createEdge((*itNeighbours), it->second,  (*itNeighbours)->tanBxL(&it->second, Vertex::elevation) / it->second.sigma(Vertex::elevation)) ;
                    }
                }
            }
        }
    }
}

void Graph::buildTablelandsMeshes()
{
    int nbi;

    for(std::map<int, Vertex>::iterator it = _vertices.begin(); it!=_vertices.end(); it++)
    {
        if (it->second.getMp() == 'p')
        {
            it->second.setMp('v');
            nbi = 0;
            searchOutlet (it->second, nbi) ;
            // if ( nbi == 0)
                // std::cerr<<"\n"<<_isolatedVertices++ <<" Impossible de sortir du plateau "<<it->second.toString()<<"\t"<<" and "<< nbi <<"issue(s)."<<std::endl;

            computeGeodesic() ;
            addTablelandsEdges() ;
            for(std::vector<Vertex *>::iterator it = _tablelandVertices.begin(); it!=_tablelandVertices.end(); it++)
                (**it).setDerive(-999999.0);
            _tablelandVertices.clear();
        }
    }
}

void Graph::searchOutlet(Vertex & m, int nbi)
{
    std::vector<Vertex *>tmpNeighbours = m.getNeighbours();

    for(std::vector<Vertex *>::iterator itNeighbours = tmpNeighbours.begin(); itNeighbours != tmpNeighbours.end(); itNeighbours++)
    {
        if (fabs((**itNeighbours).getElevation() - m.getElevation()) < 0.0001)
        {
            if ((**itNeighbours).getMp() == 'p')
            {
                (**itNeighbours).setMp('v');
                searchOutlet(**itNeighbours, nbi) ;
            }
            else if ((**itNeighbours).getMp() == 'n')
            {
                (**itNeighbours).setDerive(1.);
                nbi++;
                (**itNeighbours).setMp('i');
                _tablelandVertices.push_back((*itNeighbours));
            }
        }
    }
}

void Graph::computeGeodesic()
{
    std::vector<Vertex *>tmpNeighbours;
    int i = 0;
    while(_tablelandVertices.begin() + i != _tablelandVertices.end())
    {
        tmpNeighbours = _tablelandVertices.at(i)->getNeighbours();

        for(std::vector<Vertex *>::iterator itNeighbours = tmpNeighbours.begin(); itNeighbours != tmpNeighbours.end(); itNeighbours++)
        {
            if ((**itNeighbours).getMp() == 'v')
            {
                (**itNeighbours).setDerive(_tablelandVertices.at(i)->getDerive() + 1.);
                (**itNeighbours).setMp('g');
                _tablelandVertices.push_back(*itNeighbours);
            }
        }
        i++;
    }
}

void Graph::addTablelandsEdges()
{
    std::vector<Vertex *>tmpNeighbours;

    for (std::vector<Vertex *>::iterator it = _tablelandVertices.begin(); it!=_tablelandVertices.end(); ++it)
    {
        createVertex(**it);
        tmpNeighbours = (**it).getNeighbours();

        for(std::vector<Vertex *>::iterator itNeighbours = tmpNeighbours.begin(); itNeighbours != tmpNeighbours.end(); itNeighbours++)
        {
            if ((**itNeighbours).getDerive() > ALTMER && (**itNeighbours).getDerive() < (**it).getDerive())
            {
                createVertex(**itNeighbours);
                createEdge((*itNeighbours), **it,  (*itNeighbours)->tanBxL(*it, Vertex::derive) / (*it)->sigma(Vertex::derive)) ;
            }
        }
    }
}
