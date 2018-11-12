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
#include "structure.h"



ConfigLinter* memorizeConfig( char* pathFile) ;
// void readLineConfig(char* pathFile, int *etape, char* line, char* configFilesExtend, bool* fileExtendExist,
// 		 int* nbRules, char* allRules, int* nbExcludedFiles, char* allExcludedFiles,
// 		 bool* recursive) ;
//
// char** stringSplit(char* toSplit, char caractere, int *nbWords) ;
//
// Linter* initialiseStructLinter(int nbRules, char** rules, int nbExcludedFiles,
//         char** excludedFiles, bool recursive, char* fileExtend) ;
// void freeLinterList(Linter* linter) ;
// void freeLinter(Linter* toDestroy) ;
// void displayLinter(Linter* linter, FILE* output) ;
//
// char* str_replace(const char* stringToReplace, const char *str_regex, const char* expressionToAdd) ;



#endif /* CONFIGURATION_HEADER_CONFIG_H_ */
