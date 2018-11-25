/*
 ============================================================================
 Name        : interface.c
 Author      : Allan Maubert
 Created on	 : 2018/10/25
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include "headers/interface.h"


 void pause(){
   printf("Appuyer sur une touche pour continuer ...") ;

   fflush(stdout) ;
   getchar() ;
 }
