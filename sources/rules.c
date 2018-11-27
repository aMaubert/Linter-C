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
#include "string.h"
#include "rules.h"


/* Constantes symbolique */
#define __MAX_NUMBER_RULES__ 16
#define __MAX_CHAR_RULES__ 5
#define __SIZE_LINE__ 128
#define __SIZE_BUFFER__ 5000


void nbCharacteres(int nb,FILE * f){
  printf("------------------------------\n");
  printf("Regle Nombre de caracteres maximum par ligne :\n\n");
  printf("Nombre de caracteres autorisés : %d\n\n", nb);
  int counter=0;
  int errorLine = 0;
  char CurrentLine[248];
  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
    counter++;
    if (strlen(CurrentLine)>nb){
      printf("Nombre de caracteres dépassé à la ligne %d\n", counter);
      errorLine ++;
    }
  }
  rewind(f);
  if(errorLine == 0) printf("Le nombre de caracteres maximum par ligne n'a pas été dépassé.\n");
}