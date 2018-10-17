CC= gcc        # compilateur
CFLAGS= -Wall  # options de compilation pour les sources C

sources= sources/main.c sources/config.c


Linter-C:
	gcc -o bin\Linter-C -Wall $(sources)
	bin\Linter-C
