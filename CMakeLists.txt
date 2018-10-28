# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté hello
project(linter C)

# Crée des variables avec les fichiers à compiler
set(SRCS_PATH
    sources
    )

set(HEADERS_PATH
    ${SRCS_PATH}/headers
    )
set(BUILD_PATH
    bin
    )

set(SRCS
    ${SRCS_PATH}/main.c
    ${SRCS_PATH}/config.c
    ${SRCS_PATH}/logger.c
    ${SRCS_PATH}/linter.c
    )

set(HEADERS
    ${HEADERS_PATH}/config.h
    ${HEADERS_PATH}/linter.h
    ${HEADERS_PATH}/logger.h
    )

set(binary
    linterC
    )

# On indique que l'on veut un exécutable "linterC" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable( ${binary} ${SRCS} ${HEADERS})
