/*
 ============================================================================
 Name        : main.c
 Author      : amaubert
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include "headers/config.h"

int main(void) {
	const char defaulConfigFilePath[] = "..\\resources\\lconfig\\default.lconf" ;
	char* contentFile = readDefaultConfig(defaulConfigFilePath) ;
	printf("contenu du fichier : %s\n%s\n\n",defaulConfigFilePath,contentFile);
	fflush(stdout) ;
	system("pause") ;
	free(contentFile) ;
	return EXIT_SUCCESS;
}
