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
  bool Iscomm = false;
  bool isExist = false;
  char CurrentLine[248];
   char *Variables[258];
   char CurrentVariable[258];
   char* CurrentCarVariable;
   int posCurrentVariable = 0;
   int variableNumber = 0;
   char operator[6]={'+','-','*','/','=','%'};
  char type[][100]={"int ","char ","float ","short ","double ","long "};
  char Minletters[][1]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  char Majletters[][1]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){ 
    counter++;  

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
            else{
            int j=0;                                              // index du tableau "type" qui possede chaque type (int,char,double ....)
                                                    
           
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
              
              strncpy(CurrentVariable, CurrentCarVariable,CaraNumber); 
              printf("CurrentVariable %s\n", CurrentVariable);
              for(int i = 0; i < variableNumber; i++){
                printf("variables 1 %s\n", Variables[i]);
              }
              printf("position : %d\n", posCurrentVariable);
              printf("\n");
              if(posCurrentVariable == 0){                
                printf("entre\n");
                Variables[posCurrentVariable] = CurrentVariable;                // Ajouter la variable aux tableaux de toutes les variabels
                posCurrentVariable ++;
                variableNumber++;
              }
              
              
              
            }
            }
            }
          }// tant que ligne courrante possede du contenu
     
     
  }
  rewind(f);
  Iscomm = false;
  counter = 0;
  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
    counter ++;

   for(int i = 0; i < strlen(CurrentLine); i++){
            if(CurrentLine[i] == '/' && CurrentLine[i+1] == '*')
            {
             Iscomm = true;
             i = i + 2;
            }

            if(Iscomm == true)        //Si commentaire
            {
              //printf("ligne %d\n", counter);
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
            if(Iscomm == false){
                int isType = 0;
                for(int i = 0; i < variableNumber; i++){
                  //printf("variable %s index %d\n", Variables[i], i);
                  if (strstr(CurrentLine, Variables[i]) != NULL){

                    for(int j = 0; j < 5; j ++){
                     if(strstr(CurrentLine,type[j]) != NULL){
                      isType++;
                      }
                    }
                  if(isType == 0){
                    char* CurrentVariableOnLine = strstr(CurrentLine,Variables[i]);
                    int posVar = str_istr(CurrentLine,Variables[i]);
                    int isOperator = 0;

                    for(int i = 0 ; i < 5; i++){
                      if(posVar > 0){
                        /*printf("%c\n",CurrentLine[posVar - 1]);
                        printf("ope %c\n", operator[i]);*/
                          if(CurrentLine[posVar - 1] == operator[i]){
                            isOperator++;
                          }
                      }       
                    }
                    //printf("%d ligne %d\n", isOperator,counter);
                    if(posVar > 0){
                      if(isOperator == 0){
                        if(CurrentLine[posVar - 1] == ' '){
                          for(int i = 0; i < 5; i++){
                            if(CurrentLine[posVar + strlen(Variables[i])] == operator[i]){
                              isOperator ++;
                            }
                          }
                          if(isOperator == 0 && CurrentLine[posVar + strlen(Variables[i])] == ' '){
                            //printf("Variable utilisé ligne %d\n",counter);
                          }
                        }
                        

                        
                      }
                    }

          /*char* IsVariable = malloc(sizeof(char));
          IsVariable = strncat(IsVariable,CurrentVariableOnLine,strlen(Variables[i]));
          //printf("%s\n", Variables[i]);
          printf("contenu %s\n", CurrentLine);
          printf("a %s ligne %d\n", IsVariable,counter);*/
          

          

        }
      }
    }
            }
          


  }

  if(errorVar == 0) printf("Aucune erreur de syntaxe.\n");
}