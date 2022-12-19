/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   locadora.h
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:46
 */

#ifndef LOCADORA_H
#define LOCADORA_H

#endif /* LOCADORA_H */


typedef struct {
    char nomeFantasia[40];
    char razao[40];
    char inscricaoEst[18];
    char cnpj[18];
    char endereco[60];
    char telefone[18];
    char email[40];
    char nomeResponsavel[30];
    char telResponsavel[18];
    float multa;
} locadora;

typedef struct {
    float caixa;
    float areceber;
    float despesa;
} financeiro;

// função responsável por cadastrar locadora
void cadastro_locadora(locadora *locadoraC, int *i);

// função responsável por carregar dados da locadora do arquivo txt ou bin
void carregarLocadora(locadora **locadoraC, int *c_loca, int tipoDado);

// função responsável por alterar dados da locadora
void mudar_locadora(locadora *locadoraC);

// função responsável por tratar e limpar caracteres indesejados no final de strings
void limpaString_loca(char *a);

// função responsável por imprimir menu na tela
void menulocadora();

// função responsável por listar dados da locadora
void dados_locadora(locadora *locadoraC, int c_loca);

// função responsável por gravar dados da locadora no arquivo txt ou bin
void gravar_locadora(locadora *locadoraC, int i, int tipoDado);

// função responsável por excluir locadora
void remove_loca(locadora *locadoraC, int *i, int tipoDado);

// função responsável por excluir dados da locadora dos arquivos txt ou bin
void regravar_loca_remove(int tipoDado);

// função responsável por gravar dados financeiros da locadora nos arquivos txt ou bin
void gravar_financeiro(financeiro *financeiroC, int tipoDado);

// função responsável por carregar dados financeiros da locadora dos arquivos txt ou bin
void carregarFinanceiro(financeiro **financeiroC, int tipoDado);

// função responsável por gravar dados financeiros da locadora nos arquivos txt ou bin após alterações
void regravar_loca(locadora *locadoraC, int i, int tipoDado);

// função responsável por validar cnpj
int validaCnpj(char *CNPJ);

// função auxiliar a valida cnpj
int AUX_(char ch);