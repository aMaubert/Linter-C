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

void startLinter(int argc, char** argv) ;
void linting(ConfigLinter* linterConfig, char* pathDirectory) ;

int main(int argc, char* argv[]) {
  startLinter(argc, argv) ;

  return (EXIT_SUCCESS);
}

void startLinter(int argc, char** argv){

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

  linterConfig = loadLinterConfiguration(pathDirectory) ;


  displayLinterConfig(linterConfig) ;
  system("pause") ;
  fflush(NULL) ;

  linting(linterConfig, pathDirectory) ;

  freeConfigLinter(linterConfig) ;
}


void linting(ConfigLinter* linterConfig, char* pathDirectory){
  int countSourcesFiles ;
  char** listSourceFiles = getListSourceFiles(pathDirectory, &countSourcesFiles);

  printf("listSourceFiles : \n") ;
  for(int i = 0 ; i < countSourcesFiles; i++){
    printf("%s\n", listSourceFiles[i]) ;
  }

  // liberation de la memoire allouée
  for(int i = 0 ; i < countSourcesFiles; i++) free(listSourceFiles[i]) ;
  free(listSourceFiles) ;
}
