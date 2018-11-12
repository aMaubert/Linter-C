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
void initialiseConfigLinter(ConfigLinter* linterConfiguration){
  linterConfiguration->fileExtend = NULL ;
  linterConfiguration->countRules = 0 ;
  linterConfiguration->listRules = NULL ;
  linterConfiguration->countExcludedFiles = 0 ;
  linterConfiguration->listExcludedFiles = NULL ;
  linterConfiguration->recursive = 1 ;
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


void setFileExtend(ConfigLinter* linterConfiguration, char* fileExtend){

  linterConfiguration->fileExtend = malloc(sizeof(char) * strlen(fileExtend)) ;
  if(linterConfiguration->fileExtend != NULL) strcpy(linterConfiguration->fileExtend, fileExtend) ;
  else{
    fprintf(stderr, "probleme allocation linterConfiguration->fileExtend .\ndans : %s   ligne : %d\n", __FILE__, __LINE__);
    system("pause") ;
    exit(EXIT_FAILURE) ;
  }
}
void setListRules(ConfigLinter* linterConfiguration, int countRules, char** listKey, char** listValue){
  /* Dans le cas où dans linterConfiguration->listRules il n'y a rien */
  if(linterConfiguration->listRules == NULL){
    linterConfiguration->listRules = malloc(sizeof(RuleLinter*) * countRules) ;
    if(linterConfiguration->listRules != NULL){
      //printf("linterConfiguration->listRules alloue\n") ;
      for(int i = 0 ; i < countRules; i++){
        linterConfiguration->listRules[i] = malloc(sizeof(RuleLinter)) ;
        if(linterConfiguration->listRules[i] != NULL){
          linterConfiguration->listRules[i]->key = malloc(sizeof(char) * strlen(listKey[i])) ;
          linterConfiguration->listRules[i]->value = malloc(sizeof(char) * strlen(listValue[i])) ;
          if( (linterConfiguration->listRules[i]->key == NULL) || (linterConfiguration->listRules[i]->value == NULL) ){
            fprintf(stderr, "probleme allocation linterConfiguration->listRules[%d]->key ou linterConfiguration->listRules[%d]->value \ndans : %s   ligne : %d\n", i, i, __FILE__, __LINE__);
            system("pause") ;
            exit(EXIT_FAILURE) ;
          }
        }
        else{
          fprintf(stderr, "probleme allocation listRules[%d] \ndans : %s   ligne : %d\n", i, __FILE__, __LINE__);
          system("pause") ;
          exit(EXIT_FAILURE) ;
        }
      }
      // Affectation
      for(int i = 0 ; i < countRules; i++){
        strcpy(linterConfiguration->listRules[i]->key, listKey[i]) ;
        strcpy(linterConfiguration->listRules[i]->value, listValue[i]) ;
      }
      linterConfiguration->countRules = countRules ;
    }
    else{
      fprintf(stderr, "probleme allocation listRules dans : %s   ligne : %d\n", __FILE__, __LINE__);
      system("pause") ;
      exit(EXIT_FAILURE) ;
    }
  }
}

void setRecursive(ConfigLinter* linterConfiguration, short recursive){
  if(recursive == 0 || recursive == 1){
    linterConfiguration->recursive = recursive ;
  }
  else{
    fprintf(stderr, "mauvaise valeur de recursive : %u dans : %s   ligne : %d\n", recursive, __FILE__, __LINE__);
    exit(EXIT_FAILURE) ;
  }
}

void setListExcludedFiles(ConfigLinter* linterConfiguration, int countExcludedFiles, char** listExcludedFiles){
  // dans le cas où il n'y a pas déja des chose dans la liste
  if(linterConfiguration->countExcludedFiles > 0){
    linterConfiguration->listExcludedFiles = malloc(sizeof(char*) * countExcludedFiles) ;
    if(linterConfiguration->listExcludedFiles != NULL){
      for(int i = 0 ; i < countExcludedFiles; i++){
        linterConfiguration->listExcludedFiles[i] = malloc(sizeof(listExcludedFiles[i])) ;
        if(linterConfiguration->listExcludedFiles[i] != NULL){
          strcpy(linterConfiguration->listExcludedFiles[i], listExcludedFiles[i]) ;
        }
        else{
          fprintf(stderr, "probleme allocation listExcludedFiles[i] dans : %s   ligne : %d\n", __FILE__, __LINE__);
          exit(EXIT_FAILURE) ;
        }
      }
      linterConfiguration->countExcludedFiles = countExcludedFiles ;
    }else{
      fprintf(stderr, "probleme allocation listExcludedFiles dans : %s   ligne : %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE) ;
    }
  }
  // dans le cas où il y a  déja des chose dans la liste
  else{
    fprintf(stderr, "cas où il y a  déja des chose dans listExcludedFiles dans : %s   ligne : %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE) ;
  }
}

RuleLinter* getRuleLinter(char* key, char* value){

  RuleLinter* ruleLinter = malloc(sizeof(RuleLinter)) ;

  if(ruleLinter != NULL){

    ruleLinter->key = malloc(sizeof(char) * strlen(key)) ;

    if(ruleLinter->key != NULL) strcpy(ruleLinter->key, key) ;
    else{
      fprintf(stderr, "probleme allocation ruleLinter->key dans : %s   ligne : %d\n", __FILE__, __LINE__);
      system("pause") ;
      exit(EXIT_FAILURE) ;
    }

    ruleLinter->value = malloc(sizeof(char) * strlen(value)) ;

    if(ruleLinter->value != NULL) strcpy(ruleLinter->value, value) ;
    else{
      fprintf(stderr, "probleme allocation ruleLinter->value dans : %s   ligne : %d\n", __FILE__, __LINE__);
      system("pause") ;
      exit(EXIT_FAILURE) ;
    }
  }else{
    fprintf(stderr, "probleme allocation ruleLinter dans : %s   ligne : %d\n", __FILE__, __LINE__);
    system("pause") ;
    exit(EXIT_FAILURE) ;
  }

  return ruleLinter ;
}

void copyRule(RuleLinter* ruleToModify, RuleLinter* ruleToCopy){
  printf("fonction copyRule\n") ;
  printf("ruleToModify : %s    ruleToCopy : %s\n", ruleToModify, ruleToCopy) ;
  system("pause") ;
  ruleToModify->key = malloc(sizeof(char) * strlen(ruleToCopy->key)) ;
  if(ruleToModify->key != NULL) strcpy(ruleToModify->key, ruleToCopy->key) ;
  else{
    fprintf(stderr, "probleme allocation ruleToModify->key\n dans : %s   ligne : %d\n", __FILE__, __LINE__);
    system("pause") ;
    exit(EXIT_FAILURE) ;
  }

  ruleToModify->value = malloc(sizeof(char) * strlen(ruleToCopy->value)) ;
  if(ruleToModify->value != NULL) strcpy(ruleToModify->value, ruleToCopy->value) ;
  else{
    fprintf(stderr, "probleme allocation ruleToModify->value \ndans : %s   ligne : %d\n", __FILE__, __LINE__);
    system("pause") ;
    exit(EXIT_FAILURE) ;
  }
}


void displayListRuleLinter(RuleLinter** listRuleLinter, int countRules){
  for(int i = 0 ; i < countRules ; i++){
    printf("key : %s   value : %s\n", listRuleLinter[i]->key, listRuleLinter[i]->value);
  }
}
void displayListExcludedFiles(char** listExcludedFiles, int countExcludedFiles){
  for(int i = 0 ; i < countExcludedFiles ; i++){
    printf("excludedFile : %s\n", listExcludedFiles[i]);
  }
}

void displayLinterConfig(ConfigLinter* linterConfig){
  if(linterConfig->fileExtend != NULL) printf("linterConfig->fileExtend : %s\n", linterConfig->fileExtend) ;
  displayListRuleLinter(linterConfig->listRules, linterConfig->countRules) ;
  displayListExcludedFiles(linterConfig->listExcludedFiles, linterConfig->countExcludedFiles) ;
  printf("recursive : %u\n", linterConfig->recursive) ;
}
