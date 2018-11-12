/*
============================================================================
	Name        : logger.h
	Author      : amaubert
	Created on  : 2018/10/25
	Version     :
	Copyright   : Your copyright notice
	Description : structure logger
============================================================================
*/
#include <stdio.h>


typedef struct Logger{
  FILE* error ;
  FILE* log ;
}Logger ;


Logger* initialiseLogger() ;
void error(Logger* logger, char* message) ;
void log(Logger* logger, char* message) ;
char* getCurrentTime() ;
void freeLogger(Logger* logger) ;
