/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcGlobais.h"
#include <unistd.h>
#include <io.h>

#define MIN_ANO 1
#define MAX_ANO 2500
#define DIAS_SEM 7
#define DIAS_ANO 365
#define QTD_MES 12

const int dias_mes[2][QTD_MES] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};



void listaMovimentacao(movimentacao **movC, int c_mov){
    int i, j;
    for(i = 0; i < c_mov; i++){
        printf("Caixa (antes): R$ %.2f \n", (*movC)[i].valorAntes);
        printf("Caixa (depois): R$ %.2f \n", (*movC)[i].valorDepois);
        printf("Operacao: R$ %.2f \n", (*movC)[i].operacao);
        printf("Data: %d / %d / %d \n\n", (*movC)[i].dataOp.dia, (*movC)[i].dataOp.mes, (*movC)[i].dataOp.ano);

    }
}



void caixaLocadora(financeiro **financeiroC, int tipoDado, movimentacao **movC, int *c_mov, int *tamMov){
    int op=0;
    float newCaixa = 0;

    printf("Caixa: %.2f \n", (*financeiroC)->caixa);
    printf("1 Editar caixa\t2 Sair: ");
    scanf("%d", &op);
    if(op == 1){
        printf("Informe o valor do caixa: R$ ");
        scanf("%f", &newCaixa);
        if(newCaixa > (*financeiroC)->caixa){
            float valor = newCaixa - (*financeiroC)->caixa;
            newMovAD(movC, c_mov, tamMov, valor, tipoDado);
        }else{
            float valor = (*financeiroC)->caixa - newCaixa;
            newMovSUB(movC, c_mov, tamMov, valor, tipoDado);
        }
        (*financeiroC)->caixa = newCaixa;
        realocaMov(movC, c_mov, tamMov);

        gravar_financeiro(*financeiroC, tipoDado);

    } else{
        return;
    }

}



void newMovAD(movimentacao **movC, int *c_mov, int *tamMov, float valor, int tipoDado){
    realocaMov(movC, c_mov, tamMov);
    (*movC)[*c_mov].operacao = valor;
    obterData(&(*movC)[*c_mov].dataOp);
    if(*c_mov > 0) {
        (*movC)[*c_mov].valorAntes = (*movC)[*c_mov - 1].valorDepois;
    }else{
        (*movC)[*c_mov].valorAntes = 0;
    }
    (*movC)[*c_mov].valorDepois = (*movC)[*c_mov].valorAntes + ((*movC)[*c_mov].operacao);

    *c_mov = *c_mov + 1;
    gravar_mov(*movC, *c_mov, tipoDado);

}



void newMovSUB(movimentacao **movC, int *c_mov, int *tamMov, float valor, int tipoDado){
    realocaMov(movC, c_mov, tamMov);

    (*movC)[*c_mov].operacao = (float)(-1) * valor;
    obterData(&(*movC)[*c_mov].dataOp);
    if(*c_mov > 0) {
        (*movC)[*c_mov].valorAntes = (*movC)[*c_mov - 1].valorDepois;
    }else{
        (*movC)[*c_mov].valorAntes = 0;
    }
    (*movC)[*c_mov].valorDepois = (*movC)[*c_mov].valorAntes + ((*movC)[*c_mov].operacao);

    *c_mov = *c_mov + 1;
    gravar_mov(*movC, *c_mov, tipoDado);

}



void gravar_mov(movimentacao *movC, int i, int tipoDado){
    if (tipoDado == 1) {
        int j;

        FILE *file;

        file = fopen("movimentacao.txt", "w");
        for(j=0; j < i; j++) {
            fprintf(file, "%f\n%f\n%f\n%d\n%d\n%d\n", movC[j].valorAntes,
                    movC[j].valorDepois,
                    movC[j].operacao,
                    movC[j].dataOp.dia,
                    movC[j].dataOp.mes,
                    movC[j].dataOp.ano);
        }

        fclose(file);
    }else{
        if(tipoDado == 2){
            int j;

            FILE *file;

            file = fopen("movimentacao.bin", "wb");
            for(j = 0; j < i; j++) {
                fwrite(&movC[j], sizeof(movimentacao), 1, file);
            }
            fclose(file);
        }
    }
}


void realocaMov(movimentacao **movC, int *c_mov, int *tamMov){

    if (*c_mov == *tamMov) {
        *tamMov = *tamMov + 1;
        (*movC) = (movimentacao *) (realloc((*movC), *tamMov * sizeof(movimentacao)));
    }

    if ((*movC) == NULL) {
        printf("\nErro de alocacao de memoria.\n");
    }
}


int dataDias(data data) {
    int tot_dias;
    int i, a, b;
    tot_dias = 0;
    a = data.ano / 4;
    b = data.ano % 4;

    if (b) {
        tot_dias = DIAS_ANO * (data.ano - 1) + a;
    } else {
        tot_dias = DIAS_ANO * (data.ano - 1) + a - 1;
    }

    for (i = 0; i < QTD_MES; i++) {
        if (i + 1 == data.mes)break;
        tot_dias += dias_mes[0][i];
    }

    tot_dias += data.dia;
    return tot_dias;
}



int diasEntreDatas(data dataMaior, data dataMenor) {
    int tot_dias1, tot_dias2;

    tot_dias1 = dataDias(dataMaior);
    tot_dias2 = dataDias(dataMenor);

    if (tot_dias1 && tot_dias2) {
        return tot_dias2 - tot_dias1;
    }
    return 0;
}




void carregar_compra(compra **compraC, int *c_compra, int *tamCompra, int tipoDado) {

    if (tipoDado == 1) {
        FILE *p;
        p = fopen("compras.txt", "r");

        if (p == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(p)) {
                break;
            }

            if (*c_compra == *tamCompra) {
                *tamCompra = *tamCompra + 1;
                (*compraC) = (compra *) (realloc((*compraC), *tamCompra * sizeof(compra)));
            }

            if ((*compraC) == NULL) {
                printf("\nErro de alocacao de memoria.\n");
            }

            fscanf(p, "%d\n", &(*compraC)[*c_compra].idOperacao);
            if (feof(p)) {
                break;
            }
            fscanf(p, "%d\n", &(*compraC)[*c_compra].idFornecedor);

            fgets((*compraC)[*c_compra].razaoSocial, 40, p);
            limpaString_cat((*compraC)[*c_compra].razaoSocial);

            fgets((*compraC)[*c_compra].cnpj, 17, p);
            limpaString_cat((*compraC)[*c_compra].cnpj);

            fgets((*compraC)[*c_compra].nomeFilme, 50, p);
            limpaString_cat((*compraC)[*c_compra].nomeFilme);

            fscanf(p, "%d\n", &(*compraC)[*c_compra].ex);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].valorFilme);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].valorImposto);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].valorFrete);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].filmeTotal);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].impostoTotal);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].freteTotal);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].precoFilme);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].valorTotal);
            fscanf(p, "%f\n", &(*compraC)[*c_compra].valorDeve);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].parcelas);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].dataCompra.dia);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].dataCompra.mes);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].dataCompra.ano);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].dataPago.dia);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].dataPago.mes);
            fscanf(p, "%d\n", &(*compraC)[*c_compra].dataPago.ano);
            *c_compra = *c_compra + 1;

            if (feof(p)) {
                break;
            }

        }

        fclose(p);
    }else{
        if(tipoDado == 2){

            FILE *p;
            p = fopen("compras.bin", "r");

            if (p == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(p)) {
                    break;
                }

                if (*c_compra == *tamCompra) {
                    *tamCompra = *tamCompra + 1;
                    (*compraC) = (compra *) (realloc((*compraC), *tamCompra * sizeof(compra)));
                }

                if ((*compraC) == NULL) {
                    printf("\nErro de alocacao de memoria.\n");
                }

                fread(&(*compraC)[*c_compra], sizeof(compra), 1,p);

                if (feof(p)) {
                    break;
                }

                *c_compra = *c_compra + 1;

                if (feof(p)) {
                    break;
                }
            }

            fclose(p);

        }
    }
}



void gravar_compra(compra *compraC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;
        file = fopen("compras.txt", "w");
        for (int j = 0; j < i; j++) {
            fprintf(file, "%d\n%d\n%s\n%s\n%s\n%d\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                    compraC[j].idOperacao, compraC[j].idFornecedor,
                    compraC[j].razaoSocial, compraC[j].cnpj, compraC[j].nomeFilme,
                    compraC[j].ex, compraC[j].valorFilme, compraC[j].valorImposto,
                    compraC[j].valorFrete, compraC[j].filmeTotal, compraC[j].impostoTotal,
                    compraC[j].freteTotal, compraC[j].precoFilme, compraC[j].valorTotal,
                    compraC[j].valorDeve, compraC[j].parcelas,
                    compraC[j].dataCompra.dia, compraC[j].dataCompra.mes, compraC[j].dataCompra.ano,
                    compraC[j].dataPago.dia, compraC[j].dataPago.mes, compraC[j].dataPago.ano);
        }
        fclose(file);

    }else{
        if(tipoDado == 2){}
        FILE *file;
        file = fopen("compras.bin", "w");
        for (int j = 0; j < i; j++) {
            fwrite(&compraC[j], sizeof(compra), 1, file);
        }
        fclose(file);
    }
}



void carregar_op(operacoes **operacaoC, int *c_op, int *tamOp, int *c_idOp, int tipoDado) {

    if (tipoDado == 1) {
        FILE *p;
        p = fopen("operacoes.txt", "r");

        if (p == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(p)) {
                break;
            }

            if (*c_op == *tamOp) {
                *tamOp = *tamOp + 1;
                (*operacaoC) = (operacoes *) (realloc((*operacaoC), *tamOp * sizeof(operacoes)));
            }

            if ((*operacaoC) == NULL) {
                printf("\nErro de alocacao de memoria.\n");
            }

            fscanf(p, "%d\n", &(*operacaoC)[*c_op].idOperacao);
            if (feof(p)) {
                break;
            }
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].codFunc);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].codCliente);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].codFilme);
            fgets((*operacaoC)[*c_op].nomeFilme, 50, p);
            limpaString_cat((*operacaoC)[*c_op].nomeFilme);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].ex);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].tipoPag);
            fscanf(p, "%f\n", &(*operacaoC)[*c_op].valorTotal);
            fscanf(p, "%f\n", &(*operacaoC)[*c_op].valorDeve);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].parcelas);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataLoc.dia);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataLoc.mes);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataLoc.ano);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataDev.dia);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataDev.mes);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataDev.ano);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataEntregue.dia);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataEntregue.mes);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].dataEntregue.ano);
            fscanf(p, "%d\n", &(*operacaoC)[*c_op].devolveu);

            *c_op = *c_op + 1;

            if (feof(p)) {
                break;
            }

        }

        fclose(p);
    }else{
        if(tipoDado == 2){

            FILE *p;
            p = fopen("operacoes.bin", "r");

            if (p == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(p)) {
                    break;
                }

                if (*c_op == *tamOp) {
                    *tamOp = *tamOp + 1;
                    (*operacaoC) = (operacoes *) (realloc((*operacaoC), *tamOp * sizeof(operacoes)));
                }

                if ((*operacaoC) == NULL) {
                    printf("\nErro de alocacao de memoria.\n");
                }

                fread(&(*operacaoC)[*c_op], sizeof(operacoes), 1,p);

                if (feof(p)) {
                    break;
                }

                *c_op = *c_op + 1;

                if (feof(p)) {
                    break;
                }

            }

            fclose(p);

        }
    }
}



void gravar_op(operacoes *operacaoC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;
        file = fopen("operacoes.txt", "w");
        for (int j = 0; j < i; j++) {
            fprintf(file, "%d\n%d\n%d\n%d\n%s\n%d\n%d\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", operacaoC[j].idOperacao,
                    operacaoC[j].codFunc,operacaoC[j].codCliente, operacaoC[j].codFilme, operacaoC[j].nomeFilme, operacaoC[j].ex,
                    operacaoC[j].tipoPag ,operacaoC[j].valorTotal,
                    operacaoC[j].valorDeve, operacaoC[j].parcelas, operacaoC[j].dataLoc.dia, operacaoC[j].dataLoc.mes,
                    operacaoC[j].dataLoc.ano,
                    operacaoC[j].dataDev.dia, operacaoC[j].dataDev.mes, operacaoC[j].dataDev.ano,
                    operacaoC[j].dataEntregue.dia, operacaoC[j].dataEntregue.mes, operacaoC[j].dataEntregue.ano,
                    operacaoC[j].devolveu);
        }
        fclose(file);


    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("operacoes.bin", "w");
            for (int j = 0; j < i; j++) {
                fwrite(&operacaoC[j], sizeof(operacoes), 1, file);
            }
            fclose(file);
        }
    }
}



void carregar_conta(contaCliente **contaC, int *c_conta, int *tamConta, cliente **clienteC, int *c_cliente, int tipoDado) {
    int c;

    if (tipoDado == 1) {
        FILE *p;
        p = fopen("contas_cliente.txt", "r");

        if (p == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(p)) {
                break;
            }
            //while (c = fgetc(p) != EOF) {

            if (*c_conta == *tamConta) {
                *tamConta = *tamConta + 1;
                (*contaC) = (contaCliente *) (realloc((*contaC), *tamConta * sizeof(contaCliente)));
            }

            if ((*contaC) == NULL) {
                printf("\nErro de alocacao de memoria.\n");
            }
            //(*contaC)[*c_conta].codigo = c;
            fscanf(p, "%d\n", &(*contaC)[*c_conta].codigo);
            if (feof(p)) {
                break;
            }
            fgets((*contaC)[*c_conta].nome, 50, p);
            limpaString_cat((*contaC)[*c_conta].nome);
            fscanf(p, "%f\n", &(*contaC)[*c_conta].valorDeve);

            *c_conta = *c_conta + 1;

            if (feof(p)) {
                break;
            }
        }

        fclose(p);
    }else{
        if(tipoDado == 2){

            FILE *p;
            p = fopen("contas_cliente.bin", "r");

            if (p == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(p)) {
                    break;
                }
                //while (c = fgetc(p) != EOF) {

                if (*c_conta == *tamConta) {
                    *tamConta = *tamConta + 1;
                    (*contaC) = (contaCliente *) (realloc((*contaC), *tamConta * sizeof(contaCliente)));
                }

                if ((*contaC) == NULL) {
                    printf("\nErro de alocacao de memoria.\n");
                }
                //(*contaC)[*c_conta].codigo = c;
                fread(&(*contaC)[*c_conta], sizeof(contaCliente), 1,p);

                if (feof(p)) {
                    break;
                }

                *c_conta = *c_conta + 1;

                if (feof(p)) {
                    break;
                }
            }

            fclose(p);

        }
    }
}



void gravar_conta(contaCliente *contaC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;
        file = fopen("contas_cliente.txt", "w");
        for (int j = 0; j < i; j++) {
            fprintf(file, "%d\n%s\n%f\n", contaC[j].codigo, contaC[j].nome,
                    contaC[j].valorDeve);
        }
        fclose(file);



    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("contas_cliente.bin", "w");
            for (int j = 0; j < i; j++) {
                fwrite(&contaC[i], sizeof(contaCliente), 1, file);
            }
            fclose(file);
        }
    }
}


void obterData(data *dt) {
    tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    dt->dia = p->tm_mday;
    dt->mes = p->tm_mon + 1;
    dt->ano = p->tm_year + 1900;
}


void dataDevolucao(data *dt, data *dtDev) {
    int d = 0, m = 0, a = 0;
    d = dt->dia;
    m = dt->mes;
    a = dt->ano;
    if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10)) {
        d = d + 7;
        if (d >= 31) {
            d = d - 31;
            m++;
        }
    } else {
        if (m == 12) {
            d = d + 7;
            if (d >= 31) {
                d = d - 31;
                m = 1;
                a++;
            }
        } else {
            if (m == 2) {
                d = d + 7;
                if (d >= 28) {
                    d = d - 28;
                    m++;
                }
            } else {
                if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
                    d = d + 7;
                    if (d >= 30) {
                        d = d - 30;
                        m++;
                    }
                }
            }
        }
    }
    dtDev->dia = d;
    dtDev->mes = m;
    dtDev->ano = a;
}


void verificaIdOp(operacoes *operacaoC, int c_op, int *c_idOp) {
    int i;
    if (c_op > 0) {
        for (i = 0; i < c_op; i++) {
            *c_idOp = operacaoC[i].idOperacao;
        }
        *c_idOp = *c_idOp + 1;
    }
}



void verificaIdCompra(compra *compraC, int c_compra, int *c_idCompra) {
    int i, maior;
    if (c_compra > 0) {
        for (i = 0; i < c_compra; i++) {
            maior = 0;
            if(compraC[i].idOperacao > maior){
                maior = compraC[i].idOperacao;
            }
        }
        *c_idCompra = maior + 1;
    }
}



int verificaCliente(int *codCliente, cliente *clienteC, int c_cliente, int *pcliente) {
    int cod = 0, i = 0;

    printf("ID do cliente: ");
    scanf("%d", &cod);

    for (i = 0; i < c_cliente; i++) {
        if (clienteC[i].codigoCliente == cod) {
            *codCliente = cod;
            *pcliente = i;
            return 1;
        }
    }
    printf("Não foi encontrado nenhum cliente com ID %d.\n", cod);
    return 0;
}


int verificaFunc(int *codFunc, funcionario *funcC, int c_func, int *pfunc) {
    int cod = 0;

    printf("ID do funcionário: ");
    scanf("%d", &cod);

    for (int i = 0; i < c_func; i++) {
        if (funcC[i].codigo == cod) {
            *codFunc = cod;
            *pfunc = i;
            return 1;
        }
    }
    printf("Não foi encontrado nenhum funcionario com ID %d.\n", cod);
    return 0;
}


int verificaFilme(int *codFilme, filme *filmeC, int c_filme, int *pfilme, int *codCat, int c_cat, categoria *categoriaC,
                  int *pcat) {
    int cod = 0, i, okFilme = 0;

    char tempOp[2];

    printf("COD do filme: ");
    scanf("%s", tempOp);
    cod = strtol(tempOp, NULL, 10);

    //scanf("%d", &cod);
    // verifica se o cod do filme existe
    for (i = 0; i < c_filme; i++) {
        if (cod == filmeC[i].codigoFilme) {
            *pfilme = i;
            *codFilme = cod;
            *codCat = filmeC[i].codigoCategoria;
            okFilme++;
        }
    }
    for (int j = 0; j < c_cat; j++) {
        if (*codCat == categoriaC[j].codigo) {
            *pcat = j;
        }
    }
    if (okFilme == 0) {
        printf("Não foi encontrado nenhum filme com codigo %d.\n", cod);
        return 0;
    } else {
        return 1;
    }
}


void locarFilme(filme *filmeC, int c_filme,
                categoria *categoriaC, int c_cat,
                contaCliente **contaC, int *c_conta, int *tamConta,
                operacoes **operacaoC, int *c_op, int *tamOp, int *c_idOp,
                funcionario *funcC, int c_func,
                cliente *clienteC, int c_cliente,
                locadora *locadoraC, financeiro *financeiroC, int tipoDado,
                movimentacao **movC, int *c_mov, int *tamMov) {

    int codFilme = 0, i = 0, okFilme = 0, ex = 0, op = 0, tipoPag = 0, codFunc = 0, codCliente = 0, okFunc = 0, okCliente = 0, op_ent = 0;
    int pfilme = 0, pcliente = 0, pfunc = 0, pcat = 0, pconta = 0, codCat = 0, parcelas = 0, ex_locados = 0, ex_total = 0;
    float valorTotal = 0, valorEnt = 0, caixaAux = 0, valorRest = 0, valorLoc = 0;
    int tamDados = 1, tamF = 1, idConta = 0, idOp = 0, cont = 0;
    int pConta = 0, pOp = 0, cfilm = 0, okConta = 0;
    operacoes var;

    //verificaIdOp(*operacaoC, *c_op, c_idOp);

// verifica funcionario
    if (verificaFunc(&codFunc, funcC, c_func, &pfunc) == 0) {
        *c_op = *c_op - cont;
        return;
    }

// verifica cliente
    if (verificaCliente(&codCliente, clienteC, c_cliente, &pcliente) == 0) {
        *c_op = *c_op - cont;
        return;
    }

    do {
//ex_locados = 0;
        if (verificaFilme(&codFilme, filmeC, c_filme, &pfilme, &codCat, c_cat, categoriaC, &pcat) == 0) {
            *c_op = *c_op - cont;
            return;
        }
// verifica se tem exemplares disponiveis
        if (filmeC[pfilme].exemplarFilme == 0) {
            printf("Não temos mais exemplares do filme %s.\n", filmeC[pfilme].descricao);
            *c_op = *c_op - cont;
            return;
        } else {
            ex = filmeC[pfilme].exemplarFilme;
            ex--;
            filmeC[pfilme].
                    exemplarFilme = ex;
            ex_total++;
            filmeC[pfilme].
                    exLocados = filmeC[pfilme].exLocados + 1;
            printf("%s.\n", filmeC[pfilme].descricao);
            printf("%d.\n", filmeC[pfilme].exemplarFilme);
            valorLoc = categoriaC[pcat].valorLocacao;
            printf("Valor: %.2f.\n", valorLoc);
        }

        if (*c_op == *tamOp) {
            *tamOp = *tamOp + 1;
            (*operacaoC) = (operacoes *) (realloc((*operacaoC), *tamOp * sizeof(operacoes)));
        }
        if ((*operacaoC) == NULL) {
            printf("/nErro de alocacao de memoria.");
        }
        (*operacaoC)[*c_op].codFunc = codFunc;
        (*operacaoC)[*c_op].idOperacao = *c_idOp;
        (*operacaoC)[*c_op].codCliente = codCliente;
        (*operacaoC)[*c_op].codFilme = codFilme;
        strcpy((*operacaoC)[*c_op].nomeFilme, filmeC[pfilme].descricao);
        (*operacaoC)[*c_op].valorDeve = valorLoc;
        //valorTotal = 0.0;
        obterData(&(*operacaoC)[*c_op].dataLoc);
        dataDevolucao(&(*operacaoC)[*c_op].dataLoc, &(*operacaoC)[*c_op].dataDev);
        (*operacaoC)[*c_op].dataEntregue.dia = 00;
        (*operacaoC)[*c_op].dataEntregue.mes = 00;
        (*operacaoC)[*c_op].dataEntregue.ano = 00;
        (*operacaoC)[*c_op].devolveu = 0;


        //(*operacaoC)[*c_op] = var;
        *c_op = *c_op + 1;
        cont++;
        valorLoc = 0;
        char tempOp[2];
        printf("Locar mais filmes: \n"
               "1- Sim                      2- Não\n");
        scanf("%s", tempOp);
        op = strtol(tempOp, NULL, 10);

    } while (op != 2);

    if (*c_op == *tamOp) {
        *tamOp = *tamOp + 1;
        (*operacaoC) = (operacoes *) (realloc((*operacaoC), *tamOp * sizeof(operacoes)));
    }
    if ((*operacaoC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

// aloca memoria
    for (
            i = 0;
            i < *
                    c_conta;
            i++) {
        if (codCliente == (*contaC)[i].codigo) {
            idConta = i;
            okConta++;
        }
    }
    if (okConta == 0) {
        criar_conta(contaC, *c_conta, tamConta
        );

        (*contaC)[*c_conta].codigo = clienteC[pcliente].codigoCliente;
        strcpy((*contaC)[*c_conta].nome, clienteC[pcliente].nome);
        (*contaC)[*c_conta].valorDeve = 0;
        idConta = *c_conta;
        *c_conta = *c_conta + 1;
        okConta++;
    }
    for (i = 0;i < *c_op;i++) {
        if ((*operacaoC)[i].idOperacao == *c_idOp) {
            valorTotal = valorTotal + (*operacaoC)[i].valorDeve;
        }
    }
    char tempOp[2];

    printf("Como será feito o pagamento: \n1- Avista         2- A prazo\n");
    scanf("%s", tempOp);
    tipoPag = strtol(tempOp, NULL, 10);

    if (tipoPag == 1) {
        financeiroC->caixa = financeiroC->caixa + valorTotal;
        newMovAD(movC, c_mov, tamMov, valorTotal, tipoDado);
        for (i = 0;i < *c_op;i++) {
            if ((*operacaoC)[i].idOperacao == *c_idOp) {
                (*operacaoC)[i].valorTotal = valorTotal;
                (*operacaoC)[i].valorDeve = 0;
                (*operacaoC)[i].parcelas = 0;
                (*operacaoC)[i].tipoPag = 1;
            }
        }
        valorTotal = 0;
    } else {
        if (tipoPag == 2) {
            printf("O cliente pagara algum valor de entrada?\n"
                   "1-Sim                            2-Não\n");
            scanf("%d", &op_ent);
            if (op_ent == 1) {
                printf("Informe o valor de entrada da locação: ");
                scanf("%f", &valorEnt);
                //caixaAux = financeiroC->caixa;
                //caixaAux = caixaAux + valorEnt;
                financeiroC->caixa = financeiroC->caixa + valorEnt;
                newMovAD(movC, c_mov, tamMov, valorEnt, tipoDado);
                valorRest = valorTotal - valorEnt;
                financeiroC->areceber = financeiroC->areceber + valorRest;
                printf("Em quantas parcelas o cliente deseja dividir o valor restante de R$ %.2f (max. 3 parcelas): ", valorRest);
                scanf("%d", &parcelas);
                (*contaC)[idConta].valorDeve = (*contaC)[idConta].valorDeve + valorRest;
                for (
                        i = 0;
                        i < *
                                c_op;
                        i++) {
                    if ((*operacaoC)[i].idOperacao == *c_idOp) {
                        (*operacaoC)[i].valorTotal = valorTotal;
                        (*operacaoC)[i].valorDeve = valorRest;
                        (*operacaoC)[i].parcelas = parcelas;
                        (*operacaoC)[i].tipoPag = 2;
                    }
                }
                valorTotal = 0;
            } else {
                if (op_ent == 2) {
                    printf("Em quantas parcelas o cliente deseja dividir o valor da locacao de R$ %.2f (max. 3 parcelas): ",
                           valorTotal);
                    scanf("%d", &parcelas);
                    financeiroC->areceber = financeiroC->areceber + valorTotal;
                    (*contaC)[idConta].valorDeve = (*contaC)[idConta].valorDeve + valorTotal;
                    for (i = 0;i < *c_op;i++) {
                        if ((*operacaoC)[i].idOperacao == *c_idOp) {
                            (*operacaoC)[i].valorTotal = valorTotal;
                            (*operacaoC)[i].valorDeve = valorTotal;
                            (*operacaoC)[i].parcelas = parcelas;
                            (*operacaoC)[i].tipoPag = 2;
                        }
                    }
                    valorTotal = 0;
                }
            }
        }
    }
    for (
            i = 0;
            i < *
                    c_op;
            i++) {
        if ((*operacaoC)[i].idOperacao == *c_idOp) {
            (*operacaoC)[i].
                    ex = ex_total;
        }
    }
    gravar_conta(*contaC, *c_conta, tipoDado);
    gravar_op(*operacaoC, *c_op, tipoDado);
    regravar_filme(filmeC, c_filme, tipoDado);
    gravar_financeiro(financeiroC, tipoDado);

    *c_idOp = *c_idOp + 1;
}



void criar_conta(contaCliente **contaC, int c_conta, int *tamConta) {

    if (c_conta == *tamConta) {
        *tamConta = *tamConta + 1;
        (*contaC) = (contaCliente *) (realloc((*contaC), *tamConta * sizeof(contaCliente)));

    }
    if ((*contaC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void listaOperacao(operacoes *operacaoC, int c_op, int c_idOp, contaCliente *contaC, int c_conta, filme *filmeC,
                   int c_filme) {
    int i = 0, j = 0, idContas[c_conta], idOp = 0, p = 0, menOp = 0, quant = 0, tipo = 0, exOp[c_idOp], op = 0;

    operacoes newOp[c_op];
    for (i = 0; i < c_op; i++) {
        newOp[i] = operacaoC[i];
    }

    contaCliente newConta[c_conta];
    for (i = 0; i < c_conta; i++) {
        newConta[i] = contaC[i];
    }

    // organiza as contas dos clientes por ordem do codigo
    for (i = 0; i < c_conta; i++) {
        for (j = i + 1; j < c_conta; j++) {
            if (newConta[i].codigo > newConta[j].codigo) {
                contaCliente aux = newConta[i];
                newConta[i] = newConta[j];
                newConta[j] = aux;
            }
        }
    }

        for (i = 0; i < c_conta; i++) {
            printf("===================================================================");
            printf("\nCliente (%d):\n", newConta[i].codigo);
            printf("Nome: %s \nValor devido: R$ %.2f\n\n", newConta[i].nome, newConta[i].valorDeve);
            // verifica conta e operacao do msm cliente
            for (j = 0; j < c_op; j++) {
                if (newConta[i].codigo == newOp[j].codCliente) {
                    op = newOp[j].idOperacao;
                    printf("Operacao (%d):\n", op);
                    quant = newOp[j].ex;
                    // verifica operações com codigo igual
                    for (int k = 0; k < c_op; k++) {
                        if (newOp[k].idOperacao == op) {
                            printf("Cod Filme: %d\nNome Filme: %s\n", operacaoC[k].codFilme, operacaoC[k].nomeFilme);
                            if (operacaoC[k].devolveu == 0) {
                                printf("Devolvido: Nao\n");
                            } else {
                                printf("Devolvido: Sim\n");
                            }
                        }
                    }

                    printf("Valor total: R$ %.2f\nValor devido: R$ %.2f\nData locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n\n",
                           newOp[j].valorTotal,
                           newOp[j].valorDeve,
                           newOp[j].dataLoc.dia,
                           newOp[j].dataLoc.mes, operacaoC[j].dataLoc.ano,
                           newOp[j].dataDev.dia, operacaoC[j].dataDev.mes, operacaoC[j].dataDev.ano);
                    // pula as operacoes no laço j para n repetir
                    j = j + (quant - 1);
                }
            }
        }
}


void pagarConta(contaCliente **contaC, int c_conta, operacoes **operacaoC, int c_op, financeiro **financeiroC, int tipoDado, movimentacao **movC, int *c_mov, int *tamMov) {
    int idCliente = 0, i, okConta = 0, op = 0, quant = 0, opPaga = 0, okOp = 0, confirmPag = 0, quantParc = 0, pOp = 0, okPaga = 0;
    float valorPago = 0, unParc = 0;

    printf("ID do usuario: \n");
    scanf("%d", &idCliente);
    for (i = 0; i < c_conta; i++) {
        if ((*contaC)[i].codigo == idCliente) {
            if ((*contaC)[i].valorDeve != 0.0) {
                printf("\nCliente (%d):\nNome: %s \nValor devido: R$ %.2f\n\n", (*contaC)[i].codigo, (*contaC)[i].nome,
                       (*contaC)[i].valorDeve);
                okPaga++;
            }
            okConta++;
        }
    }

    if (okConta == 0) {
        printf("O cliente %d nao possui conta cadastrada.\n", idCliente);
        return;
    }
    if (okPaga == 0) {
        printf("O cliente %d nao possui contas em aberto.\n", idCliente);
        return;
    }

    for (i = 0; i < c_op; i++) {
        if ((*operacaoC)[i].codCliente == idCliente) {
            op = (*operacaoC)[i].idOperacao;
            printf("Operacao (%d):\n", op);
            quant = (*operacaoC)[i].ex;
            // verifica operações com codigo igual
            for (int k = 0; k < c_op; k++) {
                if (((*operacaoC)[k].idOperacao == op) && ((*operacaoC)[k].valorDeve > 0.0)) {
                    printf("Cod Filme: %d\nNome Filme: %s\n", (*operacaoC)[k].codFilme, (*operacaoC)[k].nomeFilme);
                }
            }
            printf("Valor total: R$ %.2f\nValor devido: R$ %.2f\nData locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n\n",
                   (*operacaoC)[i].valorTotal,
                   (*operacaoC)[i].valorDeve,
                   (*operacaoC)[i].dataLoc.dia,
                   (*operacaoC)[i].dataLoc.mes, (*operacaoC)[i].dataLoc.ano,
                   (*operacaoC)[i].dataDev.dia, (*operacaoC)[i].dataDev.mes, (*operacaoC)[i].dataDev.ano);
            // pula as operacoes no laço j para n repetir
            i = i + (quant - 1);
        }
    }

    printf("Qual operacao sera paga: ");
    scanf("%d", &opPaga);

    for (i = 0; i < c_op; i++) {
        if ((*operacaoC)[i].idOperacao == opPaga) {
            pOp = i;
            okOp++;
            break;
        }
    }
    if (okOp == 0) {
        printf("A operação informada nao existe.\n");
        return;
    }

    if ((*operacaoC)[pOp].parcelas == 1) {
        printf("Deve ser pago o valor restante de R$ %.2f.\nConfirmar pagamento:... 1\n"
               "Sair:.................. 2\n", (*operacaoC)[pOp].valorDeve);
        scanf("%d", &confirmPag);
        if (confirmPag == 1) {
            for (i = 0; i < c_op; i++) {
                if ((*operacaoC)[i].idOperacao == opPaga) {
                    valorPago = (*operacaoC)[i].valorDeve;
                    (*operacaoC)[i].valorDeve = 0;
                    (*operacaoC)[i].parcelas = 0;
                }
            }
            (*financeiroC)->caixa = (*financeiroC)->caixa + valorPago;
            newMovAD(movC, c_mov, tamMov, valorPago, tipoDado);
            (*financeiroC)->areceber = (*financeiroC)->areceber - valorPago;
            for (i = 0; i < c_conta; i++) {
                if ((*contaC)[i].codigo == idCliente) {
                    (*contaC)[i].valorDeve = (*contaC)[i].valorDeve - valorPago;
                }
            }
        } else {
            return;
        }
    } else {
        unParc = (*operacaoC)[pOp].valorDeve / (float)(*operacaoC)[pOp].parcelas;
        printf("Parcelas: %d\nValor de cada parcela: R$ %.2f\nO cliente deseja pagar quantas parcelas: ",
               (*operacaoC)[pOp].parcelas, unParc);
        scanf("%d", &quantParc);
        if (quantParc <= (*operacaoC)[pOp].parcelas) {
            valorPago = unParc * (float)quantParc;
            printf("Confirmar pagamento de R$ %.2f:\nSim:...... 1\n"
                   "Sair:..... 2\n", valorPago);
            scanf("%d", &confirmPag);
            if (confirmPag == 1) {
                for (i = 0; i < c_op; i++) {
                    if ((*operacaoC)[i].idOperacao == opPaga) {
                        (*operacaoC)[i].valorDeve = (*operacaoC)[i].valorDeve - valorPago;
                        (*operacaoC)[i].parcelas = (*operacaoC)[i].parcelas - quantParc;
                    }
                }
                (*financeiroC)->caixa = (*financeiroC)->caixa + valorPago;
                newMovAD(movC, c_mov, tamMov, valorPago,tipoDado);
                (*financeiroC)->areceber = (*financeiroC)->areceber - valorPago;
                for (i = 0; i < c_conta; i++) {
                    if ((*contaC)[i].codigo == idCliente) {
                        (*contaC)[i].valorDeve = (*contaC)[i].valorDeve - valorPago;
                    }
                }
            } else {
                return;
            }
        } else {
            return;
        }
    }
    gravar_op(*operacaoC, c_op, tipoDado);
    gravar_conta(*contaC, c_conta, tipoDado);
    gravar_financeiro(*financeiroC, tipoDado);
}



void devolucaoFilme(operacoes **operacaoC, int c_op, contaCliente **contaC, int c_conta, filme **filmeC, int c_filme, int tipoDado, locadora **locadora, financeiro **financeiroC,
                    movimentacao **movC, int *c_mov, int *tamMov) {
    int idCliente, i, okOp = 0, okDevolveu = 0, pconta, idOp, confirm = 0, typeDev = 0, codFilme = 1, codOk = 0, primeiraExecute = 0, existe = 0;
    int dias = 0, pos = 0, j, id;
    float multa = 0;
    printf("ID do cliente: ");
    scanf("%d", &idCliente);

    for (i = 0; i < c_op; i++) {
        if ((*operacaoC)[i].codCliente == idCliente) {
            if ((*operacaoC)[i].devolveu == 0) {
                okDevolveu++;
            }
            okOp++;
        }
    }

    if (okOp == 0) {
        printf("O cliente %d nao possui nenhuma operacao de locacao.\n", idCliente);
        return;
    }
    if (okDevolveu == 0) {
        printf("O cliente %d nao possui nenhuma devolucao em aberto.\n", idCliente);
        return;
    }

    for (i = 0; i < c_conta; i++) {
        if ((*contaC)[i].codigo == idCliente) {
            printf("\nCliente (%d):\nNome: %s \nValor devido: R$ %.2f\n\n", (*contaC)[i].codigo, (*contaC)[i].nome,
                   (*contaC)[i].valorDeve);
        }
    }

    for(i=0; i < c_op; i++){
        if((*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0){
         printf("Operacao [%d]:\n", (*operacaoC)[i].idOperacao);
         printf("Filme [Cod %d]: %s \n", (*operacaoC)[i].codFilme, (*operacaoC)[i].nomeFilme);
         pos=i;
         id = (*operacaoC)[i].idOperacao;
            for(j=pos+1; j < c_op; j++){
                if((*operacaoC)[j].codCliente == idCliente && (*operacaoC)[j].devolveu == 0 && (*operacaoC)[j].idOperacao == id){
                    printf("Filme [Cod %d]: %s \n", (*operacaoC)[j].codFilme, (*operacaoC)[j].nomeFilme);
                }
            }
            printf("Data locacao: %d / %d / %d \nData a devolver: %d / %d / %d \n",  (*operacaoC)[pos].dataLoc.dia, (*operacaoC)[pos].dataLoc.mes, (*operacaoC)[pos].dataLoc.ano,
                   (*operacaoC)[pos].dataDev.dia,(*operacaoC)[pos].dataDev.mes,(*operacaoC)[pos].dataDev.ano);
            break;
        }
    }




//    for (i = 0; i < c_op; i++) {
//        if (i == 0 && (*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0) {
//            printf("Operacao(%d):\n", (*operacaoC)[i].idOperacao);
//        } else {
//            if (i != 0 && (*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0 &&
//                (*operacaoC)[i].idOperacao != (*operacaoC)[i - 1].idOperacao) {
//                printf("Operacao(%d):\n", (*operacaoC)[i].idOperacao);
//            }
//        }
//        if ((*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0) {
//            printf("Cod Filme: %d\nNome Filme: %s\n", (*operacaoC)[i].codFilme, (*operacaoC)[i].nomeFilme);
//            printf("Data locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n\n",
//                   (*operacaoC)[i].dataLoc.dia,
//                   (*operacaoC)[i].dataLoc.mes, (*operacaoC)[i].dataLoc.ano,
//                   (*operacaoC)[i].dataDev.dia, (*operacaoC)[i].dataDev.mes, (*operacaoC)[i].dataDev.ano);
//        }
//    }

    printf("ID da operacao: ");
    scanf("%d", &idOp);

    for(i=0; i < c_op; i++){
        if(idOp == (*operacaoC)[i].idOperacao && (*operacaoC)[i].devolveu == 0){
            existe++;
        }
    }

    if(existe == 0){
        printf("Nao existem devolucoes em aberto com o codigo informado.\n");
        return;
    }
    for (i = 0; i < c_op; i++) {
        if ((*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0 && (*operacaoC)[i].idOperacao == idOp) {
            printf("Cod Filme: %d\nNome Filme: %s\n", (*operacaoC)[i].codFilme, (*operacaoC)[i].nomeFilme);
            printf("Data locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n\n",
                   (*operacaoC)[i].dataLoc.dia,
                   (*operacaoC)[i].dataLoc.mes, (*operacaoC)[i].dataLoc.ano,
                   (*operacaoC)[i].dataDev.dia, (*operacaoC)[i].dataDev.mes, (*operacaoC)[i].dataDev.ano);

        }
    }

    printf("Sera feita devolucao completa dos filmes acima:\n1- Sim               2- Não   ");
    scanf("%d", &typeDev);

    if (typeDev == 1) {
        for (i = 0; i < c_op; i++) {
            if ((*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0 &&
                (*operacaoC)[i].idOperacao == idOp) {
                pos = i;
                (*operacaoC)[i].devolveu = 1;
                obterData(&(*operacaoC)[i].dataEntregue);

                    for (j = 0; j < c_filme; j++) {
                    if ((*operacaoC)[i].codFilme == (*filmeC)[j].codigoFilme) {
                        (*filmeC)[j].exemplarFilme = (*filmeC)[j].exemplarFilme + 1;
                        (*filmeC)[j].exLocados = (*filmeC)[j].exLocados - 1;
                    }
                }
            }
        }

        dias = diasEntreDatas((*operacaoC)[pos].dataEntregue, (*operacaoC)[pos].dataDev);

        if(dias < 0){
            dias = dias *-1;
            multa = (float)(dias)* (*locadora)->multa;
            printf("Deve ser paga a multa de R$ %.2f por %d dias de atraso.\n", multa, dias);
            (*financeiroC)->caixa = (*financeiroC)->caixa + multa;
            newMovAD(movC, c_mov, tamMov, multa,tipoDado);
            system("pause");
        }


    } else {

        do {
            printf("Codigo do filme a ser devolvido (Digite 0 se os filmes ja foram informados): ");
            scanf("%d", &codFilme);
            for (i = 0; i < c_op; i++) {
                if ((*operacaoC)[i].codCliente == idCliente && (*operacaoC)[i].devolveu == 0 &&
                    (*operacaoC)[i].idOperacao == idOp && (*operacaoC)[i].codFilme == codFilme) {
                    (*operacaoC)[i].devolveu = 1;
                    codOk++;
                    pos = i;

                    obterData(&(*operacaoC)[i].dataEntregue);

                    for (j = 0; j < c_filme; j++) {
                        if ((*filmeC)[j].codigoFilme == codFilme) {
                            (*filmeC)[j].exemplarFilme = (*filmeC)[j].exemplarFilme + 1;
                            (*filmeC)[j].exLocados = (*filmeC)[j].exLocados - 1;
                        }
                    }
                }
            }

            if(codFilme == 0){
                dias = diasEntreDatas((*operacaoC)[pos].dataEntregue, (*operacaoC)[pos].dataDev);
                if(dias < 0){
                    dias = dias *-1;
                    multa = (float)(dias)* (*locadora)->multa;
                    printf("Deve ser paga a multa de R$ %.2f por %d dias de atraso.\n", multa, dias);
                    (*financeiroC)->caixa = (*financeiroC)->caixa + multa;
                    newMovAD(movC, c_mov, tamMov, multa,tipoDado);
                    system("pause");
                }


            }

            if (codOk == 0) {
                printf("O filme informado ja foi devolvido ou não existe.\n");
            }
            codOk = 0;
        } while (codFilme != 0);
    }
    gravar_financeiro(*financeiroC, tipoDado);
    gravar_op(*operacaoC, c_op, tipoDado);
    regravar_filme(*filmeC, c_filme, tipoDado);
}



void menu() {
    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                       LOCADORA                         %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Filmes                  7 - Locadora            %c\n", 186, 186);
    printf("%c    2 - Categorias              8 - Contas              %c\n", 186, 186);
    printf("%c    3 - Funcionarios            9 - Feedback            %c\n", 186, 186);
    printf("%c    4 - Clientes                10- Exportacao          %c\n", 186, 186);
    printf("%c    5 - Fornecedores            11- Importacao          %c\n", 186, 186);
    printf("%c    6 - Locacao                 12 - Limpar arquivos    %c\n", 186, 186);
    printf("%c                        0 - Sair                        %c\n", 186, 186);

//    printf("%c    6 - Locacao                                         %c\n", 186, 186);
//    printf("%c    7 - Locadora                                        %c\n", 186, 186);
//    printf("%c    8 - Contas                                          %c\n", 186, 186);
//    printf("%c    9 - Feedback                                        %c\n", 186, 186);
//    printf("%c    10 - Sair                                           %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // seta
    printf("%c ", 175);
}



void menuContas() {
    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                       FINANCEIRO                        %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Contas a receber                                %c\n", 186, 186);
    printf("%c    2 - Contas a pagar                                  %c\n", 186, 186);
    printf("%c    3 - Caixa                                           %c\n", 186, 186);
    printf("%c    4 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // seta
    printf("%c ", 175);
}



void menuLocacao() {
    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                        LOCACAO                         %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Locar filmes                                    %c\n", 186, 186);
    printf("%c    2 - Visualizar locacoes                             %c\n", 186, 186);
    printf("%c    3 - Pagar locacao                                   %c\n", 186, 186);
    printf("%c    4 - Devolucao de filmes                             %c\n", 186, 186);
    printf("%c    5 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);
}



int verificaForn(int *codForn, fornecedor *fornecedorC, int c_forn, int *pforn) {
    int cod = 0, i = 0;

    printf("ID do fornecedor: ");
    scanf("%d", &cod);

    for (i = 0; i < c_forn; i++) {
        if (fornecedorC[i].codigo == cod) {
            *codForn = cod;
            *pforn = i;
            return 1;
        }
    }
    printf("Nao foi encontrado nenhum fornecedor com ID %d.\n", cod);
    return 0;
}



void criaNovoFilme(filme **filmeC, int *c_filme, int *tamFilme, compra **compraC, int p_compra, int *c_pendente, int tipoDado){

    if (*c_filme == *tamFilme) {
        *tamFilme = *tamFilme + 1;
        (*filmeC) = (filme *) (realloc((*filmeC), *tamFilme * sizeof(filme)));
    }
    if ((*filmeC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

    (*filmeC)[*c_filme].codigoFilme = -1;
    strcpy((*filmeC)[*c_filme].descricao, (*compraC)[p_compra].nomeFilme);
    (*filmeC)[*c_filme].exLocados = 0;
    (*filmeC)[*c_filme].exemplarFilme = (*compraC)[p_compra].ex;
    (*filmeC)[*c_filme].pendente = 0;
    strcpy((*filmeC)[*c_filme].lingua, "preencher");
    (*filmeC)[*c_filme].codigoCategoria = -1;
    *c_pendente = *c_pendente + 1;
    gravar_filme(*filmeC, *c_filme, tipoDado);
    *c_filme = *c_filme + 1;
}



void compraFilme(fornecedor *fornecedorC, int c_forn, filme **filmeC, int *c_filme, int *tamFilme, compra **compraC, int *c_compra, int *tamCompra, int *c_idCompra, int *c_pendente, financeiro **financeiroC, int tipoDado,
                 movimentacao **movC, int *c_mov, int *tamMov) {

    int codForn, pforn = 0, confirma = 0, num_ex = 0, ok = 0, i, j, verify = 0, p_compra, tipoPag = 0, tipoEnt = 0, parcelas = 0;
    char descricao[50], newFilme[50];
    float valorFilme = 0, valorImposto = 0, impostoUnic = 0, freteUnic = 0, valorTotal = 0, valorPago = 0, valorDeve = 0, valorEnt = 0, valorRest = 0;
    float totalFilme = 0, valorFrete = 0;

    if (verificaForn(&codForn, fornecedorC, c_forn, &pforn) == 0) {
        return;
    }

    do {
        printf("Informe o nome do filme que deseja comprar: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]s", descricao);
        strlwr(descricao);
        printf("Exemplares: ");
        scanf("%d", &num_ex);
        printf("Valor do filme: R$ ");
        scanf("%f", &valorFilme);

        if (*c_compra == *tamCompra) {
            *tamCompra = *tamCompra + 1;
            (*compraC) = (compra *) (realloc((*compraC), *tamCompra * sizeof(compra)));
        }
        if ((*compraC) == NULL) {
            printf("/nErro de alocacao de memoria.");
        }
        strcpy((*compraC)[*c_compra].nomeFilme, descricao);
        strcpy((*compraC)[*c_compra].razaoSocial, fornecedorC[pforn].razaoSocial);
        strcpy((*compraC)[*c_compra].cnpj, fornecedorC[pforn].cnpj);
        (*compraC)[*c_compra].idFornecedor = codForn;
        (*compraC)[*c_compra].idOperacao = *c_idCompra;
        (*compraC)[*c_compra].valorFilme = valorFilme;
        (*compraC)[*c_compra].ex = num_ex;
        (*compraC)[*c_compra].filmeTotal = valorFilme * (float)num_ex;
        valorFilme = 0;
        num_ex = 0;


        printf("Comprar mais filmes?\nSim:            1\n"
               "Nao:            2: ");
        scanf("%d", &verify);

        *c_compra = *c_compra + 1;

    } while (verify != 2);

    for (i = 0; i < *c_compra; i++) {
        if ((*compraC)[i].idOperacao == *c_idCompra) {
            totalFilme = totalFilme + (*compraC)[i].valorFilme;
        }
    }

    printf("Imposto: R$ ");
    scanf("%f", &valorImposto);
    printf("Frete: R$ ");
    scanf("%f", &valorFrete);

    //calcular imposto por unidade
    impostoUnic = valorImposto / totalFilme;
    freteUnic = valorFrete / totalFilme;

    for (i = 0; i < *c_compra; i++) {
        if ((*compraC)[i].idOperacao == *c_idCompra) {
            (*compraC)[i].dataPago.dia = 00;
            (*compraC)[i].dataPago.mes = 00;
            (*compraC)[i].dataPago.ano = 00;
            obterData(&(*compraC)[i].dataCompra);
            valorTotal = valorTotal + (*compraC)[i].filmeTotal;
            (*compraC)[i].valorImposto = impostoUnic;
            (*compraC)[i].impostoTotal = valorImposto;
            (*compraC)[i].valorFrete = freteUnic;
            (*compraC)[i].freteTotal = valorFrete;
            (*compraC)[i].precoFilme = (*compraC)[i].valorFilme + (*compraC)[i].valorFrete + (*compraC)[i].valorImposto;
        }
    }

    valorTotal = valorTotal + valorImposto + valorFrete;

    for (i = 0; i < *c_compra; i++) {
        if ((*compraC)[i].idOperacao == *c_idCompra) {
            (*compraC)[i].valorTotal = valorTotal;
        }
    }

    for (i = 0; i < *c_compra; i++) {
        if ((*compraC)[i].idOperacao == *c_idCompra) {
            for (j = 0; j < *c_filme; j++) {
                strcpy(newFilme, strlwr((*filmeC)[j].descricao));
                //printf("Filme cadastrado: %s\nFilme informado: %s\n", newFilme, descricao);
                if (strcmp(newFilme, (*compraC)[i].nomeFilme) == 0) {
                    (*filmeC)[j].exemplarFilme = (*filmeC)[j].exemplarFilme + (*compraC)[i].ex;
                    ok++;
                }
            }
            if (ok == 0) {
                p_compra = i;
                criaNovoFilme(filmeC, c_filme, tamFilme, compraC, p_compra, c_pendente, tipoDado);
            }
            ok = 0;
        }
    }

    printf("Tipo de pagamento:\n"
           "1                 A vista\n"
           "2                 A prazo:\n");
    scanf("%d", &tipoPag);

    if (tipoPag == 1) {
        (*financeiroC)->caixa = (*financeiroC)->caixa - valorTotal;
        newMovSUB(movC, c_mov, tamMov, valorTotal,tipoDado);

        for (i = 0; i < *c_compra; i++) {
            if ((*compraC)[i].idOperacao == *c_idCompra) {
                obterData(&(*compraC)[i].dataPago);
                (*compraC)[i].valorDeve = 0;
                (*compraC)[i].parcelas = 0;
            }
        }

    } else {

        if (tipoPag == 2) {
            printf("Deseja dar um valor de entrada:\n"
                          "1                          Sim\n"
                          "2                          Nao: ");
            scanf("%d", &tipoEnt);
            if (tipoEnt == 1) {
                printf("Valor de entrada: R$ ");
                scanf("%f", &valorEnt);
                valorRest = valorTotal - valorEnt;
                (*financeiroC)->caixa = (*financeiroC)->caixa - valorEnt;
                newMovSUB(movC, c_mov, tamMov, valorEnt,tipoDado);
                printf("Em quantas parcelas deseja dividir o valor de R$ %.2f (max 3): ", valorRest);
                scanf("%d", &parcelas);

                for (i = 0; i < *c_compra; i++) {
                    if ((*compraC)[i].idOperacao == *c_idCompra) {
                        (*compraC)[i].valorDeve = valorRest;
                        (*compraC)[i].parcelas = parcelas;
                    }
                }
                (*financeiroC)->despesa = (*financeiroC)->despesa + valorRest;
            }else{
                if(tipoEnt == 2){
                    printf("Em quantas parcelas deseja dividir o valor de R$ %.2f (max 3): ", valorTotal);
                    scanf("%d", &parcelas);

                    for (i = 0; i < *c_compra; i++) {
                        if ((*compraC)[i].idOperacao == *c_idCompra) {
                            (*compraC)[i].valorDeve = valorTotal;
                            (*compraC)[i].parcelas = parcelas;
                        }
                    }
                    (*financeiroC)->despesa = (*financeiroC)->despesa + valorTotal;
                }
            }
        }
    }

    *c_idCompra = *c_idCompra + 1;
    gravar_compra(*compraC, *c_compra, tipoDado);
    regravar_filme(*filmeC, *c_filme, tipoDado);
    gravar_financeiro(*financeiroC, tipoDado);

}



void verificaPendentes(filme *filmeC, int c_filme, int *c_pendente){
    int i;
 for(i=0; i < c_filme; i++){
     if(filmeC[i].codigoFilme == -1){
         *c_pendente = *c_pendente + 1;
     }
 }
}



void listaCompras(compra *compraC, int c_compra, fornecedor *fornecedorC, int c_forn, int c_idCompra) {
    int i, j, id, pos;

    if (c_idCompra > 1) {
        for (i = 1; i < c_idCompra; i++) {

            for (j = 0; j < c_compra; j++) {
                if (compraC[j].idOperacao == i) {
                    //printf("\nTOTAL: %.2f\n\n", compraC[j].filmeTotal);
                    printf(" Compra (%d)\n", i);
                    printf("%c", 218);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 191);
                    printf("%c %-17s| %-50s %c\n", 179,"Fornecedor",compraC[j].razaoSocial, 179);
                    printf("%c %-17s| %-50s %c\n",179,"CNPJ", compraC[j].cnpj,179);
                    printf("%c %-17s| R$ %.2f       |%-17s| R$ %.2f        %c\n",179,"Frete:", compraC[j].freteTotal, "Imposto:", compraC[j].impostoTotal,179);
                    printf("%-72c", 179);
                    printf("%c\n", 179);
                    printf("%c %-17s| %d | %d | %d                                     %c\n", 179, "Data de compra: ", compraC[j].dataCompra.dia, compraC[j].dataCompra.mes, compraC[j].dataCompra.ano, 179);
                    printf("%-72c", 179);
                    printf("%c\n", 179);
                    printf("%c                                 Filmes                                %c\n", 179, 179);
                    printf("%c", 195);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-25s | %-11s |%-10s |%-11s %c\n",179, "Descricao", "Preco Custo (R$)", "Quantidade", "Total (R$)", 179);
                    break;
                }
            }

            for (j = 0; j < c_compra; j++) {
                if (compraC[j].idOperacao == i) {
                    printf("%c %-25s | %-16.2f | %-9.d | %-10.2f %c\n", 179, compraC[j].nomeFilme, compraC[j].valorFilme, compraC[j].ex, compraC[j].precoFilme, 179);
                    pos = j;
                }
            }
            printf("%c", 195);
            for(int t=0; t < 71; t++){
                printf("%c", 196);
            }
            printf("%c\n", 180);
            printf("%c %-56s | R$ %-7.2f %c\n", 179, "Total da nota (filmes + frete + impostos):", compraC[pos].valorTotal, 179);
            printf("%c", 192);
            for(int t=0; t < 71; t++){
                printf("%c", 196);
            }
            printf("%c\n", 217);
        }
        system("pause");
    }
}



void contasReceber(contaCliente **contaC, int c_conta, operacoes **operacaoC, int c_op, financeiro **financeiroC, int c_idOp){
    int i = 0, j = 0, idContas[c_conta], idOp = 0, p = 0, menOp = 0, quant = 0, tipo = 0, exOp[c_idOp], op = 0;

    operacoes newOp[c_op];
    for (i = 0; i < c_op; i++) {
        newOp[i] = (*operacaoC)[i];
    }

    contaCliente newConta[c_conta];
    for (i = 0; i < c_conta; i++) {
        newConta[i] = (*contaC)[i];
    }

    // organiza as contas dos clientes por ordem do codigo
    for (i = 0; i < c_conta; i++) {
        for (j = i + 1; j < c_conta; j++) {
            if (newConta[i].codigo > newConta[j].codigo) {
                contaCliente aux = newConta[i];
                newConta[i] = newConta[j];
                newConta[j] = aux;
            }
        }
    }

    for (i = 0; i < c_conta; i++) {
        if (newConta[i].valorDeve > 0.0) {
            printf("===================================================================");
            printf("\nCliente (%d):\n", newConta[i].codigo);
            printf("Nome: %s \nValor devido: R$ %.2f\n\n", newConta[i].nome, newConta[i].valorDeve);
            for (j = 0; j < c_op; j++) {
                if (newConta[i].codigo == newOp[j].codCliente && newOp[j].valorDeve > 0.0) {
                    op = newOp[j].idOperacao;
                    printf("Operacao (%d):\n", op);
                    quant = newOp[j].ex;

                    printf("Valor total: R$ %.2f\nValor devido: R$ %.2f\nData locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n\n",
                           newOp[j].valorTotal,
                           newOp[j].valorDeve,
                           newOp[j].dataLoc.dia,
                           newOp[j].dataLoc.mes, (*operacaoC)[j].dataLoc.ano,
                           newOp[j].dataDev.dia, (*operacaoC)[j].dataDev.mes, (*operacaoC)[j].dataDev.ano);
                    // pula as operacoes no laço j para n repetir
                    j = j + (quant - 1);
                }
            }
        }
    }
}



void carregarMov(movimentacao **movC, int *c_mov, int *tamMov, int tipoDado) {

        if(tipoDado == 1) {
            FILE *u;
            u = fopen("movimentacao.txt", "r");

            if (u == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(u)) {
                    break;
                }

                if (*c_mov == *tamMov) {
                    *tamMov = *tamMov + 1;
                    (*movC) = (movimentacao *) (realloc((*movC), *tamMov * sizeof(movimentacao)));
                }

                if ((*movC) == NULL) {
                    printf("\nErro de alocacao de memoria.\n");
                }

                fscanf(u, "%f\n", &(*movC)[*c_mov].valorAntes);

                if (feof(u)) {
                    break;
                }

                fscanf(u, "%f\n", &(*movC)[*c_mov].valorDepois);
                fscanf(u, "%f\n", &(*movC)[*c_mov].operacao);
                fscanf(u, "%d\n", &(*movC)[*c_mov].dataOp.dia);
                fscanf(u, "%d\n", &(*movC)[*c_mov].dataOp.mes);
                fscanf(u, "%d\n", &(*movC)[*c_mov].dataOp.ano);

                *c_mov = *c_mov + 1;

                if (feof(u)) {
                    break;
                }

            }
            fclose(u);
        }else{
            if(tipoDado == 2){
                FILE *u;
                u = fopen("movimentacao.bin", "rb");

                if (u == NULL) {
                    printf("Erro para abrir arquivo.\n");
                    exit(1);
                }

                while (1) {

                    if (feof(u)) {
                        break;
                    }

                    if (*c_mov == *tamMov) {
                        *tamMov = *tamMov + 1;
                        (*movC) = (movimentacao *) (realloc((*movC), *tamMov * sizeof(movimentacao)));
                    }

                    if ((*movC) == NULL) {
                        printf("\nErro de alocacao de memoria.\n");
                    }

                    fread(&(*movC)[*c_mov], sizeof(movimentacao), 1,u);

                    if (feof(u)) {
                        break;
                    }


                    *c_mov = *c_mov + 1;

                    if (feof(u)) {
                        break;
                    }

                }
                fclose(u);



            }
        }

}







void contasPagar (compra **compraC, int c_compra, financeiro **financeiroC, int tipoDado, movimentacao **movC, int *c_mov, int *tamMov){
    int i, j, k, pos = 0, cod = 0, op=0, quant = 0;

    for(i=0; i < c_compra; i++){
        if((*compraC)[i].valorDeve > 0.0){
            cod = (*compraC)[i].idOperacao;
            for(j=0; j < c_compra; j++){
                if((*compraC)[j].idOperacao == cod){
                    quant++;
                }
            }
                if((*compraC)[i].idOperacao == cod) {

                    printf(" Compra (%d)\n", cod);
                    printf("%c", 218);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 191);
                    printf("%c %-17s| %-50s %c\n", 179,"Fornecedor",(*compraC)[i].razaoSocial, 179);
                    printf("%c %-17s| %-50s %c\n",179,"CNPJ", (*compraC)[i].cnpj,179);
                    printf("%c %-17s| R$ %.2f       |%-17s| R$ %.2f        %c\n",179,"Frete:", (*compraC)[i].freteTotal, "Imposto:", (*compraC)[i].impostoTotal,179);
                    printf("%-72c", 179);
                    printf("%c\n", 179);
                    printf("%c                                 Filmes                                %c\n", 179, 179);
                    printf("%c", 195);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-25s | %-11s |%-10s |%-11s %c\n",179, "Descricao", "Preco Custo (R$)", "Quantidade", "Total (R$)", 179);

                    for (k = 0; k < c_compra; k++) {
                        if ((*compraC)[k].idOperacao == cod) {
                            printf("%c %-25s | %-16.2f | %-9.d | %-10.2f %c\n", 179, (*compraC)[k].nomeFilme, (*compraC)[k].valorFilme, (*compraC)[k].ex, (*compraC)[k].precoFilme, 179);
                            pos = k;
                        }
                    }
                    printf("%c", 195);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-56s | R$ %-7.2f %c\n", 179, "Total da nota (filmes + frete + impostos):", (*compraC)[pos].valorTotal, 179);

                    printf("%c", 195);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-56s | R$ %-7.2f %c\n", 179, "Valor devido:", (*compraC)[pos].valorDeve, 179);

                    printf("%c", 192);
                    for(int t=0; t < 71; t++){
                        printf("%c", 196);
                    }
                    printf("%c\n", 217);


                printf("Pagar compra: \n1 Sim\t2 Nao\t3 Sair: ");
                scanf("%d", &op);

                if(op == 1){
                    pagarCompra(financeiroC, compraC, c_compra, cod, movC, c_mov, tamMov, tipoDado);
                    gravar_financeiro(*financeiroC, tipoDado);
                    gravar_compra(*compraC, c_compra, tipoDado);
                    return;
                }else{
                    if(op == 2){
                        i= i + (quant - 1);
                        quant = 0;
                    } else{
                        if(op == 3){
                            return;
                        }
                    }
                }
            }
        }
    }
}



void pagarCompra(financeiro **financeiroC, compra **compraC, int c_compra, int cod, movimentacao **movC, int *c_mov, int *tamMov, int tipoDado){
    int i, j, k, pos = 0, parcelas = 0, confirm = 0;
    float valorPago = 0, valorRest = 0, valorParc = 0;

    for(i = 0; i < c_compra; i++){
        if((*compraC)[i].idOperacao == cod){
            pos = i;
            break;
        }
    }

    if((*compraC)[pos].parcelas == 1){
        valorPago = (*compraC)[pos].valorDeve;
        printf("Deve ser pago o valor restante de R$ %.2f\nConfirmar:\t1 Sim\t2 Nao: \n", (*compraC)[pos].valorDeve);
        printf("%c ", 175);
        scanf("%d", &confirm);

        if(confirm == 1){
            for(i=0; i < c_compra; i++){
                if((*compraC)[i].idOperacao == cod){
                    (*compraC)[i].valorDeve = 0;
                    obterData(&(*compraC)[i].dataPago);
                    (*compraC)[i].parcelas = (*compraC)[i].parcelas - 1;
                }
            }
            (*financeiroC)->caixa = (*financeiroC)->caixa - valorPago;
            newMovSUB(movC, c_mov, tamMov, valorPago, tipoDado);
            (*financeiroC)->despesa = (*financeiroC)->despesa - valorPago;
        }else{
            return;
        }

    }else {
        if ((*compraC)[pos].parcelas > 1) {
            valorParc = (*compraC)[pos].valorDeve / (float) (*compraC)[pos].parcelas;
            printf("Parcelas: %d \n", (*compraC)[pos].parcelas);
            printf("Valor de cada parcela: R$ %.2f \n", valorParc);
            printf("Quantas parcelas serao pagas: ");
            scanf("%d", &parcelas);
            while (parcelas >= (*compraC)[pos].parcelas && parcelas < 0) {
                printf("Numero de parcelas invalido (Digite 0 para sair): ");
                scanf("%d", &parcelas);
                if (parcelas == 0) {
                    return;
                }
            }
            valorPago = valorParc * (float) parcelas;
            printf("Confirmar pagamento de R$ %.2f:\t1 Sim\t2 Nao: \n", valorPago);
            printf("%c ", 175);
            scanf("%d", &confirm);
            if (confirm == 1) {
                for (i = 0; i < c_compra; i++) {
                    if ((*compraC)[i].idOperacao == cod) {
                        (*compraC)[i].valorDeve = (*compraC)[i].valorDeve - valorPago;
                        (*compraC)[i].parcelas = (*compraC)[i].parcelas - parcelas;
                        if((*compraC)[i].parcelas == 0){
                            obterData(&(*compraC)[i].dataPago);
                        }
                    }
                }
                (*financeiroC)->caixa = (*financeiroC)->caixa - valorPago;
                newMovSUB(movC, c_mov, tamMov, valorPago, tipoDado);
                (*financeiroC)->despesa = (*financeiroC)->despesa - valorPago;
            }else{
                return;
            }
        }
    }
}



void zeraArquivos() {
    int op;
    printf("Deseja limpar os arquivos:\n"
           "1-Txt\t2-Bin\t3-Ambos\t0-Sair\n");
    scanf("%d", &op);


    if (op == 1 || op == 3) {
        FILE *file;

        file = fopen("filmes.txt", "w");
        //fclose(file);
        file = fopen("categorias.txt", "w");
        //fclose(file);
        file = fopen("clientes.txt", "w");
        //fclose(file);
        file = fopen("compras.txt", "w");
        //fclose(file);
        file = fopen("contas_cliente.txt", "w");
        //fclose(file);
        file = fopen("financeiro.txt", "w");
        //fclose(file);
        file = fopen("fornecedores.txt", "w");
        //fclose(file);
        file = fopen("funcionario.txt", "w");
        //fclose(file);
        file = fopen("locadora.txt", "w");
        //fclose(file);
        file = fopen("movimentacao.txt", "w");
        //fclose(file);
        file = fopen("operacoes.txt", "w");
        fclose(file);
    } else {
        if (op == 2 || op == 3) {
            FILE *file;

            file = fopen("filmes.bin", "wb");
            //fclose(file);
            file = fopen("categorias.bin", "wb");
            //fclose(file);
            file = fopen("clientes.bin", "wb");
            //fclose(file);
            file = fopen("compras.bin", "wb");
            //fclose(file);
            file = fopen("contas_cliente.bin", "wb");
            //fclose(file);
            file = fopen("financeiro.bin", "wb");
            //fclose(file);
            file = fopen("fornecedores.bin", "wb");
            //fclose(file);
            file = fopen("funcionario.bin", "wb");
            //fclose(file);
            file = fopen("locadora.bin", "wb");
            //fclose(file);
            file = fopen("movimentacao.bin", "wb");
            //fclose(file);
            file = fopen("operacoes.bin", "wb");
            fclose(file);
        } else {
            return;
        }
    }

}