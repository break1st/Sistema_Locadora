//
// Created by Alunos on 22/11/2022.
//

#ifndef PROJETO_LOCADORA_EXPORT_H
#define PROJETO_LOCADORA_EXPORT_H

#endif //PROJETO_LOCADORA_EXPORT_H

#include "feedback.h"

typedef struct{
    char linha [200];
}dados;

// função responsável por alocar espaço na memoria para filmes
void alocaFilme(filme **filmeC, int *c_filme, int *tamFilme);

// função responsável por alocar espaço na memoria para categorias
void alocaCat(categoria **categoriaC, int *c_cat, int *tamCat);

// função responsável por alocar espaço na memoria para linhas
void alocaLinha(dados **linhaC, int *c_linha, int *tamLinha);

// função responsável por coletar os dados do arquivo importado
void coletaDados(dados **linhaC, int *c_linha, int *tamLinha);

// função responsável por tratar dados dos filmes do arquivo importado
void tratarFilme(dados **linhaC, int *c_linha, filme **filmeC, int *c_filme, int *tamFilme);

// função responsável por tratar dados das categorias do arquivo importado
void tratarCategoria(dados **linhaC, int *c_linha, categoria **categoriaC, int *c_cat, int *tamCat);

// função responsável por tratar dados dos clientes do arquivo importado
void tratarCliente(dados **linhaC, int *c_linha, cliente **clienteC, int *c_cliente, int *tamCliente);

// função responsável por tratar dados dos fornecedores do arquivo importado
void tratarFornecedor(dados **linhaC, int *c_linha, fornecedor **fornC, int *c_forn, int *tamForn);

// função responsável por tratar dados dos funcionarios do arquivo importado
void tratarFuncionario(dados **linhaC, int *c_linha, funcionario **funcC, int *c_func, int *tamFunc);

// função responsável por tratar dados das contas de clientes do arquivo importado
void tratarConta(dados **linhaC, int *c_linha, contaCliente **contaC, int *c_conta, int *tamConta);

// função responsável por tratar dados das operações de locação do arquivo importado
void tratarOp(dados **linhaC, int *c_linha, operacoes **operacaoC, int *c_op, int *tamOp);

// função responsável por tratar dados das compras de filmes do arquivo importado
void tratarCompra(dados **linhaC, int *c_linha, compra **compraC, int *c_compra, int *tamCompra);

// função responsável por tratar dados das movimentações de caixa do arquivo importado
void tratarMov(dados **linhaC, int *c_linha, movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por preencher dados tratados
void preencheDados(filme **filmeC, int *c_filme, int *tamFilme,
                   cliente **clienteC, int *c_cliente, int *tamCliente,
                   categoria **categoriaC, int *c_cat, int *tamCat,
                   funcionario **funcC, int *c_func, int *tamFunc,
                   fornecedor **fornecedorC, int *c_fornecedor, int *tamForn,
                   contaCliente **contaC, int *c_conta, int *tamConta,
                   operacoes **operacaoC, int *c_op, int *tamOp,
                   compra **compraC, int *c_compra, int *tamCompra,
                   movimentacao **movC, int *c_mov, int *tamMov,
                   locadora locadoraC, int *c_loca, int *tamLoca,
                   financeiro financeiroC,
                   dados **linhaC, int *c_linha, int *tamLinha);

// função responsavel por exportar xml de filmes
void exportarFilme(filme **filmeC, int c_filme, int tipoDado, int op);

// função responsavel por exportar xml de clientes
void exportarCliente(cliente **clienteC, int c_cliente, int tipoDado, int op);

// função responsavel por exportar xml de categorias
void exportarCategoria(categoria **categoriaC, int c_categoria, int tipoDado, int op);

// função responsavel por exportar xml de funcionarios
void exportarFuncionario(funcionario **funcC, int c_func, int tipoDado, int op);

// função responsavel por exportar xml de fornecedores
void exportarFornecedor(fornecedor **fornecedorC, int c_fornecedor, int tipoDado, int op);

// função responsavel por exportar xml de contas de clientes
void exportarContaCliente(contaCliente **contaC, int c_conta, int tipoDado, int op);

// função responsavel por exportar xml de locadora
void exportarLocadora(locadora locadoraC, int c_loca, financeiro financeiroC, int tipoDado, int op);

// função responsavel por exportar xml de operações de locações
void exportarOperacao(operacoes **operacaoC, int c_op, int tipoDado, int op);

// função responsavel por exportar xml de compras de filmes
void exportarCompra(compra **compraC, int c_compra, int tipoDado, int op);

// função responsavel por exportar xml de movimentações de caixa
void exportarMovimentacao(movimentacao **movC, int c_mov, int tipoDado, int op);

// função responsavel por exportar xml de todos os dados
void exportar(filme **filmeC, int c_filme,
              cliente **clienteC, int c_cliente,
              categoria **categoriaC, int c_categoria,
              funcionario **funcC, int c_func,
              fornecedor **fornecedorC, int c_fornecedor,
              contaCliente **contaC, int c_conta,
              operacoes **operacaoC, int c_op,
              compra **compraC, int c_compra,
              movimentacao **movC, int c_mov,
              locadora locadoraC, int c_loca,
              financeiro financeiroC,
              int tipoDado);

// função responsavel por imprimir menu na tela
void menuEx();
