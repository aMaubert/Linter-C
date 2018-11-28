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



// void undeclaredVariableRule( Logger* logger, char* pathFile){
//   FILE* inputFile = fopen( pathFile, "r") ;
//   char line[512] ;
//   if(inputFile != NULL){
//
//
//
//   }else{
//     fprintf(stderr, "%s , ligne %d\nImpossible d'ouvrir le fichier %s  en lecture\n\n", __FILE__, __LINE__, pathFile);
//     pause() ;
//     fflush(NULL) ;
//     exit(EXIT_FAILURE) ;
//   }
//   fclose(inputFile) ;
// }

// char** listDefinedFunctions(FILE* inputFile, int* countFunctions){
//
//   char** listDefinedFunctions = NULL ;
//
//   char line[512] ;
//   char buffer[512] ;
//   if(inputFile != NULL){
//
//
//
//   }else{
//     fprintf(stderr, "%s , ligne %d\nImpossible d'ouvrir le fichier %s  en lecture\n\n", __FILE__, __LINE__, pathFile);
//     pause() ;
//     fflush(NULL) ;
//     exit(EXIT_FAILURE) ;
//   }
//   fclose(inputFile) ;
//
//   return listDefinedFunctions ;
// }

/*
 * Analys of line, if line is a prototype function then return a struct Function, else return NULL
 */
Function* isAPrototypeFunction(char* line){
  char functionName[100] ;
  char functionType[100] ;
  char listParameters[100] ;
  int indexFunctionName = 0 ;
  int indexFunctionType = 0 ;
  int indexListParameters = 0 ;
  int index = 0 ;

  strcpy( functionName, "") ;
  strcpy( functionType, "") ;
  strcpy( listParameters, "") ;


  //on passe les espaces vides
  skipVoidSpace(line, &index) ;

  // On recupere le type (potentiellement)
  while( caracterAlphaNumeric(line[index]) ){
    functionType[indexFunctionType] = line[index] ;
    indexFunctionType += 1 ;
    index += 1 ;
  }
  functionType[indexFunctionType] = '\0' ;



  if(!isAPrimitivType(functionType)){ // Si sa ne correspond pas a un type primitif

    while(isAKeyWord(functionType)) { // si c'est un mot clé du langage
      //on passe les espaces vides
      skipVoidSpace(line, &index) ;

      indexFunctionType = 0 ;
      // On recupere le type (potentiellement)
      while( caracterAlphaNumeric(line[index]) ){
        functionType[indexFunctionType] = line[index] ;
        indexFunctionType += 1 ;
        index += 1 ;
      }
    }

    if(!isAPrimitivType(functionType)){// ce n'est pas un type primitif
      return NULL ;
    }

    // les structures et enumerations ne seront pas gérer
  }

  //on passe les espaces vides
  skipVoidSpace(line, &index) ;


  // On recupere nom de la fonction potentiellement
  while( caracterAlphaNumeric(line[index]) ){
    functionName[indexFunctionName] = line[index] ;
    indexFunctionName += 1 ;
    index += 1 ;
  }
  functionName[indexFunctionName] = '\0' ;



  if(line[index] != '(') return NULL ; // Ici on va pouvoir faire la difference entre fonction et variable
  index += 1 ;

  // On verifie que le nom de fonction ne correspond pas une boucle ou une condition
  if(isALoopOrCondition(functionName)) return NULL;


  //On passe les parametres
  while(line[index] != ')'){
    listParameters[indexListParameters] = line[index] ;
    indexListParameters += 1 ;
    index += 1 ;
  }
  listParameters[indexListParameters] = '\0' ;
  index += 1 ; // on passe le caracter ')'




  //on passe les espaces vides
  skipVoidSpace(line, &index) ;


  if(line[index] != ';') return NULL;

  printf("Bravo c'est bien un prototype !!!\n") ;
  printf("%s %s(%s) ;\n", functionType, functionName, listParameters) ;

  return NULL ;
}

/*
 * Return a Fuction structur if the line is a declared function, else return NULL
 *
 */
Function* isADefinedFunction(char* line){
  char functionName[100] ;
  char functionType[100] ;
  char allParameters[100] ;
  int indexFunctionName = 0 ;
  int indexFunctionType = 0 ;
  int indexListParameters = 0 ;
  int index = 0 ;

  strcpy( functionName, "") ;
  strcpy( functionType, "") ;
  strcpy( allParameters, "") ;


  //on passe les espaces vides
  skipVoidSpace(line, &index) ;

  // On recupere le type (potentiellement)
  while( caracterAlphaNumeric(line[index]) ){
    functionType[indexFunctionType] = line[index] ;
    indexFunctionType += 1 ;
    index += 1 ;
  }
  functionType[indexFunctionType] = '\0' ;



  if(!isAPrimitivType(functionType)){ // Si sa ne correspond pas a un type primitif

    while(isAKeyWord(functionType)) { // si c'est un mot clé du langage
      //on passe les espaces vides
      skipVoidSpace(line, &index) ;

      indexFunctionType = 0 ;
      // On recupere le type (potentiellement)
      while( caracterAlphaNumeric(line[index]) ){
        functionType[indexFunctionType] = line[index] ;
        indexFunctionType += 1 ;
        index += 1 ;
      }
    }

    if(!isAPrimitivType(functionType)){ // ce n'est pas un type primitif
      return NULL ;
    }

    // Attention, les structures et enumerations ne seront pas gérer
  }

  //on passe les espaces vides
  skipVoidSpace(line, &index) ;


  // On recupere nom de la fonction potentiellement
  while( caracterAlphaNumeric(line[index]) ){
    functionName[indexFunctionName] = line[index] ;
    indexFunctionName += 1 ;
    index += 1 ;
  }
  functionName[indexFunctionName] = '\0' ;

  if(line[index] != '(') return NULL ; // Ici on va pouvoir faire la difference entre fonction et variable
  index += 1 ;

  // On verifie que le nom de fonction ne correspond pas une boucle ou une condition
  if(isALoopOrCondition(functionName)) return NULL;


  //On passe les parametres
  while(line[index] != ')'){
    allParameters[indexListParameters] = line[index] ;
    indexListParameters += 1 ;
    index += 1 ;
  }
  allParameters[indexListParameters] = '\0' ;
  index += 1 ; // on passe le caracter ')'

  //on passe les espaces vides
  skipVoidSpace(line, &index) ;


  if(line[index] == ';') return NULL;

  // Si il n'y a pas de ';', on suppose que c'est une definition de fonction

  printf("Bravo c'est bien un prototype !!!\n") ;
  printf("%s %s(%s) ;\n", functionType, functionName, allParameters) ;
  int countParameters ;
  char** listParameters = strSplit(allParameters, 'c', &countParameters) ;

  printf("la liste des parametres : \n") ;
  for(int i = 0 ; i < countParameters; i++) printf("%s\n", listParameters[i]) ;

  return NULL ;
}

/*
 * Return true if array is a keyWord of C langage
 */
bool isAKeyWord(char* array){
  if( strcmp(array, "const") == 0 ) return true ;
  return false ;
}
/*
 * Skip the void space to the right direction at the start of index
 */
void skipVoidSpace(char* line, int* index){
  //on passe les espaces vides
  while(line[*index] == ' ' || line[*index] == '\t') *index += 1 ;
}
bool caracterAlphaNumeric(char c){
  if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_'  ) return true ;
  else return false ;
}
/*
 * Return 1 if instruction is a condition or a boucle langage
 */
bool isALoopOrCondition(char* instruction){
  char* listToSkip[6] = {"if","else","switch","for","do","while"} ;

  for(int i = 0 ; i < 6; i++){
    if(strcmp( instruction, listToSkip[i]) == 0) return true ;
  }
  return false ;
}

/*
 * Return 1 if instruction is a condition or a boucle langage
 */
bool isAPrimitivType(char* type){
  char* listPrimitiveTupe[7] = { "void", "double", "int", "float", "short", "long", "char"} ;

  for(int i = 0; i < 7; i++) if(strcmp(type, listPrimitiveTupe[i]) == 0) return true ;
  return false ;
}
/*
 * Split array
 * Return a string List, each element is a match splitted in array with a separator
 */
char** strSplit(char* array, char separator, int* countMatchs){
  char** ret = NULL ;
  char tmp[512] ;
  int indexTmp = 0 ;

  *countMatchs = 0 ;
  strcpy(tmp, "") ;

  for(int i = 0 ; i < strlen(array)  ; i++){
    if(array[i] == separator){
      tmp[indexTmp] = '\0' ;
      printf("2 + indexTmp : %d\n", 2 + indexTmp) ;
      ret = realloc(ret, sizeof(char*) * *countMatchs  ) ;
      if( ret != NULL) ret[*countMatchs - 1] = malloc(sizeof(char) * (2 + indexTmp) ) ;
      if( ret == NULL || ret[*countMatchs - 1] == NULL){
        fprintf( stderr, "%s , ligne : %d\nProbleme allocation memoire \n\n", __FILE__, __LINE__) ;
        pause() ;
        fflush(NULL) ;
        exit(EXIT_FAILURE) ;
      }
      strcpy(ret[*countMatchs - 1] , tmp) ;
      indexTmp = 0 ;
      *countMatchs += 1 ;
    }
    else {
      tmp[indexTmp] = array[i] ;
      indexTmp += 1 ;
    }
  }

  return ret ;
}
