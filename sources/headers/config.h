/*
============================================================================
	Name        : config.h
	Author      : amaubert
	Created on  : 2018/10/16
	Version     :
	Copyright   : Your copyright notice
	Description : file that create the Linter's structure and the config.c functions
============================================================================
*/

#ifndef CONFIGURATION_HEADER_CONFIG_H_
#define CONFIGURATION_HEADER_CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Linter{
     //une liste chainé de Linter qui qui correspondra au nombre de fichier lconfig étendues

    char **rules ; // contient la liste des règles true = activé, sinon false
    int nbRules ;
    char** excludedFiles ; //Une liste de fichier du dossier courant qui ne sera pas affecter par ce Linter
    bool recursive ; // boolean qui indique si on lance le linter à la recherche des sous-fichiers si true, sinon false
    int nbExcludedFiles ;
    char* fileExtend ; // contient le chemin du fichier lconfig étendues
    struct Linter* extends ;
}Linter ;

Linter* readDefaultConfig(const char* pathFile) ;
void readLineConfig(int *etape, char* line, char* configFilesExtend, bool* fileExtendExist,
		 int* nbRules, char* allRules, int* nbExcludedFiles, char* allExcludedFiles,
		 bool* recursive) ;
char** stringSplit(char* toSplit, char caractere, int *nbWords) ;

Linter* initialiseStructLinter(int nbRules, char** rules, int nbExcludedFiles,
        char** excludedFiles, bool recursive, char* fileExtend) ;
void freeLinterList(Linter* linter) ;
void freeLinter(Linter* toDestroy) ;
void displayLinter(Linter* linter) ;

#endif /* CONFIGURATION_HEADER_CONFIG_H_ */
