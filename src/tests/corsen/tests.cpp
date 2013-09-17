/**
 * @file tests/corsen/tests.cpp
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

#include "lib/Corsen.hpp"

/**
 * \fn void modifyFilesPath(string & absolutePath, vector<string *> & files)
 * \brief Modifie le chemin par défaut des fichiers.
 * \param absolutePath : chemin absolu ou sont stockés les fichiers
 * \param files : tableau contenant les chemins vers les fichiers .
 */

void modifyFilesPath(std::string& absolutePath,
                     std::vector < std::string* >& files)
{
    for (std::vector < std::string* >::iterator it = files.begin();
        it != files.end(); it++) {
        (*it)->insert(0, absolutePath);
    }
}

int main(int argc, char** argv)
{
    bool defaultFilePath = true;
    std::string absolutePath("");
    std::string modeFile(".mode"), parametersFile("par.txt"),
        elevationFile("alt"), outletFile("arbre"), layersFile("couche"),
        contextFile("contexte_agro_prairie.xml") ,slopeFile("pav");
    std::vector<std::string *> files;

    files.push_back(&parametersFile);
    files.push_back(&modeFile);
    files.push_back(&elevationFile);
    files.push_back(&outletFile);
    files.push_back(&slopeFile);
    files.push_back(&contextFile);
    files.push_back(&layersFile);

    /* Lecture des paramètres en ligne de commande */
    if(argc > 1) {
        int i = 1;
        char* option;

        while (i < argc) {
            option = argv[i++];
            if (strcmp(option,"-h") == 0) {
                std::cerr << "Utilisation : " << argv[0]
                          << "[-h] [-a absolute path]" << std::endl;
                std::cerr << " -a : chemin absolu" << std::endl;
                std::cerr << " -c : nom du fichier xml" << std::endl;
                std::cerr << " -h : cette aide" << std::endl;
                exit(0);
            } else if (strcmp(option, "-a") == 0) {
                if (i == argc) {
                    std::cerr << "il manque le chemin absolu" << std::endl;
                    exit(0);
                }
                defaultFilePath = false;
                absolutePath.append(argv[i++]);
                if(absolutePath.c_str()[absolutePath.size()- 1] != '/') {
                    absolutePath+="/";
                }
                modifyFilesPath(absolutePath,files);
            } else if  (strcmp(option,"-c")==0) {
                if (i == argc) {
                    std::cerr << "il manque le nom du fichier xml" << std::endl;
                    exit(0);
                }
                contextFile.clear();
                contextFile.append(argv[i++]);
                std::vector<std::string *>context;
                context.push_back(&contextFile);
                modifyFilesPath(absolutePath,context);
            } else {
                std::cerr << "Option non reconnue essayez -h" << std::endl;
                exit(0);
            }
        }
    }

    try {
        if(defaultFilePath) {
            std::string defaultFilePathStr("data/");
            modifyFilesPath(defaultFilePathStr,files);
        }
        Corsen c;
        c.read(files, absolutePath);
        c.buildGraph();
        c.display();
    } catch(std::exception & e) {
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}
