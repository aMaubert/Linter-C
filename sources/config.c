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
#define __MAX_NUMBER_RULES__ 16 // le nombre maximum de rules
#define __MAX_CHAR_RULES__ 5 // le nombre de caracteres a alloué pour chaque règle dans le tableau rules
#define __SIZE_LINE__ 128
#define __SIZE_BUFFER__ 5000

Linter* readDefaultConfig(const char* pathFile){

	FILE* inputFile = fopen(pathFile, "r") ;
	Linter* linter = NULL ;
	if(inputFile != NULL){
	//	const char extendsKey[] = "=extends\n" ;
	//	const char rulesKey[] = "=rules\n" ;
	//	const char excludedFilesKey[] = "=excludedFiles\n" ;
	//	const char recursiveKey[] = "=recursive\n" ; // variable au comportement bysare, son contenu disparais en étape 2

		char line[__SIZE_LINE__] ; // correspondra à chaque ligne du fichier .lconf
		char configFilesExtends[__SIZE_BUFFER__] ;
		int etape = 0 ;

		/* Variables qui serviront à la récupération des règles */
		char allRules[__SIZE_BUFFER__] ; // contiendra toutes les valeurs des règles à la suite séparer d'un caractère
		int nbRules = 0 ;

		char allExcludedFiles[__SIZE_BUFFER__] ;
		int nbExcludedFiles = 0 ;
		bool recursive ;


		while(fgets ( line, sizeof(line), inputFile ) != NULL){

			switch(etape){
				case 0 :
					break ;
				case 1 :
					if((strcmp(line,"=rules\n") != 0) && (strcmp(line,"\n") != 0) ){
							 strcpy(configFilesExtends,line) ;
					}
					break ;
				case 2 :
					if((strcmp(line, "=excludedFiles\n") != 0) && (strcmp(line,"\n") != 0) ){
						char eachRule[__MAX_CHAR_RULES__] ;
						char buffer[__SIZE_BUFFER__] ;
						nbRules += 1 ;
						sscanf(line,"- %s = %s\n",buffer,eachRule) ;
						strcat(eachRule, ";") ;
						strcat(allRules, eachRule) ;
					}
					break ;
				case 3 :
					if((strcmp(line, "=recursive\n") != 0) && (strcmp(line,"\n") != 0) ){
						char buffer[__SIZE_BUFFER__] ;
						sscanf(line,"- %s\n",buffer) ;
						strcat(buffer, ";") ;
						strcat(allExcludedFiles, buffer) ;
						nbExcludedFiles += 1 ;
					}
					break ;
				case 4 :
					if( strcmp(line,"\n") != 0  ){
						if(strcmp(line,"true\n") == 0) recursive = true ;
						else if(strcmp(line,"false\n") == 0) recursive = false ;
					}
					break ;
				default :
					fprintf(stderr,"erreur switch case etape %d. fichier : %s    ligne : %d\n",etape,__FILE__,__LINE__) ;
				  break ;
			}

			if(strcmp(line,"=extends\n") == 0 ){
				etape = 1 ;
			}else if(strcmp(line,"=rules\n") == 0 ){
				etape = 2 ;
			}else if(strcmp(line,"=excludedFiles\n") == 0 ){
				etape = 3 ;
			}else if(strcmp(line,"=recursive\n") == 0 ){
				etape = 4 ;
			}
			// fprintf(stderr,"\\r : %d  \\n : %d  %c (%d) ",'\r','\n',line[strlen(line) - 1],line[strlen(line) - 1]) ;
			//printf("// etape : %d     %s",etape,line) ;
		}

		/*printf("fileExtends :  %s\n",configFilesExtends) ;
		printf("allRules : %s\n", allRules) ;

		printf("allExcludedFiles : %s\n",allExcludedFiles) ;
		if(recursive == true) printf("recursive : true\n") ;
		else printf("recursive : false\n") ;*/


		if(nbRules > 0 ){
			char** rules = stringSplit(allRules, ';', &nbRules) ;
			// printf("nbWords : %d  et nbRules : %d\n", nbWords, nbRules) ;
			// printf("rules[0] : %s\n",rules[0]) ;
			// for(int i = 0 ; i < nbWordsRules ; i++) printf("rules[%d] : %s\n", i, rules[i]) ;
			char** excludedFiles = NULL ;

			if(nbExcludedFiles > 0){

				excludedFiles = stringSplit(allExcludedFiles, ';', &nbExcludedFiles) ;
			}

			linter = initialiseStructLinter(nbRules, rules, nbExcludedFiles, excludedFiles, recursive) ;

			/* on libère l'espace mémoire */
			if(excludedFiles != NULL){
				for(int i = 0 ; i < nbExcludedFiles ; i++) free(excludedFiles[i]) ;
				free(excludedFiles) ;
			}
			for(int i = 0 ; i < nbRules ; i++) free(rules[i]) ;
			free(rules) ;
		}
	}


	fclose(inputFile) ;
	return linter ;

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
			//printf("destination[%d] : %s\n", lineDestination, destination[lineDestination]) ;
			indexBuffer = 0 ;
			lineDestination += 1 ;
		}else if(toSplit[index + 1] == '\0'){
			buffer[indexBuffer] = '\0' ;
			destination[lineDestination] = malloc(sizeof(char) * strlen(buffer)) ;
			strcpy(destination[lineDestination],buffer) ;
			//printf("destination[%d] : %s\n", lineDestination, destination[lineDestination]) ;
		}else{
			buffer[indexBuffer] = toSplit[index] ;
			indexBuffer += 1 ;
		}

		index += 1 ;
	}while(toSplit[index] != '\0' ) ;

	*nbWords = countWords ;
	return destination ;
}

Linter* initialiseStructLinter(int nbRules, char** rules, int nbExcludedFiles,char** excludedFiles, bool recursive){

	/* Déclaration */


	/* Allocation */
	Linter* linter = malloc(sizeof(Linter)) ;

	if(nbRules > 0){
		linter->rules = malloc(sizeof(char*) * nbRules ) ;
		for(int i = 0; i < nbRules; i++) linter->rules[i] = malloc(sizeof(char) * (strlen(rules[i]) + 1) ) ;
	}

	if(nbExcludedFiles > 0 ){
		linter->excludedFiles = malloc(sizeof(char*) * nbExcludedFiles ) ;
		for(int i = 0 ; i < nbExcludedFiles ; i++){
			linter->excludedFiles[i] = malloc( sizeof(char) * (strlen(excludedFiles[i]) + 1) ) ;
		}
	}

	/* Affectation */

	linter->nbRules = nbRules ;
	if(linter->nbRules > 0){
		for(int i = 0; i < linter->nbRules; i++)	strcpy(linter->rules[i], rules[i]) ;

	}else linter->rules = NULL ;

	linter->nbExcludedFiles = nbExcludedFiles ;
	if(linter->nbExcludedFiles > 0){
		for(int i = 0; i < linter->nbExcludedFiles; i++) strcpy(linter->excludedFiles[i],excludedFiles[i]) ;
	}else linter->excludedFiles = NULL ;

	linter->recursive = recursive ;
	linter->extends = NULL ;

	return linter ;
}
void displayLinter(Linter* linter){
	for(int i = 0 ; i < linter->nbRules ; i++) printf("rules %d : %s\n",i + 1,  linter->rules[i]) ;
	printf("\n") ;
	for(int i = 0 ; i < linter->nbExcludedFiles ; i++) printf("le fichier %s est exclus du linter\n",  linter->excludedFiles[i]) ;
	printf("\n") ;
	if(linter->recursive == true) printf("le linter doit scanner tous les sous fichiers du repertoire : true\n") ;
	else printf("le linter doit scanner tous les sous fichiers du repertoire : false\n") ;

}
void freeLinter(Linter* toDestroy){


		for(int i = 0 ; i < toDestroy->nbExcludedFiles; i++){
			free(toDestroy->excludedFiles[i]) ;
		}
		free(toDestroy->excludedFiles) ;

		for(int i = 0 ; i < toDestroy->nbRules ; i++){
			free(toDestroy->rules[i]) ;
		}
		free(toDestroy->rules) ;
    free(toDestroy);
}
void freeLinterList(Linter* linter){
    Linter* tmp;
    while (linter) { // tant qu'il a un linter dedans
        tmp = linter;
        linter = linter->extends;
        freeLinter(tmp);
    }
}
