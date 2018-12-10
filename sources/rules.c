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
  f = fopen("C:\\Users\\Ordinateur\\Desktop\\projet\\test\\test.c", "r");
  if( f != NULL){
    printf("Fichier bien ouvert\n");
    char CurrentLine[258];
    char *Alllignes[258];
    char functions[][10] = {"if","while","for","do","void","int"};
    //char *lignes;


    //while(c)
int j = 1;
bool Iscomm = false;
   while(fgets(CurrentLine, sizeof(CurrentLine), f) != NULL){
      Alllignes[j] = CurrentLine;
        for(int i =0; i < strlen(CurrentLine); i++){

        if(Currentligne[i] == '/' && Currentligne[i+1] == '/'){
          fgets(Currentligne, sizeof(Currentligne), f);
          line++;
        }
        if(Iscomm == true)        //Si commentaire
        {
          while ((CurrentLine[i] != '*' && CurrentLine[i+1] != '/') && i <= strlen(CurrentLine))
          {
            i++;
          }

          if(CurrentLine[i] == '*' && CurrentLine[i+1] == '/'){       //Sortie commentaire
            Iscomm = false;
          }

        }

        else if(CurrentLine[i] == '/' && CurrentLine[i+1] == '*')       // Si commentaire
        {
          Iscomm = true;
          i = i+2;

          while ((CurrentLine[i] != '*' && CurrentLine[i+1] != '/') && i < strlen(CurrentLine)) // Tan quon est dans le commentaire
          {
            i++;
          }
          if(CurrentLine[i-1] == '*' && CurrentLine[i] == '/')                      // Si sortie du commentaire
          {
            Iscomm = false;
          }
          else Iscomm = true;
        }
        int k = 0;
        while(strstr(CurrentLine,functions[k]) == NULL && k < 5)
        {
          k++;
        }
        if((strstr(CurrentLine,functions[k]) != NULL) && Iscomm == false)          // Si fonction presente
        {
             if(CurrentLine[i] == '{' && i != (strlen(CurrentLine)-2)){           // Si accolade presente sur la ligne
              printf("Erreur d'accolade ligne %d \n \n", j);
            }
        }
      else  if(CurrentLine[i] == '{') printf("Erreur d'accolade ligne %d \n \n", j); // Si accolade pas sur ligne fonction
      }
      j++;

    }
    printf("Lors de l'appel d'une fonction,\nl'accolade doit etre precédée de la fonction et suivi du retour à la ligne.");

  }
    fclose(f);
  }
