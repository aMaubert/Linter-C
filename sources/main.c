/*
 ============================================================================
 Name        : main.c
 Author      : Allan Maubert
 Created on	 : 2018/10/15
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/linter.h"
#include "headers/VariableAndFunctionRules.h"

int main(int argc, char* argv[]) {
  int count ;
  char** listSplitted = strSplit("int c, void* dest, char** listArray", 'c', &count) ;

  for(int i = 0 ; i < count ; i++) printf("%s\n", listSplitted[i]) ;
  // FILE* fileInput = fopen("D:\\ESGI\\projets pedagogique ESGI\\Linter-C\\test\\testPrototypeFunction.c", "r") ;
  // char line[1024] ;
  // if(fileInput != NULL){
  //   while( fgets(line, sizeof(line), fileInput) != NULL){
  //     isADefinedFunction(line) ;
  //   }
  //
  // }

  //startLinter(argc, argv) ;
  // fclose(fileInput) ;
  return (EXIT_SUCCESS);
}
