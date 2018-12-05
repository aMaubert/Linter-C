/*
============================================================================
	Name        : structure.c
	Author      : amaubert
	date				: 07/11/2018
	Version     :
	Copyright   : Your copyright notice
	Description : content the structure's functions
============================================================================
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/structure.h"

/*
 * return 1 if the currentFile is a file excluded, else return 0
 */
short isAnexcludedFile(ConfigLinter* linterConfig, char* currentFile){
  short ret = 0 ;
  for(int i = 0 ; i < linterConfig->countExcludedFiles; i++){
    if(strstr(currentFile, linterConfig->listExcludedFiles[i]) != NULL){
      ret = 1 ;
      i = linterConfig->countExcludedFiles ;
    }
  }
  return ret ;
}
/*
  initialise a ConfigLinter structure
*/
ConfigLinter* getInitialisedConfigLinter(){
  ConfigLinter* linterConfiguration = malloc(sizeof(ConfigLinter)) ;
  linterConfiguration->fileExtend = NULL ;
  linterConfiguration->countRules = 0 ;
  linterConfiguration->listRules = NULL ;
  linterConfiguration->countExcludedFiles = 0 ;
  linterConfiguration->listExcludedFiles = NULL ;
  linterConfiguration->recursive = 1 ;
  return linterConfiguration ;
}

ConfigLinter* getConfigLinter(ConfigLinter* linterConfiguration, char* fileExtend, int countRules,
   char** listKey, char**listValue, int countExcludedFiles, char** listExcludedFiles, short recursive){

    short keyExist = 0 ;
    int index ;
    char** listAlreadyExistedKey = NULL ;
    char** listValueOfAlreadyExistedKey = NULL ;
    int countReAllocateRules = 0 ;
    int countReallocateExcludedFiles = 0 ;

    /* Allocation */

      /* reallocation fileExtend */
      if(fileExtend != NULL) linterConfiguration->fileExtend = realloc( linterConfiguration->fileExtend, sizeof(char) * (strlen(fileExtend) + 1)) ;

      /* reallocation listRules */
      // on calcul le nombre de règles à réallouer
      int countRuleKeyNotAlreadyExist = getCountRulesNotAlreadyExisted(linterConfiguration, countRules, listKey) ;
      if(linterConfiguration->countRules != countRules){
        countReAllocateRules = linterConfiguration->countRules + countRuleKeyNotAlreadyExist ;
      }
      else countReAllocateRules = countRules ;

      reallocateListRules(linterConfiguration, countReAllocateRules, listKey, listValue, countRules ) ;


      /* RéAllocation listExcludedFiles */
      // on calcul le nombre de fichier a ajouté dans la liste
      int countExcludedFilesNotAlreadyExist = getCountExcludedFilesNotAlreadyExisted(linterConfiguration, countExcludedFiles, listExcludedFiles) ;
      if(linterConfiguration->countExcludedFiles != countExcludedFiles){
        countReallocateExcludedFiles = linterConfiguration->countExcludedFiles + countExcludedFilesNotAlreadyExist ;
      }
      else countReallocateExcludedFiles = countExcludedFiles ;

      reallocateListExcludedFiles(linterConfiguration, countReallocateExcludedFiles, listExcludedFiles,  countExcludedFiles) ;

   /* definition */
  if(fileExtend != NULL) strcpy(linterConfiguration->fileExtend , fileExtend) ;

  setListRules(linterConfiguration, listKey, listValue, countRules) ;

  setListExcludedFiles(linterConfiguration, listExcludedFiles, countExcludedFiles) ;


   linterConfiguration->recursive = recursive ;

   return linterConfiguration ;
 }
 /*
  * Set the list of Excluded Files
  */
void setListExcludedFiles(ConfigLinter* linterConfiguration, char** listExcludedFiles, int countExcludedFiles){
  int index ; // sert à ajouter au bonne emplacement un nouveau fichier dans la liste
  short keyExist ;// sert a verifier si un fichier exist déjà dans la liste du linterConfiguration
  for(int i = 0 ; i < countExcludedFiles ; i++){
    keyExist = 0 ;
    for(int j = 0 ; j < linterConfiguration->countExcludedFiles ; j++){
      if(strcmp( linterConfiguration->listExcludedFiles[j], listExcludedFiles[i]) == 0){
        keyExist = 1 ;
      }
    }
    if(!keyExist){
      index = linterConfiguration->countExcludedFiles ;
      linterConfiguration->listExcludedFiles[index] = malloc(sizeof(char) * (strlen(listExcludedFiles[i]) + 2) ) ;
      strcpy(linterConfiguration->listExcludedFiles[index], listExcludedFiles[i]) ;
      linterConfiguration->countExcludedFiles += 1 ;
    }
  }
}

/*
 * Set the list of rules
 */
void setListRules(ConfigLinter* linterConfiguration, char** listKey, char** listValue, int countRules){
  int index ; // sert à ajouter des éléments qui n'existent pas déjà dans la liste
  short keyExist ;// sert a verifier si une regle  exist déjà


  for(int i = 0 ; i < countRules ; i++){
   keyExist = 0 ;
   for(int j = 0 ; j < linterConfiguration->countRules ; j++ ){
     if( strcmp(linterConfiguration->listRules[j]->key, listKey[i]) == 0){
       keyExist = 1 ;
       j = linterConfiguration->countRules ; // on sort de la 2eme boucle
     }
   }
   if(keyExist == 0){// si la regle n'existe pas alors il faut l'ajouter à la fin de la liste
     index = linterConfiguration->countRules ;
     strcpy(linterConfiguration->listRules[index]->key, listKey[i]) ;
     strcpy(linterConfiguration->listRules[index]->value, listValue[i]) ;
     linterConfiguration->countRules += 1 ;
   }
  }
}



/*
 * Return the number of Rules in listKey that is Not exist in the linterConfiguration
 */
 int getCountRulesNotAlreadyExisted(ConfigLinter* linterConfiguration,int countRules, char** listKey){
   int count = 0 ;

   for(int i = 0 ; i < linterConfiguration->countRules; i++){
     for(int j = 0; j < countRules; j++){
       if( strcmp( linterConfiguration->listRules[i]->key, listKey[j]) == 0){
         count += 1 ;
       }
     }
   }
   return countRules - count ;
 }

 /*
  * Return the number of ExcludedFiles in listExcludedFiles that is Not exist in the linterConfiguration
  */
  int getCountExcludedFilesNotAlreadyExisted(ConfigLinter* linterConfiguration,int countExcludedFiles, char** listExcludedFiles){
    int count = 0 ;
    for(int i = 0 ; i < linterConfiguration->countExcludedFiles; i++){
      for(int j = 0; j < countExcludedFiles; j++){
        if( strcmp( linterConfiguration->listExcludedFiles[i], listExcludedFiles[j]) == 0){
          count += 1 ;
        }
      }
    }
    return countExcludedFiles - count ;
  }

 /*
  * Reallocate the rule's list
  */
short reallocateListRules(ConfigLinter* linterConfiguration, int countRulesToReallocate, char** listKey, char** listValue, int countRules ){
  int indexNewRule = linterConfiguration->countRules ;
  short keyExist ;
  /* ReAllocation de la liste : on alloue un pointeur qui pointera countRulesToReallocate éléments*/
  linterConfiguration->listRules = realloc( linterConfiguration->listRules , sizeof(RuleLinter*) * countRulesToReallocate) ;
  if(linterConfiguration->listRules == NULL){
    fprintf(stderr, "probleme Allocation dans %s  ligne %d\n countRulesToReallocate : %d\n", __FILE__, __LINE__, countRulesToReallocate) ;
    system("pause") ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }
  // on RéAlloue les string contenants les valeur à leur nouvelle taille
  //On Alloue toute les nouvelles règles
  for(int i = 0 ; i < countRules; i++){
    keyExist = 0 ;
    for(int j = 0 ; j < linterConfiguration->countRules; j++){
      if( strcmp(listKey[i] ,linterConfiguration->listRules[j]->key) == 0){
        keyExist =  1 ;
      }
    }
    if(keyExist == 0 ){
      linterConfiguration->listRules[indexNewRule] = malloc(sizeof(  RuleLinter)) ;
      linterConfiguration->listRules[indexNewRule]->key = malloc( sizeof(char) * (2 + strlen(listKey[i])) ) ;
      linterConfiguration->listRules[indexNewRule]->value = malloc( sizeof(char) * (2 + strlen(listValue[i])) ) ;

      if(linterConfiguration->listRules[indexNewRule] == NULL ||
         linterConfiguration->listRules[indexNewRule]->key == NULL ||
         linterConfiguration->listRules[indexNewRule]->value == NULL)
      {
        fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
        system("pause") ;
        fflush(NULL) ;
        exit(EXIT_FAILURE) ;
      }
      indexNewRule += 1 ;
    }
  }
  return 1 ; // Si qqchose se passe mal on sort du programme en erreur Fatal
}

/*
 * Reallocate the Excluded Files's list
 */
short reallocateListExcludedFiles(ConfigLinter* linterConfiguration, int countExcludedFilesToReallocate, char** listExcludedFiles,  int countExcludedFiles ){
  int j = 0 ;
  // On RéAlloue la liste en ajoutant l'espace pour les nouveaux fichiers a exclure
  linterConfiguration->listExcludedFiles = realloc(linterConfiguration->listExcludedFiles , sizeof(char*) * countExcludedFilesToReallocate) ;
  if(linterConfiguration->listExcludedFiles == NULL){
    fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
    system("pause") ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }
  for(int i = linterConfiguration->countExcludedFiles ; i < countExcludedFilesToReallocate; i++ ){
    linterConfiguration->listExcludedFiles[i] = malloc(sizeof(char) * (2 + strlen(listExcludedFiles[j]))) ;
    if(linterConfiguration->listExcludedFiles[i] == NULL){
      fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
      system("pause") ;
      fflush(NULL) ;
      exit(EXIT_FAILURE) ;
    }
    j += 1 ;
  }
  return 1 ;
}

/*
  free a ConfigLinter structure
*/
void freeConfigLinter(ConfigLinter* linterConfiguration){
  free(linterConfiguration->fileExtend) ;

  for(int i = 0 ; i < linterConfiguration->countRules; i++){
    freeRuleLinter(linterConfiguration->listRules[i]) ;
  }
  free(linterConfiguration->listRules) ;

  for(int i = 0 ; i < linterConfiguration->countExcludedFiles; i++){
    free(linterConfiguration->listExcludedFiles[i]) ;
  }
  free(linterConfiguration->listExcludedFiles) ;
  free(linterConfiguration) ;
}

/*
  free a RuleLinter structure
*/
void freeRuleLinter(RuleLinter* ruleLinter){
  free(ruleLinter->key) ;
  free(ruleLinter->value) ;
  free(ruleLinter) ;
}

void displayListRuleLinter(RuleLinter** listRuleLinter, int countRules){
  printf("\nliste des regles du linter (%d) :\n", countRules);
  for(int i = 0 ; i < countRules ; i++){
    printf("%s : %s\n", listRuleLinter[i]->key, listRuleLinter[i]->value);
  }
}
void displayListExcludedFiles(char** listExcludedFiles, int countExcludedFiles){
  printf("\nliste des fichier exclu du linter (%d) :\n", countExcludedFiles) ;
  for(int i = 0 ; i < countExcludedFiles ; i++){
    printf("%s\n", listExcludedFiles[i]);
  }
}

void displayLinterConfig(ConfigLinter* linterConfig){
  printf("===============================================\n") ;
  printf("======      Configuration du Linter      ======\n\n") ;
  if(linterConfig->fileExtend != NULL) printf("Dernier fichier lconf etendue : %s\n", linterConfig->fileExtend) ;
  displayListRuleLinter(linterConfig->listRules, linterConfig->countRules) ;
  displayListExcludedFiles(linterConfig->listExcludedFiles, linterConfig->countExcludedFiles) ;
  printf("\nlinter recursive : %u\n\n", linterConfig->recursive) ;
}
