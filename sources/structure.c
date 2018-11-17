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
  initialise a ConfigLinter structure
*/
ConfigLinter* getInitialisedConfigLinter(){
  ConfigLinter* linterConfiguration = malloc(sizeof(ConfigLinter)) ;
  linterConfiguration->fileExtend = NULL ;
  linterConfiguration->countRules = 0 ;
  linterConfiguration->countAllocateRules = 16 ;
  linterConfiguration->listRules = NULL ;
  linterConfiguration->countExcludedFiles = 0 ;
  linterConfiguration->countAllocateExcludedFiles = 10 ;
  linterConfiguration->listExcludedFiles = NULL ;
  linterConfiguration->recursive = 1 ;
  return linterConfiguration ;
}

ConfigLinter* getConfigLinter(ConfigLinter* linterConfiguration, char* fileExtend,
  int countRules, int countAllocateRules,char** listKey, char**listValue, int countExcludedFiles,
  int countAllocateExcludedFiles, char** listExcludedFiles, short recursive){

    short keyExist = 0 ;
    int index ;
    /* Allocation */

   linterConfiguration = realloc(linterConfiguration , sizeof(ConfigLinter)) ;

   if(fileExtend != NULL) linterConfiguration->fileExtend = realloc( linterConfiguration->fileExtend, sizeof(char) * strlen(fileExtend)) ;

   linterConfiguration->listRules = realloc( linterConfiguration->listRules , sizeof(RuleLinter*) * countAllocateRules) ;

   linterConfiguration->listExcludedFiles = realloc( linterConfiguration->listExcludedFiles, sizeof(char*) * countAllocateExcludedFiles) ;

   if(linterConfiguration == NULL){
     fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
     system("pause") ;
     exit(EXIT_FAILURE) ;
   }
   if(linterConfiguration->fileExtend == NULL && fileExtend != NULL){
     fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
     system("pause") ;
     exit(EXIT_FAILURE) ;
   }
   if(linterConfiguration->listRules == NULL){
     fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
     system("pause") ;
     exit(EXIT_FAILURE) ;
   }
   if(linterConfiguration->listExcludedFiles == NULL){
     fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
     system("pause") ;
     exit(EXIT_FAILURE) ;
   }


   index = 0 ;
  for(int i = linterConfiguration->countRules ; i < countRules; i++ ){
    keyExist = 0;

    for(int j = 0 ; j < linterConfiguration->countRules ; j++ ){
      if(strcmp(linterConfiguration->listRules[j]->key , listKey[index]) ){
        linterConfiguration->listRules[j]->value = realloc(linterConfiguration->listRules[j]->value, sizeof(char) * strlen(listKey[index]) ) ;
        index += 1 ;
        keyExist = 1;
      }
    }
    if(keyExist == 0){
      linterConfiguration->listRules[i] = malloc(sizeof(  RuleLinter)) ;
      linterConfiguration->listRules[i]->key = malloc(sizeof(char) * strlen(listKey[index]) ) ;
      linterConfiguration->listRules[i]->value = malloc(sizeof(char) * strlen(listValue[index]) ) ;
      index += 1 ;
    }
  }




   /* definition */
  if(fileExtend != NULL) strcpy(linterConfiguration->fileExtend , fileExtend) ;

   /* on défini d'abord ceux où la clé existe*/
   for(int i = 0 ; i < countRules ; i++){
     for(int j = 0 ; j < linterConfiguration->countRules ; j++ ){
       if( strcmp(linterConfiguration->listRules[j]->key, listKey[i]) == 0){
         strcpy(linterConfiguration->listRules[j]->value , listValue[i]) ;
         j = linterConfiguration->countRules ; // on sort de la 2eme boucle
       }
     }
   }

   /* enfin ceux dont la clé n'existe pas*/
   for(int i = 0 ; i < countRules ; i++){
     keyExist = 0 ;
     for(int j = 0 ; j < linterConfiguration->countRules ; j++ ){
       if( strcmp(linterConfiguration->listRules[j]->key, listKey[i]) == 0){
         keyExist = 1 ;
       }
     }

     if(keyExist == 0){

       index = linterConfiguration->countRules ;
       if(linterConfiguration->listRules[index] == NULL ||  linterConfiguration->listRules[index]->key == NULL ||
         linterConfiguration->listRules[index]->value == NULL){
         fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
         system("pause") ;
         exit(EXIT_FAILURE) ;
       }else{
         strcpy(linterConfiguration->listRules[index]->key, listKey[i]) ;
         strcpy(linterConfiguration->listRules[index]->value, listValue[i]) ;
         linterConfiguration->countRules += 1 ;
       }

     }
   }

   for(int i = 0 ; i < countExcludedFiles ; i++){
     keyExist = 0 ;
     for(int j = 0 ; j < linterConfiguration->countExcludedFiles ; j++){
       if(strcmp( linterConfiguration->listExcludedFiles[j], listExcludedFiles[i]) == 0){
         keyExist = 1 ;
       }
     }
     if(!keyExist){
       index = linterConfiguration->countExcludedFiles ;
       linterConfiguration->listExcludedFiles[index] = malloc(sizeof(char) * strlen(listExcludedFiles[i])) ;
       strcpy(linterConfiguration->listExcludedFiles[index], listExcludedFiles[i]) ;
       linterConfiguration->countExcludedFiles += 1 ;
     }
   }

   linterConfiguration->recursive = recursive ;

   linterConfiguration->countAllocateRules = countAllocateRules ;
   linterConfiguration->countAllocateExcludedFiles = countAllocateExcludedFiles ;
   if(linterConfiguration->countRules != countRules){
     fprintf(stderr, "ERROR - linterConfiguration->countRules != countRules soit %d != %d", linterConfiguration->countRules, countRules) ;
     system("pause") ;
     exit(EXIT_FAILURE) ;
   }
   if(linterConfiguration->countExcludedFiles != countExcludedFiles){
     fprintf(stderr, "ERROR - linterConfiguration->countExcludedFiles != countExcludedFiles soit %d != %d", linterConfiguration->countExcludedFiles, countExcludedFiles) ;
     system("pause") ;
     exit(EXIT_FAILURE) ;
   }

   return linterConfiguration ;
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


// void setFileExtend(ConfigLinter* linterConfiguration, char* fileExtend){
//
//   linterConfiguration->fileExtend = malloc(sizeof(char) * strlen(fileExtend)) ;
//   if(linterConfiguration->fileExtend != NULL) strcpy(linterConfiguration->fileExtend, fileExtend) ;
//   else{
//     fprintf(stderr, "probleme allocation linterConfiguration->fileExtend .\ndans : %s   ligne : %d\n", __FILE__, __LINE__);
//     system("pause") ;
//     exit(EXIT_FAILURE) ;
//   }
// }
// void setListRules(ConfigLinter* linterConfiguration, int countRules, char** listKey, char** listValue){
//   /* Dans le cas où dans linterConfiguration->listRules il n'y a rien */
//   int countRulesKeyExist = 0 ;
//   /* verification si des regles ont déjà une clée*/
//   if(linterConfiguration->countRules != 0){
//
//     for(int i = 0 ; i < countRules; i++){
//       if( strcmp( linterConfiguration->listRules[i]->key, listKey[i]) == 0  ) countRulesKeyExist += 1 ;
//     }
//     countRules = countRules - countRulesKeyExist ;
//   }
//   linterConfiguration->listRules = realloc(linterConfiguration->listRules, sizeof(RuleLinter*) * (linterConfiguration->countRules + countRules) ) ;
//   if(linterConfiguration->listRules != NULL){
//     if(linterConfiguration->countRules != 0) {
//       for(int i = linterConfiguration->countRules; i < (linterConfiguration->countRules + countRules) ; i++ ){
//         linterConfiguration->listRules[i] = malloc(sizeof(RuleLinter)) ;
//         if(linterConfiguration->listRules[i] == NULL){
//           fprintf(stderr, "probleme allocation linterConfiguration->listRules[i] .\ndans : %s   ligne : %d\n", __FILE__, __LINE__);
//           system("pause") ;
//           exit(EXIT_FAILURE) ;
//         }
//       }
//     }else{
//       for(int i = 0; i <  countRules ; i++ ){
//         linterConfiguration->listRules[i] = malloc(sizeof(RuleLinter)) ;
//         if(linterConfiguration->listRules[i] == NULL){
//           fprintf(stderr, "probleme allocation linterConfiguration->listRules[i] .\ndans : %s   ligne : %d\n", __FILE__, __LINE__);
//           system("pause") ;
//           exit(EXIT_FAILURE) ;
//         }
//       }
//     }
//   }else{
//     fprintf(stderr, "probleme allocation linterConfiguration->listRules .\ndans : %s   ligne : %d\n", __FILE__, __LINE__);
//     system("pause") ;
//     exit(EXIT_FAILURE) ;
//
//   }
//   // Affectation
//   if(linterConfiguration->countRules != 0){
//     short keyExist = 0 ;
//     int index = linterConfiguration->countRules ;
//     for(int i = 0 ; i < (countRules + countRulesKeyExist); i++){
//       keyExist = 0 ;
//       for(int j = 0 ; j < linterConfiguration->countRules ; j++){
//         if(strcmp(linterConfiguration->listRules[j]->key , listKey[i]) == 0 ){
//           strcpy(linterConfiguration->listRules[j]->value , listValue[i]) ;
//           keyExist = 1 ;
//         }
//       }
//       if(keyExist == 0){
//         strcpy(linterConfiguration->listRules[index]->key ,  listKey[i]) ;
//         strcpy(linterConfiguration->listRules[index]->value ,  listValue[i]) ;
//         index += 1;
//       }
//     }
//
//   }else{
//     for(int i = 0 ; i < countRules; i++){
//       strcpy(linterConfiguration->listRules[i]->key, listKey[i]) ;
//       strcpy(linterConfiguration->listRules[i]->value, listValue[i]) ;
//     }
//   }
//   linterConfiguration->countRules += countRules ;
// }
//
// void setRecursive(ConfigLinter* linterConfiguration, short recursive){
//   if(recursive == 0 || recursive == 1){
//     linterConfiguration->recursive = recursive ;
//   }
//   else{
//     fprintf(stderr, "mauvaise valeur de recursive : %u dans : %s   ligne : %d\n", recursive, __FILE__, __LINE__);
//     exit(EXIT_FAILURE) ;
//   }
// }
//
// void setListExcludedFiles(ConfigLinter* linterConfiguration, int countExcludedFiles, char** listExcludedFiles){
//   // dans le cas où il n'y a pas déja des chose dans la liste
//   if(linterConfiguration->countExcludedFiles > 0){
//     linterConfiguration->listExcludedFiles = malloc(sizeof(char*) * countExcludedFiles) ;
//     if(linterConfiguration->listExcludedFiles != NULL){
//       for(int i = 0 ; i < countExcludedFiles; i++){
//         linterConfiguration->listExcludedFiles[i] = malloc(sizeof(listExcludedFiles[i])) ;
//         if(linterConfiguration->listExcludedFiles[i] != NULL){
//           strcpy(linterConfiguration->listExcludedFiles[i], listExcludedFiles[i]) ;
//         }
//         else{
//           fprintf(stderr, "probleme allocation listExcludedFiles[i] dans : %s   ligne : %d\n", __FILE__, __LINE__);
//           exit(EXIT_FAILURE) ;
//         }
//       }
//       linterConfiguration->countExcludedFiles = countExcludedFiles ;
//     }else{
//       fprintf(stderr, "probleme allocation listExcludedFiles dans : %s   ligne : %d\n", __FILE__, __LINE__);
//       exit(EXIT_FAILURE) ;
//     }
//   }
//   // dans le cas où il y a  déja des chose dans la liste
//   else{
//     fprintf(stderr, "cas où il y a  déja des chose dans listExcludedFiles dans : %s   ligne : %d\n", __FILE__, __LINE__);
//     exit(EXIT_FAILURE) ;
//   }
// }
//
// RuleLinter* getRuleLinter(char* key, char* value){
//
//   RuleLinter* ruleLinter = malloc(sizeof(RuleLinter)) ;
//
//   if(ruleLinter != NULL){
//
//     ruleLinter->key = malloc(sizeof(char) * strlen(key)) ;
//
//     if(ruleLinter->key != NULL) strcpy(ruleLinter->key, key) ;
//     else{
//       fprintf(stderr, "probleme allocation ruleLinter->key dans : %s   ligne : %d\n", __FILE__, __LINE__);
//       system("pause") ;
//       exit(EXIT_FAILURE) ;
//     }
//
//     ruleLinter->value = malloc(sizeof(char) * strlen(value)) ;
//
//     if(ruleLinter->value != NULL) strcpy(ruleLinter->value, value) ;
//     else{
//       fprintf(stderr, "probleme allocation ruleLinter->value dans : %s   ligne : %d\n", __FILE__, __LINE__);
//       system("pause") ;
//       exit(EXIT_FAILURE) ;
//     }
//   }else{
//     fprintf(stderr, "probleme allocation ruleLinter dans : %s   ligne : %d\n", __FILE__, __LINE__);
//     system("pause") ;
//     exit(EXIT_FAILURE) ;
//   }
//
//   return ruleLinter ;
// }
//
// void copyRule(RuleLinter* ruleToModify, RuleLinter* ruleToCopy){
//   printf("fonction copyRule\n") ;
//   printf("ruleToModify : %s    ruleToCopy : %s\n", ruleToModify, ruleToCopy) ;
//   system("pause") ;
//   ruleToModify->key = malloc(sizeof(char) * strlen(ruleToCopy->key)) ;
//   if(ruleToModify->key != NULL) strcpy(ruleToModify->key, ruleToCopy->key) ;
//   else{
//     fprintf(stderr, "probleme allocation ruleToModify->key\n dans : %s   ligne : %d\n", __FILE__, __LINE__);
//     system("pause") ;
//     exit(EXIT_FAILURE) ;
//   }
//
//   ruleToModify->value = malloc(sizeof(char) * strlen(ruleToCopy->value)) ;
//   if(ruleToModify->value != NULL) strcpy(ruleToModify->value, ruleToCopy->value) ;
//   else{
//     fprintf(stderr, "probleme allocation ruleToModify->value \ndans : %s   ligne : %d\n", __FILE__, __LINE__);
//     system("pause") ;
//     exit(EXIT_FAILURE) ;
//   }
// }


void displayListRuleLinter(RuleLinter** listRuleLinter, int countRules){
  printf("\nliste des regles du linter :\n");
  for(int i = 0 ; i < countRules ; i++){
    printf("%s : %s\n", listRuleLinter[i]->key, listRuleLinter[i]->value);
  }
}
void displayListExcludedFiles(char** listExcludedFiles, int countExcludedFiles){
  printf("\nliste des fichier exclu du linter :\n") ;
  for(int i = 0 ; i < countExcludedFiles ; i++){
    printf("%s\n", listExcludedFiles[i]);
  }
}

void displayLinterConfig(ConfigLinter* linterConfig){
  printf("===============================================\n") ;
  printf("======      Configuration du Linter      ======\n\n") ;
  if(linterConfig->fileExtend != NULL) printf("fichier lconf etendue : %s\n", linterConfig->fileExtend) ;
  displayListRuleLinter(linterConfig->listRules, linterConfig->countRules) ;
  displayListExcludedFiles(linterConfig->listExcludedFiles, linterConfig->countExcludedFiles) ;
  printf("\nlinter recursive : %u\n", linterConfig->recursive) ;
}
