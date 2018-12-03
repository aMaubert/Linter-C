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
#include "headers/codingConventionRules.h"
#include "headers/interface.h"

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
         sprintf(message, "mauvaise indention à la ligne : %d  du fichier %s\nLa bonne indentation a cette ligne est de %d espace(s)/tabulation(s)  !\n\n", countLine, fileName, (currentIndent - indent) ) ;
         messageLog(logger, message) ;
       }
     }else{ // sinon on verifie l'indention courrant
       short goodIndent = isIndent(line, currentIndent) ;
       if(goodIndent == 0){ // si goodIndent vaut 0, cela veut dire que l'indentation est mauvaise, il faut le repporté dans les logs
         char message[1024] ;
         sprintf(message, "mauvaise indention à la ligne : %d  du fichier %s\nLa bonne indentation a cette ligne est de %d espace(s)/tabulation(s) !\n\n", countLine, fileName, currentIndent) ;
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
      sprintf(message, "Nombre de caracteres limites depasses (%d), a la ligne %d du fichier %s\n", nb, counter, fileName) ;
      messageLog(logger, message) ;
    }

  }
  rewind(f);
}
