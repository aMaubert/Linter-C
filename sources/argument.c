/*
 ============================================================================
 Name        : argument.c
 Author      : Allan Maubert
 Created on	 : 2018/11/01
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "headers/argument.h"
#include "headers/directory.h"

short validArgument( int argc, char** argv){
 	short ret = 1 ;

 	if(argc == 2 ){
 		ret = directoryExist( argv[1]) ;
 	}else{
 		ret = 0 ;
 	}

 	return ret ;
}
