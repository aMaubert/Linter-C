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

char** listDefinedFunctions(char* pathFile, int* countFunctions){
  FILE* inputFile = fopen(pathFile, "r") ;
  char** listDefinedFunctions = NULL ;

  char line[512] ;
  char buffer[512] ;
  if(inputFile != NULL){



  }else{
    fprintf(stderr, "%s , ligne %d\nImpossible d'ouvrir le fichier %s  en lecture\n\n", __FILE__, __LINE__, pathFile);
    pause() ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }
  fclose(inputFile) ;

  return listDefinedFunctions ;
}

chort isAPrototypeFunction(char* line, char* name, char* type){
  char functionName[100] ;
  char functionType[100] ;
  char listParameters[100] ;
  int indexFunctionName = 0 ;
  int indexFunctionType = 0 ;
  int indexListParameters = 0 ;
  int index = 0 ;

  strcpy(functionName, "") ;
  strcpy( functionType, "") ;
  strcpy( listParameters, "") ;


  //on passe les espaces vides
  while(line[index] == " " || line[index] == "\t") index += 1 ;

  // On recupere le type (potentiellement)
  while( caracterAlphaNumeric(line[index]) ){
    functionType[indexFunctionType] = line[index] ;
    indexFunctionType += 1 ;
    index += 1 ;
  }

  functionType[indexFunctionType] = '\0' ;
  if(!isAPrimitivType(functionType)) return 0 ;

  //on passe les espaces vides
  while(line[index] == " " || line[index] == "\t") index += 1 ;

  // On recupere nom de la fonction potentiellement
  while( caracterAlphaNumeric(line[index]) ){
    functionName[indexFunctionName] = line[index] ;
    indexFunctionName += 1 ;
    index += 1 ;
  }

  if(line[index] != '(') return 0 ;

  //On passe les parametres
  while(line[index] != ")"){
    listParameters[indexListParameters] = line[index] ;
    indexListParameters += 1 ;
    index += 1 ;
  }

  // On verifie que le nom de fonction ne correspond pas une boucle ou une condition
  if(isALoopOrCondition(functionName)) return 0 ;








return 1 ;
}

short caracterAlphaNumeric(char c){
  if( (c > 'A' && c < 'Z') || (c > 'a' && c < 'z') || (c > '0' && c < '9') || c == "_"  ) return 1 ;
  else return 0 ;
}
/*
 * Return 1 if instruction is a condition or a boucle langage
 */
short isALoopOrCondition(char* instruction){
  char listToSkip[6][] = {"if",
                         "else",
                         "switch",
                         "for",
                         "do",
                         "while"} ;

  for(int i = 0 ; i < 6; i++){
    if(strcmp( instruction, listToSkip[i]) == 0) return 1 ;
  }
  return 0 ;
}

/*
 * Return 1 if instruction is a condition or a boucle langage
 */
short isAPrimitivType(char* type){
  char listPrimitiveTupe[7][] = { "void",
                                  "double",
                                  "int",
                                  "float",
                                  "short",
                                  "long",
                                  "char"} ;
for(int i = 0; i < 7; i++) if(strcmp(type, listPrimitiveTupe[i]) == 0) return 1 ;
return 0 ;
}
