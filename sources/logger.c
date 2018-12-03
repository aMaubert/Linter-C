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

/*
 * Initialize Logger
 */
Logger* initialiseLogger(char* pathDirectory){

  Logger* logger = malloc(sizeof(Logger))  ;
  char* outputLog = malloc(sizeof(char) * (1 + strlen(pathDirectory) + strlen("/linter.log") ) ) ;
  char* outputError = malloc(sizeof(char) * (1 + strlen(pathDirectory) + strlen("/linter.error") )) ;

  if(outputLog == NULL || outputError == NULL){
    fprintf(stderr, "%s , ligne : %d\nProbleme allocation memoire\n\n", __FILE__, __LINE__) ;
    system("pause") ;
    fflush(NULL) ;
    exit(EXIT_FAILURE) ;
  }

  strcpy(outputLog, pathDirectory) ;
  strcat( outputLog, "/linter.log") ;

  strcpy(outputError, pathDirectory) ;
  strcat( outputError, "/linter.error") ;

  logger->error = fopen( outputError, "w") ;
  logger->log = fopen( outputLog, "w") ;

  free(outputLog) ;
  free(outputError) ;

  return logger ;
}
/*
 * Return a string with the curent system dateTime
 */
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
/*
 * Append message in the error file
 */
void messageError(Logger* logger, char* message){

    char* dateTime = getCurrentTime() ;
    char buffer[256] ;
    strcpy(buffer, dateTime) ;
    strcat(buffer, " - ERROR - \n") ;

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
/*
 * Append message in the log file
 */
void messageLog(Logger* logger, char* message){

      char* dateTime = getCurrentTime() ;
      char buffer[256] ;
      strcpy(buffer, dateTime) ;
      strcat(buffer, " - INFO - \n") ;

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

/*
 * Close the log files
 */
void closeLogger(Logger* logger){
  fclose(logger->error) ;
  fclose(logger->log) ;
  free(logger) ;
}
