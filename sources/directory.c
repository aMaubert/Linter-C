/*
 ============================================================================
 Name        : directory.c
 Author      : Allan Maubert
 Created on	 : 2018/11/01
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include "headers/directory.h"

/*
 * Return 1 if the argument path is a path to a repository, else return 0
 */
short directoryExist( char* path){
	short isDirectory = 1 ;
	DIR* directory;
	directory = opendir(path);

	if(directory == NULL)    isDirectory = 0 ;

	closedir(directory);
	return isDirectory ;
}
/**
 *  get the list of file that content path
 *  the pointer count is used to count the number of elements (file name)
 *  return the list of Files in a char**
 */
char** getListFilesInDirectory(char* path, int* count){

  *count = 0 ;
  DIR* directory = opendir(path);
  struct dirent *lecture = NULL;
  char** listFiles = NULL ;

  if(directory != NULL){
    while(lecture = readdir(directory)){

      *count += 1 ;
      listFiles = realloc(listFiles, sizeof(char*) * (*count) ) ;

      if(listFiles == NULL){
        fprintf(stderr, "file %s , ligne : %d\nProbleme allocation memoire\n\n", __FILE__, __LINE__) ;
        system("pause") ;
        fflush(NULL) ;
      }else{
        listFiles[*count - 1] = malloc(sizeof(char) * (1 + strlen(lecture->d_name))) ;
        if(listFiles[*count - 1] == NULL){
          fprintf(stderr, "file %s , ligne : %d\nProbleme allocation memoire\n\n", __FILE__, __LINE__) ;
          system("pause") ;
          fflush(NULL) ;
        }
        strcpy(listFiles[*count - 1], lecture->d_name) ;

      }
    }
 }else{
   fprintf(stderr, "file : %s , ligne:%d\nle chemin du dossier donner en parametre n'est pas correct !!!\nChemin donnee : %s\n\n", __FILE__, __LINE__, path) ;
   system("pause") ;
   fflush(NULL) ;
 }
 closedir(directory);
 free(lecture) ;
 return listFiles ;
}
/*
 * return the path of the config file extend if exist, else return NULL
 */
char* getPathConfigFileExtend(char* pathRootDirectory, char* nameFileExtend){
	int countFiles ;
	char** listFiles =  getListFilesInDirectory(pathRootDirectory, &countFiles) ;
	char* pathConfigFileExtend = NULL ;
	for(int i = 0 ; i < countFiles; i++){
		// si le fichier se situe bien dans le repertoire pathRootDirectory
		if(strcmp( listFiles[i], nameFileExtend) == 0){
			pathConfigFileExtend = malloc(sizeof(char) * ( 2 + strlen(pathRootDirectory) + strlen(nameFileExtend))) ;
			if(pathConfigFileExtend == NULL){
				fprintf(stderr, "%s , ligne : %d\nProbleme Allocation memoire\n\n", __FILE__, __LINE__) ;
				system("pause") ;
				fflush(NULL) ;
			}
			strcpy( pathConfigFileExtend, pathRootDirectory) ;
			strcat(pathConfigFileExtend, "/") ;
			strcat(pathConfigFileExtend, nameFileExtend) ;
			i = countFiles ;
		}
	}
	/* Dans le cas où le fichier n'a pas été trouver, alors élargir la recherche dans les sous-repertoire*/
	if(pathConfigFileExtend == NULL){
		char sousDirectory[256] ;
		for(int i = 0 ; i < countFiles; i++){
			// manipulation pour obtenir les chemins des potentiels sous-repertoires

			strcpy( sousDirectory, pathRootDirectory) ;
			strcat( sousDirectory, "/") ;
			strcat( sousDirectory, listFiles[i]) ;
			// Dans le cas où le fichier est un repertoire (différent du repertoire courrant où du repertoire parent)
			// on execute de façon recursive la recherche
			if(directoryExist(sousDirectory) && (strcmp(listFiles[i], "..") != 0) && (strcmp(listFiles[i], ".") != 0)){
				pathConfigFileExtend = getPathConfigFileExtend( sousDirectory, nameFileExtend) ;
				if(pathConfigFileExtend != NULL) i = countFiles ;
			}
		}
	}


	// On libere la mémoire alloué
	for(int i = 0 ; i < countFiles; i++) free(listFiles[i]) ;
	free(listFiles) ;

	return pathConfigFileExtend ;
}

/*
 * Return the path of the config file in the directory that is analyzed
 */
char* getConfigFile(char* pathDirectory){

	char** listFiles  = NULL;
  int countListFiles = 0 ;
  char* defaultConfFile = NULL ;

  listFiles = getListFilesInDirectory(pathDirectory, &countListFiles) ;
  for(int i = 0 ; i < countListFiles; i++){
    if( strstr(listFiles[i], ".lconf") != NULL){ // Si on trouve la chaine .lconf
        defaultConfFile = malloc(sizeof(char) * (2 + strlen(pathDirectory) + strlen(listFiles[i])) ) ;
        if(defaultConfFile != NULL){
          strcpy( defaultConfFile, pathDirectory) ;
          strcat( defaultConfFile, "/") ;
          strcat( defaultConfFile, listFiles[i]) ;
					i = countListFiles ;
        }
    }
  }

	// on libere la mémoire alloué
	for(int i = 0 ; i < countListFiles; i++){
		free(listFiles[i]) ;
	}
	free(listFiles) ;
	return defaultConfFile ;

}

/*
 *
 * Return the path of the new file (fileExtendName), fileExtendName is the relative path of a file that start to path
 */
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
 * the value of the argument : countSourcesFiles contents the number of sources c Files
 * Retrun the list of sources c files in the current directory
 */
char** getListSourceFiles(char* currentDirectory, int* countSourcesFiles){
	int countAllFiles ;
	int countSourcesCFiles = 0;
	char** listAllFiles = getListFilesInDirectory( currentDirectory, &countAllFiles) ;
	char** listSourcesCFiles = NULL ;

	for(int i = 0 ; i < countAllFiles; i++){
		// Si on trouve l'extention .c
		if(strstr(listAllFiles[i], ".c") != NULL){
			countSourcesCFiles += 1 ;
			listSourcesCFiles = realloc(listSourcesCFiles, sizeof(char*) * countSourcesCFiles) ;
			if(listSourcesCFiles != NULL) listSourcesCFiles[countSourcesCFiles - 1] = malloc(sizeof(char) * (2 + strlen(currentDirectory) + strlen(listAllFiles[i]))) ;
			if(listSourcesCFiles == NULL || listSourcesCFiles[countSourcesCFiles - 1] == NULL){
				fprintf(stderr, "%s , ligne %d\nP¨robleme allocation memoire .\n\n", __FILE__, __LINE__) ;
				system("pause") ;
				fflush(NULL) ;
				exit(EXIT_FAILURE) ;
			}

			strcpy(listSourcesCFiles[countSourcesCFiles - 1], currentDirectory) ;
			strcat(listSourcesCFiles[countSourcesCFiles - 1], "/") ;
			strcat(listSourcesCFiles[countSourcesCFiles - 1], listAllFiles[i]) ;
		}
	}
	// on libere la mémoire allouée
	for(int i = 0 ; i < countAllFiles; i++) free(listAllFiles[i]) ;
	free(listAllFiles) ;

	*countSourcesFiles = countSourcesCFiles ;
	return listSourcesCFiles ;
}
