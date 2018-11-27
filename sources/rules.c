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

void array_bracket_eol(FILE* f){
    printf("------------------------------\n");
    printf("Regle Accolade :\n\n");
    char Currentligne[258];
    char *Alllignes[258];
    char functions[][10] = {"if","while","for","do","void","int"};
    //char *lignes;


    //while(c)
    int errorBracket = 0;
    int j = 1;
    bool Iscomm = false;
     while(fgets(Currentligne, sizeof(Currentligne), f) != NULL){
        Alllignes[j] = Currentligne;
          for(int i =0; i < strlen(Currentligne); i++){

          if(Iscomm == true)        //Si commentaire
          {
            while ((Currentligne[i] != '*' && Currentligne[i+1] != '/') && i <= strlen(Currentligne))
            {
              i++;
            }

            if(Currentligne[i] == '*' && Currentligne[i+1] == '/'){       //Sortie commentaire
              Iscomm = false;
            }

          }

          else if(Currentligne[i] == '/' && Currentligne[i+1] == '*')       // Si commentaire
          {
            Iscomm = true;
            i = i+2;

            while ((Currentligne[i] != '*' && Currentligne[i+1] != '/') && i < strlen(Currentligne)) // Tan quon est dans le commentaire
            {
              i++;
            }
            if(Currentligne[i-1] == '*' && Currentligne[i] == '/')                      // Si sortie du commentaire
            {
              Iscomm = false;
            }
            else Iscomm = true;
          }
          int k = 0;
          while(strstr(Currentligne,functions[k]) == NULL && k < 5)
          {
            k++;
          }
          if((strstr(Currentligne,functions[k]) != NULL) && Iscomm == false)          // Si fonction presente
          {
               if(Currentligne[i] == '{' && i != (strlen(Currentligne)-2)){           // Si accolade presente sur la ligne
                errorBracket++;
                printf("Erreur d'accolade à la ligne %d \n \n", j);
              }
          }
        else  if(Currentligne[i] == '{'){
          printf("Erreur d'accolade à la ligne %d \n \n", j); // Si accolade pas sur ligne fonction
          errorBracket++;
        }
        }
        j++;

      }
      rewind(f);
      if(errorBracket == 0)printf("Aucune erreur de syntaxe.\n");
}