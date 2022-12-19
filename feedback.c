//
// Created by Breno on 16/11/2022.
//

#include <ctype.h>
#include "feedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <io.h>
#include <math.h>


void menuFeedback() {
    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                       FEEDBACK                         %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Clientes                                        %c\n", 186, 186);
    printf("%c    2 - Filmes                                          %c\n", 186, 186);
    printf("%c    3 - Locacoes restantes para que o filme se pague    %c\n", 186, 186);
    printf("%c    4 - Locacoes                                        %c\n", 186, 186);
    printf("%c    5 - Contas a receber                                %c\n", 186, 186);
    printf("%c    6 - Contas a pagar                                  %c\n", 186, 186);
    printf("%c    7 - Movimentacao de caixa                           %c\n", 186, 186);
    printf("%c    8 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // seta
    printf("%c ", 175);
}



void fb_locacaoRest(operacoes **operacaoC, int c_op, filme **filmeC, int c_filme){
    int operacao = 0, i;
    float valorLoc = 0, valorFalta = 0, restante = 0, valorFilme =0;

    for(i=0; i < c_filme; i++){
        operacao = 0;
        valorLoc = 0;
        valorFalta = 0;
        restante = 0;
        printf("\nFilme: %s [cod %d]:\n", (*filmeC)[i].descricao, (*filmeC)[i].codigoFilme);
        for(int j=0;j < c_op; j++){
            if((*filmeC)[i].codigoFilme ==  (*operacaoC)[j].codFilme){
                operacao++;
            }

        }
        valorLoc = (*filmeC)[i].valor * (float) operacao;
        if(valorLoc >= (*filmeC)[i].valor){
            printf("O filme ja se pagou.\n");
        }else{

            valorFalta = (*filmeC)[i].valor - valorLoc;
            restante = ceil(valorFalta/(*filmeC)[i].valor);
            if(restante == 1){
                printf("Falta %.f locacao para o filme se pagar.\n", restante);
            }else{
                printf("Faltam %.f locacoes para o filme se pagar.\n", restante);
            }
        }

    }

}



void fb_Clientes(cliente **clienteC, int c_cliente){
    char sexoF[15]="feminino", sexoM[15]="masculino";
    int m = 0, f = 0, i, j, tipo = 0, codMenor, codMaior;
    printf("Filtar por:\n1- Codigo\t2- Sexo: ");
    scanf("%d", &tipo);


    if(tipo == 1){
        printf("A partir de qual codigo deseja filtrar: ");
        scanf("%d", &codMenor);
        printf("Ate qual codigo deseja filtrar: ");
        scanf("%d", &codMaior);

        cliente new[c_cliente];
        cliente aux;

        for(i=0; i < c_cliente; i++) {
            new[i] = (*clienteC)[i];
        }

        for(i=0; i < c_cliente; i++){
                for (j = i + 1; j < c_cliente; j++) {
                    if (new[i].codigoCliente > new[j].codigoCliente) {
                        aux = new[i];
                        new[i] = new[j];
                        new[j] = aux;
                    }
                }
            }
        printf("\n");
        for(i=0; i < c_cliente; i++){
            if(new[i].codigoCliente >= codMenor && new[i].codigoCliente <= codMaior) {
                printf("Cod: %d \n", new[i].codigoCliente);
                printf("Nome: %s \n", new[i].nome);
                printf("Endereco: %s \n", new[i].endereco);
                printf("CPF: %s \n", new[i].cpf);
                printf("Telefone: %s \n", new[i].telefone);
                printf("Email: %s \n", new[i].email);
                printf("Sexo: %s \n", new[i].sexo);
                printf("Estado Civil: %s \n", new[i].estadoCivil);
                printf("Data de nascimento: %s \n\n", new[i].dataNascimento);
            }
        }
    }else{
        if(tipo == 2) {
            cliente femi[c_cliente];
            cliente masc[c_cliente];
            for (i = 0; i < c_cliente; i++) {
                char sexo[20];
               // if (strcmp((*clienteC)[i].sexo, sexoM) == 0) {
                strcpy(sexo,(*clienteC)[i].sexo);
                strlwr(sexo);
                    if (strncmp(sexo, sexoM, 1) == 0){
                    masc[m] = (*clienteC)[i];
                    m++;
                } else {
                        if (strncmp(sexo, sexoF, 1) == 0){
                        femi[f] = (*clienteC)[i];
                        f++;
                    }
                }
            }
            printf("\n-- Masculino --\n");
            for (i = 0; i < m; i++) {
                printf("Cod: %d \n", masc[i].codigoCliente);
                printf("Nome: %s \n", masc[i].nome);
                printf("Endereco: %s \n", masc[i].endereco);
                printf("CPF: %s \n", masc[i].cpf);
                printf("Telefone: %s \n", masc[i].telefone);
                printf("Email: %s \n", masc[i].email);
                printf("Estado Civil: %s \n", masc[i].estadoCivil);
                printf("Data de nascimento: %s \n\n", masc[i].dataNascimento);

            }
            printf("\n");
            printf("-- Feminino --\n");
            for (i = 0; i < f; i++) {
                printf("Cod: %d \n", femi[i].codigoCliente);
                printf("Nome: %s \n", femi[i].nome);
                printf("Endereco: %s \n", femi[i].endereco);
                printf("CPF: %s \n", femi[i].cpf);
                printf("Telefone: %s \n", femi[i].telefone);
                printf("Email: %s \n", femi[i].email);
                printf("Estado Civil: %s \n", femi[i].estadoCivil);
                printf("Data de nascimento: %s \n\n", femi[i].dataNascimento);
            }
        }
    }
}



void fb_Filmes(filme **filmeC, int c_filme) {
    int i, j, codMenor, codMaior;
    filme new[c_filme];
    filme aux;

    printf("A partir de qual codigo deseja filtrar: ");
    scanf("%d", &codMenor);
    printf("Ate qual codigo deseja filtrar: ");
    scanf("%d", &codMaior);

    for (i = 0; i < c_filme; i++) {
        new[i] = (*filmeC)[i];
    }

    for (i = 0; i < c_filme; i++) {
        for (j = i + 1; j < c_filme; j++) {
            if (new[i].codigoFilme > new[j].codigoFilme) {
                aux = new[i];
                new[i] = new[j];
                new[j] = aux;
            }
        }
    }
    printf("\n");
    for (i = 0; i < c_filme; i++) {
        if(new[i].codigoFilme >= codMenor && new[i].codigoFilme <= codMaior) {
            printf("Codigo: %d \n", new[i].codigoFilme);
            printf("Descricao: %s \n", new[i].descricao);
            printf("Exemplares: %d \n", new[i].exemplarFilme);
            printf("Codigo categoria: %d \n", new[i].codigoCategoria);
            printf("Lingua: %s \n", new[i].lingua);
            printf("\n");
        }
    }
}



void fb_Locacoes(operacoes **operacaoC, int c_op, contaCliente **contaC, int c_conta, funcionario **funcC, int c_func) {
    int i, j, k, op, idOp = 0, quant = 0;
    printf("Filtrar por:\n1- A vista\t2- Por vendedor: ");
    scanf("%d", &op);

    if (op == 1) {
        for (i = 0; i < c_op; i++) {
            if ((*operacaoC)[i].tipoPag == 1) {
                printf("\n");
                printf("Operacao[%d]:\n", (*operacaoC)[i].idOperacao);
                printf("Valor total: R$ %.2f\n", (*operacaoC)[i].valorTotal);
                printf("Data de locacao: %d / %d / %d\n", (*operacaoC)[i].dataLoc.dia, (*operacaoC)[i].dataLoc.mes,
                       (*operacaoC)[i].dataLoc.ano);
                printf("Data para devolucao: %d / %d / %d\n", (*operacaoC)[i].dataDev.dia, (*operacaoC)[i].dataDev.mes,
                       (*operacaoC)[i].dataDev.ano);
                idOp = (*operacaoC)[i].idOperacao;
                quant = (*operacaoC)[i].ex;
                for (j = 0; j < c_op; j++) {
                    if ((*operacaoC)[i].devolveu == 1 && (*operacaoC)[i].idOperacao == idOp) {
                        printf("Filme: %s \n", (*operacaoC)[i].nomeFilme);
                        printf("Data devolvido: %d / %d / %d\n", (*operacaoC)[i].dataEntregue.dia,
                               (*operacaoC)[i].dataEntregue.mes, (*operacaoC)[i].dataEntregue.ano);
                    }
                }
                i = i + (quant - 1);
            }
        }
    } else {
        if (op == 2) {
            for (i = 0; i < c_func; i++) {
                for (j = 0; j < c_op; j++) {
                    if ((*funcC)[i].codigo == (*operacaoC)[j].codFunc) {
                        printf("\n");
                        printf("Funcionario[%d]: %s \n", (*funcC)[i].codigo, (*funcC)[i].nome);
                        printf("Operacao[%d]:\n", (*operacaoC)[j].idOperacao);
                        printf("Valor total: R$ %.2f \n", (*operacaoC)[j].valorTotal);
                        printf("Data de locacao: %d / %d / %d\n", (*operacaoC)[j].dataLoc.dia,
                               (*operacaoC)[j].dataLoc.mes,
                               (*operacaoC)[j].dataLoc.ano);
                        printf("Data para devolucao: %d / %d / %d\n", (*operacaoC)[j].dataDev.dia,
                               (*operacaoC)[j].dataDev.mes,
                               (*operacaoC)[j].dataDev.ano);
                        idOp = (*operacaoC)[j].idOperacao;
                        quant = (*operacaoC)[j].ex;
                        for (k = 0; k < c_op; k++) {
                            if ((*operacaoC)[k].idOperacao == idOp) {
                                printf("Filme: %s \n", (*operacaoC)[k].nomeFilme);
                                if ((*operacaoC)[k].devolveu == 1) {
                                    printf("Data devolvido: %d / %d / %d\n", (*operacaoC)[i].dataEntregue.dia,
                                           (*operacaoC)[i].dataEntregue.mes, (*operacaoC)[i].dataEntregue.ano);
                                }
                            }
                        }
                    }
                    j = j + quant - 1;
                }
            }
        }
    }
}



int dataAntes(data dtDev1, data dtDev2){
    if(dtDev1.ano == dtDev2.ano){
        if(dtDev1.mes == dtDev2.mes){
            if(dtDev1.dia >= dtDev2.dia){
                return 2;
            }else{
                return 1;
            }
        }
    }

    if(dtDev1.ano == dtDev2.ano){
        if(dtDev1.mes >= dtDev2.mes){
                return 2;
            }else{
            if(dtDev1.mes <= dtDev2.mes){
                return 1;
            }
        }
    }

    if(dtDev1.ano >= dtDev2.ano){
        return 2;
    }else{
        return 1;
    }

}




void fb_ContasReceber(contaCliente **contaC, int c_conta, operacoes **operacaoC, int c_op, int c_idOp){
    int i = 0, j = 0, k,op = 0, idContas[c_conta], idOp = 0, p = 0, menOp = 0, quant = 0, tipo = 0, exOp[c_idOp];
    int opr = 0, codMenor, codMaior;
    printf("Filtrar por:\n1- Codigos\t2- Data da nota: ");
    scanf("%d", &op);

    if(op==1){
        printf("A partir de qual codigo deseja filtrar: ");
        scanf("%d", &codMenor);
        printf("Ate qual codigo deseja filtrar: ");
        scanf("%d", &codMaior);

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
        if (newConta[i].valorDeve > 0.0 && newConta[i].codigo >= codMenor && newConta[i].codigo <= codMaior) {
            printf("\nCliente [%d]:\n", newConta[i].codigo);
            printf("Nome: %s \nValor devido: R$ %.2f\n", newConta[i].nome, newConta[i].valorDeve);
            for (j = 0; j < c_op; j++) {
                if (newConta[i].codigo == newOp[j].codCliente && newOp[j].valorDeve > 0.0) {
                    opr = newOp[j].idOperacao;
                    printf("Operacao [%d]:\n", opr);
                    quant = newOp[j].ex;
                    printf("Valor total: R$ %.2f\nValor devido: R$ %.2f\nData locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n",
                           newOp[j].valorTotal,
                           newOp[j].valorDeve,
                           newOp[j].dataLoc.dia,
                           newOp[j].dataLoc.mes, newOp[j].dataLoc.ano,
                           newOp[j].dataDev.dia, newOp[j].dataDev.mes, newOp[j].dataDev.ano);
                    // pula as operacoes no laço j para n repetir
                    j = j + (quant - 1);
                }
            }
            printf("___________________________________________________________\n");

        }
    }
}else{
    if(op == 2){
        operacoes newOp[c_op];
        for (i = 0; i < c_op; i++) {
            newOp[i] = (*operacaoC)[i];
        }

        contaCliente newConta[c_conta];
        for (i = 0; i < c_conta; i++) {
            newConta[i] = (*contaC)[i];
        }
        // organiza as contas dos clientes por ordem do codigo
        for (i = 0; i < c_op; i++) {
            for (j = i + 1; j < c_op; j++) {
                if(dataAntes(newOp[i].dataDev, newOp[j].dataDev) == 2) {
                    operacoes aux = newOp[i];
                    newOp[i] = newOp[j];
                    newOp[j] = aux;
                }
            }
        }

        for(i=0; i < c_op; i++){
            for(j=0; j < c_conta; j++){
                if(newOp[i].codCliente == (*contaC)[j].codigo && newOp[i].valorDeve > 0.0) {
                    printf("\nCliente [%d]:\n", (*contaC)[j].codigo);
                    printf("Nome: %s \nValor devido: R$ %.2f\n", (*contaC)[j].nome, (*contaC)[j].valorDeve);
                    opr = newOp[i].idOperacao;
                    quant = newOp[i].ex;
                    printf("Operacao [%d]:\n", opr);
                    printf("Valor total: R$ %.2f\nValor devido: R$ %.2f\nData locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n",
                           newOp[i].valorTotal,
                           newOp[i].valorDeve,
                           newOp[i].dataLoc.dia,
                           newOp[i].dataLoc.mes, newOp[i].dataLoc.ano,
                           newOp[i].dataDev.dia, newOp[i].dataDev.mes, newOp[i].dataDev.ano);
                    i = i + (quant - 1);
//                    for (k = 0; k < c_op; k++) {
//                        if (newOp[k].idOperacao == opr) {
//                            printf("Valor total: R$ %.2f\nValor devido: R$ %.2f\nData locacao: %d / %d / %d\nData devolucao: %d / %d / %d\n",
//                                   newOp[k].valorTotal,
//                                   newOp[k].valorDeve,
//                                   newOp[k].dataLoc.dia,
//                                   newOp[k].dataLoc.mes, newOp[k].dataLoc.ano,
//                                   newOp[k].dataDev.dia, newOp[k].dataDev.mes, newOp[k].dataDev.ano);
//                            }
//                        }
                    }
                }
            //i = i + (quant - 1);
            }
        }
    }
}



void fb_contasPagar(compra **compraC, int c_compra, fornecedor **fornecedorC, int c_forn) {
    int i, j, k, cod, pos, quant = 0, op = 0, codMenor, codMaior;

    printf("Filtrar por:\n1- Codigos\t2- Data da nota: ");
    scanf("%d", &op);

    if (op == 1) {

        printf("A partir de qual codigo deseja filtrar: ");
        scanf("%d", &codMenor);
        printf("Ate qual codigo deseja filtrar: ");
        scanf("%d", &codMaior);

        compra new[c_compra];
        compra aux;

        for (i = 0; i < c_compra; i++) {
            new[i] = (*compraC)[i];
        }

        for (i = 0; i < c_compra; i++) {
            for (j = i + 1; j < c_compra; j++) {
                if (new[i].idFornecedor > new[j].idFornecedor) {
                    aux = new[i];
                    new[i] = new[j];
                    new[j] = aux;
                }
            }
        }

        for (i = 0; i < c_compra; i++) {
            if (new[i].valorDeve > 0.0 && new[i].idFornecedor >= codMenor && new[i].idFornecedor <= codMaior) {
                //quant = new[i].ex;
                cod = new[i].idOperacao;
                printf(" Compra (%d)\n", new[i].idOperacao);
                printf("%c", 218);
                for (int t = 0; t < 71; t++) {
                    printf("%c", 196);
                }
                printf("%c\n", 191);
                printf("%c %-17s| %-50s %c\n", 179, "Fornecedor", new[i].razaoSocial, 179);
                printf("%c %-17s| %-50s %c\n", 179, "CNPJ", new[i].cnpj, 179);
                printf("%c %-17s| R$ %.2f       |%-17s| R$ %.2f        %c\n", 179, "Frete:", new[i].freteTotal,
                       "Imposto:",
                       new[i].impostoTotal, 179);
                printf("%-72c", 179);
                printf("%c\n", 179);
                printf("%c %-17s| %d | %d | %d                                     %c\n", 179, "Data de compra: ", new[i].dataCompra.dia, new[i].dataCompra.mes, new[i].dataCompra.ano, 179);
                printf("%-72c", 179);
                printf("%c\n", 179);
                printf("%c                                 Filmes                                %c\n", 179, 179);
                printf("%c", 195);
                for (int t = 0; t < 71; t++) {
                    printf("%c", 196);
                }
                printf("%c\n", 180);
                printf("%c %-25s | %-11s |%-10s |%-11s %c\n", 179, "Descricao", "Preco Custo (R$)", "Quantidade",
                       "Total (R$)",
                       179);

                for (k = 0; k < c_compra; k++) {
                    if (new[k].idOperacao == cod) {
                        printf("%c %-25s | %-16.2f | %-9.d | %-10.2f %c\n", 179, new[k].nomeFilme, new[k].valorFilme,
                               new[k].ex,
                               new[k].precoFilme, 179);
                        pos = k;
                    }
                }
                printf("%c", 195);
                for (int t = 0; t < 71; t++) {
                    printf("%c", 196);
                }
                printf("%c\n", 180);
                printf("%c %-56s | R$ %-7.2f %c\n", 179, "Total da nota (filmes + frete + impostos):",
                       new[pos].valorTotal,
                       179);

                printf("%c", 195);
                for (int t = 0; t < 71; t++) {
                    printf("%c", 196);
                }
                printf("%c\n", 180);
                printf("%c %-56s | R$ %-7.2f %c\n", 179, "Valor devido:", new[pos].valorDeve, 179);

                printf("%c", 192);
                for (int t = 0; t < 71; t++) {
                    printf("%c", 196);
                }
                printf("%c\n\n", 217);
                for (int l = 0; l < c_compra; l++) {
                    if (new[l].idOperacao == cod) {
                        quant++;
                    }
                }
                i = i + (quant - 1);
                quant = 0;
            }
        }
    }else{
        if(op == 2){

            compra new[c_compra];
            compra aux;

            for (i = 0; i < c_compra; i++) {
                new[i] = (*compraC)[i];
            }

            for (i = 0; i < c_compra; i++) {
                for (j = i + 1; j < c_compra; j++) {
                    if (dataAntes(new[i].dataCompra, new[j].dataCompra) == 2) {
                        aux = new[i];
                        new[i] = new[j];
                        new[j] = aux;
                    }
                }
            }
            for (i = 0; i < c_compra; i++) {
                if (new[i].valorDeve > 0.0) {
                    //quant = new[i].ex;
                    cod = new[i].idOperacao;
                    printf(" Compra (%d)\n", new[i].idOperacao);
                    printf("%c", 218);
                    for (int t = 0; t < 71; t++) {
                        printf("%c", 196);
                    }
                    printf("%c\n", 191);
                    printf("%c %-17s| %-50s %c\n", 179, "Fornecedor", new[i].razaoSocial, 179);
                    printf("%c %-17s| %-50s %c\n", 179, "CNPJ", new[i].cnpj, 179);
                    printf("%c %-17s| R$ %.2f       |%-17s| R$ %.2f        %c\n", 179, "Frete:", new[i].freteTotal,
                           "Imposto:",
                           new[i].impostoTotal, 179);
                    printf("%-72c", 179);
                    printf("%c\n", 179);
                    printf("%c %-17s| %d | %d | %d                                     %c\n", 179, "Data de compra: ", new[i].dataCompra.dia, new[i].dataCompra.mes, new[i].dataCompra.ano, 179);
                    printf("%-72c", 179);
                    printf("%c\n", 179);
                    printf("%c                                 Filmes                                %c\n", 179, 179);
                    printf("%c", 195);
                    for (int t = 0; t < 71; t++) {
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-25s | %-11s |%-10s |%-11s %c\n", 179, "Descricao", "Preco Custo (R$)", "Quantidade",
                           "Total (R$)",
                           179);

                    for (k = 0; k < c_compra; k++) {
                        if (new[k].idOperacao == cod) {
                            printf("%c %-25s | %-16.2f | %-9.d | %-10.2f %c\n", 179, new[k].nomeFilme, new[k].valorFilme,
                                   new[k].ex,
                                   new[k].precoFilme, 179);
                            pos = k;
                        }
                    }
                    printf("%c", 195);
                    for (int t = 0; t < 71; t++) {
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-56s | R$ %-7.2f %c\n", 179, "Total da nota (filmes + frete + impostos):",
                           new[pos].valorTotal,
                           179);

                    printf("%c", 195);
                    for (int t = 0; t < 71; t++) {
                        printf("%c", 196);
                    }
                    printf("%c\n", 180);
                    printf("%c %-56s | R$ %-7.2f %c\n", 179, "Valor devido:", new[pos].valorDeve, 179);

                    printf("%c", 192);
                    for (int t = 0; t < 71; t++) {
                        printf("%c", 196);
                    }
                    printf("%c\n\n", 217);
                    for (int l = 0; l < c_compra; l++) {
                        if (new[l].idOperacao == cod) {
                            quant++;
                        }
                    }
                    i = i + (quant - 1);
                    quant = 0;
                }
            }


        }
    }
}



