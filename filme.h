/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   filme.h
 * Author: Alunos
 *
 * Created on 22 de Setembro de 2022, 13:40
 */

#ifndef FILME_H
#define FILME_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* FILME_H */

#include "categoria.h"


typedef struct {
    int codigoFilme;
    char descricao[100];
    float valor;
    int exemplarFilme;
    int codigoCategoria;
    char lingua[10];
    int exLocados;
    int pendente;
} filme;

typedef struct{
    int dia;
    int mes;
    int ano;
}data;

typedef struct {
    float valorAntes;
    float valorDepois;
    float operacao;
    data dataOp;
} movimentacao;

typedef struct{
    int idOperacao;
    int idFornecedor;
    char razaoSocial[40];
    char cnpj[17];
    char nomeFilme[100];
    int ex;
    float valorFilme;
    float valorImposto;
    float valorFrete;
    float filmeTotal;
    float impostoTotal;
    float freteTotal;
    float precoFilme;
    float valorTotal;
    float valorDeve;
    int parcelas;
    data dataCompra;
    data dataPago;
}compra;

typedef struct{
    int idOperacao;
    int codFunc;
    int codCliente;
    int codFilme;
    char nomeFilme[100];
    int ex;
    int tipoPag; //1 avista   - 2 aprazo
    float valorTotal;
    float valorDeve;
    int parcelas;
    data dataLoc;
    data dataDev;
    data dataEntregue;
    int devolveu;
}operacoes;



// função responsável pelo cadastro de novos filmes
void cadastra_filme(filme *filmeC, int *c_filme, int *tamFilme, categoria *categoriaC, int c_cat, int tipoDado);

// função responsável por alterar dados dos filmes cadastrados
void mudar_filme(filme *filmeC, int c_filme, categoria *categoriaC, int c_cat);

// função responsável por listar filmes cadastrados
void lista_filme(filme *filmeC, int c_filme);

// função responsável por gravar filmes nos arquivos txt ou bin
void gravar_filme(filme *filmeC, int i, int tipoDado);

// função responsável por tratar e limpar caracteres indesejados no final de strings
void limpaString_filme(char *a);

// função responsável por carregar filmes dos arquivos txt ou bin
void carregarFilme(filme **filmeC, int *c_filme, int *tamFilme, int tipoDado);

// função responsável por excluir filmes
void remove_filme(filme **filmeC, int *c_filme);

// função responsável por imprimir menu na tela
void menufilme();

// função responsável por gravar filmes nos arquivos txt ou bin após alterações
void regravar_filme(filme *filmeC, int k, int tipoDado);

// função responsável por terminar o cadastro de filmes pendentes
void cadastroPendentes(filme *filmeC, int c_filme, int *c_pendente, categoria *categoriaC, int c_cat, int tipoDado);

