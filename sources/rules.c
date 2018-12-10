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


void no_trailing_spaces(FILE* f){
      printf("------------------------------\n");
      printf("Regle Pas d'espace en fin de ligne :\n\n");
      int line = 1;
      char CurrentLine[258];
      bool Iscomm = false;
      int errorTrailing = 0;

      while(fgets(CurrentLine, sizeof(CurrentLine), f) != NULL){
           for(int i = 0; i < strlen(CurrentLine); i++){
            if(CurrentLine[i] == '/' && CurrentLine[i+1] == '*')
            {
             Iscomm = true;
             i = i + 2;
            }

            if(Iscomm == true)        //Si commentaire
            {
              while ((CurrentLine[i] != '*' && CurrentLine[i+1] != '/') && i <= strlen(CurrentLine))
              {
                i++;
              }

              if(CurrentLine[i] == '*' && CurrentLine[i+1] == '/'){    //Sortie commentaire
              Iscomm = false;
              i++;
              }
            }
          }

          int lastc = strlen(CurrentLine) - 2;
          if(CurrentLine[lastc] == ' ' && Iscomm == false){
            errorTrailing++;
            printf("Erreur de syntaxe à la ligne %d\n", line);
          }
          line ++;
        }
        
      rewind(f);
      if(errorTrailing == 0) printf("Aucune erreur de syntaxe.\n");
}