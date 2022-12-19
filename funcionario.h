/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   funcionario.h
 * Author: Alunos
 *
 * Created on 22 de Setembro de 2022, 15:13
 */

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* FUNCIONARIO_H */

typedef struct {
    int codigo;
    char nome[30];
    char cargo[30];
    char endereco[60];
    char telefone[17];
    char email[40];
} funcionario;


// função responsável por cadastrar funcionários
void cadastro_func(funcionario *funcC, int *c_func, int *tamFunc, int tipoDado);

// função responsável por gravar dados dos funcionários nos arquivos txt ou bin
void gravar_func(funcionario *funcC, int i, int tipoDado);

// função responsável por gravar dados dos funcionários nos arquivos txt ou bin após alterações
void regravar_func(funcionario *funcC, int k, int tipoDado);

// função responsável por tratar e limpar caracteres indesejados no final de strings
void limpaString_func(char *a);

// função responsável por carregar dados dos funcionários dos arquivos txt ou bin
void carregarFunc(funcionario **funcC, int *c_func, int *tamFunc, int tipoDado);

// função responsável por listar funcionarios cadastrados
void lista_func(funcionario *funcC, int c_func);

// função responsável por excluir funcionarios
void remove_func(funcionario *funcC, int *c_func);

// função responsável por imprimir menu tela
void menufunc();

// função responsável por alterar dados de funcionarios
void mudar_func(funcionario *funcC, int c_func);