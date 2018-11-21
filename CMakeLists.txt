# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté Linter C
project(linter C)

file(
        GLOB_RECURSE

        source_files

      sources/*
)

set(binary
    linterC
    )

# On indique que l'on veut un exécutable "linterC" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable( ${binary} ${source_files} )

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(
    ${binary}
    ${PROJECT_SOURCE_DIR}/bin/regex2.dll
    )
