//
// Created by Alunos on 22/11/2022.
//

#include <ctype.h>
#include "export.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <io.h>


void menuEx(){
    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                        EXPORTACAO                        %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Exportar filme                                  %c\n", 186, 186);
    printf("%c    2 - Exportar cliente                                %c\n", 186, 186);
    printf("%c    3 - Exportar categoria                              %c\n", 186, 186);
    printf("%c    4 - Exportar fornecedor                             %c\n", 186, 186);
    printf("%c    5 - Exportar funcionario                            %c\n", 186, 186);
    printf("%c    6 - Exportar locadora                               %c\n", 186, 186);
    printf("%c    7 - Exportar conta cliente                          %c\n", 186, 186);
    printf("%c    8 - Exportar locacoes                               %c\n", 186, 186);
    printf("%c    9 - Exportar compras                                %c\n", 186, 186);
    printf("%c    10 - Exportar movimentacao de caixa                  %c\n", 186, 186);
    printf("%c    11- Exportar todos os dados                         %c\n", 186, 186);
    printf("%c    0 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // seta
    printf("%c ", 175);

}




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
              int tipoDado) {
    int op;
    scanf("%d", &op);


        if(op == 1 || op == 11 && c_filme > 0) {
            exportarFilme(filmeC, c_filme, tipoDado, op);
        }
        if(op == 2 || op == 11 && c_cliente > 0){
            exportarCliente(clienteC, c_cliente, tipoDado, op);
        }
        if(op == 3 || op == 11 && c_categoria > 0){
            exportarCategoria(categoriaC, c_categoria, tipoDado, op);
        }
        if(op == 4 || op == 11 && c_fornecedor > 0){
            exportarFornecedor(fornecedorC, c_fornecedor, tipoDado, op);
        }
        if(op == 5 || op == 11 && c_func > 0){
            exportarFuncionario(funcC, c_func, tipoDado, op);
        }
        if(op == 6 || op == 11 && c_loca > 0){
            exportarLocadora(locadoraC, c_loca, financeiroC, tipoDado, op);
        }
        if(op == 7 || op == 11 && c_conta > 0){
            exportarContaCliente(contaC, c_conta, tipoDado, op);
        }
        if(op == 8 || op == 11 && c_op > 0){
            exportarOperacao(operacaoC, c_op, tipoDado, op);
        }
        if(op == 9 || op == 11 && c_compra > 0){
            exportarCompra(compraC, c_compra, tipoDado, op);
        }
        if(op == 10 || op == 11 && c_mov > 0){
            exportarMovimentacao(movC, c_mov, tipoDado, op);
        }
        if(op == 0){
            return;
        }

}



void exportarFilme(filme **filmeC, int c_filme, int tipoDado, int op) {

        FILE *file;

        if(op == 1) {
            file = fopen("exFilme.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "w");
            }
        }

        fprintf(file,"<dados>\n"
                     "\t<filme>\n");

        for(int i=0; i < c_filme; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<codigo>%d</codigo>\n"
                          "\t\t\t<descricao>%s</descricao>\n"
                          "\t\t\t<valor>%.2f</valor>\n"
                          "\t\t\t<ex>%d</ex>\n"
                          "\t\t\t<IDcategoria>%d</IDcategoria>\n"
                          "\t\t\t<lingua>%s</lingua>\n"
                          "\t\t\t<exLocados>%d</exLocados>\n"
                          "\t\t\t<pendente>%d</pendente>\n"
                          "\t\t</registro>\n", (*filmeC)[i].codigoFilme,
                    (*filmeC)[i].descricao,
                    (*filmeC)[i].valor,
                    (*filmeC)[i].exemplarFilme,
                    (*filmeC)[i].codigoCategoria,
                    (*filmeC)[i].lingua,
                    (*filmeC)[i].exLocados,
                    (*filmeC)[i].pendente);
        }

        fprintf(file,"\t</filme>\n");
        if(op == 1) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}



void exportarCliente(cliente **clienteC, int c_cliente, int tipoDado, int op) {

        FILE *file;

        if(op == 2) {
            file = fopen("exCliente.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 2) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<cliente>\n");
        for(int i=0; i < c_cliente; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<codigo>%d</codigo>\n"
                          "\t\t\t<nome>%s</nome>\n"
                          "\t\t\t<endereco>%s</endereco>\n"
                          "\t\t\t<cpf>%s</cpf>\n"
                          "\t\t\t<telefone>%s</telefone>\n"
                          "\t\t\t<email>%s</email>\n"
                          "\t\t\t<sexo>%s</sexo>\n"
                          "\t\t\t<estCivil>%s</estCivil>\n"
                          "\t\t\t<dataNascimento>%s</dataNascimento>\n"
                          "\t\t</registro>\n", (*clienteC)[i].codigoCliente,
                    (*clienteC)[i].nome,
                    (*clienteC)[i].endereco,
                    (*clienteC)[i].cpf,
                    (*clienteC)[i].telefone,
                    (*clienteC)[i].email,
                    (*clienteC)[i].sexo,
                    (*clienteC)[i].estadoCivil,
                    (*clienteC)[i].dataNascimento);
        }

        fprintf(file,"\t</cliente>\n");
        if(op == 2) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}



void exportarCategoria(categoria **categoriaC, int c_categoria, int tipoDado, int op) {

        FILE *file;

        if(op == 3) {
            file = fopen("exCategoria.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 3) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<categoria>\n");
        for(int i=0; i < c_categoria; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<codigo>%d</codigo>\n"
                          "\t\t\t<descricao>%s</descricao>\n"
                          "\t\t\t<valor>%.2f</valor>\n"
                          "\t\t\t<ativo>%d</ativo>\n"
                          "\t\t</registro>\n", (*categoriaC)[i].codigo,
                    (*categoriaC)[i].descricao,
                    (*categoriaC)[i].valorLocacao,
                    (*categoriaC)[i].ativo);
        }

        fprintf(file,"\t</categoria>\n");
        if(op == 3) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}



void exportarFuncionario(funcionario **funcC, int c_func, int tipoDado, int op) {

        FILE *file;

        if(op == 5) {
            file = fopen("exFuncionario.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 5) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<funcionario>\n");
        for(int i=0; i < c_func; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<codigo>%d</codigo>\n"
                          "\t\t\t<nome>%s</nome>\n"
                          "\t\t\t<cargo>%s</cargo>\n"
                          "\t\t\t<endereco>%s</endereco>\n"
                          "\t\t\t<telefone>%s</telefone>\n"
                          "\t\t\t<email>%s</email>\n"
                          "\t\t</registro>\n", (*funcC)[i].codigo,
                    (*funcC)[i].nome,
                    (*funcC)[i].cargo,
                    (*funcC)[i].endereco,
                    (*funcC)[i].telefone,
                    (*funcC)[i].email);
        }

        fprintf(file,"\t</funcionario>\n");
        if(op == 5) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}



void exportarFornecedor(fornecedor **fornecedorC, int c_fornecedor, int tipoDado, int op) {

        FILE *file;

        if(op == 4) {
            file = fopen("exFornecedor.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 4) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<fornecedor>\n");
        for(int i=0; i < c_fornecedor; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<codigo>%d</codigo>\n"
                          "\t\t\t<nomeFantasia>%s</nomeFantasia>\n"
                          "\t\t\t<razaoSocial>%s</razaoSocial>\n"
                          "\t\t\t<inscricao>%s</inscricao>\n"
                          "\t\t\t<cnpj>%s</cnpj>\n"
                          "\t\t\t<endereco>%s</endereco>\n"
                          "\t\t\t<telefone>%s</telefone>\n"
                          "\t\t\t<email>%s</email>\n"
                          "\t\t</registro>\n", (*fornecedorC)[i].codigo,
                    (*fornecedorC)[i].nomeFantasia,
                    (*fornecedorC)[i].razaoSocial,
                    (*fornecedorC)[i].inscricaoEst,
                    (*fornecedorC)[i].cnpj,
                    (*fornecedorC)[i].endereco,
                    (*fornecedorC)[i].tel,
                    (*fornecedorC)[i].email);
        }

        fprintf(file,"\t</fornecedor>\n");
        if(op == 4) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}



void exportarLocadora(locadora locadoraC, int c_loca, financeiro financeiroC, int tipoDado, int op) {

        FILE *file;

        if(op == 6) {
            file = fopen("exLocadora.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 6) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<locadora>\n");
        for(int i=0; i < c_loca; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<nomeFantasia>%s</nomeFantasia>\n"
                          "\t\t\t<razaoSocial>%s</razaoSocial>\n"
                          "\t\t\t<inscricao>%s</inscricao>\n"
                          "\t\t\t<cnpj>%s</cnpj>\n"
                          "\t\t\t<endereco>%s</endereco>\n"
                          "\t\t\t<telefone>%s</telefone>\n"
                          "\t\t\t<email>%s</email>\n"
                          "\t\t\t<nomeResponsavel>%s</nomeResponsavel>\n"
                          "\t\t\t<telResponsavel>%s</telResponsavel>\n"
                          "\t\t\t<multa>%.2f</multa>\n"
                          "\t\t\t<caixa>%.2f</caixa>\n"
                          "\t\t\t<areceber>%.2f</areceber>\n"
                          "\t\t\t<despesa>%.2f</despesa>\n"
                          "\t\t</registro>\n", locadoraC.nomeFantasia,
                    locadoraC.razao,
                    locadoraC.inscricaoEst,
                    locadoraC.cnpj,
                    locadoraC.endereco,
                    locadoraC.telefone,
                    locadoraC.email,
                    locadoraC.nomeResponsavel,
                    locadoraC.telResponsavel,
                    locadoraC.multa,
                    financeiroC.caixa,
                    financeiroC.areceber,
                    financeiroC.despesa);
        }

        fprintf(file,"\t</locadora>\n");
        if(op == 6) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}



void exportarContaCliente(contaCliente **contaC, int c_conta, int tipoDado, int op) {

        FILE *file;

        if(op == 7) {
            file = fopen("exContaCliente.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 7) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<contaCliente>\n");
        for(int i=0; i < c_conta; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<codigo>%d</codigo>\n"
                          "\t\t\t<nome>%s</nome>\n"
                          "\t\t\t<valorDeve>%f</valorDeve>\n"
                          "\t\t</registro>\n", (*contaC)[i].codigo,
                    (*contaC)[i].nome,
                    (*contaC)[i].valorDeve);
        }

        fprintf(file,"\t</contaCliente>\n");
        if(op == 7) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);

}




void exportarOperacao(operacoes **operacaoC, int c_op, int tipoDado, int op) {

        FILE *file;

        if(op == 8) {
            file = fopen("exLocacao.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 8) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<locacao>\n");
        for(int i=0; i < c_op; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<idOperacao>%d</idOperacao>\n"
                          "\t\t\t<codFuncionario>%d</codFuncionario>\n"
                          "\t\t\t<codCliente>%d</codCliente>\n"
                          "\t\t\t<codFilme>%d</codFilme>\n"
                          "\t\t\t<nomeFilme>%s</nomeFilme>\n"
                          "\t\t\t<ex>%d</ex>\n"
                          "\t\t\t<tipoPag>%d</tipoPag>\n"
                          "\t\t\t<valorTotal>%f</valorTotal>\n"
                          "\t\t\t<valorDeve>%f</valorDeve>\n"
                          "\t\t\t<parcelas>%d</parcelas>\n"
                          "\t\t\t<dataLoc>%d/%d/%d</dataLoc>\n"
                          "\t\t\t<dataDev>%d/%d/%d</dataDev>\n"
                          "\t\t\t<dataEntregue>%d/%d/%d</dataEntregue>\n"
                          "\t\t\t<devolveu>%d</devolveu>\n"
                          "\t\t</registro>\n", (*operacaoC)[i].idOperacao,
                    (*operacaoC)[i].codFunc,
                    (*operacaoC)[i].codCliente,
                    (*operacaoC)[i].codFilme,
                    (*operacaoC)[i].nomeFilme,
                    (*operacaoC)[i].ex,
                    (*operacaoC)[i].tipoPag,
                    (*operacaoC)[i].valorTotal,
                    (*operacaoC)[i].valorDeve,
                    (*operacaoC)[i].parcelas,
                    (*operacaoC)[i].dataLoc.dia,
                    (*operacaoC)[i].dataLoc.mes,
                    (*operacaoC)[i].dataLoc.ano,
                    (*operacaoC)[i].dataDev.dia,
                    (*operacaoC)[i].dataDev.mes,
                    (*operacaoC)[i].dataDev.ano,
                    (*operacaoC)[i].dataEntregue.dia,
                    (*operacaoC)[i].dataEntregue.mes,
                    (*operacaoC)[i].dataEntregue.ano,
                    (*operacaoC)[i].devolveu);
        }

        fprintf(file,"\t</locacao>\n");
        if(op == 8) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);


}



void exportarCompra(compra **compraC, int c_compra, int tipoDado, int op) {

        FILE *file;

        if(op == 9) {
            file = fopen("exCompra.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 9) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<compra>\n");
        for(int i=0; i < c_compra; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<idOperacao>%d</idOperacao>\n"
                          "\t\t\t<idFornecedor>%d</idFornecedor>\n"
                          "\t\t\t<razaoSocial>%s</razaoSocial>\n"
                          "\t\t\t<cnpj>%s</cnpj>\n"
                          "\t\t\t<nomeFilme>%s</nomeFilme>\n"
                          "\t\t\t<ex>%d</ex>\n"
                          "\t\t\t<valorFilme>%f</valorFilme>\n"
                          "\t\t\t<valorImposto>%f</valorImposto>\n"
                          "\t\t\t<valorFrete>%f</valorFrete>\n"
                          "\t\t\t<filmeTotal>%f</filmeTotal>\n"
                          "\t\t\t<impostoTotal>%f</impostoTotal>\n"
                          "\t\t\t<freteTotal>%f</freteTotal>\n"
                          "\t\t\t<precoFilme>%f</precoFilme>\n"
                          "\t\t\t<valorTotal>%f</valorTotal>\n"
                          "\t\t\t<valorDeve>%f</valorDeve>\n"
                          "\t\t\t<parcelas>%d</parcelas>\n"
                          "\t\t\t<dataCompra>%d/%d/%d</dataCompra>\n"
                          "\t\t\t<dataPago>%d/%d/%d</dataPago>\n"
                          "\t\t</registro>\n", (*compraC)[i].idOperacao,
                    (*compraC)[i].idFornecedor,
                    (*compraC)[i].razaoSocial,
                    (*compraC)[i].cnpj,
                    (*compraC)[i].nomeFilme,
                    (*compraC)[i].ex,
                    (*compraC)[i].valorFilme,
                    (*compraC)[i].valorImposto,
                    (*compraC)[i].valorFrete,
                    (*compraC)[i].filmeTotal,
                    (*compraC)[i].impostoTotal,
                    (*compraC)[i].freteTotal,
                    (*compraC)[i].precoFilme,
                    (*compraC)[i].valorTotal,
                    (*compraC)[i].valorDeve,
                    (*compraC)[i].parcelas,
                    (*compraC)[i].dataCompra.dia,
                    (*compraC)[i].dataCompra.mes,
                    (*compraC)[i].dataCompra.ano,
                    (*compraC)[i].dataPago.dia,
                    (*compraC)[i].dataPago.mes,
                    (*compraC)[i].dataPago.ano);
        }

        fprintf(file,"\t</compra>\n");
        if(op == 9) {
            fprintf(file, "</dados>\n");
        }
        fclose(file);


}



void exportarMovimentacao(movimentacao **movC, int c_mov, int tipoDado, int op) {

        FILE *file;

        if(op == 10) {
            file = fopen("exMovimentacao.xml", "w");
        }else{
            if(op == 11){
                file = fopen("exDados.xml", "a");
            }
        }

        if(op == 10) {
            fprintf(file, "<dados>\n");
        }
        fprintf(file,"\t<movimentacao>\n");
        for(int i=0; i < c_mov; i++) {
            fprintf(file, "\t\t<registro>\n"
                          "\t\t\t<valorAntes>%f</valorAntes>\n"
                          "\t\t\t<valorDepois>%f</valorDepois>\n"
                          "\t\t\t<operacao>%f</operacao>\n"
                          "\t\t\t<dataOp>%d/%d/%d</dataOp>\n"
                          "\t\t</registro>\n", (*movC)[i].valorAntes,
                    (*movC)[i].valorDepois,
                    (*movC)[i].operacao,
                    (*movC)[i].dataOp.dia,
                    (*movC)[i].dataOp.mes,
                    (*movC)[i].dataOp.ano);
        }

        fprintf(file,"\t</movimentacao>\n");
        fprintf(file, "</dados>\n");
//        if(op == 1) {
//            fprintf(file, "</dados>\n");
//        }
        fclose(file);

    }



void alocaLinha(dados **linhaC, int *c_linha, int *tamLinha){

    if (*c_linha == *tamLinha) {
        *tamLinha = *tamLinha + 1;
        (*linhaC) = (dados *) (realloc((*linhaC), *tamLinha * sizeof(dados)));
    }
    if ((*linhaC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaFilme(filme **filmeC, int *c_filme, int *tamFilme){

    if (*c_filme == *tamFilme) {
        *tamFilme = *tamFilme + 1;
        (*filmeC) = (filme *) (realloc((*filmeC), (*tamFilme + 1) * sizeof(filme)));
    }
    if ((*filmeC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaCat(categoria **categoriaC, int *c_cat, int *tamCat){

    if (*c_cat == *tamCat) {
        *tamCat = *tamCat + 1;
        (*categoriaC) = (categoria *) (realloc((*categoriaC), *tamCat * sizeof(categoria)));
    }
    if ((*categoriaC) == NULL) {
        printf("\nErro de alocacao de memoria.\n");
    }

}



void alocaCliente(cliente **clienteC, int *c_cliente, int *tamCliente){

    if (*c_cliente == *tamCliente) {
        *tamCliente = *tamCliente + 1;
        (*clienteC) = (cliente *) (realloc((*clienteC), *tamCliente * sizeof(cliente)));
    }
    if ((*clienteC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaFunc(funcionario **funcC, int *c_func, int *tamFunc){

    if (*c_func == *tamFunc) {
        *tamFunc = *tamFunc + 1;
        (*funcC) = (funcionario *) (realloc((*funcC), *tamFunc * sizeof(funcionario)));
    }
    if ((*funcC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaForn(fornecedor **fornC, int *c_forn, int *tamForn){

    if (*c_forn == *tamForn) {
        *tamForn = *tamForn + 1;
        (*fornC) = (fornecedor *) (realloc((*fornC), *tamForn * sizeof(fornecedor)));
    }
    if ((*fornC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaConta(contaCliente **contaC, int *c_conta, int *tamConta){

    if (*c_conta == *tamConta) {
        *tamConta = *tamConta + 1;
        (*contaC) = (contaCliente *) (realloc((*contaC), *tamConta * sizeof(contaCliente)));
    }
    if ((*contaC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaOp(operacoes **operacaoC, int *c_op, int *tamOp){

    if (*c_op == *tamOp) {
        *tamOp = *tamOp + 1;
        (*operacaoC) = (operacoes *) (realloc((*operacaoC), *tamOp * sizeof(operacoes)));
    }
    if ((*operacaoC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaCompra(compra **compraC, int *c_compra, int *tamCompra){

    if (*c_compra == *tamCompra) {
        *tamCompra = *tamCompra + 1;
        (*compraC) = (compra *) (realloc((*compraC), *tamCompra * sizeof(compra)));
    }
    if ((*compraC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}



void alocaMov(movimentacao **movC, int *c_mov, int *tamMov){

    if (*c_mov == *tamMov) {
        *tamMov = *tamMov + 1;
        (*movC) = (movimentacao *) (realloc((*movC), *tamMov * sizeof(movimentacao)));
    }
    if ((*movC) == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

}




void coletaDados(dados **linhaC, int *c_linha, int *tamLinha){
    char local[60];

    printf("Informe o local do arquivo: ");
    //scanf("%s", local);

    FILE *file;
    file = fopen("C:\\Users\\Breno\\Desktop\\exDados.xml", "r");

    if (file == NULL) {
        printf("Erro para abrir arquivo.\n");
        exit(1);
    }

    while(1){

        if(feof(file)){
            break;
        }
        alocaLinha(linhaC, c_linha, tamLinha);
        fgets((*linhaC)[*c_linha].linha, 200, file);
        if(feof(file)){
            break;
        }
        alocaLinha(linhaC, c_linha, tamLinha);
        *c_linha = *c_linha + 1;
        if(feof(file)){
            break;
        }
    }

    fclose(file);

}



void tratarFilme(dados **linhaC, int *c_linha, filme **filmeC, int *c_filme, int *tamFilme){
    int i;
    char *p;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<filme>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {
                alocaFilme(filmeC, c_filme, tamFilme);

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*filmeC)[*c_filme].codigoFilme = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*filmeC)[*c_filme].descricao, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*filmeC)[*c_filme].valor = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*filmeC)[*c_filme].exemplarFilme = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*filmeC)[*c_filme].codigoCategoria = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*filmeC)[*c_filme].lingua, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*filmeC)[*c_filme].exLocados = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*filmeC)[*c_filme].pendente = strtol(p, NULL, 10);
                    i++;
                }
                *c_filme = *c_filme + 1;
                i++;

                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarCategoria(dados **linhaC, int *c_linha, categoria **categoriaC, int *c_cat, int *tamCat){
    int i;
    char *p;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<categoria>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {
                alocaCat(categoriaC, c_cat, tamCat);

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*categoriaC)[*c_cat].codigo = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*categoriaC)[*c_cat].descricao, p);;
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*categoriaC)[*c_cat].valorLocacao = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*categoriaC)[*c_cat].ativo = strtol(p, NULL, 10);
                    i++;
                }

                *c_cat = *c_cat + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarCliente(dados **linhaC, int *c_linha, cliente **clienteC, int *c_cliente, int *tamCliente){
    int i;
    char *f;

    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<cliente>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {
                alocaCliente(clienteC, c_cliente, tamCliente);

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    (*clienteC)[*c_cliente].codigoCliente = strtol(f, NULL, 10);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].nome, f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].endereco, f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].cpf, f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].telefone, f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].email,f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].sexo, f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].estadoCivil, f);
                    i++;
                }

                f = strtok((*linhaC)[i].linha, ">");
                f = strtok(NULL, "<");
                if(f != NULL) {
                    strcpy((*clienteC)[*c_cliente].dataNascimento, f);
                    i++;
                }
                *c_cliente = *c_cliente + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarFuncionario(dados **linhaC, int *c_linha, funcionario **funcC, int *c_func, int *tamFunc){
    int i,j;
    char type[30];
    char dado[50];
    char linha[50];
    char *p;
    char *ponteiro;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<funcionario>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {
                alocaFunc(funcC, c_func, tamFunc);
                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*funcC)[*c_func].codigo = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*funcC)[*c_func].nome, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*funcC)[*c_func].cargo, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*funcC)[*c_func].endereco, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*funcC)[*c_func].telefone, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*funcC)[*c_func].email,p);
                    i++;
                }
                *c_func = *c_func + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarFornecedor(dados **linhaC, int *c_linha, fornecedor **fornC, int *c_forn, int *tamForn){
    int i,j;
    char type[30];
    char dado[50];
    char linha[50];
    char *p;
    char *ponteiro;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<fornecedor>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {
                alocaForn(fornC, c_forn, tamForn);
                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*fornC)[*c_forn].codigo = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].nomeFantasia, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].razaoSocial, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].inscricaoEst, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].cnpj, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].endereco,p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].tel,p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*fornC)[*c_forn].email,p);
                    i++;
                }
                *c_forn = *c_forn + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarConta(dados **linhaC, int *c_linha, contaCliente **contaC, int *c_conta, int *tamConta){
    int i,j;
    char type[30];
    char dado[50];
    char linha[50];
    char *p;
    char *ponteiro;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<contaCliente>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {

                alocaConta(contaC, c_conta, tamConta);
                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*contaC)[*c_conta].codigo = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*contaC)[*c_conta].nome, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*contaC)[*c_conta].valorDeve = strtof(p, NULL);
                    i++;
                }

                *c_conta = *c_conta + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarOp(dados **linhaC, int *c_linha, operacoes **operacaoC, int *c_op, int *tamOp){
    int i,j;
    char type[30];
    char dado[50];
    char linha[50];
    char *p;
    char *ponteiro;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<locacao>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {

                alocaOp(operacaoC, c_op, tamOp);
                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].idOperacao = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].codFunc = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].codCliente = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].codFilme = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*operacaoC)[*c_op].nomeFilme, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].ex = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].tipoPag = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].valorTotal = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].valorDeve = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].parcelas = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataLoc.dia = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataLoc.mes = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataLoc.ano = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataDev.dia = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataDev.mes = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataDev.ano = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataEntregue.dia = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataEntregue.mes = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].dataEntregue.ano = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*operacaoC)[*c_op].devolveu = strtol(p, NULL, 10);
                    i++;
                }

                *c_op = *c_op + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarCompra(dados **linhaC, int *c_linha, compra **compraC, int *c_compra, int *tamCompra){
    int i,j;
    char type[30];
    char dado[50];
    char linha[50];
    char *p;
    char *ponteiro;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<compra>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {

                alocaCompra(compraC, c_compra, tamCompra);
                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].idOperacao = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].idFornecedor = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*compraC)[*c_compra].razaoSocial, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*compraC)[*c_compra].cnpj, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    strcpy((*compraC)[*c_compra].nomeFilme, p);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].ex = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].valorFilme = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].valorImposto = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].valorFrete = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].filmeTotal = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].impostoTotal = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].freteTotal = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].precoFilme = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].valorTotal = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].valorDeve = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].parcelas = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*compraC)[*c_compra].dataCompra.dia = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*compraC)[*c_compra].dataCompra.mes = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].dataCompra.ano = strtol(p, NULL, 10);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*compraC)[*c_compra].dataPago.dia = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*compraC)[*c_compra].dataPago.mes = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*compraC)[*c_compra].dataPago.ano = strtol(p, NULL, 10);
                    i++;
                }

                *c_compra = *c_compra + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}



void tratarMov(dados **linhaC, int *c_linha, movimentacao **movC, int *c_mov, int *tamMov){
    int i,j;
    char type[30];
    char dado[50];
    char linha[50];
    char *p;
    char *ponteiro;


    for(i=0; i < *c_linha; i++) {
        if(strstr((*linhaC)[i].linha, "<movimentacao>") != NULL){
            // abaixo pulamos a linha <registro>
            i = i + 2;

            while (1) {

                alocaMov(movC, c_mov, tamMov);
                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*movC)[*c_mov].valorAntes = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*movC)[*c_mov].valorDepois = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*movC)[*c_mov].operacao = strtof(p, NULL);
                    i++;
                }

                p = strtok((*linhaC)[i].linha, ">");
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*movC)[*c_mov].dataOp.dia = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "/");
                if(p != NULL) {
                    (*movC)[*c_mov].dataOp.mes = strtol(p, NULL, 10);
                }
                p = strtok(NULL, "<");
                if(p != NULL) {
                    (*movC)[*c_mov].dataOp.ano = strtol(p, NULL, 10);
                    i++;
                }

                *c_mov = *c_mov + 1;

                i++;
                if(strstr((*linhaC)[i].linha, "<registro>") != NULL){
                    i++;
                }else{
                    break;
                }
            }
        }
    }

}




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
                   dados **linhaC, int *c_linha, int *tamLinha){


    tratarCliente(linhaC, c_linha, clienteC, c_cliente, tamCliente);
    //tratarFilme(linhaC, c_linha, filmeC, c_filme, tamFilme);
    tratarCategoria(linhaC, c_linha, categoriaC, c_cat, tamCat);
    tratarFornecedor(linhaC, c_linha, fornecedorC, c_fornecedor, tamForn);
    tratarFuncionario(linhaC, c_linha, funcC, c_func, tamFunc);
    tratarConta(linhaC, c_linha, contaC, c_conta, tamConta);
    tratarOp(linhaC, c_linha, operacaoC, c_op, tamOp);
    tratarCompra(linhaC, c_linha, compraC, c_compra, tamCompra);
    tratarMov(linhaC, c_linha, movC, c_mov, tamMov);
    tratarFilme(linhaC, c_linha, filmeC, c_filme, tamFilme);
    }


