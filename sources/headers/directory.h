/*
============================================================================
	Name        : directory.h
	Author      : amaubert
	Created on  : 2018/11/23
	Version     :
	Copyright   : Your copyright notice
	Description :
============================================================================
*/
#ifndef DIRECTORY_HEADER_INCLUDED_
#define DIRECTORY_HEADER_INCLUDED_




short directoryExist( char* path) ;
char** getListFilesInDirectory(char* path, int* count) ;
char* getConfigFile(char* pathDirectory) ;
char** getListDirectory(char* pathDirectory, int* countDirectory) ;

#endif /* DIRECTORY_HEADER_INCLUDED_ */
