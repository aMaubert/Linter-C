CC= gcc        # compilateur
CFLAGS= -Wall  # options de compilation pour les sources C

sources= sources/main.c sources/config.c

headers= sources/headers/config.h

Linter-C:
	gcc -o bin\Linter-C -Wall $(sources) $(headers)
