/**
 * @file tests/boost_graph/partitioning/utils.hpp
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

#ifndef TESTS_BOOST_GRAPH_PARTITIONING_UTILS_H
#define TESTS_BOOST_GRAPH_PARTITIONING_UTILS_H 1

#include <tests/boost_graph/partitioning/defs.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

void Global_Neigh_community(UnorientedGraph *g,
                            const EntiersEntiers &Partition,
                            Entiers *community, int vertex, int comm_in);

OrientedGraphs Graph_Partition(const EntiersEntiers &Partition,
                               OrientedGraph *go,
                               UnorientedGraph *g,
                               OutputEdgeList &outputedgelist,
                               InputEdgeList &inputedgelist,
                               Connections &connections);

void List_edge_partie(Entiers *Partie, OrientedGraph *go, Edges &edge_partie,
                      OutputEdges &outputedgespartie);

void construire_graph(UnorientedGraph *g, OrientedGraph *graph);

double Modif_Cut_one_cluster(Entiers &cluster, UnorientedGraph &g, double &vol);

std::vector<double> modif_cut_tmp(UnorientedGraph *g, EntiersEntiers &Partition,
                             std::vector<std::vector<double> > tabe_cut,
                                  int vertexs,
                             int comm_in, Entiers community, double cut,
                             std::string name);

double Calcul_poids(Entiers *partie, UnorientedGraph *g);

bool Est_connexe(UnorientedGraph *g, EntiersEntiers Partition, Entiers &part);

void Affinage_equilibrage_charge(UnorientedGraph *g, EntiersEntiers &Partition);

Entiers Neigh_community(UnorientedGraph *g, EntiersEntiers &Partition,
                        int vertex, int comm_in);

void Modif_fonction_Gain_Cut(EntiersEntiers &Partition,UnorientedGraph *g,
                             Entiers &community, int val, double &cut,
                             std::string name);

void Affinage_recherche_locale(UnorientedGraph *g, EntiersEntiers &Partition,
                               double &cut, std::string name);

void projection(EntiersEntiers &Partition,ListEntiersEntiers::iterator lit);

bool contraction_HEM(UnorientedGraph *g, Base_Graph &baseg,
                     ListEntiersEntiers &liste_corr, int val_reduc,
                     int &val_cpt);
bool contraction_Random_Maching(UnorientedGraph *g, Base_Graph &baseg,
                                ListEntiersEntiers &liste_corr, int val_reduc,
                                int &val_cpt);

Entiers Liste_adjacence(UnorientedGraph &g, int vertexs,
                        const Entiers &random_vertices);

int rand_fini(int a, int b);
int recherche_val2(const std::vector<float> &tab,float val);
int recherche_val_double(const std::vector<double> &tab,double val);
int recherche_val(const std::vector<int> &tab,int val);
int dichotomie(const Entiers &tab,int i);
void suprim_val(Entiers &tab,int i);
bool In_tab(const Entiers &tab, int val);
bool In_tab_dichotomie(const Entiers &tab, int val);
double Cut_cluster(const EntiersEntiers &tab_cluster,UnorientedGraph &g,
                   std::string name);
void Modif_fonction_Gain_Cut(EntiersEntiers &Partition,UnorientedGraph *g,
                             int community_out,int community_in,int val,
                             double &cut);
void Liste_Voisin(const Entiers &P,Entiers &tab,const UnorientedGraph &g);
int Cout_coupe(Entiers P,int val, UnorientedGraph &g);
double Cout_coupe_pond(Entiers P,int val, UnorientedGraph &g);
int In_community_dichotomie(const EntiersEntiers &part, int val);
double Degree(UnorientedGraph &g , int node);
double Cluster_Degree(UnorientedGraph &g , const Entiers &cluster);

void make_unoriented_graph(const OrientedGraph& og, UnorientedGraph& uog);

void adjacence_ggp(int vertex, Entiers &sommets_adj, UnorientedGraph *g);

float modif_Cout_coupe(const Entiers &P, int val, float cut, UnorientedGraph *g);

} } } // namespace paradevs tests boost_graph

#endif
