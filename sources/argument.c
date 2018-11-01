/*
 ============================================================================
 Name        : argument.c
 Author      : Allan Maubert
 Created on	 : 2018/11/01
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include "headers/argument.h"

 bool validArgument(Logger* logger, int argc, char** argv){
 	bool ret = true ;

 	if(argc == 2 ){
 		ret = isDirectory(logger, argv[1]) ;

 	}else{
 		error(logger, "ce programme n'accepte qu'un parametre, le chemin du dossier a linter") ;
 		ret = false ;
 	}

 	return ret ;
 }
 bool isDirectory(Logger* logger, char* path){
 	bool isDirectory = true ;
 	struct dirent *lecture;
 	DIR* directory;
 	directory = opendir(path);

 	if(directory == NULL){
 		error(logger, "le chemin du dossier donner en parametre n'est pas correct !!!") ;
 		isDirectory = false ;
 	}
 	closedir(directory);

 	return isDirectory ;
 }
