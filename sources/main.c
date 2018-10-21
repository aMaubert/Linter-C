/*
 ============================================================================
 Name        : main.c
 Author      : Allan Maubert
 date				 : 15/10/2018
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include "headers/config.h"

#define __ROOT_PATH_ALLAN__ "d:\\projets ESGI\\Linter-C\\\0" // le chemin du dossier du projet chez Allan
#define __DEFAULT_CONFIG_PATH__ "resources\\lconfig\\default.lconf\0"

#define __DEFAULT_CONIG_RELATIF_PATH__ "..\\resources\\lconfig\\default.lconf"

int main(void) {
	
	/* Chemin absolue à éviter */
  /*char* defaulConfigFileAbsolutePath = malloc(sizeof(char) * (strlen(__ROOT_PATH_ALLAN__) + strlen(__DEFAULT_CONFIG_PATH__) ));
	defaulConfigFileAbsolutePath = strcat(defaulConfigFileAbsolutePath,__ROOT_PATH_ALLAN__) ;
	defaulConfigFileAbsolutePath = strcat(defaulConfigFileAbsolutePath,__DEFAULT_CONFIG_PATH__) ;*/

	/* chemin relative */
	char defaulConfigFileRelatifPath[] = __DEFAULT_CONIG_RELATIF_PATH__ ;
	Linter* linter = readDefaultConfig( defaulConfigFileRelatifPath) ;
//	printf("contenu du fichier : %s\n%s\n\n",defaulConfigFileRelatifPath,contentFile);
  displayLinter(linter) ;
	freeLinterList(linter) ;
  //printf("defaulConfigFileRelatifPath : %s\n",defaulConfigFileRelatifPath) ;
	fflush(stdout) ;
	system("pause") ;
//	free(contentFile) ;
	return EXIT_SUCCESS;
}
