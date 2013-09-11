/*!
 * \file Functions.cpp
 * \brief
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

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "Functions.h"

#define COMMENTC     '#'

char * programName;
char * workingDirectory;

void Functions::fatalError(const char* s, int erreurcode)
{
     fprintf( stderr,"Erreur fatale: %s > arret de %s\n", s?s:"", programName);

     /*  avant de retourner  dans le repertoire d'ou TNT est appele */
     if (workingDirectory)
          chdir(workingDirectory);
     exit(erreurcode);
}


//void Functions::handleError(const char* s)
//{
//     switch(errno) {
//     case 0:  /* il n'y a pas d'erreur,   */
//          fprintf(stderr,"%s: CECI NE DEVRAIT PAS ARRIVER il n'y a pas d'erreur!!\n",s?s:"");
//          break;
//
//     case EPERM:  /*non super" utilisateur */
//          fprintf( stderr,"%s: acces refuse: il faut etre Super Utilisateur pour ce faire!\n",s?s:"");
//          break;
//
//     case 	ENOENT:		/* No such file or directory	*/
//          fprintf( stderr," %s: Fichier/Repertoire inexistant\n", s?s:"");
//          break;
//
//     case 	ENOMEM:		/* No enough memory 	*/
//          fatalError("pas assez de memoire", errno);
//          break;
//
//     case 	ENXIO:	/* No such device or address */
//          fprintf( stderr,"%s: adresse/peripherique inexistant\n", s?s:"");
//          break;
//
//     case 	EAGAIN : /* Resource temporarily unavailable*/
//          fprintf( stderr,"%s: ressources momentanement indisponibles\n",s?s:"");
//          break;
//
//     case 	EACCES : /* Permission denied	*/
//          fprintf( stderr,"%s: acces refuse, vos droits sont limites\n", s?s:"");
//          break;
//
//     case 	EEXIST :  /* File exists	*/
//          fprintf( stderr,"%s : fichier/repertoire deja existant\n",s?s:"");
//          break;
//
//     case 	ENODEV : /* No such device	*/
//          fprintf( stderr,"%s: peripherique inexistant\n", s?s:"");
//          break;
//
//     case 	ENOTDIR: /* Not a directory	*/
//          fprintf( stderr,"%s: n'est pas un repertoire\n", s?s:"");
//          break;
//
//     case 	EISDIR : /* Is a directory	*/
//          fprintf( stderr,"%s: est un repertoire\n", s?s:"");
//          break;
//
//     case 	EINVAL : /* Invalid argument	*/
//          fprintf( stderr,"%s : valeur de l'argument passe  inacceptable\n",s?s:"");
//          break;
//
//     case 	ENOTTY : /* Inappropriate ioctl for device */
//          fprintf( stderr,"%s : fonction inadaptee pour ce peripherique\n",s?s:"");
//          break;
//
//     case 	EFBIG  : /* File too large	*/
//          fprintf( stderr,"%s : fichier trop grand\n",s?s:"");
//          break;
//
//     case 	ENOSPC : /* No space left on device	*/
//          fprintf( stderr,"%s: plus de place disponible sur le peripherique\n",s?s:"");
//          break;
//
//     case 	EROFS  : /* Read only file system	*/
//          fprintf( stderr,"%s : systeme de fichier monte en mode lecture seule\n",s?s:"");
//          break;
//
//     case 	EDOM   : /* Math arg out of domain of func*/
//          fprintf(stderr,"%s: argument hors du domaine de definition fonc. math\n",s?s:"");
//          break;
//
//     case 	ERANGE : /* Math result not representable*/
//          fprintf( stderr,"%s : resultat non significatif\n",s?s:"");
//          break;
//
//     case 	EOVERFLOW : /* vue too large to be stored in data type */
//          fprintf( stderr,"%s : Resultat hors gabarit, trop grand\n",s?s:"");
//          break;
//
//     default :
//          fprintf( stderr,"Une erreur non geree par %s est survenue. errno = %d\n",programName, errno);
//          break;
//     }
//}
//
//void Functions::ignorelf( char *s)
//{
//     char *p = s-1;
//
//     while(*++p && (*p != '\r' && *p != '\n')) {}
//     *p ='\0';
//}

//bool Functions::isComment(char *s)
//{
//     char *p = s;
//
//     ignorelf(s);   /* ignore le caractere fin-de-ligne LF ou CR*/
//     /* ignore les espaces d'en-tete */
//     while(*p and isspace(*p)) {
//          ++p;
//     }
//
//     return *p == COMMENTC or *p == '\0';
//}

//FILE* Functions::openFile(const char* nom, const char* mode)
//{
//     FILE * fp;
//
//     if ((fp = fopen (nom,mode)) == NULL) {
//          handleError(nom);
//          fatalError(nom, errno);
//     }
//     return(fp);
//}

//bool is_reseau(int lig, int col)
//{
//     return getmatbit(Mcouche[numero_couche_riviere], lig, col);
//}




