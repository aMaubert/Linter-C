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


void unused_variable(FILE* f){
  printf("------------------------------\n");
  printf("Regle Presence de variable inutile :\n\n");
  int counter=0;
  int errorVar = 0;
  char CurrentLine[248];
   char *Variables[258];
   char CurrentVariable[258];
   char* CurrentCarVariable;
   int posCurrentVariable = 0;
   int variableNumber = 0;
  char type[][100]={"int ","char ","float ","short ","double ","long "};
  char Minletters[][1]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  char Majletters[][1]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){ // tant que ligne courrante possede du contenu
     
      int j=0;                                              // index du tableau "type" qui possede chaque type (int,char,double ....)
      counter++;                                            // numero de la ligne
     
      while(strstr(CurrentLine,type[j])==NULL && j<5)       // recherche d'un type sur la ligne courrante
      {
        j++;
      }
      
      if(strstr(CurrentLine,type[j])!=NULL)                 // si presence d'un type
      {
        
        if(strstr(CurrentLine,"(") == NULL){                // si non presence d'une parenthese
        CurrentCarVariable = strstr(CurrentLine, type[j]);     // chaine de caractere recuperant le contenu de la ligne courante en commencant par le type.
        int index = 0;                                      // index de la chaine
        while(CurrentCarVariable[index] != ' '){                      // passer le type
         
          index ++;
        }
       
        while(CurrentCarVariable[index] == ' '){                      // permet d'avoir comme premier caractere le premier caractere de la variable
         
          index ++;
        }
       
        int CaraNumber = 1;                                 //Affiche le nombre de caractere de la variable déclarée
        CurrentCarVariable += index;
        index = 0;
        while(CurrentCarVariable[index] != ',' && CurrentCarVariable[index] != ';' && CurrentCarVariable[index] != ' ' && CurrentCarVariable[index] != '='  && index < strlen(CurrentCarVariable)){
           //Tant que variable[index] appartient a la variable
           //printf("caracteres %c\n",CurrentCarVariable[index]);
          index++;
          CaraNumber++;

        }
        
        CurrentCarVariable[index] = '\0';
        CaraNumber += 1;
        if(CaraNumber> 1) CaraNumber = CaraNumber - 1;
        strncpy(CurrentVariable, CurrentCarVariable,CaraNumber); // ajouter la variable aux tableaux de toutes les variables declarées
        Variables[posCurrentVariable] = CurrentVariable;
         //strcat(Variables[posCurrentVariable], " ");
         //strcat(Variables[posCurrentVariable] , CurrentVariable);
       //   printf("1");
       printf("%s\n", Variables[posCurrentVariable]);
       variableNumber++;

        posCurrentVariable++;
      }
      }
  }
  rewind(f);
  
  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
    int isType = 0;
    for(int i = 0; i < variableNumber; i++){
      if (strstr(CurrentLine, Variables[i]) != NULL){
        for(int j = 0; j < 5; j ++){
          if(strstr(CurrentLine,type[j]) != NULL){
            isType++;
          }
        }
        if(isType == 0){
          char* CurrentVariableOnLine = strstr(CurrentLine,Variables[i]);
          

        }
      }
    }

  }

  if(errorVar == 0) printf("Aucune erreur de syntaxe.\n");
}
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
  if(errorVar == 0) printf("Aucune erreur de syntaxe.\n");
}