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

#include <stdbool.h>

/*
 * Define the caracteristic f a fonction
 */
typedef struct Function{
  char* returnType ;
  char* name ;
  bool defined ;
  char* listParameters  ;
}Function ;


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
  RuleLinter** listRules ;
  int countExcludedFiles ;
  char** listExcludedFiles ;
  short recursive ; // 1 if recursive, else 0
}ConfigLinter ;

// structure Function
Function* getInitializedFunction() ;
void setFunction(Function* FunctionToSet, char* returnType, char* name, bool defined, char* listParameters) ;
void freeFunction(Function* FunctionToFree) ;

// structure ruleLinter
void displayListRuleLinter(RuleLinter** listRuleLinter, int countRules) ;
void freeRuleLinter(RuleLinter* ruleLinter) ;

//structure ConfigLinter
void displayLinterConfig(ConfigLinter* linterConfig) ;


int getCountExcludedFilesNotAlreadyExisted(ConfigLinter* linterConfiguration,int countExcludedFiles, char** listExcludedFiles) ;
int getCountRulesNotAlreadyExisted(ConfigLinter* linterConfiguration,int countRules, char** listKey) ;

short reallocateListRules(ConfigLinter* linterConfiguration, int countRulesToReallocate, char** listKey, char** listValue, int countRules ) ;
short reallocateListExcludedFiles(ConfigLinter* linterConfiguration, int countExcludedFilesToReallocate, char** listExcludedFiles,  int countExcludedFiles ) ;

void setListRules(ConfigLinter* linterConfiguration, char** listKey, char** listValue, int countRules) ;
void setListExcludedFiles(ConfigLinter* linterConfiguration, char** listExcludedFiles, int countExcludedFiles) ;

ConfigLinter* getInitializedConfigLinter() ;
ConfigLinter* getConfigLinter(ConfigLinter* linterConfiguration, char* fileExtend, int countRules,
   char** listKey, char**listValue, int countExcludedFiles, char** listExcludedFiles, short recursive) ;

short isAnexcludedFile(ConfigLinter* linterConfig, char* currentFile) ;


#endif // STRUCTURE_HEADER_INCLUDED_
