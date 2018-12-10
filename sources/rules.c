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

void operatorsSpacingRule(FILE * f){
  int line = 1;
  char CurrentLine[258];
  char type[][100]={"FILE","int","char","float","short","double","long"};
  bool Iscomm = false;
  int errorOperator = 0;
   while(fgets(CurrentLine, sizeof(CurrentLine), f) != NULL){
    for(int i = 0; i < strlen(CurrentLine); i++){
      if(CurrentLine[i] == '/' && CurrentLine[i+1] == '/'){
        fgets(CurrentLine, sizeof(CurrentLine), f);
          line++;
      }
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
          fgets(CurrentLine, sizeof(CurrentLine), f);
          line++;
          Iscomm = false;
          i++;
        }
      }
      int erreur = 0;
      /* Test equals operator */
      if(CurrentLine[i] == '=' && Iscomm == false){
         if((CurrentLine[i+1] != ' ' && CurrentLine[i+1] != '=')||(CurrentLine[i-1] != ' '&& CurrentLine[i-1] != '='&& CurrentLine[i-1] != '-'&& CurrentLine[i-1] != '+'&& CurrentLine[i-1] != '/'&& CurrentLine[i-1] != '*'&& CurrentLine[i-1] != '%')){
          erreur ++;
        }
      }
      /* Test addition operator */
      else if((CurrentLine[i] == '+' && Iscomm == false)&&(CurrentLine[i-1]!='+') && (CurrentLine[i+1]!='+')){
            if((CurrentLine[i+1] != ' ' && CurrentLine[i+1] != '=') ||(CurrentLine[i-1] != ' ')){
                    erreur++;
            }
      }
     /* Test soustraction operator */
      else if ((CurrentLine[i] == '-' && Iscomm == false)&&(CurrentLine[i-1]!='-') && (CurrentLine[i+1]!='-')){
        if((CurrentLine[i+1] != ' ' && CurrentLine[i+1] != '=')||(CurrentLine[i-1] != ' ')){
            erreur++;
        }
      }
      /* Test ultiplication and division operator */
      else if ((CurrentLine[i] == '*' && Iscomm == false)||(CurrentLine[i] == '/' && Iscomm == false)||(CurrentLine[i] == '%' && Iscomm == false)){
            int isTypeBefore = 0;
            if(CurrentLine[i] == '*'){
              char beforeStar[258];
              int t = i-1;
              int nbCharacteres = 0;
              while((CurrentLine[t] != ' ' & CurrentLine[t] != '(')&& t > 0){
                nbCharacteres++;
                t--;
              }
              if( t == 0) nbCharacteres++;
              if(CurrentLine[t] == ' ') t++;

              beforeStar[nbCharacteres] = '\0';
              for(int k = 0; k < nbCharacteres; k ++){
                beforeStar[k] = CurrentLine[t+k];
              }

              for(int j=0;j < 6;j++){

               if(strcmp(beforeStar,type[j])){
                  isTypeBefore++;
                } 
                
              }
            }
            if((CurrentLine[i+1] != ' ' && CurrentLine[i+1] != '=')||(CurrentLine[i-1] != ' ') && isTypeBefore == 0){
                erreur++ ;
            }
      }
      if(erreur > 0){
        char message[512] ;
        printf("Erreur de syntaxe : %d erreur(s) ligne %d\n", erreur, line);
       // sprintf(message, "Regle : Operators_Spacing\nIl y a %d erreur(s) de syntaxe à la ligne %d du fichier  .\n", erreur, line) ;
        //messageLog(logger, message) ;
        errorOperator++;
      }
    }
     line ++;
  }
  rewind(f);
}