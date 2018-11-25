/*
 ============================================================================
 Name        : codingConventionRules.h
 Author      : Allan Maubert
 Created on	 : 2018/10/25
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#ifndef CODING_CONVENTION_RULES_HEADER_INCLUDED_
#define CODING_CONVENTION_RULES_HEADER_INCLUDED_

#include "logger.h"

void indentRule( Logger* logger, char* pathFile, int indent) ;
short indentNextLine(char* line) ;
short reverseIndentNextLine(char* line) ;
short isIndent(char* line, int currentIndent) ;


#endif /* CODING_CONVENTION_RULES_HEADER_INCLUDED_ */
