/*
============================================================================
	Name        : config.c
	Author      : amaubert
	date				: 15/10/2018
	Version     :
	Copyright   : Your copyright notice
	Description : allows to get the Linter's congif
============================================================================
*/
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include "headers/config.h"
#include "headers/structure.h"

// chemin du fichier default.lconf qui contient les parametres par defauts
#define __DEFAULT_CONF_FILE__ "D:/ESGI/projets pedagogique ESGI/Linter-C/resources/lconfig/default.lconf"

ConfigLinter* loadLinterConfiguration(char* pathDirectory){

	ConfigLinter* linterConfig = NULL ;
	char* pathConfigFile = getConfigFile(pathDirectory) ;

  if(pathConfigFile != NULL){
		linterConfig = memorizeConfig( pathConfigFile , linterConfig) ;

		while(linterConfig->fileExtend != NULL){
	    // on verifie que le nom du fichier contient l'extention .lconf
	    if(strstr( linterConfig->fileExtend, ".lconf") == NULL){
	      fprintf(stderr, "le fichier etendu %s .\ndans %s .\nne contient pas l'extention .lconf !!!\n\n", linterConfig->fileExtend, pathConfigFile) ;
	      system("pause") ;
	      fflush(NULL) ;
	      exit(EXIT_FAILURE) ;
	    }
	    // on recupere le chemin du fichier de config etendu
	    pathConfigFile = getPathConfigFileExtend( pathDirectory, linterConfig->fileExtend) ;
	    if(pathConfigFile == NULL){ // si on ne l'a pas trouver on sort du progrmme en erreur fatale
	      fprintf(stderr, "le fichier etendu %s n'est pas present dans le repertoire et sous repertoire(s) du dossier.\n\n", linterConfig->fileExtend) ;
	      system("pause") ;
	      fflush(NULL) ;
	      exit(EXIT_FAILURE) ;
	    }
	    free(linterConfig->fileExtend) ;
	    linterConfig->fileExtend = NULL ;
	    linterConfig = memorizeConfig( pathConfigFile , linterConfig) ;
	  }
	}

  linterConfig = memorizeConfig( __DEFAULT_CONF_FILE__ , linterConfig) ;

	free(pathConfigFile) ;

	return linterConfig ;
}
/*
 * memorize the congig file in a structur ConfigLinter
 * return a structure ConfigLinter that contain the parametre in the config File
 */
ConfigLinter* memorizeConfig( char* pathFile, ConfigLinter* linterConfig){

	FILE* inputFile = fopen(pathFile, "r") ;

	char line[256] ;
	char buffer1[256] ;
	char buffer2[256] ;
	int countRules = 0, countExcludedFile = 0 ;


	/* variable qui serviront a remplir la structure */
	char* extendFile = NULL ;
	int countAllocateRules = 16;
	char** listKey = malloc(sizeof(char*) * countAllocateRules) ;
	char** listValue = malloc(sizeof(char*) * countAllocateRules) ;
	for(int i = 0 ; i < countAllocateRules; i++){
		listKey[i] = NULL ;
		listValue[i] = NULL ;
	}

	int countAllocateExcludedFiles = 10 ;
	char** listExcludedFiles = malloc(sizeof(char*) * countAllocateExcludedFiles) ;
	for(int i = 0 ; i < countAllocateExcludedFiles; i++) listExcludedFiles[i] = NULL ;

	char valeurRecursive[10] ;
	short recursive = 1 ;

	if(inputFile != NULL){

 		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=extends\n") != 0) ) ;

		// récuperation du chemin relative d'un et un seul fichier lconf
		fgets( line, sizeof(line), inputFile ) ;
		if((strcmp(line,"\n") != 0)){
			extendFile = malloc(sizeof(char) * (2 + strlen(line) ) ) ;
			sscanf(line, "%s\n", extendFile) ;
		}

		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=rules\n") != 0) ) ;

		// récuperation de la liste des règles du linter
		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "\n") != 0) ){

			sscanf(line, "- %s = %s\n", buffer1, buffer2) ;
			countRules += 1 ;
			if(countRules > countAllocateRules){
				countAllocateRules = countRules ;
				listKey = realloc( listKey, sizeof(char*) * countAllocateRules) ;
				listValue = realloc( listValue, sizeof(char*) * countAllocateRules) ;
				if(listKey == NULL || listValue == NULL){
					fprintf(stderr, "Probleme allocation memoire dans %s ligne : %d\n", __FILE__, __LINE__) ;
					system("pause") ;
					exit(EXIT_FAILURE) ;
				}
				listKey[countRules - 1] = NULL ;
				listValue[countRules - 1] = NULL ;
			}

			listKey[countRules - 1] = realloc( listKey[countRules - 1], sizeof(char) * (strlen(buffer1) + 1) ) ;
			listValue[countRules - 1] = realloc( listValue[countRules - 1], sizeof(char) * (strlen(buffer2) + 1)) ;

			if(listKey[countRules - 1] == NULL || listValue[countRules - 1] == NULL){
				fprintf(stderr, "Probleme allocation memoire dans %s ligne : %d\n", __FILE__, __LINE__) ;
				system("pause") ;
				exit(EXIT_FAILURE) ;
			}
			strcpy( listKey[countRules - 1], buffer1) ;
			strcpy( listValue[countRules - 1], buffer2) ;
		}

		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=excludedFiles\n") != 0) ) ;

		// récuperation de la liste des fichier à exclure du linter
		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "\n") != 0) ){

			sscanf(line, "%s\n", buffer1) ;
			countExcludedFile += 1 ;
			if(countExcludedFile > countAllocateExcludedFiles){
				countAllocateExcludedFiles = countExcludedFile ;
				listExcludedFiles = realloc( listExcludedFiles, sizeof(char*) * countAllocateExcludedFiles) ;

				if(listExcludedFiles == NULL){
					fprintf(stderr, "Probleme allocation memoire dans %s ligne : %d\n", __FILE__, __LINE__) ;
					system("pause") ;
					exit(EXIT_FAILURE) ;
				}
				listExcludedFiles[countExcludedFile - 1] = NULL ;
			}

			listExcludedFiles[countExcludedFile - 1] = realloc(listExcludedFiles[countExcludedFile - 1] , sizeof(char) * (strlen(buffer1) + 1) ) ;


			if(listExcludedFiles[countExcludedFile - 1] == NULL){
				fprintf(stderr, "Probleme allocation memoire listExcludedFiles[%d]\n", (countExcludedFile - 1)) ;
				fprintf(stderr, "excludedFile : %s    strlen(excludedFile) : %d\n",  buffer1, (int)strlen(buffer1)) ;
				fprintf(stderr, "dans %s ligne : %d\n",  __FILE__, __LINE__) ;
				system("pause") ;
				exit(EXIT_FAILURE) ;
			}

			strcpy(listExcludedFiles[countExcludedFile - 1] , buffer1) ;

		}

		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=recursive\n") != 0) ) ;

		if(fgets( line, sizeof(line), inputFile ) != NULL){
			sscanf(line, "%s\n", valeurRecursive) ;
			if(strcmp(valeurRecursive , "true") == 0) recursive = 1 ;
			else if(strcmp(valeurRecursive , "false") == 0) recursive = 0 ;
			if(linterConfig != NULL) recursive = linterConfig->recursive ;
		}

	}
	else{
		fprintf(stderr, "dans : %s   ligne : %d\nOuverture du fichier : %s   Impossible .\n\n", __FILE__, __LINE__, pathFile);
		system("pause") ;
		fflush(NULL) ;
		exit(EXIT_FAILURE) ;
	}

	/* on ferme le fichier car on a fini de le lire*/
	fclose(inputFile) ;


	if( linterConfig == NULL ) linterConfig = getInitialisedConfigLinter() ;
	if(linterConfig == NULL){
		fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
		system("pause") ;
		exit(EXIT_FAILURE) ;
	}


	 linterConfig = getConfigLinter(linterConfig, extendFile, countRules, listKey, listValue,
		  														countExcludedFile, listExcludedFiles, recursive) ;

		// On libere la mémoire
	 free(extendFile) ;

	 for(int i = 0 ; i < countRules; i++){
		 free(listKey[i]) ;
		 free(listValue[i]) ;
	 }
	 free(listKey) ;
	 free(listValue) ;

	 for(int i = 0 ; i < countExcludedFile; i++){
		 free(listExcludedFiles[i]) ;
	 }
	 free(listExcludedFiles) ;

	 // if(linterConfig->fileExtend != NULL){
	 //
		//  pathFile = changePathExtendFile( pathFile, linterConfig->fileExtend) ;
		//  printf("ligne : %d,  pathFile : %s\n", __LINE__, pathFile) ;
		//  linterConfig = memorizeConfig( pathFile, linterConfig) ;
	 // }

	return linterConfig ;

}
