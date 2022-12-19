cmake_minimum_required(VERSION 3.23)
project(Projeto_Locadora C)

set(CMAKE_C_STANDARD 11)

add_executable(Projeto_Locadora main.c categoria.c categoria.h filme.c filme.h cliente.c cliente.h funcionario.c funcionario.h fornecedor.c fornecedor.h locadora.c locadora.h funcGlobais.c funcGlobais.h feedback.c feedback.h export.c export.h)
