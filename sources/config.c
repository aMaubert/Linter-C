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

char* readDefaultConfig(const char* pathFile){

	FILE* inputFile = fopen(pathFile, "r") ;
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
