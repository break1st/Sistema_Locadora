/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   cliente.h
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:46
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#endif /* CLIENTE_H */


typedef struct {
    int codigoCliente;
    char nome[30];
    char endereco[60];
    char cpf[13];
    char telefone[20];
    char email[40];
    char sexo[15];
    char estadoCivil[15];
    char dataNascimento[12];
} cliente;

typedef struct{
    int codigo;
    char nome[30];
    float valorDeve;
}contaCliente;


// função auxiliar a validacao de cpf
int aux(char ch);

// função responsável por validar cpf
int validaCPF(char *cpf);

// função responsável por cadastrar novos clientes
void cadastro_cliente(cliente *clienteC, int *c_cliente, int *tamCliente, int tipoDado);

// função responsável por gravar dados dos clientes nos arquivos txt ou bin
void gravar_cliente(cliente *clienteC, int i, int tipoDado);

// função responsável por gravar dados dos clientes nos arquivos txt ou bin após alterações
void regravar_cliente(cliente *clienteC, int k, int tipoDado);

// função responsável por tratar e limpar caracteres indesejados no final de strings
void limpaString_cliente(char *a);

// função responsável por carregar dados dos clientes dos arquivos txt ou bin
void carregarCliente(cliente **clienteC, int *c_cliente, int *tamCliente, int tipoDado);

// função responsável por listar clientes cadastrados
void lista_cliente(cliente *clienteC, int c_cliente);

// função responsável por alterar dados de clientes cadastrados
void mudar_cliente(cliente *clienteC, int c_cliente);

// função responsável por excluir clientes cadastrados
void remove_cliente(cliente **clienteC, int *c_cliente);

// função responsável por imprimir menu na tela
int menucliente();
