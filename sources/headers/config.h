/*
 * 	Name : Linter-C/sources/headers/config.h
 *  Created on: 2018/10/16
 *  Author: Allan Maubert
 */

#ifndef CONFIGURATION_HEADER_CONFIG_H_
#define CONFIGURATION_HEADER_CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 *  Structure qui permet de récupérer la configuration du linter
 *  qui sont activés, savoir si il y a des fichiers a exclure
 *  lors du scan du Linter et si le linter doit être récursive.
 *  Il y a un total de 16 règles, qui seront représenté par des
 *  valeurs booléennes true -> règle active, false -> non-active :
 *
 *  - array-bracket-eol = on        -------->  rules[0] = true
 *  - operators-spacing = off       -------->  rules[1] = false
 *  - comma-spacing = on            -------->  rules[2] = true
 *  - indent = on                   -------->  rules[3] = true
 *  - comments-header = on          -------->  rules[4] = true
 *  - max-line-numbers = off        -------->  rules[5] = false
 *  - max-file-line-numbers = on    -------->  rules[6] = true
 *  - no-trailing-spaces = off      -------->  rules[7] = false
 *  - no-multi-declaration = on     -------->  rules[8] = true
 *  - unused-variable = on          -------->  rules[9] = true
 *  - undeclared-variable = off     -------->  rules[10] = false
 *  - no-prototype = off            -------->  rules[11] = false
 *  - unused-function = on          -------->  rules[12] = true
 *  - undeclared-function = on      -------->  rules[13] = true
 *  - variable-assignment-type = on -------->  rules[14] = true
 *  - function-parameters-type = off-------->  rules[15] = false
 *
 */
typedef struct{
    Linter* extends ; //une liste chainé de Linter qui qui correspondra au nombre de fichier lconfig étendues
    bool *rules ; // contient la liste des règles true = activé, sinon false
    char** excludedFiles ; //Une liste de fichier du dossier courant qui ne sera pas affecter par ce Linter
    bool recursive ; // boolean qui indique si on lance le linter à la recherche des sous-fichiers si true, sinon false
    int nbExcludedFiles ;
}Linter ;



char* readDefaultConfig(const char* pathFile) ;
Linter* initialiseStructLinter(bool* rules, int nbExcludedFiles,char** excludedFiles, bool recursive) ;

#endif /* CONFIGURATION_HEADER_CONFIG_H_ */
