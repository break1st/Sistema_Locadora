/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   fornecedor.h
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:46
 */

#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#endif /* FORNECEDOR_H */



typedef struct {
    int codigo;
    char nomeFantasia[40];
    char razaoSocial[40];
    char inscricaoEst[17];
    char cnpj[17];
    char endereco[60];
    char tel[20];
    char email[40];
} fornecedor;

// função responsavel por carregar dados dos fornecedores dos arquivos txt ou bin
void carregarForn(fornecedor **fornecedorC, int *c_forn, int *tamForn, int tipoDado);

// função responsavel por gravar dados dos fornecedores nos arquivos txt ou bin
void gravar_forn(fornecedor *fornecedorC, int i, int tipoDado);

// função responsavel por gravar dados dos fornecedores nos arquivos txt ou bin após alterações
void regravar_forn(fornecedor *fornecedorC, int k, int tipoDado);

// função responsavel por cadastrar novos fornecedores
void cadastro_forn(fornecedor *fornecedorC, int *c_forn, int *tamForn, int tipoDado);

// função responsavel por alterar cadastro de fornecedores
void mudar_forn(fornecedor *fornecedorC, int c_forn);

// função responsável por tratar e limpar caracteres indesejados no final de strings
void limpaString_forn(char *a);

// função responsavel por listar fornecedores cadastrados
void lista_forn(fornecedor *fornecedorC, int c_forn);

// função responsavel por excluir fornecedores cadastrados
void remove_forn(fornecedor *fornecedorC, int *c_forn);

// função responsavel por validar cnpj
int validaCNPJ(char *CNPJ);

// função responsavel por auxiliar na validação do cnpj
int aux_(char ch);

// função responsavel por imprimir menu na tela
void menuforn();