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

#ifndef LOGGER_HEADER_INCLUDED_
#define LOGGER_HEADER_INCLUDED_

#include <stdio.h>


typedef struct Logger{
  FILE* error ;
  FILE* log ;
}Logger ;


Logger* initialiseLogger(char* pathDirectory) ;
void messageError(Logger* logger, char* message) ;
void messageLog(Logger* logger, char* message) ;
char* getCurrentTime() ;
void freeLogger(Logger* logger) ;

 #endif /* LOGGER_HEADER_INCLUDED_ */
