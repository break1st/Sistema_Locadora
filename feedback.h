//
// Created by Breno on 16/11/2022.
//

#ifndef PROJETO_LOCADORA_FEEDBACK_H
#define PROJETO_LOCADORA_FEEDBACK_H

#endif //PROJETO_LOCADORA_FEEDBACK_H

#include "funcGlobais.h"

// função responsável imprimir menu na tela
void menuFeedback();

// função responsável pelo modulo de feedback de clientes
void fb_Clientes(cliente **clienteC, int c_cliente);

// função responsável pelo modulo de feedback de filmes
void fb_Filmes(filme **filmeC, int c_filme);

// função responsável pelo modulo de feedback de locacoes
void fb_Locacoes(operacoes **operacaoC, int c_op, contaCliente **contaC, int c_conta, funcionario **funcC, int c_func);

// função responsável pelo modulo de feedback de contas a receber
void fb_ContasReceber(contaCliente **contaC, int c_conta, operacoes **operacaoC, int c_op, int c_idOp);

// função responsável pelo modulo de feedback de contas a pagar
void fb_contasPagar(compra **compraC, int c_compra, fornecedor **fornecedorC, int c_forn);

// função responsável pelo modulo de feedback de locacoes restantes para o filme se pagar
void fb_locacaoRest(operacoes **operacaoC, int c_op, filme **filmeC, int c_filme);

// função responsável por calcular qual data é menor
int dataAntes(data dtDev1, data dtDev2);

