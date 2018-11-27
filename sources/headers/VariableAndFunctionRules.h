/*
============================================================================
	Name        : VariableAndFunctionRules.h
	Author      : amaubert
	Created on  : 2018/11/26
	Version     :
	Copyright   : Your copyright notice
	Description :
============================================================================
*/

#ifndef VARIABLE_AND_FUNCTION_RULES_HEADER_INCLUDED_
#define VARIABLE_AND_FUNCTION_RULES_HEADER_INCLUDED_

void undeclaredVariableRule( Logger* logger, char* pathFile) ;
char** listDefinedFunctions(char* pathFile, int* countFunctions) ;
short isAFunction(char* line) ;
short caracterAlphaNumeric(char c) ;

#endif /* VARIABLE_AND_FUNCTION_RULES_HEADER_INCLUDED_ */
