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

short directoryExist( char* path){
	short isDirectory = 1 ;
	DIR* directory;
	directory = opendir(path);

	if(directory == NULL){
		fprintf(stderr, "file : %s , ligne:%d\nle chemin du dossier donner en parametre n'est pas correct !!!\nChemin donnee : %s\n\n", __FILE__, __LINE__, path) ;
    system("pause") ;
    fflush(NULL) ;
    isDirectory = 0 ;
	}
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
        }else{
          strcpy(listFiles[*count - 1], lecture->d_name) ;
          printf("listFiles[%d] : %s\n",  (*count - 1), listFiles[*count - 1]) ;
        }
      }
    }
 }else{
   fprintf(stderr, "file : %s , ligne:%d\nle chemin du dossier donner en parametre n'est pas correct !!!\nChemin donnee : %s\n\n", __FILE__, __LINE__, path) ;
   system("pause") ;
   fflush(NULL) ;
 }
 closedir(directory);
 return listFiles ;
}

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
	return defaultConfFile ;

}
