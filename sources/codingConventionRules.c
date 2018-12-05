/*
 ============================================================================
 Name        : codingConventionRules.c
 Author      : Allan Maubert
 Created on	 : 2018/10/25
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "headers/codingConventionRules.h"
#include "headers/interface.h"
/*
 * Indent rule
 */
 void indentRule( Logger* logger, FILE* inputFile, int indent, char* fileName){
   int currentIndent = 0 ;
   int countLine = 0 ;
   char line[50000] ;

   while(fgets(line, sizeof(line), inputFile) != NULL){
     countLine += 1 ;
     // On verifie si l'indentation de la ligne courante est bonne
     if(reverseIndentNextLine(line)){ // si on ferme un bloc avec le '}', le nombre d'intentation est de  (currentIndent - indent)
       short goodIndent = isIndent(line, currentIndent - indent) ;
       if(goodIndent == 0){
         char message[1024] ;
         sprintf(message, "Regle : indent\nMauvaise indention à la ligne : %d  du fichier %s\nLa bonne indentation a cette ligne est de %d espace(s)/tabulation(s)  !\n\n", countLine, fileName, (currentIndent - indent) ) ;
         messageLog(logger, message) ;
       }
     }else{ // sinon on verifie l'indention courrant
       short goodIndent = isIndent(line, currentIndent) ;
       if(goodIndent == 0){ // si goodIndent vaut 0, cela veut dire que l'indentation est mauvaise, il faut le repporté dans les logs
         char message[1024] ;
         sprintf(message, "Regle : indent\nMauvaise indention à la ligne : %d  du fichier %s\nLa bonne indentation a cette ligne est de %d espace(s)/tabulation(s) !\n\n", countLine, fileName, currentIndent) ;
         messageLog(logger, message) ;
       }
     }

     if(indentNextLine(line)) currentIndent += indent ; // lorsque l'ouvre un bloc d'instruction avec le '{', l'indentation courrant augmente de indent unité d'espaces
     else if(reverseIndentNextLine(line)) currentIndent -= indent ;// lorsque l'ouvre un bloc d'instruction avec le '}', l'indentation courrant diminue de indent unité d'espaces

   }

   rewind(inputFile) ;

 }
/*
 * return 1 if the current line is indented correctly (the indent is with spaces or Tabulations), else return 0 ;
 */
short isIndent(char* line, int currentIndent){
  char c ;
  int indexLine = 0 ;
  int countSpaces = 0 ;
  int countTabulations = 0 ;

  // si l'indentation a été faite avec des espaces
  do{
    c = line[indexLine] ;
    if(c == ' '){
      countSpaces += 1 ;
      indexLine += 1 ;
    }
  }while(c == ' ') ;
  if(countSpaces == currentIndent) return 1 ;

  // si l'indentation a été faite avec des tabulations
  indexLine = 0 ;
  do{
    c = line[indexLine] ;
    if(c == '\t'){
      countTabulations += 1 ;
      indexLine += 1 ;
    }
  }while(c == '\t') ;
  if(countTabulations == currentIndent) return 1 ;

  return 0 ;
}
short indentNextLine(char* line){
   if(strstr(line, "{\n") != NULL) return 1 ;
   else if(strstr(line, "{//") != NULL) return 1; // dans le cas où l'on a un commentaire monoligne
   return 0 ;
 }

short reverseIndentNextLine(char* line){
  if(strstr(line, "}\n") != NULL) return 1 ;
  else if(strstr(line, "}//") != NULL) return 1; // dans le cas où l'on a un commentaire monoligne
  return 0 ;
}

/*
 * Max_line_numbers Rule
 */
void maxLineNumbersRule(Logger* logger, FILE * f, int nb, char* fileName){

  int counter=0;
  char CurrentLine[50000];
  char message[1024] ;
  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
    counter++;
    if ( strlen(CurrentLine) > nb){
      sprintf(message, "Regle : Max_line_numbers\nNombre de caracteres limites depasses (%d), a la ligne %d du fichier %s\n", nb, counter, fileName) ;
      messageLog(logger, message) ;
    }

  }
  rewind(f);
}

/*
 * Max_File_Line_Numbers rule
 */
void maxFileLineNumbersRule(Logger* logger, FILE * f, int nb, char* fileName){
  int counter = 0 ;
  char CurrentLine[50000];
  int dif=0;
  while(fgets(CurrentLine, sizeof(CurrentLine), f) !=NULL){
      counter++;
  }
  if(counter > nb){
    dif = counter - nb;
    char message[1024] ;
    sprintf(message, "Regle : Max_File_Line_Numbers\nLe maximum de lignes etant de %d .\nIl y a %d ligne(s) de trop, dans le fichier : %s .\n", nb, dif, fileName) ;
    messageLog(logger, message) ;
  }

    rewind(f);
}

/*
 * Array_Bracket_Eol rule
 */
void arrayBracketEolRule(Logger* logger, FILE * f, char* fileName){
  char Currentligne[50000];
  char functions[][10] = {"if","while","for","do","void","int"};
  int j = 1;
  bool Iscomm = false;

  while(fgets(Currentligne, sizeof(Currentligne), f) != NULL){

      for(int i = 0; i < strlen(Currentligne); i++){

        if(Iscomm == true)        //Si commentaire
        {
          while ((Currentligne[i] != '*' && Currentligne[i+1] != '/') && i <= strlen(Currentligne))
          {
            i++;
          }
          if(Currentligne[i] == '*' && Currentligne[ i + 1 ] == '/'){       //Sortie commentaire
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
               char message[512] ;
               sprintf(message, "Regle : Array_Bracket_Eol\nl'accolade ouvrante '{' ne se trouve pas en fin de ligne .\nDans le fichier %s , a la ligne : %d\n", fileName, j - 1) ;
               messageLog(logger, message) ;
            }
        }
      else  if(Currentligne[i] == '{'){ // Si accolade pas sur ligne fonction
        char message[512] ;
        sprintf(message, "Regle : Array_Bracket_Eol\nl'accolade ouvrante '{' ne se trouve pas en fin de ligne .\nDans le fichier %s , a la ligne : %d\n", fileName, j - 1) ;
        messageLog(logger, message) ;
      }
    }
    j++;

  }
}
/*
 * Operators-Spacing rule
 */
void operatorsSpacingRule(Logger* logger, FILE * f, char* fileName){
  int line = 1;
  char Currentligne[50000];
  bool Iscomm = false;
  int errorOperator = 0;

  while(fgets(Currentligne, sizeof(Currentligne), f) != NULL){
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
      int erreur = 0;
      if(Currentligne[i] == '=' && Iscomm == false){

        if(Currentligne[i+1] != ' '){
          erreur ++;
        }
        if(Currentligne[i-1] == '+' |Currentligne[i-1] == '-'|Currentligne[i-1] == '*'|Currentligne[i-1] == '/' ){
          if(Currentligne[i-2] != ' '){
            erreur ++;
          }
        }
        else if(Currentligne[i-1] != ' '){
          erreur ++;
        }
      }
      if(erreur > 0){
        char message[512] ;
        sprintf(message, "Regle : Operators_Spacing\nIl y a %d erreur(s) de syntaxe à la ligne %d du fichier %s .\n", erreur, line, fileName) ;
        messageLog(logger, message) ;
        errorOperator++;
      }
    }

    line ++;
  }
  rewind(f);
}
