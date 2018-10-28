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


#define __ROOT_PATH_ALLAN__ "d:\\projets ESGI\\Linter-C\\\0" // le chemin du dossier du projet chez Allan
#define __DEFAULT_CONFIG_PATH__ "resources\\lconfig\\default.lconf\0"
#define __DEFAULT_CONFIG_RELATIF_PATH__ "..\\resources\\lconfig\\default.lconf"

bool validArgument(Logger* logger, int argc, char** argv) ;

int main(int argc, char* argv[]) {

	Logger* logger = initialiseLogger() ;

	bool argumentIsValid = validArgument(logger, argc, argv) ;

	error(logger, "test") ;
	error(logger, "23652") ;
	error(logger, "test") ;

	/* Chemin absolue à éviter */
	  /*char* defaulConfigFileAbsolutePath = malloc(sizeof(char) * (strlen(__ROOT_PATH_ALLAN__) + strlen(__DEFAULT_CONFIG_PATH__) ));
		defaulConfigFileAbsolutePath = strcat(defaulConfigFileAbsolutePath,__ROOT_PATH_ALLAN__) ;
		defaulConfigFileAbsolutePath = strcat(defaulConfigFileAbsolutePath,__DEFAULT_CONFIG_PATH__) ;*/


	/* chemin relative */
	char defaulConfigFileRelatifPath[] = __DEFAULT_CONFIG_RELATIF_PATH__ ;

	/* mémorisation des configuration du linter */
	Linter* linter = readDefaultConfig( defaulConfigFileRelatifPath) ;
	if(linter->fileExtend != NULL) log(logger, linter->fileExtend) ;

  displayLinter(linter, stdout) ;

	/* Lancement du Linter */

	/* ecrire les erreurs et les logs dans les fichiers */

	/* Liberation des espaces mémoires alloués */
	freeLinterList(linter) ;

	closeLogger(logger) ;


	fflush(stdout) ;
	system("pause") ;
//	free(contentFile) ;
	return EXIT_SUCCESS;
}

bool validArgument(Logger* logger, int argc, char** argv){
	bool ret = true ;

	if(argc == 2 ){
		struct dirent *lecture;
    DIR* directory;
    directory = opendir(argv[1]);

		if(directory != NULL){
			while ((lecture = readdir(directory))) {
	        printf("%s\n", lecture->d_name);
	    }
		}else{
			error(logger, "le chemin du dossier donner en parametre n'est pas correct !!!") ;
			ret = false ;
		}
    closedir(directory);

	}else ret = false ;

	return ret ;
}
