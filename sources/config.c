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


/* Constantes symbolique */


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
			listKey[countRules - 1] = realloc( listKey[countRules - 1], sizeof(char) * strlen(ruleKey)) ;
			listValue[countRules - 1] = realloc( listValue[countRules - 1], sizeof(char) * strlen(ruleValue)) ;

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

			listExcludedFiles[countExcludedFile - 1] = realloc(listExcludedFiles[countExcludedFile - 1] , sizeof(char) * strlen(excludedFile)) ;
			if(listExcludedFiles[countExcludedFile - 1] == NULL){
				fprintf(stderr, "Probleme allocation memoire dans %s ligne : %d\n", __FILE__, __LINE__) ;
				system("pause") ;
				exit(EXIT_FAILURE) ;
			}

			strcpy(listExcludedFiles[countExcludedFile - 1] , excludedFile) ;

		}



		while( (fgets( line, sizeof(line), inputFile ) != NULL) && (strcmp(line, "=recursive\n") != 0) ) ;

		if(fgets( line, sizeof(line), inputFile ) != NULL){
			sscanf(line, "%s\n", valeurRecursive) ;
		}

	}
	else{
		fprintf(stderr, "dans : %s   ligne : %d\nOuverture du fichier : %s   Impossible .\n", __FILE__, __LINE__, pathFile);
    exit(EXIT_FAILURE) ;
	}


	fclose(inputFile) ;

	short recursive = 1 ;
	if( strcmp(valeurRecursive, "false") == 0 ) recursive = 0 ;


	if( linterConfig == NULL ) linterConfig = getInitialisedConfigLinter() ;
	if(linterConfig == NULL){
		fprintf(stderr, "probleme Allocation dans %s  ligne %d\n", __FILE__, __LINE__) ;
		system("pause") ;
		exit(EXIT_FAILURE) ;
	}


	 linterConfig = getConfigLinter(linterConfig, extendFile, countRules, countAllocateRules, listKey, listValue,
		  countExcludedFile, countAllocateExcludedFiles, listExcludedFiles, recursive) ;

	 if(extendFile != NULL){
		 printf("file a etendre \n") ;


		 const char *str_regex = "(/[0-9a-zA-Z]*\\.lconf)";
		 char* expression = malloc(sizeof(char) * (strlen(linterConfig->fileExtend) + 1) ) ;
		 strcpy(expression, "/") ;
		 strcat(expression, linterConfig->fileExtend) ;
		 char* path = str_replace(pathFile, str_regex, expression) ;
	 	 free(expression) ;

		 linterConfig = memorizeConfig( path, linterConfig) ;
	 }else{
		 printf("pas file a etendre \n") ;
	 }

	displayLinterConfig(linterConfig) ;
	return linterConfig ;

}


// void readLineConfig(char* pathFile, int *etape, char* line, char* configFilesExtend, bool* fileExtendExist,
// 		 int* nbRules, char* allRules, int* nbExcludedFiles, char* allExcludedFiles,
// 		 bool* recursive){
//
// 	const char extendsKey[] = "=extends\n" ;
// 	const char rulesKey[] = "=rules\n" ;
// 	const char excludedFilesKey[] = "=excludedFiles\n" ;
// 	const char recursiveKey[] = "=recursive\n" ;
//
// 	switch(*etape){
// 		case 0 :
// 			break ;
// 		case 1 :
// 			if((strcmp(line,rulesKey) != 0) && (strcmp(line,"\n") != 0) ){
// 				 const char *str_regex = "(/[0-9a-zA-Z]*\\.lconf)";
// 				 char* expression = malloc(sizeof(char) * (strlen(line) + 1) ) ;
// 				 strcpy(expression, "/") ;
// 				 strcat(expression, line) ;
// 				 char* path = str_replace(pathFile, str_regex, expression) ;
//  			 	 free(expression) ;
// 				 strcpy(configFilesExtend, path) ;
// 				 *fileExtendExist = true ;
// 			}
// 			break ;
// 		case 2 :
// 			if((strcmp(line, excludedFilesKey) != 0) && (strcmp(line,"\n") != 0) ){
// 				char eachRule[__MAX_CHAR_RULES__] ;
// 				char buffer[__SIZE_BUFFER__] ;
// 				*nbRules += 1 ;
// 				sscanf(line,"- %s = %s\n",buffer,eachRule) ;
// 				strcat(eachRule, ";") ;
// 				strcat(allRules, eachRule) ;
// 			}
// 			break ;
// 		case 3 :
// 			if((strcmp(line, recursiveKey) != 0) && (strcmp(line,"\n") != 0) ){
// 				char buffer[__SIZE_BUFFER__] ;
// 				sscanf(line,"- %s\n",buffer) ;
// 				strcat(buffer, ";") ;
// 				strcat(allExcludedFiles, buffer) ;
// 				*nbExcludedFiles += 1 ;
// 			}
// 			break ;
// 		case 4 :
// 			if( strcmp(line,"\n") != 0  ){
// 				if(strcmp(line,"true\n") == 0) *recursive = true ;
// 				else if(strcmp(line,"false\n") == 0) *recursive = false ;
// 			}
// 			break ;
// 		default :
// 			fprintf(stderr,"erreur switch case etape %d. fichier : %s    ligne : %d\n",*etape,__FILE__,__LINE__) ;
// 			break ;
// 	}
//
// 	if(strcmp(line,extendsKey) == 0 ){
// 		*etape = 1 ;
// 	}else if(strcmp(line,rulesKey) == 0 ){
// 		*etape = 2 ;
// 	}else if(strcmp(line,excludedFilesKey) == 0 ){
// 		*etape = 3 ;
// 	}else if(strcmp(line, recursiveKey) == 0 ){
// 		*etape = 4 ;
// 	}
// }
//
//
//
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
