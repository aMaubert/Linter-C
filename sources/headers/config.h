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

char* changePathExtendFile(char* path, char* fileExtendName) ;
ConfigLinter* memorizeConfig( char* pathFile, ConfigLinter* linterConfig) ;
ConfigLinter* loadLinterConfiguration(char* pathDirectory) ;



#endif /* CONFIGURATION_HEADER_CONFIG_H_ */
