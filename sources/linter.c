/*
 ============================================================================
 Name        : linter.c
 Author      : Allan Maubert
 Created on	 : 2018/10/22
 Version     :
 Copyright   : Your copyright notice
 Description : file that contents all the Linter's functionalities
 ============================================================================
 */


 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "headers/linter.h"
 #include "headers/config.h"
 #include "headers/argument.h"
 #include "headers/directory.h"
 #include "headers/codingConventionRules.h"

/*
 * start the linter program
 */
void startLinter(int argc, char** argv){

  ConfigLinter* linterConfig  = NULL;
  short argumentIsValid = validArgument(argc, argv) ;
  if(!argumentIsValid ){
    fprintf(stderr, "Le linter doit avoir un chemin vers le dossier en parametre !!!\n\n") ;
    pause() ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }

  char* pathDirectory = NULL ;

  pathDirectory = malloc(sizeof(char) * (1 + strlen(argv[1]))) ;
  strcpy(pathDirectory , argv[1]) ;

  linterConfig = loadLinterConfiguration(pathDirectory) ;
  displayLinterConfig(linterConfig) ;
  pause() ;
  fflush(NULL) ;
  printf("\nAnalyse des fichiers en cours ...") ;
  linting(linterConfig, pathDirectory) ;
  printf("\nAnalyse terminer\n") ;
  pause() ;
  fflush(NULL) ;



  freeConfigLinter(linterConfig) ;
  free(pathDirectory) ;
}

/*
 * Start the analysis on the currentFile with the different rules activated
 */
void analyse( ConfigLinter* linterConfig, Logger* logger, char* currentFile){
 int ruleNumber ;
 FILE* inputFile = fopen( currentFile, "r") ;
 if(inputFile != NULL){
   for(int i = 0 ; i < linterConfig->countRules; i++){
     ruleNumber = getRuleNumber(linterConfig->listRules[i]->key) ; // On recupere l'identifiant de la regle correspondant
     switch(ruleNumber){
       case 0 :
          fprintf(stderr, "the rule : %s  doesn't exist anymore\n", linterConfig->listRules[i]->key) ;
          pause() ;
          fflush(NULL) ;
          exit(EXIT_FAILURE) ;
          break ;
       case 1 : //rule : array-bracket-eol
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            arrayBracketEolRule( logger, inputFile, currentFile) ;
          }
          break ;
       case 2 : //rule : operators-spacing
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            operatorsSpacingRule( logger,inputFile, currentFile) ;
          }
          break ;
       case 3 : //rule : comma-spacing
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : comma-spacing a faire\n") ;
          }
          break ;
       case 4 : //rule : indent
          if(strcmp(linterConfig->listRules[i]->value, "off") != 0 ){
            int indent = atoi(linterConfig->listRules[i]->value) ;
            if(indent == 0){
              fprintf(stderr, "mauvaise valeur de la regle %s : %s\n", linterConfig->listRules[i]->key, linterConfig->listRules[i]->value) ;
              pause() ;
              fflush(NULL) ;
              exit(EXIT_FAILURE) ;
            }else{
              indentRule( logger, inputFile, indent, currentFile) ;
            }

          }
          break ;
       case 5 : //rule : comments-header
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : comments-header a faire\n") ;
          }
          break ;
       case 6 : //rule : max-line-numbers
          if(strcmp(linterConfig->listRules[i]->value, "off") != 0 ){
            int maxLineNumbers = atoi(linterConfig->listRules[i]->value) ;
            if(maxLineNumbers == 0){
              fprintf(stderr, "mauvaise valeur de la regle %s : %s\n", linterConfig->listRules[i]->key, linterConfig->listRules[i]->value) ;
              pause() ;
              fflush(NULL) ;
              exit(EXIT_FAILURE) ;
            }else{
              maxLineNumbersRule( logger, inputFile, maxLineNumbers, currentFile) ;
            }

          }
          break ;
       case 7 : //rule : max-file-line-numbers
          if(strcmp(linterConfig->listRules[i]->value, "off") != 0 ){
            int maxFileLineNumbers = atoi(linterConfig->listRules[i]->value) ;
            if(maxFileLineNumbers == 0){
              fprintf(stderr, "mauvaise valeur de la regle %s : %s\n", linterConfig->listRules[i]->key, linterConfig->listRules[i]->value) ;
              pause() ;
              fflush(NULL) ;
              exit(EXIT_FAILURE) ;
            }else{
              maxFileLineNumbersRule( logger, inputFile, maxFileLineNumbers, currentFile) ;
            }
          }
          break ;
       case 8 : //rule : no-trailing-spaces
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : no-trailing-spaces a faire\n") ;
          }
          break ;
       case 9 : //rule : no-multi-declaration
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : no-multi-declaration a faire\n") ;
          }
          break ;
       case 10 : //rule : unused-variable
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : unused-variable a faire\n") ;
          }
          break ;
       case 11 : //rule : undeclared-variable
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : undeclared-variable a faire\n") ;
          }
              break ;
       case 12 : //rule : no-prototype
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : no-prototype a faire\n") ;
          }
          break ;
       case 13 : //rule : unused-function
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : unused-function a faire\n") ;
          }
          break ;
       case 14 : //rule : undeclared-function
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : undeclared-function a faire\n") ;
          }
          break ;
       case 15 : //rule : variable-assignment-type
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : variable-assignment-type a faire\n") ;
          }
          break ;
       case 16 : //rule : function-parameters-type
          if(strcmp(linterConfig->listRules[i]->value, "on") == 0 ){
            messageLog( logger, "regle : function-parameters-type a faire\n") ;
          }
          break ;
       default :
          fprintf(stderr, "%s , ligne : %d\nErreur Switch case regle\n\n", __FILE__, __LINE__) ;
          pause() ;
          fflush(NULL) ;
          exit(EXIT_FAILURE) ;
          break ;
     }
   }
 }
 else{
   fprintf(stderr, "%s , ligne%d\nLe fichier %s n'a pas pu etre ouvert en lecture\n\n", __FILE__, __LINE__, currentFile );
   pause() ;
   fflush(NULL) ;
   exit(EXIT_FAILURE) ;
 }

fclose(inputFile) ;
}

 /*
  * start the linter for the c source files in the current directory ( recursive, optionnal)
  */
void linting(ConfigLinter* linterConfig, char* pathDirectory){
  int countSourcesFiles ;
  char** listSourceFiles = getListSourceFiles(pathDirectory, &countSourcesFiles);

  short isAnExcludedFile = 0 ;
  Logger* logger = NULL ;

  if(countSourcesFiles > 0) logger = initialiseLogger(pathDirectory) ;


  for(int i = 0 ; i < countSourcesFiles; i++){
    isAnExcludedFile = isAnexcludedFile(linterConfig, listSourceFiles[i]) ;

    if(!isAnExcludedFile){ // Si c"est un fichier a analyser
      analyse(linterConfig, logger, listSourceFiles[i]) ;
    }
  }
  // liberation de la memoire allouée
  for(int i = 0 ; i < countSourcesFiles; i++) free(listSourceFiles[i]) ;
  free(listSourceFiles) ;

  closeLogger(logger) ;

  // on le fait de maniere recursive si l'option a été activer
  if(linterConfig->recursive == 1 ){

    int countDirectory ;
    char** listDirectory = getListDirectory(pathDirectory, &countDirectory) ;

    for(int i = 0 ; i < countDirectory; i++){
      linting(linterConfig, listDirectory[i]) ;
    }

    // on libere l'espace memoire allouée
    for(int i = 0 ; i < countDirectory; i++ ) free(listDirectory[i]) ;
    free(listDirectory) ;
  }
}

 /*
  * return the identifiant number of the rule, that identifiant is >= 1
  * if the ruleKey doesn't exist in the list of rules, then return 0
  */
int getRuleNumber(char* RuleKey){
  int countRules = 16 ;
  char* listAllRulesKey[16] = {"array-bracket-eol",
                               "operators-spacing",
                               "comma-spacing",
                               "indent",
                               "comments-header",
                               "max-line-numbers",
                               "max-file-line-numbers",
                               "no-trailing-spaces",
                               "no-multi-declaration",
                               "unused-variable",
                               "undeclared-variable",
                               "no-prototype",
                               "unused-function",
                               "undeclared-function",
                               "variable-assignment-type",
                               "function-parameters-type" } ;

  for(int i = 0 ; i < 16; i++){
    if(strcmp(RuleKey, listAllRulesKey[i]) == 0) return i + 1 ;
  }
  return 0 ; // return 0 if the rule doesn't exist
}
