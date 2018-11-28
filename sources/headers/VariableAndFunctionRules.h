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

#include <stdbool.h>
#include "structure.h"

Function* isAPrototypeFunction(char* line) ;
Function* isADefinedFunction(char* line) ;

bool isAKeyWord(char* array) ;
void skipVoidSpace(char* line, int* index) ;
bool caracterAlphaNumeric(char c) ;
bool isALoopOrCondition(char* instruction) ;
bool isAPrimitivType(char* type) ;

char** strSplit(char* array, char separator, int* countMatchs) ;

#endif /* VARIABLE_AND_FUNCTION_RULES_HEADER_INCLUDED_ */
