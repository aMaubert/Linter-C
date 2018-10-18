/*
============================================================================
	Name        : config.c
	Author      : amaubert
	date				: 15/10/2018
	Version     :
	Copyright   : Your copyright notice
	Description : fichier servant à récupérer les configuration du Linter
============================================================================
*/

#include "headers/config.h"

/* Constantes symbolique */
#define _NOMBRE_RULES_ 16


char* readDefaultConfig(const char* pathFile){

	FILE* inputFile = fopen(pathFile, "r") ;
	const char extendsKey[] = "=extends" ;
	const char rulesKey[] = "=rules" ;
	const char excludedFilesKey[] = "=excludedFiles" ;
	const char recursiveKey[] = "=recursive" ;

	char* contentFile = NULL ;

	if(inputFile != NULL){
			int numberCaracters = 0 ;
			char c ;

			do{
				c = fgetc(inputFile) ;
				if(c != EOF) numberCaracters += 1 ;
			}while(c != EOF) ;

			contentFile = malloc(sizeof(char) * (numberCaracters + 1) ) ;

			rewind(inputFile) ;
			for(int i = 0; i < numberCaracters ; i++){
				contentFile[i] = fgetc(inputFile) ;
			}
			contentFile[numberCaracters] = '\0' ;
	}


	fclose(inputFile) ;
	return contentFile ;

}

Linter* initialiseStructLinter(bool* rules, int nbExcludedFiles,char** excludedFiles, bool recursive){

	/* Déclaration */


	/* Allocation et affectation*/
	Linter* linter = malloc(sizeof(Linter)) ;
	linter->rules = malloc(sizeof(bool) * _NOMBRE_RULES_) ;

	if(nbExcludedFiles > 0 ) linter->nbExcludedFiles = nbExcludedFiles ;
	else linter->nbExcludedFiles = 0 ;

	if(linter->nbExcludedFiles > 0 ){
		linter->excludedFiles = malloc(sizeof(char*) * linter->nbExcludedFiles ) ;
		for(int i = 0 ; i < linter->nbExcludedFiles ; i++){
			linter->excludedFiles[i] = malloc( sizeof(char) * strlen(excludedFiles[i]) ) ;
			linter->excludedFiles[i] = strcpy(linter->excludedFiles[i],excludedFiles[i]) ;
		}
	}
	linter->recursive = recursive ;
	linter->extends = NULL ;

	return linter ;
}

void freeLinter(Linter* toDestroy){

    free(toDestroy->rules);
    free(toDestroy->recursive);
		for(int i = 0 ; i < toDestroy->nbExcludedFiles; i++){
			free(toDestroy->excludedFiles[i]) ;
		}
		free(toDestroy->excludedFiles) ;
		free(toDestroy->nbExcludedFiles) ;
    free(toDestroy);
}
void freeLinterList(Linter* linter)
{
    Linter* tmp;
    while (linter) { // tant qu'il a un linter dedans
        tmp = linter;
        linter = linter->extends;
        freeLinter(tmp);
    }
}
