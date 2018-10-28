/*
 ============================================================================
 Name        : main.c
 Author      : Allan Maubert
 Created on	 : 2018/10/15
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <regex.h>
#include "headers/config.h"
#include "headers/logger.h"


#define __ROOT_PATH_ALLAN__ "d:\\projets ESGI\\Linter-C\\"
#define __DEFAULT_CONFIG_PATH__ "resources\\lconfig\\default.lconf.."
#define __DEFAULT_CONFIG_RELATIF_PATH__ "../resources/lconfig/default.lconf"

bool validArgument(Logger* logger, int argc, char** argv) ;
bool isDirectory(Logger* logger, char* path) ;
void lancementProgramme() ;

// const char *str_request = "../resources/lconfig/default.lconf";
// const char *str_regex = "/[0-9a-zA-Z]*\\.lconf";

int main(int argc, char* argv[]) {
	int err;
   regex_t preg;
	 const char *str_request = "../resources/lconfig/default.lconf";
	 const char *str_regex = "(/[0-9a-zA-Z]*\\.lconf)";

/* (1) */
   err = regcomp (&preg, str_regex, REG_EXTENDED);
   if (err == 0)
   {
      int match;
      size_t nmatch = 0;
      regmatch_t *pmatch = NULL;

      nmatch = preg.re_nsub;
      pmatch = malloc (sizeof (*pmatch) * nmatch);
      if (pmatch)
      {
/* (2) */
         match = regexec (&preg, str_request, nmatch, pmatch, 0);
/* (3) */
         regfree (&preg);
/* (4) */
         if (match == 0)
         {
            char *site = NULL;
            int start = pmatch[0].rm_so; // debut du match
            int end = pmatch[0].rm_eo;// fin du match
            size_t size = (strlen(str_request) - (end - start));//taille en octet du match

            site = malloc (sizeof (*site) * (size + strlen("/deuxiemeFichier.lconf") ));
            if (site)
            {
               strncpy (site, &str_request[0], size);
							 site[size] = '\0';
							 strcat(site, "/deuxiemeFichier.lconf") ;
               printf ("%s\n", site);
               free (site);
            }
         }
/* (5) */
         else if (match == REG_NOMATCH)
         {
            printf ("%s n\'est pas une adresse internet valide\n", str_request);
         }
/* (6) */
         else
         {
            char *text;
            size_t size;

/* (7) */
            size = regerror (err, &preg, NULL, 0);
            text = malloc (sizeof (*text) * size);
            if (text)
            {
/* (8) */
               regerror (err, &preg, text, size);
               fprintf (stderr, "%s\n", text);
               free (text);
            }
            else
            {
               fprintf (stderr, "Memoire insuffisante\n");
               exit (EXIT_FAILURE);
            }
         }
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   puts ("\nPress any key\n");
/* Dev-cpp */
   getchar ();
   return (EXIT_SUCCESS);
}
void lancementProgramme(int argc, char** argv ){
	Logger* logger = initialiseLogger() ;

	bool argumentIsValid = validArgument(logger, argc, argv) ;

	/* chemin relative */
	char defaulConfigFileRelatifPath[] = __DEFAULT_CONFIG_RELATIF_PATH__ ;

	/* mémorisation des configuration du linter */
	Linter* linter = memorizeConfig( defaulConfigFileRelatifPath) ;
	if(linter->fileExtend != NULL){
		printf("linter->fileExtend : %s\n", linter->fileExtend) ;
		linter = memorizeConfig( linter->fileExtend) ;
	}

  displayLinter(linter, stdout) ;

	/* Lancement du Linter */

	/* Liberation des espaces mémoires alloués */
	freeLinterList(linter) ;

	closeLogger(logger) ;


	fflush(stdout) ;
	system("pause") ;
	//	free(contentFile) ;
}

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
