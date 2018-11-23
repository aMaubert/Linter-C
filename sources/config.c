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


ConfigLinter* memorizeConfig( char* pathFile, ConfigLinter* linterConfig){

	FILE* inputFile = fopen(pathFile, "r") ;

	char line[256] ;
	char ruleKey[256] ;
	char ruleValue[256] ;
	char excludedFile[256] ;
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
			extendFile = malloc(strlen(line)) ;
			sscanf(line, "%s\n", extendFile) ;
		}

		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=rules\n") != 0) ) ;

		// récuperation de la liste des règles du linter
		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "\n") != 0) ){

			sscanf(line, "- %s = %s\n", ruleKey, ruleValue) ;
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

			listKey[countRules - 1] = realloc( listKey[countRules - 1], sizeof(char) * (strlen(ruleKey) + 1) ) ;
			listValue[countRules - 1] = realloc( listValue[countRules - 1], sizeof(char) * (strlen(ruleValue) + 1)) ;

			if(listKey[countRules - 1] == NULL || listValue[countRules - 1] == NULL){
				fprintf(stderr, "Probleme allocation memoire dans %s ligne : %d\n", __FILE__, __LINE__) ;
				system("pause") ;
				exit(EXIT_FAILURE) ;
			}
			strcpy( listKey[countRules - 1], ruleKey) ;
			strcpy( listValue[countRules - 1], ruleValue) ;
		}

		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=excludedFiles\n") != 0) ) ;

		// récuperation de la liste des fichier à exclure du linter
		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "\n") != 0) ){

			sscanf(line, "%s\n", excludedFile) ;
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

			listExcludedFiles[countExcludedFile - 1] = realloc(listExcludedFiles[countExcludedFile - 1] , sizeof(char) * (strlen(excludedFile) + 1) ) ;


			if(listExcludedFiles[countExcludedFile - 1] == NULL){
				fprintf(stderr, "Probleme allocation memoire listExcludedFiles[%d]\n", (countExcludedFile - 1)) ;
				fprintf(stderr, "excludedFile : %s    strlen(excludedFile) : %d\n",  excludedFile, (int)strlen(excludedFile)) ;
				fprintf(stderr, "dans %s ligne : %d\n",  __FILE__, __LINE__) ;
				system("pause") ;
				exit(EXIT_FAILURE) ;
			}

			strcpy(listExcludedFiles[countExcludedFile - 1] , excludedFile) ;

		}

		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=recursive\n") != 0) ) ;

		if(fgets( line, sizeof(line), inputFile ) != NULL){
			sscanf(line, "%s\n", valeurRecursive) ;
			if(strcmp(valeurRecursive , "true") == 0) recursive = 1 ;
			else if(strcmp(valeurRecursive , "false") == 0) recursive = 0 ;

			if(linterConfig != NULL) recursive = linterConfig->recursive ;
			printf( "valeurRecursive : %s  , recursive : %d\n", valeurRecursive, (int) recursive) ;
			system("pause") ;
			fflush(stdout) ;
		}

	}
	else{
		fprintf(stderr, "dans : %s   ligne : %d\nOuverture du fichier : %s   Impossible .\n\n", __FILE__, __LINE__, pathFile);
		system("pause") ;
		fflush(NULL) ;
		exit(EXIT_FAILURE) ;
	}

	fclose(inputFile) ;


	if( linterConfig == NULL ) linterConfig = getInitialisedConfigLinter() ;
	if(linterConfig == NULL){
		fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
		system("pause") ;
		exit(EXIT_FAILURE) ;
	}


	 linterConfig = getConfigLinter(linterConfig, extendFile, countRules, listKey, listValue,
		  countExcludedFile, listExcludedFiles, recursive) ;


	 if(extendFile != NULL){

		 pathFile = changePathExtendFile( pathFile, linterConfig->fileExtend) ;
		 printf("ligne : %d,  pathFile : %s\n", __LINE__, pathFile) ;
		 linterConfig = memorizeConfig( pathFile, linterConfig) ;
	 }


	return linterConfig ;

}
char* changePathExtendFile(char* path, char* fileExtendName){

	for(int i = strlen(path) ; i >= 0 ; i--){
		if(path[i] == '/' || path[i] == '\\'){
			path[i + 1] = '\0' ;
			i = 0 ;
		}
	}

	path = realloc(path, sizeof(char) * (1 + strlen(path) + strlen(fileExtendName))) ;
	if(path == NULL){
		fprintf(stderr, "file : %s , ligne : %d\nProbleme Allocation memoire\n\n", __FILE__, __LINE__) ;
		system("pause") ;
		fflush(NULL) ;
	}
	else{
		strcat(path , fileExtendName) ;
	}
	return path ;
}


/*
 *
 * @return : le nombres de mots contenus dans toSplit
 *
 */
char** stringSplit(char* toSplit, char caractere, int *nbWords){
	int index = 0 ;
	int countWords = 0 ;
	char** destination = NULL ;

	do{
		if((toSplit[index] == caractere) && (toSplit[index + 1] != '\0') ) countWords += 1 ;

		index += 1 ;
	}while(toSplit[index] != '\0' ) ;
	countWords += 1 ;
	destination = malloc(sizeof(char* ) * countWords) ;
	char buffer[4086] ;
	index = 0 ;
	int indexBuffer = 0 ;
	int lineDestination = 0 ;
	do{
		if((toSplit[index] == caractere) && (toSplit[index + 1] != '\0') ){
			buffer[indexBuffer] = '\0' ;
			destination[lineDestination] = malloc(sizeof(char) * strlen(buffer)) ;
			strcpy(destination[lineDestination],buffer) ;
			indexBuffer = 0 ;
			lineDestination += 1 ;
		}else if(toSplit[index + 1] == '\0'){
			buffer[indexBuffer] = '\0' ;
			destination[lineDestination] = malloc(sizeof(char) * strlen(buffer)) ;
			strcpy(destination[lineDestination],buffer) ;
		}else{
			buffer[indexBuffer] = toSplit[index] ;
			indexBuffer += 1 ;
		}

		index += 1 ;
	}while(toSplit[index] != '\0' ) ;

	*nbWords = countWords ;
	return destination ;
}

char* str_replace(const char* stringToReplace, const char *str_regex, const char* expressionToAdd){
	 int err;
   regex_t preg;
	 err = regcomp (&preg, str_regex, REG_EXTENDED); // compile l'expression  reguliere

	 if (err == 0){ // si la compilation a fonctionner
      int match;
      size_t numberMatch = 0;
      regmatch_t *pmatch = NULL;

      numberMatch = preg.re_nsub; // on recupère le nombre de match
      pmatch = malloc (sizeof (*pmatch) * numberMatch);
      if (pmatch){
         match = regexec (&preg, stringToReplace, numberMatch, pmatch, 0);
         regfree (&preg);

         if (match == 0){
            char *ret = NULL;
            int start = pmatch[0].rm_so; // debut du match
            int end = pmatch[0].rm_eo;// fin du match
            size_t size = (strlen(stringToReplace) - (end - start));//taille en octet du match

            ret = malloc (sizeof (*ret) * (size + strlen(expressionToAdd) ));
            if (ret){
               strncpy (ret, &stringToReplace[0], size);
							 ret[size] = '\0';
							 strcat(ret, expressionToAdd) ;
               return ret ;
            }
         }
         else if (match == REG_NOMATCH){
            printf ("Il n'y a aucun resultat pour la regex donné dans : %s\n", stringToReplace);
         }
				 else{
            char *text;
            size_t size;

            size = regerror (err, &preg, NULL, 0);
            text = malloc (sizeof (*text) * size);
            if (text){

               regerror (err, &preg, text, size);
               fprintf (stderr, "%s\n", text);
               free (text);
            }else{
               fprintf (stderr, "Memoire insuffisante\n");
            }
         }
      }else{
         fprintf (stderr, "Memoire insuffisante\n");
      }
   }
	 return NULL ;
 }
