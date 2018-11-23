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
#include "headers/directory.h"


#define __DEFAULT_CONF_FILE__ "D:/ESGI/projets pedagogique ESGI/Linter-C/resources/lconfig/default.lconf"



int main(int argc, char* argv[]) {

  ConfigLinter* linterConfig  = NULL;
  short argumentIsValid = validArgument(argc, argv) ;
  if(!argumentIsValid ){
    printf("Le linter doit avoir un chemin vers le dossier en parametre !!!\n\n") ;
    system("pause") ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }

  char* pathDirectory = NULL ;

  pathDirectory = malloc(sizeof(char) * (1 + strlen(argv[1]))) ;
  strcpy(pathDirectory , argv[1]) ;

  char* pathConfigFile = getConfigFile(pathDirectory) ;

  printf("pathConfigFile : %s\n", pathConfigFile) ;
  if(pathConfigFile != NULL) linterConfig = memorizeConfig( pathConfigFile , linterConfig) ;
  
  linterConfig = memorizeConfig( __DEFAULT_CONF_FILE__ , linterConfig) ;



  displayLinterConfig(linterConfig) ;
  system("pause") ;

  fflush(NULL) ;
  return (EXIT_SUCCESS);
}
