/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   funcGlobais.h
 * Author: Alunos
 *
 * Created on 13 de Outubro de 2022, 14:05
 */

#ifndef FUNCGLOBAIS_H
#define FUNCGLOBAIS_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* FUNCGLOBAIS_H */

//#include "categoria.h"
#include "locadora.h"
#include "funcionario.h"
#include "fornecedor.h"
#include "cliente.h"
#include "filme.h"

typedef struct {
    int tm_sec;   // Indica os segundos de 0 a 59
    int tm_min;   // Indica os minutos de 0 a 59
    int tm_hour;  // Indica as horas de 0 a 24
    int tm_mday;  // Indica os dias do mês de 1 a 31
    int tm_mon;   // Indica os meses do ano de 0 a 11
    int tm_year;  // Indica o ano a partir de 1900
    int tm_wday;  // Indica o dia da semana de 0 (domingo) até 6 (sábado)
    int tm_yday;  // Indica o dia do ano de 1 a 365
    int tm_isdst; // Indica o horário de verão se for diferente de zero
}tm;

// função responsável por carregar dados das movimentações do caixa dos arquivos txt ou bin
void carregarMov(movimentacao **movC, int *c_mov, int *tamMov, int tipoDado);

// função responsável pelas operações de locações de filmes
void locarFilme(filme *filmeC, int c_filme,
                categoria *categoriaC, int c_cat,
                contaCliente **contaC, int *c_conta, int *tamConta,
                operacoes **operacaoC, int *c_op, int *tamOp, int *c_idOp,
                funcionario *funcC, int c_func,
                cliente *clienteC, int c_cliente,
                locadora *locadoraC, financeiro *financeiroC, int tipoDado,
                movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por criar contas de clientes
void criar_conta(contaCliente **contaC, int c_conta, int *tamConta);

// função responsável por carregar dados dos filmes comprados dos arquivos txt ou bin
void carregar_compra(compra **compraC, int *c_compra, int *tamCompra, int tipoDado);

// função responsável por visualizar e editar os dados do caixa da locadora
void caixaLocadora(financeiro **financeiroC, int tipoDado, movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por listar movimentações de caixa
void listaMovimentacao(movimentacao **movC, int c_mov);

// função responsável por gravar dados das movimentações de caixa nos arquivos txt ou bin
void gravar_mov(movimentacao *movC, int i, int tipoDado);

// função responsável por alocar espaço na memoria para movimentações de caixa
void realocaMov(movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por adicionar nova operação de adição nas movimentações do caixa
void newMovAD(movimentacao **movC, int *c_mov, int *tamMov, float valor, int tipoDado);

// função responsável por adicionar nova operação de subtração nas movimentações do caixa
void newMovSUB(movimentacao **movC, int *c_mov, int *tamMov, float valor, int tipoDado);

// função responsável por gravar dados financeiros da locadora nos arquivos txt ou bin
void gravar_financeiro(financeiro *financeiroC, int tipoDado);

// função responsável por gravar dados dos filmes comprados nos arquivos txt ou bin
void gravar_compra(compra *compraC, int i, int tipoDado);

// função responsável por verificar se existe compra com id igual ao informado
void verificaIdCompra(compra *compraC, int c_compra, int *c_idCompra);

// função responsável por verificar se existe operação de locação com id igual ao informado
void verificaIdOp(operacoes *operacaoC, int c_op, int *c_idOp);

// função responsável por listar operações de locações
void listaOperacao(operacoes *operacaoC, int c_op, int c_idOp, contaCliente *contaC, int c_conta, filme *filmeC, int c_filme);

// função responsável por obter data do sistema
void obterData(data *dt);

// função responsável por calcular data de devolução
void dataDevolucao(data *dt, data *dtDev);

// função responsável por gravar dados das operações de locação nos arquivos txt ou bin
void gravar_op(operacoes *operacaoC, int i, int tipoDado);

// função responsável por carregar dados das operações de locação dos arquivos txt ou bin
void carregar_op(operacoes **operacaoC, int *c_op, int *tamOp, int *c_idOp, int tipoDado);

// função responsável por gravar dados das contas dos clientes nos arquivos txt ou bin
void gravar_conta(contaCliente *contaC, int i, int tipoDado);

// função responsável por carregar dados das contas dos clientes dos arquivos txt ou bin
void carregar_conta(contaCliente **contaC, int *c_conta, int *tamConta, cliente **clienteC, int *c_cliente, int tipoDado);

// função responsável pelo pagamento de contas da locadora
void pagarConta(contaCliente **contaC, int c_conta, operacoes **operacaoC, int c_op, financeiro **financeiroC, int tipoDado, movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por imprimir menu na tela
void menuLocacao();

// função responsável por verificar se existe cliente com o codigo informado
int verificaCliente(int *codCliente, cliente *clienteC, int c_cliente, int *pcliente);

// função responsável por verificar se existe funcionario com o codigo informado
int verificaFunc(int *codFunc, funcionario *funcC, int c_func, int *pfunc);

// função responsável por verificar se existe filme com o codigo informado
int verificaFilme(int *codFilme, filme *filmeC, int c_filme, int *pfilme, int *codCat, int c_cat, categoria *categoriaC, int *pcat);

// função responsável por imprimir menu na tela
void menu();

// função responsável por imprimir menu na tela
void menuContas();

// função responsável por converter data em dias
int dataDias(data data);

// função responsável por calcular dias entre duas datas
int diasEntreDatas(data dataMaior, data dataMenor);

// função responsável pela operação de comprar filmes
void compraFilme(fornecedor *fornecedorC, int c_forn, filme **filmeC, int *c_filme, int *tamFilme, compra **compraC, int *c_compra, int *tamCompra, int *c_idCompra, int *c_pendente, financeiro **financeiroC, int tipoDado,movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por criar filmes pendentes
void criaNovoFilme(filme **filmeC, int *c_filme, int *tamFilme, compra **compraC, int p_compra, int *c_pendente, int tipoDado);

// função responsável por listar filmes comprados
void listaCompras(compra *compraC, int c_compra, fornecedor *fornecedorC, int c_forn, int c_idCompra);

// função responsável por verificar filmes pendentes
void verificaPendentes(filme *filmeC, int c_filme, int *c_pendente);

// função responsável pela devolução de filmes locados
void devolucaoFilme(operacoes **operacaoC, int c_op, contaCliente **contaC, int c_conta, filme **filmeC, int c_filme, int tipoDado, locadora **locadora, financeiro **financeiroC,
                    movimentacao **movC, int *c_mov, int *tamMov);

// função responsável pelas contas a receber
void contasReceber(contaCliente **contaC, int c_conta, operacoes **operacaoC, int c_op, financeiro **financeiroC, int c_idOp);

// função responsável pelas contas a pagar
void contasPagar (compra **compraC, int c_compra, financeiro **financeiroC, int tipoDado, movimentacao **movC, int *c_mov, int *tamMov);

// função responsável por pagar contas de compras da locadora
void pagarCompra(financeiro **financeiroC, compra **compraC, int c_compra, int cod, movimentacao **movC, int *c_mov, int *tamMov, int tipoDado);

// função responsável por limpar os arquivos txt ou bin
void zeraArquivos();
