/*
============================================================================
	Name        : structure.h
	Author      : amaubert
	Created on  : 2018/11/07
	Version     :
	Copyright   : Your copyright notice
	Description : file that declare the structures used in this linter C
============================================================================
*/

#ifndef STRUCTURE_HEADER_INCLUDED_
#define STRUCTURE_HEADER_INCLUDED_


/*
  Define a rule with key -> value
*/
typedef struct RuleLinter{
  char* key ;
  char* value ;
}RuleLinter ;

typedef struct ConfigLinter{
  char* fileExtend ; // the lconf file that can to be extend
  int countRules ;
  int countAllocateRules ;
  RuleLinter** listRules ;
  int countExcludedFiles ;
  char** listExcludedFiles ;
  short recursive ; // 1 if recursive, else 0
}ConfigLinter ;

void displayListRuleLinter(RuleLinter** listRuleLinter, int countRules) ;
void displayLinterConfig(ConfigLinter* linterConfig) ;

ConfigLinter* getInitialisedConfigLinter() ;

void freeConfigLinter(ConfigLinter* linterConfiguration) ;
void freeRuleLinter(RuleLinter* ruleLinter) ;

RuleLinter* getRuleLinter(char* key, char* value) ;

void setFileExtend(ConfigLinter* linterConfiguration, char* fileExtend) ;
void setListRules(ConfigLinter* linterConfiguration, int countRules, char** listKey, char** listValue) ;
void setListExcludedFiles(ConfigLinter* linterConfiguration, int countExcludedFiles, char** listExcludedFiles) ;
void setRecursive(ConfigLinter* linterConfiguration, short recursive) ;

RuleLinter** realloclistRuleLinter(RuleLinter** listToResize, int oldSize, int newSize) ;

void copyRule(RuleLinter* ruleToModify, RuleLinter* ruleToCopy) ;



#endif // STRUCTURE_HEADER_INCLUDED_
