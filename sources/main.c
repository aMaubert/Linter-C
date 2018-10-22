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
#include "headers/config.h"

#define __ROOT_PATH_ALLAN__ "d:\\projets ESGI\\Linter-C\\\0" // le chemin du dossier du projet chez Allan
#define __DEFAULT_CONFIG_PATH__ "resources\\lconfig\\default.lconf\0"

#define __DEFAULT_CONFIG_RELATIF_PATH__ "..\\resources\\lconfig\\default.lconf"

int main(void) {

	/* Chemin absolue ()à éviter */
  /*char* defaulConfigFileAbsolutePath = malloc(sizeof(char) * (strlen(__ROOT_PATH_ALLAN__) + strlen(__DEFAULT_CONFIG_PATH__) ));
	defaulConfigFileAbsolutePath = strcat(defaulConfigFileAbsolutePath,__ROOT_PATH_ALLAN__) ;
	defaulConfigFileAbsolutePath = strcat(defaulConfigFileAbsolutePath,__DEFAULT_CONFIG_PATH__) ;*/

	/* chemin relative */
	char defaulConfigFileRelatifPath[] = __DEFAULT_CONFIG_RELATIF_PATH__ ;
	Linter* linter = readDefaultConfig( defaulConfigFileRelatifPath) ;
//	if(linter->fileExtend != NULL) printf("")

  displayLinter(linter) ;


	/* Lancement du Linter */







	freeLinterList(linter) ;
	fflush(stdout) ;
	system("pause") ;
//	free(contentFile) ;
	return EXIT_SUCCESS;
}
