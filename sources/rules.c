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


void comments_header(FILE* f){
    printf("------------------------------\n");
    printf("Regle Présence d'un commentaire multi-ligne:\n\n");
    int line = 1;
    int afterComm = 0;
    int isCommBefore = 0;
    char Currentligne[258];
    bool Iscomm = false;
    //fonction typeof

       while(fgets(Currentligne, sizeof(Currentligne), f) != NULL){
        int erreur = 0;
         for(int i = 0; i < strlen(Currentligne); i++){
          if(Currentligne[i] == '/' && Currentligne[i+1] == '*' && line == 1)
          {
            isCommBefore = 1;
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
          if(Iscomm == false && isCommBefore == 1)
          {
            if(Currentligne[i] != ' ') afterComm ++;
          }
        }
        line ++;
      }
      rewind(f);
      if(afterComm > 0) printf("La présence d'un commentaire multi-ligne en entete de fichier a été confirmé.\n");
      else printf("La présence d'un commentaire multi-ligne en entete de fichier n'a pas été confirmé.\n");
}