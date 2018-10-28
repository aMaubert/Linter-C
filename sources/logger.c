/*
============================================================================
	Name        : logger.c
	Author      : amaubert
	date				: 25/10/2018
	Version     :
	Copyright   : Your copyright notice
	Description : a logger that write in the .log, .stat, .err files
============================================================================
*/


#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers/logger.h"

#define __RELATIVE_PATH_OUTPUT_ERROR__ "../log/linter_C.err"
#define __RELATIVE_PATH_OUTPUT_LOG__ "../log/linter_C.log"

Logger* initialiseLogger(){
  Logger* logger = malloc(sizeof(Logger))  ;
  logger->error = fopen( __RELATIVE_PATH_OUTPUT_ERROR__, "w") ;
  logger->log = fopen( __RELATIVE_PATH_OUTPUT_LOG__, "w") ;
  return logger ;
}
char* getCurrentTime(){
  time_t timestamp ; /* timestamp contient maintenant la date et l'heure courante */
  struct tm *date;
  char buffer[256] ;

  time( &timestamp );
  date = localtime(&timestamp) ;
  strftime(buffer, sizeof(buffer), "%Y/%m/%d  %X", date);
  char* ret = malloc(sizeof(buffer)) ;
  strcpy(ret, buffer) ;
  return ret ;
}

void error(Logger* logger, char* message){

    char* dateTime = getCurrentTime() ;
    char buffer[256] ;
    strcpy(buffer, dateTime) ;
    strcat(buffer, " - INFO - ") ;

    int tailleBuffer = strlen(buffer) ;

    int tailleMessage = strlen(message) ;

    char* line = malloc(sizeof(char) * ( tailleBuffer + tailleMessage + 1) ) ;

    strcpy(line, buffer) ;
    strcat(line, message) ;

    if(strchr(line, '\n') == NULL ){
      char* ptr = strchr(line, '\0') ;
      *ptr = '\n' ;
      ptr += 1 ;
      *ptr = '\0' ;
    }


    if(logger->error != NULL){
      fprintf(logger->error,"%s",line) ;

    }else printf("fichier error pas ouvert , pb ouverture fichier\n") ;

}

void log( Logger* logger, char* message){

      char* dateTime = getCurrentTime() ;
      char buffer[256] ;
      strcpy(buffer, dateTime) ;
      strcat(buffer, " - INFO - ") ;

      int tailleBuffer = strlen(buffer) ;

      int tailleMessage = strlen(message) ;

      char* line = malloc(sizeof(char) * ( tailleBuffer + tailleMessage + 1) ) ;

      strcpy(line, buffer) ;
      strcat(line, message) ;

      if(strchr(line, '\n') == NULL ){
        char* ptr = strchr(line, '\0') ;
        *ptr = '\n' ;
        ptr += 1 ;
        *ptr = '\0' ;
      }

      if(logger->log != NULL){

        fprintf(logger->log,"%s",line) ;

      }else printf("fichier log pas ouvert , pb ouverture fichier\n") ;
}

void closeLogger(Logger* logger){
  fclose(logger->error) ;
  fclose(logger->log) ;
  free(logger) ;
}
