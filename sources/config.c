/*
 * 	Name : config.c
 *
 *  Created on: 14 oct. 2018
 *  Author: ESGI
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
