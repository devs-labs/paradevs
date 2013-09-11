/*!
 * \file ContextFileReader.h
 * \brief Lecteur de fichier de type context.
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

#ifndef CONTEXTFILEREADER_H_
#define CONTEXTFILEREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "ContextData.h"
#include "XmlReader.h"
#include "Functions.h"

#define LINSIZE 1024

/*! \class ContextFileReader
 * \brief représente le lecteur de fichier de type context.
 *
 */

class ContextFileReader
{
public :

	/*!
	 *  \brief Lecture.
	 *
	 *  Lit le fichier des paramètres d'entrées.
	 *
	 *  \param docname : le nom du du document à lire et analyser.
	 *  \param numberDays : Durée en jours de la simulation.
	 *  \param simulationStartDate : Date du premier jour.
	 *  \param outletsCoordinates : Coordonnées exutoires.
	 *  \return EXIT_SUCCESS - Fin normal de la méthode.
	 */


	static int read(const char * docname,  ContextData::day_t & numberDays, ContextData::date_t & simulationStartDate, ContextData::mesh_chrono_t outletsCoordinates[])
	{
		xmlDocPtr doc_context = XmlReader::parseDoc(docname);

		/* Coordonnées exutoire */

		getOutletCoordinates(doc_context, outletsCoordinates);

		/* Durée en jours de la simulation */

		numberDays = XmlReader::getIntParamValue(doc_context,"duree_simulation");

		ContextData * ctxtD = ContextData::getInstance();

		/* Date du premier jour */
		simulationStartDate = getDate(((char *)XmlReader::getStringParamValue(doc_context,"debut-simulation")));

		ctxtD->_soilNumber = XmlReader::getIntParamValue(doc_context,"nb_sols");

		ctxtD->_soilFileName = (char*)XmlReader::getStringParamValue(doc_context,"file_sol_loc");

		ctxtD->_defaultNetworkSlope = XmlReader::getFloatParamValue(doc_context,"defaut_pente_reseau");

		ctxtD->_pptionAccess = XmlReader::getFloatParamValue(doc_context,"prop_acces_eau");

		xmlFreeDoc(doc_context);
		xmlCleanupParser();
		xmlMemoryDump();

		return EXIT_SUCCESS;
	}

	/*!
	 *  \brief Obtenir date.
	 *
	 *  Transforme une représentation chaînée d'une date en une structure date.
	 *
	 *  \param dateStr : représentation chaînée d'une date au format jj/mm/aaaa.
	 *  \return structure date avec un attribut pour le jour, le mois et l'année.
	 */

private :

	static ContextData::date_t getDate(char dateStr[11])
	{
		ContextData::date_t date;
		char c1,c2;

		if(sscanf(dateStr,"%2d%c%2d%c%4d", &date.day,&c1,&date.month,&c2,&date.year)!=5)
			printf("\n Erreur dans la lecture de date sur la chaine %s",dateStr);

		return date;
	}

	/*!
	 *  \brief Obtenir coordonnées exutoire.
	 *
	 *  Récupère les coordonnées de l'exutoire dans le document XML.
	 *
	 *  \param doc_context : document dans lequel se trouve l'information.
	 *  \param outletsCoordinates : structure dans laquelle les données trouvées seront sauvegardées.
	 *  \return void.
	 */

	static void getOutletCoordinates(xmlDocPtr doc_context, ContextData::mesh_chrono_t outletsCoordinates[])
	{
		xmlNodePtr cur_node = NULL;
		xmlChar *value_x;
		xmlChar *value_y;

		cur_node = XmlReader::findNodeWithTagAndAttrName(doc_context, "mesh", "exutoire");
		if (cur_node!=NULL)
		{
			value_x = xmlGetProp(cur_node,(const xmlChar*)"x-value");
			value_y = xmlGetProp(cur_node,(const xmlChar*)"y-value");
			outletsCoordinates[0].line= atoi((const char*) value_x );
			outletsCoordinates[0].column= atoi((const char*) value_y );
			xmlFree(value_x);
			xmlFree(value_y);
		}
		else
		{
			std::cerr <<"Error  : Outlet coordinate not defined\n";
			exit(0);
		}
	}
};

#endif /* CONTEXTFILEREADER_H_ */











/*---------------------------------------------------------------------------*/
/*  lecture_fichier_contexte :                                               */
/* Entree : nomfich                                               			 */
/*          fichier renfermant les parametres d'entrees                 	 */
/*---------------------------------------------------------------------------*/
/*void lecture_fichier_contexte (char *nomfich, jour_t & nbjours, struct_date_t & date_deb_simu, struct_maille_chrono_t TabMailles [])
{
    FILE *fpnomfich = NULL;
    char tbuf[LINSIZE];
    int afmsg;

 *tbuf = 0;

    if( !nomfich) {
        printf("\nVeuillez taper le nom du fichier contexte, puis appuyez sur ENTREE [CR/LF]");
        printf("\n ou appuyez sur ENTREE pour entrer les valeurs a partir du 'clavier'\n");

        putchar('?');

        fgets(tbuf, LINSIZE, stdin);  Demande le nom du fichier contexte
        putchar('\n');
        Util::ignorelf(tbuf);
         Si le nom du fichier contexte est donne
        if( tbuf[0]) {
            int i = -1;  determine sa longueur et
            while( tbuf[++i]) {}

            if((nomfich = (char *)malloc(i+1)) == NULL)
                Util::traiterreur(tbuf);
            else     --  copie-le dans la variable nomfich --
            {
                i = -1;
                while ((nomfich[++i] = tbuf[i]))
                {

                }

            }
        }
    }

     Si le nom de fichier contexte n'est pas donne
       ou si on a pas pu l'ouvrir,
       On lit les valeurs initiales au clavier [entree standard]

    afmsg = (nomfich == NULL) ? 1 : 0;

    if( ! afmsg) {
         Essaie d'ouvrir le fichier, en cas d'impossiblite dis pourquoi
        if( !(fpnomfich = fopen (nomfich,"r"))) {
        	Util::traiterreur(nomfich);
            afmsg = 1;
        }
    }

     Les param d'entree doivent etre donnes dans un fichier
     et ne peuvent plus etre lus au clavier
    if( !fpnomfich) {
        fpnomfich = stdin;
        printf("VOUS DEVEZ DONNER LE NOM DU FICHIER DES PARAMETRES D'ENTREE !!");
        exit(0);
    }

    //exutoire = NULL;

    appel de la fonction qui va lire le fichier des parametres d'entree

    read_context_file(nomfich, nbjours, date_deb_simu, TabMailles);


    fclose(fpnomfich);
}*/


