/*
 ============================================================================
 Name        : VariableAndFunctionRules.c
 Author      : Allan Maubert
 Created on	 : 2018/10/26
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/VariableAndFunctionRules.h"
#include "headers/interface.h"


void undeclaredVariableRule( Logger* logger, char* pathFile){
  FILE* inputFile = fopen( pathFile, "r") ;
  char line[512] ;
  if(inputFile != NULL){



  }else{
    fprintf(stderr, "%s , ligne %d\nImpossible d'ouvrir le fichier %s  en lecture\n\n", __FILE__, __LINE__, pathFile);
    pause() ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }
  fclose(inputFile) ;
}
