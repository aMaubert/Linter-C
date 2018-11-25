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

 void indentRule( Logger* logger, char* pathFile, int indent){
   int currentIndent = 0 ;
   int countLine = 0 ;
   char line[1024] ;
   FILE* inputFile = fopen(pathFile, "r") ;


   if(inputFile != NULL){
     while(fgets(line, sizeof(line), inputFile) != NULL){
       countLine += 1 ;


       // On verifie si l'indentation de la ligne courante est bonne
       if(reverseIndentNextLine(line)){ // si on ferme un bloc avec le '}', le nombre d'intentation est de  (currentIndent - indent)
         short goodIndent = isIndent(line, currentIndent - indent) ;
         if(goodIndent == 0){
           char message[1024] ;
           sprintf(message, "mauvaise indention à la ligne : %d  du fichier %s\nLa bonne indentation a cette ligne est de %d espace(s) !\n\n", countLine, pathFile, (currentIndent - indent) ) ;
           messageLog(logger, message) ;
         }
       }else{
         short goodIndent = isIndent(line, currentIndent) ;
         if(goodIndent == 0){
           char message[1024] ;
           sprintf(message, "mauvaise indention à la ligne : %d  du fichier %s\nLa bonne indentation a cette ligne est de %d espace(s) !\n\n", countLine, pathFile, currentIndent) ;
           messageLog(logger, message) ;
         }
       }


       if(indentNextLine(line)) currentIndent += indent ; // lorsque l'ouvre un bloc d'instruction avec le '{', l'indentation courrant augmente de indent unité d'espaces
       else if(reverseIndentNextLine(line)) currentIndent -= indent ;// lorsque l'ouvre un bloc d'instruction avec le '}', l'indentation courrant diminue de indent unité d'espaces

     }

   }else{
     fprintf(stderr, "Impossible d'ouvrir le fichier %s  en lecture\n",pathFile );
     pause() ;
     fflush(NULL) ;
     exit(EXIT_FAILURE) ;
   }
   fclose(inputFile) ;

 }
/*
 * return 1 if the current line is indented, else return 0 ;
 */
short isIndent(char* line, int currentIndent){
  char c ;
  int indexLine = 0 ;
  int indentLine = 0 ;
  do{
    c = line[indexLine] ;
    if(c == ' '){
      indentLine += 1 ;
      indexLine += 1 ;
    }
  }while(c == ' ') ;
  if(indentLine == currentIndent) return 1 ;
  else return 0 ;
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
