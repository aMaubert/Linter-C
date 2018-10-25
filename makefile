CC= gcc        # compilateur
CFLAGS= -Wall  # options de compilation pour les sources C

sources= sources/main.c sources/config.c sources/linter.c sources/logger.c

headers= sources/headers/config.h sources/headers/linter.h sources/headers/logger.h

Linter-C:
	gcc -o bin\Linter-C -Wall $(sources) $(headers)
