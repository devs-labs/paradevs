/**
 * @file tests/boost_graph/partitioning/main.cpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013 ULCO http://www.univ-litoral.fr
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

#include <tests/boost_graph/partitioning/gggp.hpp>
#include <tests/boost_graph/partitioning/graph_build.hpp>

#include <boost/timer.hpp>

#include <iostream>

using namespace paradevs::tests::boost_graph;

UnorientedGraph::vertex_iterator vertexIt, vertexEnd;
UnorientedGraph::adjacency_iterator neighbourIt, neighbourEnd;

OrientedGraph::vertex_iterator vertexIto, vertexEndo;
OrientedGraph::adjacency_iterator neighbourIto, neighbourEndo;

int main()
{
    boost::timer t;

    srand((unsigned)time(NULL));

    UnorientedGraph* g = new UnorientedGraph();
    OrientedGraph* go = new OrientedGraph();

    build_graph(*g, *go);

    int nbr_parties = 3;
    Edges edge_partie;
    OutputEdgeList outputedgeslist(nbr_parties);
    InputEdgeList inputedgelist;
    Connections connections;

    /*EntiersEntiers Partition;
      Entiers *part = new Entiers();
      Base_Graph baseg;
      baseg.push_back(g);
      ListEntiersEntiers liste_corr;
      uint cpt=0;
      while(num_vertices(*baseg.at(cpt))>4)
      {
      contraction_HEM(baseg.at(cpt),baseg,liste_corr);
      cpt++;
      }

      edge_t e1;
      bool found;
      for(uint i=0;i<baseg.size();i++){
      tie(vertexIt, vertexEnd) = vertices((*baseg.at(i)));
      for (; vertexIt != vertexEnd; ++vertexIt)
      {
      std::cout << *vertexIt << " est connecté avec ";
      tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, (*baseg.at(i)));
      for (; neighbourIt != neighbourEnd; ++neighbourIt){
      std::cout << *neighbourIt << " ";
      tie(e1,found)=edge(vertex(*vertexIt,*baseg.at(i)),vertex(*neighbourIt,*baseg.at(i)),*baseg.at(i));
      std::cout << "poids arc : "<<(*baseg.at(i))[e1]._weight<<"\n";
      }
      std::cout<<" et son poids est de "<< (*baseg.at(i))[*vertexIt]._weight<<std::endl;
      }
      std::cout<<"\n"<<std::endl;
      }


      for(int i =0;i<num_vertices(*baseg.at(baseg.size()-1));i++)
      {
      part->push_back(i);
      }
      Partition.push_back(part);

      bissectionRec(baseg.at(baseg.size()-1),Partition,3,"gggp_pond");
      //Pseudo_random_partitioning(g,Partition,3);
      std::cout<<"Nombre de parties : "<<Partition.size()<<std::endl;

      std::clog<<"Resultat de la partition : "<<std::endl;
      std::cout<<"****"<<std::endl;
      for(uint i = 0; i< Partition.size() ; i++)
      {
      for(uint j = 0 ; j<Partition.at(i)->size() ; j++)
      {
      std::cout<<(*baseg.at(baseg.size()-1))[Partition.at(i)->at(j)]._index<<std::endl;
      }
      std::cout<<"\n"<<std::endl;
      }
      std::cout<<"****"<<std::endl;


      ListEntiersEntiers::iterator lit(liste_corr.end());
      lit--;
      for(uint y =0; y<liste_corr.size();y++){
      projection(Partition,lit);

      std::clog<<"liste de correspondance : "<<std::endl;
      for(uint i = 0; i < (*lit)->size(); i++)
      {
      for(uint j = 0; j < (*lit)->at(i)->size();j++){
      std::cout<<(*lit)->at(i)->at(j)<<std::endl;;
      }
      std::cout<<"\n"<<std::endl;
      }

      std::clog<<"Resultat projection : "<<std::endl;
      for(uint i = 0; i< Partition.size() ; i++)
      {
      for(uint j = 0 ; j<Partition.at(i)->size() ; j++)
      {
      std::cout<<Partition.at(i)->at(j)<<std::endl;
      }
      std::cout<<"\n"<<std::endl;
      }

      double cut = Cut_cluster(Partition,*baseg.at(baseg.size()-2-y),"norm");

      std::cout<<"Cout de coupe avant affinage : "<<cut<<std::endl;

      Affinage_recherche_locale(baseg.at(baseg.size()-2-y),Partition,cut,"norm");
      //Affinage_equilibrage_charge(baseg.at(baseg.size()-2-y),Partition);
      std::cout<<"Cout de coupe après affinage : "<<cut<<std::endl;
      std::cout<<"\n"<<std::endl;
      double tmp = Cut_cluster(Partition,*baseg.at(baseg.size()-2-y),"norm");
      std::cout<<"verification cout de coupe après affinage : "<<tmp<<std::endl;
      std::cout<<"\n"<<std::endl;
      std::clog<<"Partition après affinage : "<<std::endl;
      for(uint i = 0; i< Partition.size() ; i++)
      {
      for(uint j = 0 ; j<Partition.at(i)->size() ; j++)
      {
      std::cout<<Partition.at(i)->at(j)<<std::endl;
      }
      std::cout<<"\n"<<std::endl;
      }

      lit--;
      }
      std::cout<<"mathieu va me buter ! et en plus c'est walker !!!"<<std::endl;
      std::cout<<"\n"<<std::endl;

      OrientedGraphs Graphes = Graph_Partition(Partition,go,g,outputedgeslist,inputedgelist,connections);*/

    OrientedGraphs graphs = Multiniveau(4, g, go, nbr_parties, "gggp_pond",
                                        "cut_norm", "norm", edge_partie ,
                                        outputedgeslist, inputedgelist,
                                        connections);

    std::cout << std::endl;
    std::cout << "Sous Graphes :" << std::endl;
    for (uint i = 0; i< graphs.size(); i++) {
        tie(vertexIto, vertexEndo) = vertices(graphs[i]);
        for (; vertexIto != vertexEndo; ++vertexIto) {
            std::cout << graphs[i][*vertexIto]._index
                      << " est connecté avec ";
            tie(neighbourIto, neighbourEndo) = adjacent_vertices(*vertexIto,
                                                                 graphs[i]);
            for (; neighbourIto != neighbourEndo; ++neighbourIto)
                std::cout << graphs[i][*neighbourIto]._index << " ";
            std::cout << " et son poids est de "
                      << graphs[i][*vertexIto]._weight<<std::endl;
        }
        std::cout << std::endl;
    }

    std::clog << "OutputEdgeList :" << std::endl;
    for (uint i = 0; i < outputedgeslist.size(); i++) {
        for (uint j = 0; j < outputedgeslist.at(i).size(); j++){
            std::cout << outputedgeslist.at(i).at(j).first << " "
                      << outputedgeslist.at(i).at(j).second << std::endl;
        }
    }
    std::cout << std::endl;

    std::clog << "InputEdgeList :" << std::endl;
    for (uint i = 0; i < inputedgelist.size(); i++) {
        for (uint j = 0; j < inputedgelist.at(i).size(); j++){
            std::cout << inputedgelist.at(i).at(j).first << " "
                      << inputedgelist.at(i).at(j).second << std::endl;
        }
    }
    std::cout << std::endl;

    std::clog << "Connections :" << std::endl;
    for (uint i = 0; i < connections.size(); i++) {
        std::cout << "(" << connections.at(i).first.first << ","
                  << connections.at(i).first.second << ") -> ("
                  << connections.at(i).second.first << ","
                  << connections.at(i).second.second << ")"
                  << std::endl;
    }

    /*for(EntiersEntiers::iterator it = Partition.begin(); it != Partition.end(); it++)
      {
      delete *it;
      *it = NULL;
      }

      for(ListEntiersEntiers::iterator it = liste_corr.begin(); it != liste_corr.end(); it++)
      {
      for(EntiersEntiers::iterator it1 = (*it)->begin(); it1 != (*it)->end(); it1++)
      {
      delete *it1;
      *it1 = NULL;
      }
      delete *it;
      *it = NULL;
      }

      for(Base_Graph::iterator it = baseg.begin(); it != baseg.end(); it++)
      {
      delete *it;
      *it = NULL;
      }*/

    // for(OrientedGraphs::iterator it = Graphes.begin(); it != Graphes.end();
    //     it++) {
    //     delete *it;
    //     *it = NULL;
    // }

    std::cout << "Duration : " << t.elapsed() << " seconds" << std::endl;

    //EntiersEntiersEntiers Stock_Partition;
    /*for(int i=0;i<11;i++){
      g1=g;
      Partition1=Partition;
      bissectionRec(g1,Partition1,4,"gggp");
      Stock_Partition.push_back(Partition1);
      Cut.push_back(Cut_cluster(Partition1,g));
      Partition1.clear();
      g1.clear();
      }

      for(int i =0;i<Cut.size();i++){
      std::cout<<Cut[i]<<std::endl;
      }
      std::cout<<"\n"<<std::endl;
      std::cout<<recherche_val_double(Cut,*min_element(Cut.begin(),Cut.end()))<<std::endl;
      std::cout<<"\n"<<std::endl;
      EntiersEntiers tmp = Stock_Partition[recherche_val_double(Cut,*min_element(Cut.begin(),Cut.end()))];
      for(int i =0; i<tmp.size();i++){
      for(int j=0; j<tmp[i].size();j++){
      std::cout<<tmp[i][j]<<std::endl;
      }
      std::cout<<"\n"<<std::endl;
      }*/

    /*EntiersEntiers liste_corr;
    //double cut = Cut_cluster(Partition,g);
    Base_Graph baseg;
    baseg.push_back(g);




    std::cout<<"LIste des noeuds fusionés : "<<std::endl;
    for(uint i = 0; i< liste_corr.size() ; i++)
    {
    for(uint j = 0 ; j<liste_corr.at(i).size() ; j++)
    {
    std::cout<<liste_corr[i][j]<<std::endl;
    }
    std::cout<<"\n"<<std::endl;
    }*/


}
