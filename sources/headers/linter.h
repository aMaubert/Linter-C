/*
 ============================================================================
 Name        : linter.h
 Author      : Allan Maubert
 Created on	 : 2018/10/22
 Version     :
 Copyright   : Your copyright notice
 Description : file that contents all the Linter's functionalities
 ============================================================================
 */

 #ifndef LINTER_HEADER_INCLUDED_
 #define LINTER_HEADER_INCLUDED_

 #include "logger.h"
 #include "structure.h"

 void startLinter(int argc, char** argv) ;
 void linting(ConfigLinter* linterConfig, char* pathDirectory) ;
 int getRuleNumber(char* RuleKey) ;
 void analyse( ConfigLinter* linterConfig, Logger* logger, char* currentFile) ;



 #endif /* LINTER_HEADER_INCLUDED_ */
