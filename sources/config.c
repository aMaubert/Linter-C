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

#include <regex.h>
#include "headers/config.h"

/* Constantes symbolique */
#define __MAX_NUMBER_RULES__ 16
#define __MAX_CHAR_RULES__ 5
#define __SIZE_LINE__ 128
#define __SIZE_BUFFER__ 5000

Linter* memorizeConfig( char* pathFile){
	printf("fichier : %s    ligne : %d\n", __FILE__,  __LINE__) ;
	printf("chemin du fichier lconf : %s\n", pathFile) ;
	FILE* inputFile = fopen(pathFile, "r") ;
	Linter* linter = NULL ;
	if(inputFile != NULL){

		char line[__SIZE_LINE__] ; // correspondra à chaque ligne du fichier .lconf
		int etape = 0 ;


		char configFilesExtend[__SIZE_BUFFER__]  ; // permet de récupérer le fichier etendue
		bool fileExtendExist = false ;


		/* Variables qui serviront à la récupération des règles */
		char allRules[__SIZE_BUFFER__] ; // contiendra toutes les valeurs des règles à la suite séparer d'un caractère
		int nbRules = 0 ;

		char allExcludedFiles[__SIZE_BUFFER__] ;
		int nbExcludedFiles = 0 ;
		bool recursive ;



		while(fgets ( line, sizeof(line), inputFile ) != NULL){
			readLineConfig(pathFile, &etape, line, configFilesExtend, &fileExtendExist, &nbRules, allRules, &nbExcludedFiles,
				 						allExcludedFiles, &recursive) ;
		}
		if(nbRules > 0 ){
			char** rules = stringSplit(allRules, ';', &nbRules) ;

			char** excludedFiles = NULL ;

			if(nbExcludedFiles > 0){

				excludedFiles = stringSplit(allExcludedFiles, ';', &nbExcludedFiles) ;
			}

			if(fileExtendExist == true){
				linter = initialiseStructLinter(nbRules, rules, nbExcludedFiles, excludedFiles,
																				recursive, configFilesExtend) ;
			}else{
				linter = initialiseStructLinter(nbRules, rules, nbExcludedFiles, excludedFiles,
																				recursive, NULL) ;
			}


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

void readLineConfig(char* pathFile, int *etape, char* line, char* configFilesExtend, bool* fileExtendExist,
		 int* nbRules, char* allRules, int* nbExcludedFiles, char* allExcludedFiles,
		 bool* recursive){

	const char extendsKey[] = "=extends\n" ;
	const char rulesKey[] = "=rules\n" ;
	const char excludedFilesKey[] = "=excludedFiles\n" ;
	const char recursiveKey[] = "=recursive\n" ;

	switch(*etape){
		case 0 :
			break ;
		case 1 :
			if((strcmp(line,rulesKey) != 0) && (strcmp(line,"\n") != 0) ){
				 const char *str_regex = "(/[0-9a-zA-Z]*\\.lconf)";
				 char* expression = malloc(sizeof(char) * (strlen(line) + 1) ) ;
				 strcpy(expression, "/") ;
				 strcat(expression, line) ;
				 char* path = str_replace(pathFile, str_regex, expression) ;
 			 	 free(expression) ;
				 strcpy(configFilesExtend, path) ;
				 *fileExtendExist = true ;
			}
			break ;
		case 2 :
			if((strcmp(line, excludedFilesKey) != 0) && (strcmp(line,"\n") != 0) ){
				char eachRule[__MAX_CHAR_RULES__] ;
				char buffer[__SIZE_BUFFER__] ;
				*nbRules += 1 ;
				sscanf(line,"- %s = %s\n",buffer,eachRule) ;
				strcat(eachRule, ";") ;
				strcat(allRules, eachRule) ;
			}
			break ;
		case 3 :
			if((strcmp(line, recursiveKey) != 0) && (strcmp(line,"\n") != 0) ){
				char buffer[__SIZE_BUFFER__] ;
				sscanf(line,"- %s\n",buffer) ;
				strcat(buffer, ";") ;
				strcat(allExcludedFiles, buffer) ;
				*nbExcludedFiles += 1 ;
			}
			break ;
		case 4 :
			if( strcmp(line,"\n") != 0  ){
				if(strcmp(line,"true\n") == 0) *recursive = true ;
				else if(strcmp(line,"false\n") == 0) *recursive = false ;
			}
			break ;
		default :
			fprintf(stderr,"erreur switch case etape %d. fichier : %s    ligne : %d\n",*etape,__FILE__,__LINE__) ;
			break ;
	}

	if(strcmp(line,extendsKey) == 0 ){
		*etape = 1 ;
	}else if(strcmp(line,rulesKey) == 0 ){
		*etape = 2 ;
	}else if(strcmp(line,excludedFilesKey) == 0 ){
		*etape = 3 ;
	}else if(strcmp(line, recursiveKey) == 0 ){
		*etape = 4 ;
	}
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

Linter* initialiseStructLinter(int nbRules, char** rules, int nbExcludedFiles,
				char** excludedFiles, bool recursive, char* fileExtend){

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

	if(fileExtend != NULL ) linter->fileExtend = malloc(sizeof(char) * strlen(fileExtend)) ;

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
	if(fileExtend != NULL ) strcpy(linter->fileExtend, fileExtend) ;
	else linter->fileExtend = NULL ;

	linter->extends = NULL ;

	return linter ;
}
void displayLinter(Linter* linter, FILE* output){

	fprintf(output, "linter (id : %p)\n",linter) ;

	if(linter->fileExtend != NULL) fprintf(output, "fichier config suivant : %s\n", linter->fileExtend) ;
	else fprintf(output, "il n'y a pas de fichier config suivant\n") ;

	for(int i = 0 ; i < linter->nbRules ; i++) fprintf(output, "rules %d : %s\n",i + 1,  linter->rules[i]) ;
	fprintf(output, "\n") ;

	for(int i = 0 ; i < linter->nbExcludedFiles ; i++) fprintf(output, "le fichier %s est exclus du linter\n",  linter->excludedFiles[i]) ;
	fprintf(output, "\n") ;

	if(linter->recursive == true) fprintf(output, "le linter doit scanner tous les sous fichiers du repertoire : true\n") ;
	else fprintf(output, "le linter doit scanner tous les sous fichiers du repertoire : false\n") ;
	fprintf(output, "\n") ;
	if(linter->extends != NULL ) displayLinter(linter->extends, output) ;
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
		free(toDestroy->fileExtend) ;
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
