/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   locadora.c
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:46
 */

#include "locadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void carregarLocadora(locadora **locadoraC, int *c_loca, int tipoDado) {

    if (tipoDado == 1) {
        FILE *l;
        l = fopen("locadora.txt", "r");

        if (l == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        //financeiroC->caixa = 0;
        while (!feof(l)) {

            fscanf(l, "%d\n", c_loca);

            fgets((*locadoraC)->nomeFantasia, 40, l);
            limpaString_loca((*locadoraC)->nomeFantasia);

            fgets((*locadoraC)->razao, 40, l);
            limpaString_loca((*locadoraC)->razao);

            fgets((*locadoraC)->inscricaoEst, 18, l);
            limpaString_loca((*locadoraC)->inscricaoEst);

            fgets((*locadoraC)->cnpj, 18, l);
            limpaString_loca((*locadoraC)->cnpj);

            fgets((*locadoraC)->endereco, 60, l);
            limpaString_loca((*locadoraC)->endereco);

            fgets((*locadoraC)->telefone, 18, l);
            limpaString_loca((*locadoraC)->telefone);

            fgets((*locadoraC)->email, 40, l);
            limpaString_loca((*locadoraC)->email);

            fgets((*locadoraC)->nomeResponsavel, 30, l);
            limpaString_loca((*locadoraC)->nomeResponsavel);

            fgets((*locadoraC)->telResponsavel, 18, l);
            limpaString_loca((*locadoraC)->telResponsavel);

            fscanf(l, "%f\n", &(*locadoraC)->multa);

        }
        fclose(l);
        if (*c_loca == 0) {
            printf("Cadastre previamente sua locadora de filmes.\n");
            cadastro_locadora((*locadoraC), c_loca);
            gravar_locadora((*locadoraC), *c_loca, tipoDado);
        }
    }else {
        if (tipoDado == 2) {

            FILE *l;
            l = fopen("locadora.bin", "r");

            if (l == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            int clocatemp = 0;

            //financeiroC->caixa = 0;
            while (!feof(l)) {
                fread(&clocatemp, sizeof(int), 1, l);
                *c_loca = clocatemp;
                fread(&(*locadoraC)[0], sizeof(locadora), 1, l);

            }
            fclose(l);
            if (*c_loca == 0) {
                printf("Cadastre previamente sua locadora de filmes.\n");
                cadastro_locadora((*locadoraC), c_loca);
                gravar_locadora((*locadoraC), *c_loca, tipoDado);
            }

        } else {
            printf("Cadastre previamente sua locadora de filmes.\n");
            cadastro_locadora((*locadoraC), c_loca);
            gravar_locadora((*locadoraC), *c_loca, tipoDado);
        }
    }
}




int AUX_(char ch) {
    return (int) (ch > 47 && ch < 58) ? ch - 48 : -1;
}



// a função abaixo valida o CNPJ
int validaCnpj(char *CNPJ) {
    int soma, dig;
    //Primeiro Digito Verificador
    //Obter Soma
    if (strlen(CNPJ) == 14) {
        soma = ((AUX_(CNPJ[0])* 5) +
                (AUX_(CNPJ[1])* 4) +
                (AUX_(CNPJ[2]) * 3) +
                (AUX_(CNPJ[3]) * 2) +
                (AUX_(CNPJ[4]) * 9) +
                (AUX_(CNPJ[5]) * 8) +
                (AUX_(CNPJ[6]) * 7) +
                (AUX_(CNPJ[7]) * 6) +
                (AUX_(CNPJ[8]) * 5) +
                (AUX_(CNPJ[9]) * 4) +
                (AUX_(CNPJ[10]) * 3) +
                (AUX_(CNPJ[11]) * 2));
        //Verificar se o primeiro digito verificador é valido
        if ((dig = 11 - (soma % 11)) == AUX_(CNPJ[12])) { //Subtrair base 11 do resto da divisão por 11
            soma = ((AUX_(CNPJ[0])* 6) +
                    (AUX_(CNPJ[1])* 5)+
                    (AUX_(CNPJ[2]) * 4) +
                    (AUX_(CNPJ[3]) * 3) +
                    (AUX_(CNPJ[4]) * 2) +
                    (AUX_(CNPJ[5]) * 9) +
                    (AUX_(CNPJ[6]) * 8) +
                    (AUX_(CNPJ[7]) * 7) +
                    (AUX_(CNPJ[8]) * 6) +
                    (AUX_(CNPJ[9]) * 5) +
                    (AUX_(CNPJ[10]) * 4) +
                    (AUX_(CNPJ[11]) * 3) +
                    (AUX_(CNPJ[12]) * 2));
            if ((dig = 11 - (soma % 11)) == AUX_(CNPJ[13])) {
                return 0;
            } else {
                return 1;
            }
        }
    }
    return 1;
}





// a função abaixo cadastra a locadora
// Parâmetros: array dinamico da locadora e quantidade de locadora cadastradas

void cadastro_locadora(locadora *locadoraC, int *i) {

    if(*i == 1){
        printf("Já existe uma locadora cadastrada.\n");
        return;
    }

    printf("Nome fantasia: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->nomeFantasia);
    printf("Razão social: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->razao);
    printf("Inscricao estadual: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->inscricaoEst);
    printf("CNPJ: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->cnpj);

    while (validaCnpj(locadoraC->cnpj) != 0) {
        printf("CNPJ inválido. Informe um CNPJ válido.\n");
        printf("CNPJ: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]s", locadoraC->cnpj);
    }


    printf("Endereco completo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->endereco);
    printf("Telefone: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->telefone);
    printf("E-mail: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->email);
    printf("Nome do responsavel: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->nomeResponsavel);
    printf("Telefone do responsavel: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->telResponsavel);
    printf("Multa por atraso: ");
    setbuf(stdin, NULL);
    scanf("%f", &locadoraC->multa);

    *i = *i + 1;
}



// a função abaixo imprime os dados da locadora na tela
// Parâmetro: array dinamico da locadora

void dados_locadora(locadora *locadoraC, int c_loca) {

    if(c_loca == 0){
        printf("Não existe uma locadora cadastrada.\n");
        return;
    }
    printf(" Nome fantasia: %s \n", locadoraC->nomeFantasia);
    printf(" Razao social: %s \n", locadoraC->razao);
    printf(" Inscricao estadual: %s \n", locadoraC->inscricaoEst);
    printf(" CNPJ: %s \n", locadoraC->cnpj);
    printf(" Endreco completo: %s \n", locadoraC->endereco);
    printf(" Telefone: %s \n", locadoraC->telefone);
    printf(" E-mail: %s \n", locadoraC->email);
    printf(" Nome do responsavel: %s \n", locadoraC->nomeResponsavel);
    printf(" Telefone do responsavel: %s \n", locadoraC->telResponsavel);
    printf(" Multa por atraso: %.2f \n", locadoraC->multa);
}



// a função abaixo imprime um menu de opção

void menulocadora() {

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
    printf("%c    1 - Visualizar dados                                %c\n", 186, 186);
    printf("%c    2 - Alterar dados                                   %c\n", 186, 186);
    printf("%c    3 - Excluir dados                                   %c\n", 186, 186);
    printf("%c    4 - Cadastrar locadora                              %c\n", 186, 186);
    printf("%c    5 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);

}



// a função abaixo limpa o final de cada string
// Parâmetro: string

void limpaString_loca(char *a) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '\n') {
            a[i] = '\0';
            break;
        }
    }
}



// a função abaixo muda os dados da locadora cadastrada
// Parâmetros: array dinamico  da locadora

void mudar_locadora(locadora *locadoraC) {
    printf("Nome fantasia: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->nomeFantasia);
    printf("Razão social: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->razao);
    printf("Inscricao estadual: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->inscricaoEst);
    printf("CNPJ: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->cnpj);

    while (validaCnpj(locadoraC->cnpj) != 0) {
        printf("CNPJ inválido. Informe um CNPJ válido.\n");
        printf("CNPJ: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]s", locadoraC->cnpj);
    }

    printf("Endereco completo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->endereco);
    printf("Telefone: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->telefone);
    printf("E-mail: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->email);
    printf("Nome do responsavel: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->nomeResponsavel);
    printf("Telefone do responsavel: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", locadoraC->telResponsavel);
    printf("Multa por atraso: ");
    scanf("%f", &locadoraC->multa);
}



// a função abaixo grava os dados da locadora no .txt
// Parâmetros: array dinamico da locadora, quantidade de locadoras cadastradas

void gravar_locadora(locadora *locadoraC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("locadora.txt", "a");
        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n", i,
                locadoraC->nomeFantasia,
                locadoraC->razao,
                locadoraC->inscricaoEst,
                locadoraC->cnpj,
                locadoraC->endereco,
                locadoraC->telefone,
                locadoraC->email,
                locadoraC->nomeResponsavel,
                locadoraC->telResponsavel,
                locadoraC->multa);


        fclose(file);


    }else{
        if(tipoDado == 2){

            FILE *file;
            file = fopen("locadora.bin", "a");
            fwrite(&i, sizeof(int), 1, file);
            fwrite(locadoraC, sizeof(locadora), 1, file);
            fclose(file);

        }
    }
}



void gravar_financeiro(financeiro *financeiroC, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("financeiro.txt", "w");
        fprintf(file, "%f\n%f\n%f\n",
                financeiroC->caixa,
                financeiroC->areceber,
                financeiroC->despesa);

        fclose(file);
    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("financeiro.bin", "w");
            fwrite(financeiroC, sizeof(financeiro), 1, file);
            fclose(file);
        }
    }
}



void carregarFinanceiro(financeiro **financeiroC, int tipoDado) {

    if (tipoDado == 1) {
        FILE *l;
        l = fopen("financeiro.txt", "r");

        if (l == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (!feof(l)) {

            fscanf(l, "%f\n", &(*financeiroC)->caixa);
            fscanf(l, "%f\n", &(*financeiroC)->areceber);
            fscanf(l, "%f\n", &(*financeiroC)->despesa);

        }
        fclose(l);

    }else{
        if(tipoDado == 2){

            FILE *l;
            l = fopen("financeiro.bin", "r");

            if (l == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (!feof(l)) {

                fread(&(*financeiroC)[0], sizeof(financeiro), 1,l);

            }
            fclose(l);

        }
    }
}



void regravar_loca(locadora *locadoraC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("locadora.txt", "w");

        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n", i,
                locadoraC->nomeFantasia,
                locadoraC->razao,
                locadoraC->inscricaoEst,
                locadoraC->cnpj,
                locadoraC->endereco,
                locadoraC->telefone,
                locadoraC->email,
                locadoraC->nomeResponsavel,
                locadoraC->telResponsavel,
                locadoraC->multa);


        fclose(file);


    } else {
        if (tipoDado == 2) {
            FILE *file;

            file = fopen("locadora.bin", "w");
            fwrite(&i, sizeof(int), 1, file);
            fwrite(&locadoraC, sizeof(locadora), 1, file);
            fclose(file);
        }
    }
}

void remove_loca(locadora *locadoraC, int *i, int tipoDado) {
    *i = *i - 1;
}

void regravar_loca_remove(int tipoDado) {
    FILE *file;

    if(tipoDado == 1) {
        file = fopen("locadora.txt", "w");
        fclose(file);
    }else{
        if(tipoDado == 2){
            file = fopen("locadora.bin", "w");
            fclose(file);
        }
    }

}