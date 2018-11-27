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


void coma_spacing(FILE* f){
    printf("------------------------------\n");
    printf("Regle Espace à droite d'une virgule :\n\n");
    int line = 1;
    char Currentligne[258];
    bool Iscomm = false;
    int errorSpace = 0;
    //fonction typeof

       while(fgets(Currentligne, sizeof(Currentligne), f) != NULL){
        int erreur = 0;
         for(int i = 0; i < strlen(Currentligne); i++){
          if(Currentligne[i] == '/' && Currentligne[i+1] == '*')
          {
           Iscomm = true;
           i = i + 2;
          }

          if(Iscomm == true)        //Si commentaire
          {
            while ((Currentligne[i] != '*' && Currentligne[i+1] != '/') && i <= strlen(Currentligne))
            {
              i++;
            }

            if(Currentligne[i] == '*' && Currentligne[i+1] == '/'){    //Sortie commentaire
            Iscomm = false;
            i++;
            }
          }
          
          if(Currentligne[i] == ','){
            if(Currentligne[i+1] != ' ') erreur++;
          }
        }
        if(erreur > 0){
          printf("%d erreur(s) de syntaxe à la ligne %d\n", erreur,line); 
          errorSpace++;
        } 
        line++;
     }
     rewind(f);
       if(errorSpace == 0) printf("Aucune erreur de syntaxe.\n");
}
