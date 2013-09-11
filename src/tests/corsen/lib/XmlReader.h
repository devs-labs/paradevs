/*!
 * \file XmlReader.h
 * \brief Lecteur XML de base
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

#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <string>
#include <sstream>

/*! \class XmlReader
 *
 * \brief permet d'analyser un fichier XML
 *
 */


class XmlReader
{
public :

	static xmlNodePtr findNodeWithTagAttributAndAttrValue(xmlDocPtr doc, const char* tagName, const char* attributeName, const char* attributeValue)
	{
		xmlNodePtr cur = NULL;
		//xmlChar *name;
		std::string name;

		cur = xmlDocGetRootElement(doc);

		if (cur == NULL) {
			fprintf(stderr,"Empty document\n");
			xmlFreeDoc(doc);
			exit(EXIT_FAILURE);
		}

		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrcmp(cur->name, (const xmlChar *)tagName))) {
				if (getAttributeAndTest(cur,attributeName,attributeValue)) {
					break;
				}
			}
			cur = cur->next;
		}

		if (cur==NULL) {
			fprintf(stderr,"\n Tag name %s with attribute %s=%s is not defined\n ",tagName, attributeName,attributeValue);
			exit(EXIT_FAILURE);
		}
		return cur;

	}

	/*!
	 *  \brief trouver un noeud
	 *
	 *  Méthode qui permet de trouver un noeud avec le nom d'une balise  et le nom d'un attribut.
	 *
	 *  \param doc : le document dans lequel chercher.
	 *  \param tagName : le nom de la balise .
	 *  \param attributeName : le nom de l'attribut.
	 *  \return un pointeur sur le noeud.
	 */

	static xmlNodePtr findNodeWithTagAndAttrName(xmlDocPtr doc, const char* tagName, const char* attributeName)
	{
		xmlNodePtr cur =NULL;
		cur = findNode(doc,tagName,attributeName);

		if (cur==NULL) {
			fprintf(stderr,"\n Tag name %s with attribute %s is not defined\n ",tagName, attributeName);
			//exit(EXIT_FAILURE);
		}
		return cur;

	}
	/*!
	 *  \brief trouver valeur d'un attribut à partir du document.
	 *
	 *  Méthode qui permet de trouver la valeur d'un attribut avec le nom d'un attribut.
	 *
	 *  \param paramName : nom de l'attribut. On considère qu'il n'y a pas de doublons.
	 *  \param doc : le document dans lequel chercher.
	 *  \return la valeur de l'attribut sous forme de chaîne de caractères, NULL sinon
	 */

	static xmlChar* getStringParamValue(xmlDocPtr doc, const char* paramName)
	{
		xmlChar *value;

		value = getParamValue(doc,paramName);
		if (value==NULL) {
			fprintf(stderr,"Value of parameter %s is not defined",paramName);
			exit(EXIT_FAILURE);
		} else {
			return value;
		}
	}


	/*!
	 *  \brief trouver valeur d'un attribut à partir d'un noeud du document.
	 *
	 *  Méthode qui permet de trouver la valeur d'un attribut avec le nom d'un attribut.
	 *
	 *
	 *  \param paramName : nom de l'attribut. On considère qu'il n'y a pas de doublons.
	 *  \param node : le noeud dans lequel chercher.
	 *  \return la valeur de l'attribut sous forme de chaîne de caractères, NULL sinon
	 */


	static xmlChar* getStringParamValueFromNode(xmlNodePtr node, const char* paramName)
	{
		xmlChar *value;

		value = getParamValueFromNode(node,paramName);
		if (value==NULL) {
			fprintf(stderr,"Value of parameter %s is not defined",paramName);
			exit(EXIT_FAILURE);
		} else {
			return value;
		}

	}

	/*!
	 *  \brief trouver valeur d'un attribut à partir du document.
	 *
	 *  Méthode qui permet de trouver la valeur d'un attribut avec le nom d'un attribut.
	 *
	 *
	 *  \param paramName : nom de l'attribut. On considère qu'il n'y a pas de doublons.
	 *  \param doc : le document dans lequel chercher.
	 *  \return la valeur de l'attribut sous forme de réel, NULL sinon
	 */

	static float getFloatParamValue(xmlDocPtr doc, const char* paramName)
	{
		xmlChar *value;
		float valueFloat;
		value = getParamValue(doc,paramName);
		if (value==NULL) {
			fprintf(stderr,"Value of parameter %s is not defined",paramName);
			exit(EXIT_FAILURE);
		} else {
			std::istringstream stringValue((char *) value);
			stringValue>>valueFloat;
			return valueFloat;
		}

	}

	/*!
	 *  \brief trouver valeur d'un attribut à partir d'un noeud du document.
	 *
	 *  Méthode qui permet de trouver la valeur d'un attribut avec le nom d'un attribut.
	 *
	 *
	 *  \param paramName : nom de l'attribut. On considère qu'il n'y a pas de doublons.
	 *  \param node : le noeud dans lequel chercher.
	 *  \return la valeur de l'attribut sous la forme d'un réel, NULL sinon
	 */


	static float getFloatParamValueFromNode(xmlNodePtr node, const char* paramName)
	{
		xmlChar *value;
		float valueFloat;

		value = getParamValueFromNode(node,paramName);
		if (value==NULL) {
			fprintf(stderr,"Value of parameter %s is not defined",paramName);
			exit(EXIT_FAILURE);
		} else {
			std::istringstream stringValue((char *) value);
			stringValue>>valueFloat;
			return valueFloat;
		}

	}

	/*!
	 *  \brief trouver valeur d'un attribut à partir du document.
	 *
	 *  Méthode qui permet de trouver la valeur d'un attribut avec le nom d'un attribut.
	 *
	 *
	 *  \param paramName : nom de l'attribut. On considère qu'il n'y a pas de doublons.
	 *  \param doc : le document dans lequel chercher.
	 *  \return la valeur de l'attribut sous la forme d'un entier, NULL sinon
	 */

	static int getIntParamValue(xmlDocPtr doc, const char* paramName)
	{
		xmlChar *value;
		int intValue;

		value = getParamValue(doc,paramName);
		if (value==NULL) {
			//fprintf(stderr,"Value of parameter %s is not defined\n",paramName);
			return 0;
		} else {
			std::istringstream stringValue((char *) value);
			stringValue>>intValue;
			return intValue;
		}

	}

	static xmlChar *getParamValue(xmlDocPtr doc, const char* paramName)
	{
		xmlNodePtr cur;

		cur = xmlDocGetRootElement(doc);

		if (cur == NULL) {
			fprintf(stderr,"Empty document\n");
			xmlFreeDoc(doc);
			exit(EXIT_FAILURE);
		}

		if (xmlStrcmp(cur->name, (const xmlChar *) "context")) {
			fprintf(stderr,"Document of the wrong type, root node != context");
			xmlFreeDoc(doc);
			exit(EXIT_FAILURE);
		}
		return getParamValueFromNode(cur,paramName);


	}

	static xmlDocPtr parseDoc(const char *docname)
	{
		xmlDocPtr xmlDoc = xmlParseFile(docname);

		/* Lecture et analyse du document XML contenu dans docname */
		if (xmlDoc == NULL) {
			fprintf(stderr,"Document %s not parsed successfully. \n",docname);
			exit(EXIT_FAILURE);
		}
		return xmlDoc;
	}

	static std::string getAttribute(xmlNodePtr cur, const char* attr)
	{
		const xmlChar* attrName = (const xmlChar *)attr;
		xmlChar* prop = xmlGetProp(cur, attrName);
		std::string s((const char*)prop);
		xmlFree(prop);
		return s;

	}

	static bool getAttributeAndTest(xmlNodePtr cur, const char* attr, const char* attrValue)
	{
		bool isGoodAttr = false;
		const xmlChar* attrName = (const xmlChar *)attr;
		xmlChar* prop = xmlGetProp(cur, attrName);

		if (prop != NULL) {
			std::string s((const char*)prop);

			if (s.compare(attrValue)==0) {
				isGoodAttr = true;
			}
			xmlFree(prop);
		}
		return isGoodAttr;

	}

private :

	static xmlNodePtr findNode(xmlDocPtr doc, const char* tagName, const char* attributeName)
	{
		xmlNodePtr cur = NULL;

		cur = xmlDocGetRootElement(doc);

		if (cur == NULL) {
			fprintf(stderr,"Empty document\n");
			xmlFreeDoc(doc);
			exit(EXIT_FAILURE);
		}

		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrcmp(cur->name, (const xmlChar *)tagName))) {
				//name = (xmlChar *)xmlGetProp(cur, ( const xmlChar* )"name");
				if (getAttributeAndTest(cur,"name",attributeName)) {
					break;
				}
			}
			cur = cur->next;
		}

		if (cur==NULL) {
			fprintf(stderr,"\n Tag name %s with attribute %s is not defined\n ",tagName, attributeName);
			//exit(EXIT_FAILURE);
		}

		return cur;
	}


	static xmlChar *getParamValueFromNode(xmlNodePtr cur, const char* paramName)
	{
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"param"))) {
				if (getAttributeAndTest(cur, "name", paramName)) {
					//printf("%s \n",getAttribute(cur,"value").c_str());
					return (xmlChar *)(getAttribute(cur,"value").c_str());
				}
			}
			cur = cur->next;
		}
		return NULL;
	}
};

#endif /* XMLREADER_H_ */
