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
#include "headers/logger.h"
#include "headers/argument.h"
#include "headers/structure.h"

// #define __ROOT_PATH_ALLAN__ "d:\\projets ESGI\\Linter-C\\"
// #define __DEFAULT_CONFIG_PATH__ "resources\\lconfig\\default.lconf.."
#define __DEFAULT_CONFIG_RELATIF_PATH__ "../resources/lconfig/default.lconf"


// void lancementProgramme() ;



int main(int argc, char* argv[]) {
  char defaulConfigFileRelatifPath[] = __DEFAULT_CONFIG_RELATIF_PATH__ ;
  ConfigLinter* linterConfig = memorizeConfig( defaulConfigFileRelatifPath) ;
  system("pause") ;
  return (EXIT_SUCCESS);
}


// void lancementProgramme(int argc, char** argv ){
// 	Logger* logger = initialiseLogger() ;
//
//   /* on vérifie les arguments en entré du main */
// 	bool argumentIsValid = validArgument(logger, argc, argv) ;
//
// 	/* chemin relative du fichier de configuration à mémorisé*/
// 	char defaulConfigFileRelatifPath[] = __DEFAULT_CONFIG_RELATIF_PATH__ ;
//
// 	/* mémorisation des configuration du linter */
// 	Linter* linter = memorizeConfig( defaulConfigFileRelatifPath) ;
//
//   /* affichage des configurations du linter */
//   displayLinter(linter, stdout) ;
//
// 	/* Lancement du Linter */
//
// 	/* Liberation des espaces mémoires alloués */
// 	freeLinterList(linter) ;
//
// 	closeLogger(logger) ;
//
//
// 	fflush(stdout) ;
// 	system("pause") ;
// }
