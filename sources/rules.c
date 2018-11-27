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


void oneVariable (FILE * f){
  printf("------------------------------\n");
  printf("Regle Declaration d'une seule variable maximum par ligne :\n\n");
  int counter=0;
  int errorVar = 0;
  char CurrentLine[248];
  char tab[][100]={"int","char","float","short","double","long"};

  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
  
      int j=0;
      counter++;
      
      while(strstr(CurrentLine,tab[j])==NULL && j<5)
      {
        j++;
      }
      if(strstr(CurrentLine,tab[j])!=NULL)
      {
        
        for(int i=0;i<strlen(CurrentLine);i++)
        {
          if(CurrentLine[i]==',' && strstr(CurrentLine,"(")==NULL)
          {
            printf("Nombre de déclaration de variable dépassé à la ligne %d\n",counter);
            errorVar++;
          }
        }
      }
  }
  rewind(f);
  if(errorVar == 0) printf("Aucune erreur de syntaxe.\n");
}