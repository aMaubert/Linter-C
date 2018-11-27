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


void nbLine (int nb,FILE * f){
  printf("------------------------------\n");
  printf("Regle Nombre de ligne maximum dans un fichier :\n\n");
  int counter = 0 ;

  char CurrentLine[248];
  int dif=0;
  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
      counter++;
  }
  if(counter > nb)
    {
      dif = counter - nb;
      printf("Nombre de ligne dépassé : %d ligne(s) de trop. \n", dif);
    }
  else
    {
      printf("Le nombre de ligne est correct. \n");
    }
    rewind(f);
}