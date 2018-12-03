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
#include <stdbool.h>
#include <string.h>
#include "headers/linter.h"

void test() ;

int main(int argc, char* argv[]) {

  startLinter(argc, argv) ;
  return (EXIT_SUCCESS);
}

/*
 * test Function
 */
void test(){
  Logger* logger = initialiseLogger("D:\\ESGI\\projets pedagogique ESGI\\Linter-C\\test") ;
  FILE* inputFile = fopen("D:\\ESGI\\projets pedagogique ESGI\\Linter-C\\test\\testMaxLineNumbers.c", "r") ;
  if (inputFile != NULL){
    maxLineNumbersRule(logger, inputFile, 10) ;
  }

  fclose(inputFile) ;


}
