/*
 ============================================================================
 Name        : main.c
 Author      : Allan Maubert
 Created on	 : 2018/10/15
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "headers/config.h"
#include "headers/logger.h"


#define __ROOT_PATH_ALLAN__ "d:\\projets ESGI\\Linter-C\\"
#define __DEFAULT_CONFIG_PATH__ "resources\\lconfig\\default.lconf.."
#define __DEFAULT_CONFIG_RELATIF_PATH__ "../resources/lconfig/default.lconf"

bool validArgument(Logger* logger, int argc, char** argv) ;
bool isDirectory(Logger* logger, char* path) ;
void lancementProgramme() ;

int main(int argc, char* argv[]) {

lancementProgramme( argc, argv ) ;
   return (EXIT_SUCCESS);
}
void lancementProgramme(int argc, char** argv ){
	Logger* logger = initialiseLogger() ;

	//bool argumentIsValid = validArgument(logger, argc, argv) ;

	/* chemin relative */
	char defaulConfigFileRelatifPath[] = __DEFAULT_CONFIG_RELATIF_PATH__ ;

	/* mémorisation des configuration du linter */
	Linter* linter = memorizeConfig( defaulConfigFileRelatifPath) ;


  displayLinter(linter, stdout) ;

	/* Lancement du Linter */

	/* Liberation des espaces mémoires alloués */
	freeLinterList(linter) ;

	closeLogger(logger) ;


	fflush(stdout) ;
	system("pause") ;
	//	free(contentFile) ;
}

bool validArgument(Logger* logger, int argc, char** argv){
	bool ret = true ;

	if(argc == 2 ){
		ret = isDirectory(logger, argv[1]) ;

	}else{
		error(logger, "ce programme n'accepte qu'un parametre, le chemin du dossier a linter") ;
		ret = false ;
	}

	return ret ;
}

bool isDirectory(Logger* logger, char* path){
	bool isDirectory = true ;
	struct dirent *lecture;
	DIR* directory;
	directory = opendir(path);

	if(directory == NULL){
		error(logger, "le chemin du dossier donner en parametre n'est pas correct !!!") ;
		isDirectory = false ;
	}
	closedir(directory);

	return isDirectory ;
}
