/**
 * @file tests/boost_graph/partitioning/gggp.cpp
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

#include <algorithm>
#include <iostream>

namespace paradevs { namespace tests { namespace boost_graph {

extern UnorientedGraph::vertex_iterator vertexIt, vertexEnd;
extern UnorientedGraph::adjacency_iterator neighbourIt, neighbourEnd;

extern OrientedGraph::vertex_iterator vertexIto, vertexEndo;
extern OrientedGraph::adjacency_iterator neighbourIto, neighbourEndo;

void gggp(UnorientedGraph *g, Entiers *sommetsSource,
          Entiers *sommetsDestination, EntiersEntiers &Partition)
{
    int val;
    Entiers sommets_adj;

    if (sommetsSource->size() - 1 == 0) {
        Entiers tailles;

        val = 0;
        for (uint i = 0;i < Partition.size(); i++) {
            tailles.push_back(Partition.at(i)->size());
        }

        uint tmp = *max_element(tailles.begin(), tailles.end());

        for (uint i = 0; i < Partition.size(); i++) {
            if (Partition.at(i)->size() == tmp) {
                gggp(g, Partition.at(i), sommetsDestination, Partition);
            }
            break;
        }
    } else {

        // Tirage aléatoire de l'indice du premier sommet entre 0 et
        // taille du tableau -1
        val = rand_fini(0, sommetsSource->size() - 1);
    }

    float poids_max=sommetsSource->size()/2.;
    float poids=1;
    Entiers sommets_cut;

    //clog<<"Etape 1 : "<<std::endl;
    sommetsDestination->push_back(sommetsSource->at(val));
    sommetsSource->erase(sommetsSource->begin() + val);

    if (sommetsSource->size() < 2) {
        return;
    }

    while (poids < poids_max) {
//		for(uint i =0; i< sommetsDestination.size();i++){
//			std::cout<<sommetsDestination.at(i)<<std::endl;
//		}
        Liste_Voisin(*sommetsDestination, sommets_adj, *g);
        if (sommets_adj.size() == 0) {
            std::cout<<"Je suis sorti !!!! "<<std::endl;
            break;
        } else {
            /*clog<<"Liste voisin est : "<<std::endl;
              for(int i=0;i<sommets_adj.size();i++)
              {
              std::cout<<sommets_adj[i]<<std::endl;
              }*/
            std::sort(sommets_adj.begin(), sommets_adj.end());
            for (uint i = 0; i < sommets_adj.size(); i++) {
                sommets_cut.push_back(Cout_coupe(*sommetsDestination,
                                                 sommets_adj[i], *g));
            }

            int tmp = recherche_val(sommets_cut,
                                    *min_element(sommets_cut.begin(),
                                                 sommets_cut.end()));
            sommetsDestination->push_back(sommets_adj[tmp]);
            suprim_val(*sommetsSource, sommets_adj[tmp]);
            suprim_val(sommets_adj, sommets_adj[tmp]);

            sommets_cut.clear();
            poids++;
        }
    }

    for (uint i = 0; i < sommetsSource->size(); i++) {
        for (uint j = 0; j < sommetsDestination->size(); j++) {
            remove_edge(sommetsSource->at(i), sommetsDestination->at(j), *g);
        }
    }
    sort(sommetsDestination->begin(), sommetsDestination->end());
}

void gggp_pond(UnorientedGraph *g, Entiers *sommetsSource,
               Entiers *sommetsDestination, EntiersEntiers &Partition)
{
    int val;
    Entiers sommets_adj;
    if((sommetsSource->size()-1)==0){
        val=0;
        std::cout<<"Entré dans le debug ! "<<std::endl;
        Entiers tailles;
        for(uint i=0;i<Partition.size();i++){
            tailles.push_back(Partition.at(i)->size());
        }
        uint tmp=*max_element(tailles.begin(),tailles.end());
        for(uint i=0; i<Partition.size();i++){
            if(Partition.at(i)->size()==tmp)
                gggp_pond(g,Partition[i],sommetsDestination,Partition);
            break;
        }
    }
    else
        val=rand_fini(0,sommetsSource->size()-1);//Tirage aléatoire de l'indice du premier sommet entre 0 et taille du tableau -1
    double poids_max=0;
    for(uint i=0;i<sommetsSource->size();i++){
        poids_max+=(*g)[sommetsSource->at(i)]._weight;
    }
    poids_max/=2.;
    double poids=(*g)[sommetsSource->at(val)]._weight;
    std::vector<float> sommets_cut;

    sommetsDestination->push_back(sommetsSource->at(val));
    sommetsSource->erase(sommetsSource->begin() + val);

    if(sommetsSource->size()<2)
        return;

    while(poids<poids_max)
    {
        Liste_Voisin(*sommetsDestination,sommets_adj,*g);
        if((sommets_adj.size()==0))
        {
            std::cout<<"Je suis sorti !!!! "<<std::endl;
            return;
        }
        else{
            sort(sommets_adj.begin(), sommets_adj.end());

            for(uint i=0;i<sommets_adj.size();i++)
            {
                sommets_cut.push_back(Cout_coupe_pond(*sommetsDestination,sommets_adj[i],*g));
            }
            sommetsDestination->push_back(sommets_adj[recherche_val2(sommets_cut,*min_element(sommets_cut.begin(),sommets_cut.end()))]);
            poids+=(*g)[sommets_adj[recherche_val2(sommets_cut,*min_element(sommets_cut.begin(),sommets_cut.end()))]]._weight;
            suprim_val(*sommetsSource, sommets_adj[recherche_val2(sommets_cut,*min_element(sommets_cut.begin(),sommets_cut.end()))]);
            suprim_val(sommets_adj, sommets_adj[recherche_val2(sommets_cut,*min_element(sommets_cut.begin(),sommets_cut.end()))]);

            sommets_cut.clear();

        }
    }

    edge_t e1;
    // bool found;

    for (uint i=0; i<sommetsSource->size();i++)
    {
        for (uint j=0; j<sommetsDestination->size();j++)
        {
            remove_edge(sommetsSource->at(i),sommetsDestination->at(j),*g);
        }
    }
    sort(sommetsDestination->begin(), sommetsDestination->end());
}

void Iter_2l(EntiersEntiers &part, int nbr_parties, UnorientedGraph *g,
             const std::string &nom)
{
    if (nom!="gggp_pond"){
        //std::cout<<"je jsuis dans gggp"<<std::endl;

        for(int i = 0; i<floor(log(nbr_parties)/log(2)); i++)
        {
            //std::cout<<"Et un tours de plus !!!! "<<std::endl;
            for(int j = 0; j< pow(2,i);j++)
            {
                Entiers *Q = new Entiers();
                gggp(g,part[j],Q,part);
                part.push_back(Q);
            }

        }
    } else {
        //std::cout<<"je jsuis dans gggp_pond"<<std::endl;

        for(int i = 0; i<floor(log(nbr_parties)/log(2)); i++)
        {
            std::cout<<"Et un tours de plus !!!! "<<std::endl;
            for(int j = 0; j< pow(2,i);j++)
            {
                Entiers *Q = new Entiers();
                gggp_pond(g,part.at(j),Q,part);
                std::clog<<"sortie du gggp_pond"<<std::endl;
                part.push_back(Q);
            }

        }
    }
}

void bissectionRec(UnorientedGraph *g, EntiersEntiers &Partition,
                   int nbr_parties, const std::string &nom)
{
    if((nbr_parties&(nbr_parties-1))==0)
    {
        //std::cout<<"C'est de la forme 2l : "<<nbr_parties<<std::endl;
        Iter_2l(Partition,nbr_parties,g,nom);
    } else {
        int puissance_2=0;

        Entiers tailles;

        while(pow(2,puissance_2)<nbr_parties)
            puissance_2++;


        Iter_2l(Partition,pow(2,puissance_2-1),g,nom);

        for(unsigned int i = 0; i< Partition.size() -1 ; i++)
        {
            for(EntiersEntiers::iterator it1 = Partition.begin() + i ; it1!=Partition.end(); it1++)
            {
                if((*it1)->size() > Partition.at(i)->size())
                    Partition.at(i)->swap(**it1);
            }
        }
        /*std::cout<<"****"<<std::endl;
          for(int k=0; k<Partition.size(); k++)
          {
          for(int j=0; j<Partition[k]->size(); j++)
          {
          std::cout<<Partition[k]->at(j)<<std::endl;
          }
          std::cout<<"\n"<<std::endl;
          }
          std::cout<<"****"<<std::endl;
          std::cout<<"Et on termine les dernières bissections !!!! "<<std::endl;*/
        for(int j = 0; j<nbr_parties-pow(2,puissance_2-1);j++)
        {
            Entiers *Q = new Entiers();
            if(nom!="gggp_pond")
                gggp(g,Partition.at(j),Q,Partition);
            else
                gggp_pond(g,Partition.at(j),Q,Partition);
            Partition.push_back(Q);
            //Q.clear();
        }
    }
}

/**
 * Fonction réalisant un partitionnement pseudo aléatoire suivant un voisinage.
 * @param *g : adresse d'un graphe de type boost graphe undirected
 * @param Partition : vecteur contenant des vecteurs d'entiers [tableau contenant les parties de la partition]
 * @param nbr_partie : entier correspondant au nombre de parties voulues pour la partition
 * @return
 */

void Pseudo_random_partitioning(UnorientedGraph *g, EntiersEntiers &Partition,
                                uint nbr_parties)
{
    /*
     * Principe : distribution des sommets de la première partie en plusieurs autres parties
     * Le partitionnement étant pseudo aléatoire il n'y a pas de contrainte stricte sur le nombre
     * de sommets par partie
     */


    uint size = Partition.at(0)->size();
    uint cpt_sommets=1;
    int val;
    uint cpt;

    if(nbr_parties==size){
        for(uint i = 0; i < nbr_parties;i++){
            if(Partition.at(0)->size()!=1)
            {
                val=rand_fini(0,Partition.at(0)->size()-1);//tirage aléatoire d'un sommets
            }
            else
                val=0;

            int vertex = Partition.at(0)->at(val);
            Entiers *part = new Entiers();
            part->push_back(vertex);// ajout du sommet tiré
            suprim_val(*Partition.at(0),vertex);//suppression du sommet dans la premiere partie


        }
    }
    /*
     * Boucle sur le nombre de partie à réaliser
     */
    for(uint i = 0; i < nbr_parties-1;i++){
        if(Partition.at(0)->size()!=1)
        {
            val=rand_fini(0,Partition.at(0)->size()-1);//tirage aléatoire d'un sommets
        }
        else
            val=0;
        int vertex = Partition.at(0)->at(val);
        /*
         * Initialisation d'un pointeur sur un vecteur d'entier, dans notre cas
         * la n+1 ième partie de la partition
         */
        Entiers *part = new Entiers();
        part->push_back(vertex);// ajout du sommet tiré
        suprim_val(*Partition.at(0),vertex);//suppression du sommet dans la premiere partie
        cpt=1;

        /*
         * Pour chaque element de la nouvelle partie faire
         */
        for(uint j = 0; j<part->size();j++){
            /*
             * Détermination des voisins de chacun des sommets de cette nouvelle
             * partie et ajoue de ce voisin si celui-ci est présent dans la première partie (Partition[0])
             */
            tie(neighbourIt, neighbourEnd) = adjacent_vertices(part->at(j),*g);
            for (; neighbourIt != neighbourEnd; ++neighbourIt){
                if(In_tab(*Partition.at(0),*neighbourIt)==1){
                    std::cout<<"le voisin déplacé est : "<<*neighbourIt<<std::endl;
                    part->push_back(*neighbourIt);
                    cpt_sommets++;
                    suprim_val(*Partition.at(0),*neighbourIt);
                    cpt++;
                }
                /*
                 * Si le nombre moyen de sommets est atteind dans la partie on sort de la boucle des voisins
                 * Même chose si l'on a rencontré le nombre total de sommets
                 */
                if(cpt==(size/nbr_parties)+1)
                    break;
                if(cpt_sommets==size)
                    break;
            }

            /*
             * Même chose
             */
            if(cpt==(size/nbr_parties)+1)
                break;
            if(cpt_sommets==size)
                break;
        }
        Partition.push_back(part);// ajoue de la nouvelle partie à la partition
        if(cpt_sommets==size)
            break;
    }
}

OrientedGraphs Multiniveau(uint niveau_contraction,
                           UnorientedGraph *g,
                           OrientedGraph *go,
                           int nbr_parties,
                           std::string type_methode,
                           std::string choix_affinage,
                           std::string type_cut,
                           Edges& /* edge_partie */,
                           OutputEdgeList& outputedgeslist,
                           InputEdgeList& inputedgelist,
                           Connections& connections)
{
    EntiersEntiers Partition;
    Entiers *part = new Entiers();
    Base_Graph baseg;
    baseg.push_back(g);
    ListEntiersEntiers liste_corr;
    uint cpt =0;
    while(num_vertices(*baseg.at(cpt))>niveau_contraction)
    {
        contraction_HEM(baseg.at(cpt),baseg,liste_corr);
        cpt++;
    }

    for(uint i = 0;i < num_vertices(*baseg.at(baseg.size() - 1)); i++)
    {
        part->push_back(i);
    }
    Partition.push_back(part);

    bissectionRec(baseg.at(baseg.size()-1),Partition,nbr_parties,type_methode);

    std::clog<<"Partition : "<<std::endl;
    for(uint i = 0; i< Partition.size() ; i++)
    {
    for(uint j = 0 ; j<Partition.at(i)->size() ; j++)
    {
    std::cout<<(*baseg.at(baseg.size()-1))[Partition.at(i)->at(j)]._index<<std::endl;
    }
    std::cout<<"\n"<<std::endl;
    }

    ListEntiersEntiers::iterator lit(liste_corr.end());
    lit--;
    for(uint y =0; y<liste_corr.size();y++){
        projection(Partition,lit);
        double cut = Cut_cluster(Partition,*baseg.at(baseg.size()-2-y),type_cut);
        std::cout<<"Cout de coupe avant affinage : "<<cut<<std::endl;

        if(choix_affinage=="charge")
            Affinage_equilibrage_charge(baseg.at(baseg.size()-2-y),Partition);
        else
            Affinage_recherche_locale(baseg.at(baseg.size()-2-y),Partition,cut,type_cut);

        std::cout<<"Cout de coupe après affinage : "<<cut<<std::endl;
        lit--;
    }

    OrientedGraphs Graphes = Graph_Partition(Partition, go, g, outputedgeslist,
                                             inputedgelist, connections);

    for(int k=0; k<Partition.size(); k++)
    {
    	for(int j=0; j<Partition[k]->size(); j++)
    	{
    		std::cout<<Partition[k]->at(j)<<std::endl;
    	}
    	std::cout<<"\n"<<std::endl;
    }
    std::cout<<"****"<<std::endl;

    for(EntiersEntiers::iterator it = Partition.begin(); it != Partition.end(); it++)
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
    }
    return Graphes;
}

} } } // namespace paradevs tests boost_graph
