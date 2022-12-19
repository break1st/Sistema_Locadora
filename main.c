/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "filme.h"
//#include "categoria.h"
//#include "cliente.h"
//#include "funcionario.h"
//#include "fornecedor.h"
//#include "funcGlobais.h"
//#include "locadora.h"
#include "export.h"

/*
 *
 */

filme *filmeC;
categoria *categoriaC;
fornecedor *fornecedorC;
funcionario *funcC;
cliente *clienteC;
locadora *locadoraC;
//conta_cliente *contasC;
//filmes_conta *filmesLoc;
financeiro *financeiroC;
contaCliente *contaC;
operacoes *operacaoC;
compra *compraC;
movimentacao *movC;
dados *linhaC;

int main() {
    int menuOp = 0, funcaoOp = 0, tipoDado = 0;
    int c_filme = 0, tamFilme = 1;
    int c_cat = 0, tamCat = 1;
    int c_cliente = 0, tamCliente = 1;
    int c_func = 0, tamFunc = 1;
    int c_forn = 0, tamForn = 1;
    int c_loca = 0, tamLoca = 1;
    int tamFin = 1;
    int tamDados = 1, tamF = 1;
    int c_conta = 0, tamConta = 1;
    int c_op = 0, tamOp = 1;
    int c_idOp = 1;
    int c_idCompra = 1;
    int c_compra = 0, tamCompra = 1;
    int c_mov = 0, tamMov = 1;
    int c_pendente = 0;
    int c_linha = 0, tamLinha = 1;

    linhaC = (dados *) (malloc(tamLinha * sizeof (dados)));
    filmeC = (filme *) (malloc(tamFilme * sizeof(filme)));
    categoriaC = (categoria *) (malloc(tamCat * sizeof(categoria)));
    clienteC = (cliente *) (malloc(tamCliente * sizeof(cliente)));
    funcC = (funcionario *) (malloc(tamFunc * sizeof(funcionario)));
    fornecedorC = (fornecedor *) (malloc(tamForn * sizeof(fornecedor)));
    locadoraC = (locadora *) (malloc(tamLoca * sizeof(locadora)));
    //contasC = (conta_cliente *) (malloc(tamContas * sizeof (conta_cliente)));
    contaC = (contaCliente *) (malloc(tamConta * sizeof(contaCliente)));
    operacaoC = (operacoes *) (malloc(tamOp * sizeof(operacoes)));
    financeiroC = (financeiro *) (malloc(tamFin * sizeof(financeiro)));
    //contasC->operacoes = (operacao *) (malloc(tamDados * sizeof(operacao)));
    //contasC->operacoes->codigo = (int *) (malloc(tamDados * sizeof(int)));
    compraC = (compra *)(malloc(tamCompra * sizeof(compra)));
    movC = (movimentacao *)(malloc(tamMov * sizeof(movimentacao)));

    printf("Voce deseja trabalhar com dados em:\n1 Tipo txt\n2 Tipo bin\n3 Memoria:\n");
    printf("%c ", 175);
    setbuf(stdin, NULL);
    scanf("%d", &tipoDado);
    //scanf("%s", temp);
    //tipoDado = strtol(temp, NULL, 10);

    while(tipoDado != 1 && tipoDado != 2 && tipoDado != 3){
        printf("Por favor, informe uma opcao valida: \n1 Tipo txt\n2 Tipo bin:\n3 Memoria:\n");
        printf("%c ", 175);
        scanf("%d", &tipoDado);
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    // carrega filmes
    carregarFilme(&filmeC, &c_filme, &tamFilme, tipoDado);
    // carrega categorias
    carregarCat(&categoriaC, &c_cat, &tamCat, tipoDado);
    // carrega clientes
    carregarCliente(&clienteC, &c_cliente, &tamCliente, tipoDado);
    // carrega funcionarios
    carregarFunc(&funcC, &c_func, &tamFunc, tipoDado);
    // carrega fornecedores
    carregarForn(&fornecedorC, &c_forn, &tamForn, tipoDado);
    // carrega locadora
    carregarLocadora(&locadoraC, &c_loca, tipoDado);
    // carrega operacoes
    carregar_op(&operacaoC, &c_op, &tamOp, &c_idOp, tipoDado);
    // carrega contas de clientes
    carregar_conta(&contaC, &c_conta, &tamConta, &clienteC, &c_cliente, tipoDado);
    // carrega compras de filmes feitas
    carregar_compra(&compraC, &c_compra, &tamCompra, tipoDado);
    // carrega dados financeiros da locadora
    carregarMov(&movC, &c_mov, &tamMov, tipoDado);
    financeiroC->caixa = 0;
    financeiroC->despesa = 0;
    financeiroC->areceber = 0;

    carregarFinanceiro(&financeiroC, tipoDado);

    menu();
    scanf("%d", &menuOp);
    while (menuOp != 0) {

        verificaIdOp(operacaoC, c_op, &c_idOp);
        verificaIdCompra(compraC, c_compra, &c_idCompra);
        verificaPendentes(filmeC, c_filme, &c_pendente);

        if(c_mov == 0){
            movC[0].valorAntes = 0;
            movC[0].valorDepois = financeiroC->caixa;
            movC[0].operacao = 0;
            obterData(&movC[0].dataOp);
            realocaMov(&movC, &c_mov, &tamMov);
            c_mov++;
            gravar_mov(movC, c_mov, tipoDado);
        }


        system("cls");
        if (menuOp == 1) {
            menufilme();
            scanf("%d", &funcaoOp);
            while (funcaoOp != 8) {

                if (funcaoOp == 1) {
                    system("cls");
                    if (c_filme == tamFilme) {
                        tamFilme = tamFilme + 1;
                        filmeC = (filme *) (realloc(filmeC, tamFilme * sizeof(filme)));
                    }
                    if (filmeC == NULL) {
                        printf("/nErro de alocacao de memoria.");
                    }

                    cadastra_filme(filmeC, &c_filme, &tamFilme, categoriaC, c_cat, tipoDado);
                    system("cls");
                } else {
                    if (funcaoOp == 2) {
                        system("cls");
                        mudar_filme(filmeC, c_filme, categoriaC, c_cat);
                        regravar_filme(filmeC, c_filme, tipoDado);
                        system("cls");
                    } else {
                        if (funcaoOp == 3) {
                            system("cls");
                            lista_filme(filmeC, c_filme);
                            system("cls");
                        } else {
                            if (funcaoOp == 4) {
                                system("cls");
                                remove_filme(&filmeC, &c_filme);
                                regravar_filme(filmeC, c_filme, tipoDado);
                                system("cls");
                            }else{
                                if(funcaoOp == 5){
                                    system("cls");
                                    compraFilme(fornecedorC, c_forn, &filmeC, &c_filme, &tamFilme, &compraC, &c_compra, &tamCompra, &c_idCompra, &c_pendente, &financeiroC, tipoDado, &movC, &c_mov, &tamMov);
                                    system("cls");
                                }else {
                                    if (funcaoOp == 6) {
                                        system("cls");
                                        listaCompras(compraC, c_compra, fornecedorC, c_forn, c_idCompra);
                                        system("cls");
                                    } else {
                                        if (funcaoOp == 7) {
                                            system("cls");
                                            cadastroPendentes(filmeC, c_filme, &c_pendente, categoriaC, c_cat, tipoDado);
                                            system("cls");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                menufilme();
                scanf("%d", &funcaoOp);
            }
        } else {
            if (menuOp == 2) {
                menucat();
                scanf("%d", &funcaoOp);
                while (funcaoOp != 5) {
                    if (funcaoOp == 1) {
                        system("cls");
                        if (c_cat == tamCat) {
                            tamCat = tamCat + 1;
                            categoriaC = (categoria *) (realloc(categoriaC, tamCat * sizeof(categoria)));
                        }
                        if (categoriaC == NULL) {
                            printf("\nErro de alocacao de memoria.\n");
                        }

                        cadastra_cat(categoriaC, &c_cat, &tamCat, tipoDado);
                        system("cls");
                    } else {
                        if (funcaoOp == 2) {
                            system("cls");
                            mudar_cat(categoriaC, c_cat);
                            regravar_cat(categoriaC, c_cat, tipoDado);
                            system("cls");
                        } else {
                            if (funcaoOp == 3) {
                                system("cls");
                                lista_cat(categoriaC, c_cat);
                                system("cls");
                            } else {
                                if (funcaoOp == 4) {
                                    system("cls");
                                    remove_cat(categoriaC, &c_cat);
                                    regravar_cat(categoriaC, c_cat, tipoDado);
                                    system("cls");
                                } else {
                                }
                            }
                        }
                    }
                    menucat();
                    scanf("%d", &funcaoOp);
                    system("cls");
                }
            } else {
                if (menuOp == 3) {
                    menufunc();
                    scanf("%d", &funcaoOp);
                    while (funcaoOp != 5) {
                        //funcaoOp = menu_func();
                        if (funcaoOp == 1) {
                            system("cls");
                            if (c_func == tamFunc) {
                                tamFunc++;
                                funcC = (funcionario *) (realloc(funcC, tamFunc * sizeof(funcionario)));
                            }
                            if (funcC == NULL) {
                                printf("/nErro de alocacao de memoria.");
                            }

                            cadastro_func(funcC, &c_func, &tamFunc, tipoDado);
                            system("cls");
                        } else {
                            if (funcaoOp == 2) {
                                system("cls");
                                mudar_func(funcC, c_func);
                                regravar_func(funcC, c_func, tipoDado);
                                system("cls");
                            } else {
                                if (funcaoOp == 3) {
                                    system("cls");
                                    lista_func(funcC, c_func);
                                    system("cls");
                                } else {
                                    if (funcaoOp == 4) {
                                        system("cls");
                                        remove_func(funcC, &c_func);
                                        regravar_func(funcC, c_func, tipoDado);
                                        system("cls");
                                    } else {
                                    }
                                }
                            }
                        }
                        menufunc();
                        scanf("%d", &funcaoOp);
                        system("cls");
                    }
                } else {
                    if (menuOp == 4) {
                        menucliente();
                        scanf("%d", &funcaoOp);
                        while (funcaoOp != 5) {
                            if (funcaoOp == 1) {
                                system("cls");
                                if (c_cliente == tamCliente) {
                                    tamCliente++;
                                    clienteC = (cliente *) (realloc(clienteC, tamCliente * sizeof(cliente)));
                                }
                                if (clienteC == NULL) {
                                    printf("/nErro de alocacao de memoria.");
                                }

                                cadastro_cliente(clienteC, &c_cliente, &tamCliente, tipoDado);
                                system("cls");
                            } else {
                                if (funcaoOp == 2) {
                                    system("cls");
                                    mudar_cliente(clienteC, c_cliente);
                                    regravar_cliente(clienteC, c_cliente, tipoDado);
                                    system("cls");
                                } else {
                                    if (funcaoOp == 3) {
                                        system("cls");
                                        lista_cliente(clienteC, c_cliente);
                                        system("cls");
                                    } else {
                                        if (funcaoOp == 4) {
                                            system("cls");
                                            remove_cliente(&clienteC, &c_cliente);
                                            regravar_cliente(clienteC, c_cliente, tipoDado);
                                            system("cls");
                                        } else {
                                        }
                                    }
                                }
                            }
                            menucliente();
                            scanf("%d", &funcaoOp);
                            system("cls");
                        }
                    } else {
                        if (menuOp == 5) {
                            menuforn();
                            scanf("%d", &funcaoOp);
                            while (funcaoOp != 5) {
                                if (funcaoOp == 1) {
                                    system("cls");
                                    if (c_forn == tamForn) {
                                        tamForn++;
                                        fornecedorC = (fornecedor *) (realloc(fornecedorC,
                                                                              tamForn * sizeof(fornecedor)));
                                    }
                                    if (fornecedorC == NULL) {
                                        printf("/nErro de alocacao de memoria.");
                                    }
                                    system("cls");
                                    cadastro_forn(fornecedorC, &c_forn, &tamForn, tipoDado);
                                } else {
                                    if (funcaoOp == 2) {
                                        system("cls");
                                        mudar_forn(fornecedorC, c_forn);
                                        regravar_forn(fornecedorC, c_forn, tipoDado);
                                        system("cls");
                                    } else {
                                        if (funcaoOp == 3) {
                                            system("cls");
                                            lista_forn(fornecedorC, c_forn);
                                            system("cls");
                                        } else {
                                            if (funcaoOp == 4) {
                                                system("cls");
                                                remove_forn(fornecedorC, &c_forn);
                                                regravar_forn(fornecedorC, c_forn, tipoDado);
                                                system("cls");
                                            }
                                        }
                                    }
                                }
                                menuforn();
                                scanf("%d", &funcaoOp);
                                system("cls");
                            }
                        } else {
                            if (menuOp == 6) {
                                menuLocacao();
                                scanf("%d", &funcaoOp);
                                while (funcaoOp != 5) {
                                    if (funcaoOp == 1) {
                                        system("cls");
                                        locarFilme(filmeC, c_filme, categoriaC, c_cat,
                                                   &contaC, &c_conta, &tamConta,
                                                   &operacaoC, &c_op, &tamOp, &c_idOp,
                                                   funcC, c_func, clienteC, c_cliente, locadoraC, financeiroC, tipoDado, &movC, &c_mov, &tamMov);
                                        system("cls");
                                    } else {
                                        if (funcaoOp == 2) {
                                            system("cls");
                                            listaOperacao(operacaoC, c_op, c_idOp, contaC, c_conta, filmeC, c_filme);
                                        } else {
                                            if (funcaoOp == 3) {
                                                system("cls");
                                                pagarConta(&contaC, c_conta, &operacaoC, c_op, &financeiroC, tipoDado, &movC, &c_mov, &tamMov);
                                                system("cls");
                                            } else {
                                                if (funcaoOp == 4) {
                                                    system("cls");
                                                    devolucaoFilme(&operacaoC, c_op, &contaC, c_conta, &filmeC, c_filme, tipoDado, &locadoraC, &financeiroC, &movC, &c_mov, &tamMov);
                                                    system("cls");
                                                }
                                            }
                                        }
                                    }
                                    menuLocacao();
                                    scanf("%d", &funcaoOp);
                                    system("cls");
                                }
                            } else {
                                if (menuOp == 7) {
                                    menulocadora();
                                    scanf("%d", &funcaoOp);
                                    while (funcaoOp != 5) {
                                        if (funcaoOp == 1) {
                                            system("cls");
                                            dados_locadora(locadoraC, c_loca);
                                        } else {
                                            if (funcaoOp == 2) {
                                                system("cls");
                                                mudar_locadora(locadoraC);
                                                regravar_loca(locadoraC, c_loca, tipoDado);
                                                system("cls");
                                            } else {
                                                if (funcaoOp == 3) {
                                                    system("cls");
                                                    remove_loca(locadoraC, &c_loca, tipoDado);
                                                    regravar_loca_remove(tipoDado);
                                                    system("cls");
                                                } else {
                                                    if (funcaoOp == 4) {
                                                        system("cls");
                                                        cadastro_locadora(locadoraC, &c_loca);
                                                        gravar_locadora(locadoraC, c_loca, tipoDado);
                                                        system("cls");
                                                    }
                                                }
                                            }
                                        }
                                        menulocadora();
                                        scanf("%d", &funcaoOp);
                                        system("cls");
                                    }
                                }
                            }
                            if (menuOp == 8) {
                                menuContas();
                                scanf("%d", &funcaoOp);
                                while(funcaoOp != 4){
                                    if(funcaoOp == 1){
                                        system("cls");
                                        contasReceber(&contaC, c_conta, &operacaoC, c_op, &financeiroC, c_idOp);
                                        }else{
                                        if(funcaoOp == 2){
                                            system("cls");
                                            contasPagar (&compraC, c_compra, &financeiroC, tipoDado, &movC, &c_mov, &tamMov);
                                            system("cls");
                                        }else{
                                            if(funcaoOp == 3){
                                                system("cls");
                                                caixaLocadora(&financeiroC, tipoDado, &movC, &c_mov, &tamMov);
                                                system("cls");
                                            }
                                        }
                                    }
                                    menuContas();
                                    scanf("%d", &funcaoOp);
                                    system("cls");
                                }
                            }else{
                                if(menuOp == 9){
                                    menuFeedback();
                                    scanf("%d", &funcaoOp);
                                    while(funcaoOp != 8){
                                        if(funcaoOp == 1){
                                            system("cls");
                                            fb_Clientes(&clienteC, c_cliente);
                                            }else{
                                            if(funcaoOp == 2){
                                                system("cls");
                                                fb_Filmes(&filmeC, c_filme);
                                            }else{
                                                if(funcaoOp == 3){
                                                    system("cls");
                                                    fb_locacaoRest(&operacaoC, c_op, &filmeC, c_filme);
                                                }else{
                                                    if(funcaoOp == 4){
                                                        system("cls");
                                                        fb_Locacoes(&operacaoC, c_op, &contaC, c_conta, &funcC, c_func);
                                                    }else{
                                                        if(funcaoOp == 5){
                                                            system("cls");
                                                            fb_ContasReceber(&contaC, c_conta, &operacaoC, c_op, c_idOp);
                                                        }else{
                                                            if(funcaoOp == 6){
                                                                system("cls");
                                                                fb_contasPagar(&compraC, c_compra, &fornecedorC, c_forn);
                                                            }else{
                                                                if(funcaoOp == 7){
                                                                    system("cls");
                                                                    listaMovimentacao(&movC, c_mov);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        menuFeedback();
                                        scanf("%d", &funcaoOp);
                                        system("cls");
                                    }
                                }else{
                                    if(menuOp == 10){
                                        menuEx();
                                            exportar(&filmeC, c_filme,
                                                     &clienteC, c_cliente,
                                                     &categoriaC, c_cat,
                                                     &funcC, c_func,
                                                     &fornecedorC, c_forn,
                                                     &contaC, c_conta,
                                                     &operacaoC, c_op,
                                                     &compraC, c_compra,
                                                     &movC, c_mov,
                                                     *locadoraC, c_loca,
                                                     *financeiroC, tipoDado);
                                        }else{

                                        if(menuOp == 11){
                                            coletaDados(&linhaC, &c_linha, &tamLinha);
                                            preencheDados(&filmeC, &c_filme, &tamFilme,
                                                          &clienteC, &c_cliente, &tamCliente,
                                                          &categoriaC, &c_cat, &tamCat,
                                                          &funcC, &c_func, &tamFunc,
                                                          &fornecedorC, &c_forn, &tamForn,
                                                          &contaC, &c_conta, &tamConta,
                                                          &operacaoC, &c_op, &tamOp,
                                                          &compraC, &c_compra, &tamCompra,
                                                          &movC, &c_mov, &tamMov,
                                                          *locadoraC, &c_loca, &tamLoca,
                                                          *financeiroC,
                                                          &linhaC, &c_linha, &tamLinha);
                                            regravar_filme(filmeC, c_filme, tipoDado);
                                            gravar_compra(compraC, c_compra, tipoDado);
                                            gravar_financeiro(financeiroC, tipoDado);
                                            regravar_cat(categoriaC, c_cat, tipoDado);
                                            regravar_func(funcC, c_func, tipoDado);
                                            regravar_cliente(clienteC, c_cliente, tipoDado);
                                            regravar_forn(fornecedorC, c_forn, tipoDado);
                                            gravar_conta(contaC, c_conta, tipoDado);
                                            gravar_op(operacaoC, c_op, tipoDado);
                                            regravar_loca(locadoraC, c_loca, tipoDado);
                                        }else{
                                            if(menuOp == 12){
                                                zeraArquivos();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        menu();
        scanf("%d", &menuOp);
        system("cls");
        //system("cls");
    }


    return (EXIT_SUCCESS);
}
