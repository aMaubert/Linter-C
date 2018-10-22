CC= gcc        # compilateur
CFLAGS= -Wall  # options de compilation pour les sources C

sources= sources/main.c sources/config.c sources/linter.c

headers= sources/headers/config.h sources/headers/linter.h

Linter-C:
	gcc -o bin\Linter-C -Wall $(sources) $(headers)
