/*
============================================================================
	Name        : argument.h
	Author      : amaubert
	Created on  : 2018/11/01
	Version     :
	Copyright   : Your copyright notice
	Description :
============================================================================
*/

#ifndef CONFIGURATION_HEADER_CONFIG_H_
#define CONFIGURATION_HEADER_CONFIG_H_

#include "logger.h"

idArgument(Logger* logger, int argc, char** argv) ;
bool isDirectory(Logger* logger, char* path) ;

#endif /* CONFIGURATION_HEADER_CONFIG_H_ */
