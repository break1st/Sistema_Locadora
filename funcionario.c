/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   funcionario.c
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"

void carregarFunc(funcionario **funcC, int *c_func, int *tamFunc, int tipoDado) {

    if (tipoDado == 1) {
        FILE *e;
        e = fopen("funcionario.txt", "r");

        if (e == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(e)) {
                break;
            }

            if (*c_func == *tamFunc) {
                *tamFunc = *tamFunc + 1;
                (*funcC) = (funcionario *) (realloc((*funcC), *tamFunc * sizeof(funcionario)));
            }
            if ((*funcC) == NULL) {
                printf("/nErro de alocacao de memoria.");
            }

            fscanf(e, "%d\n", &(*funcC)[*c_func].codigo);

            if (feof(e)) {
                break;
            }

            fgets((*funcC)[*c_func].nome, 30, e);
            limpaString_func((*funcC)[*c_func].nome);
            fgets((*funcC)[*c_func].cargo, 30, e);
            limpaString_func((*funcC)[*c_func].cargo);
            fgets((*funcC)[*c_func].endereco, 60, e);
            limpaString_func((*funcC)[*c_func].endereco);
            fgets((*funcC)[*c_func].telefone, 17, e);
            limpaString_func((*funcC)[*c_func].telefone);
            fgets((*funcC)[*c_func].email, 30, e);
            limpaString_func((*funcC)[*c_func].email);

            *c_func = *c_func + 1;

            if (feof(e)) {
                break;
            }

        }

        fclose(e);

    }else{
        if(tipoDado == 2){

            FILE *e;
            e = fopen("funcionario.bin", "r");

            if (e == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(e)) {
                    break;
                }

                if (*c_func == *tamFunc) {
                    *tamFunc = *tamFunc + 1;
                    (*funcC) = (funcionario *) (realloc((*funcC), *tamFunc * sizeof(funcionario)));
                }
                if ((*funcC) == NULL) {
                    printf("/nErro de alocacao de memoria.");
                }

                fread(&(*funcC)[*c_func], sizeof(funcionario), 1,e);

                if (feof(e)) {
                    break;
                }


                *c_func = *c_func + 1;

                if (feof(e)) {
                    break;
                }

            }

            fclose(e);

        }
    }
}




// a função abaixo cadastra um novo funcionario
// Parâmetros: array dinamico de funcionarios, quantidade de funcionarios cadastrados e tamanho da memória alocada para funcionarios

void cadastro_func(funcionario *funcC, int *c_func, int *tamFunc, int tipoDado) {
    int codUnico = 0, i, ok = 0;

    if (*c_func == *tamFunc) {
        *tamFunc = *tamFunc + 1;
        funcC = (funcionario *) (realloc(funcC, *tamFunc * sizeof (funcionario)));
    }
    if (funcC == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

    system("clear");
    printf("Codigo: ");
    setbuf(stdin, NULL);
    scanf("%d", &funcC[*c_func].codigo);
    printf("Nome: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &funcC[*c_func].nome);
    printf("Cargo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &funcC[*c_func].cargo);
    printf("Endereco: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &funcC[*c_func].endereco);
    printf("Telefone: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &funcC[*c_func].telefone);
    printf("E-mail: ");
    setbuf(stdin, NULL);
    scanf("%s", &funcC[*c_func].email);
    gravar_func(funcC, *c_func, tipoDado);
    *c_func = *c_func + 1;

}



//  a função abaixa grava os dados no arquivo txt após cadastro de funcionario
// Parâmetros: array dinâmico de funcionarios e numero do funcionario cadastrado

void gravar_func(funcionario *funcC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("funcionario.txt", "a");
        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n", funcC[i].codigo,
                funcC[i].nome,
                funcC[i].cargo,
                funcC[i].endereco,
                funcC[i].telefone,
                funcC[i].email);

        fclose(file);


    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("funcionario.bin", "a");

            fwrite(&funcC[i], sizeof(funcionario), 1, file);

            fclose(file);
        }

    }
}



// a função abaixa grava os dados no arquivo txt após mudança de dados ou exclusão de algum funcionario
// Parâmetros: array dinâmico de funcionarios e número de funcionarios cadastrados

void regravar_func(funcionario *funcC, int k, int tipoDado) {
    int i = 0;

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("funcionario.txt", "w");
        for (i = 0; i < k; i++) {
            fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n", funcC[i].codigo,
                    funcC[i].nome,
                    funcC[i].cargo,
                    funcC[i].endereco,
                    funcC[i].telefone,
                    funcC[i].email);
        }
        fclose(file);

    }else{
        if(tipoDado == 2){
            FILE *file;
            file = fopen("funcionario.bin", "w");
            for (i = 0; i < k; i++) {
                fwrite(&funcC[i], sizeof(funcionario), 1, file);

            }
            fclose(file);

        }
    }
}



// a função abaixo remove o espaço dado no final de cada string
// Parâmetro: string

void limpaString_func(char *a) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '\n') {
            a[i] = '\0';
            break;
        }
    }
}



// A função abaixo carrega os funcionarios cadastrados no arquivo txt - NÂO TÁ FUNCIONANDO
// Parâmetros: array dinâmico de funcionarios, tamanho da memoria alocada por referencia e quantidade de funcionarios cadastrados por referencia

void carregar_func(funcionario *funcC, int *tamFunc, int *c_func) {
    FILE *p;
    p = fopen("funcionarios.txt", "r");

    if (p == NULL) {
        printf("Erro para abrir arquivo.\n");
        exit(1);
    }

    while (!feof(p)) {

        if (*c_func == *tamFunc) {
            *tamFunc = *tamFunc + 1;
            funcC = (funcionario *) (realloc(funcC, *tamFunc * sizeof (funcionario)));
        }
        if (funcC == NULL) {
            printf("/nErro de alocacao de memoria.");
        }


        fscanf(p, "%d\n", &funcC[*c_func].codigo);
        fgets(funcC[*c_func].nome, 30, p);
        limpaString_func(funcC[*c_func].nome);
        fgets(funcC[*c_func].cargo, 30, p);
        limpaString_func(funcC[*c_func].cargo);
        fgets(funcC[*c_func].endereco, 60, p);
        limpaString_func(funcC[*c_func].endereco);
        fgets(funcC[*c_func].telefone, 17, p);
        limpaString_func(funcC[*c_func].telefone);
        fgets(funcC[*c_func].email, 40, p);
        limpaString_func(funcC[*c_func].email);

        *c_func = *c_func + 1;
    }
    fclose(p);
}



// a função abaixo lista os funcionarios cadastrados
// Parâmetros: array dinâmico de funcionarios e número de funcionarios cadastrados

void lista_func(funcionario *funcC, int c_func) {
    int i = 0, op = 0, achou = 0;


    if (c_func == 0) {
        printf("Não existem funcionários cadastrados.\n");
        return;
    }

    system("clear");
    for(i=0; i < c_func; ){
    printf("Codigo: %d \n", funcC[i].codigo);
    printf("Nome: %s \n", funcC[i].nome);
    printf("Cargo: %s \n", funcC[i].cargo);
    printf("Endereco: %s \n", funcC[i].endereco);
    printf("Telefone: %s \n", funcC[i].telefone);
    printf("E-mail: %s \n", funcC[i].email);
    printf("\n");

    printf("1 - Avançar para o proximo funcionario\n");
    printf("2 - Voltar para o funcionario anterior\n");
    printf("3 - Sair\n");
    printf(">> ");
    scanf("%d", &op);
    system("cls");
    if (op == 1) {
        i++;
        if (i == c_func) {
            printf("Este e o ultimo funcionario cadastrado.\n");
            break;
        }
    } else {
        if (op == 2) {
            i--;
            if (i < 0) {
                printf("Este e o primeiro funcionario cadastrado.\n");
                break;
            }
        } else {
            if (op == 3) {
                return;
            }
        }
    }
}
}



// a função abaixo remove algum funcionario cadastrado
// Parâmetros: array dinâmico de funcionarios e quantidade de funcionarios cadastrados

void remove_func(funcionario *funcC, int *c_func) {
    int codExcluir = 0, codigoTemp, i, j, k, ok = 0, pos = 0;
    char nomeTemp[30], cargoTemp[30], enderecoTemp[60], telTemp[17], emailTemp[40];

    system("clear");
    printf("Informe o codigo do funcionario que deseja excluir os dados: ");
    scanf("%d", &codExcluir);

    for (i = 0; i < *c_func; i++) {
        if (funcC[i].codigo == codExcluir) {
            pos = i;
            ok++;
            break;
        }
    }
    if (pos == *c_func - 1) {
        *c_func = *c_func - 1;
        return;
    } else {
        for (j = pos; j < *c_func; j++) {
            if (j + 1 < *c_func && ok == 1) {
                funcC[j].codigo = funcC[j+1].codigo;
                strcpy(funcC[j].nome, funcC[j+1].nome);
                strcpy(funcC[j].cargo, funcC[j+1].cargo);
                strcpy(funcC[j].endereco, funcC[j+1].endereco);
                strcpy(funcC[j].telefone, funcC[j+1].telefone);
                strcpy(funcC[j].email, funcC[j+1].email);
            }
        }
    }
    *c_func = *c_func - 1;

    if (ok == 0) {
        printf("Não foi encontrado nenhum funcionario com o codigo %d.\n", codExcluir);
        return;
    }
}



// a função abaixo imprime um menu de opções na tela

void menufunc() {

    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                      FUNCIONARIO                       %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Cadastrar funcionario                           %c\n", 186, 186);
    printf("%c    2 - Alterar funcionario                             %c\n", 186, 186);
    printf("%c    3 - Visualizar funcionarios                         %c\n", 186, 186);
    printf("%c    4 - Excluir funcionario                             %c\n", 186, 186);
    printf("%c    5 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);

}


// a função abaixo altera dados do funcionário desejado
// Parâmetros: array dinamico de funcionários e quantidade de funcionários cadastrados

void mudar_func(funcionario *funcC, int c_func) {
    int mudarFunc = 0, i = 0, ok = 0;

    system("clear");
    printf("Informe o codigo do funcionario que deseja alterar o cadastro: ");
    scanf("%d", &mudarFunc);
    for (i = 0; i < c_func; i++) {
        if (funcC[i].codigo == mudarFunc) {

            printf("CODIGO (UNICO): \n");
            scanf("%d", &funcC[i].codigo);
            printf("NOME: \n");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &funcC[i].nome);
            //scanf("%d", &funcionarioCadastrado[n].nome);
            printf("CARGO: \n");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &funcC[i].cargo);
            //scanf("%d", &funcionarioCadastrado[n].cargo);
            printf("ENDERECO: \n");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &funcC[i].endereco);
            //scanf("%d", &funcionarioCadastrado[n].endereco);
            printf("TELEFONE: \n");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &funcC[i].telefone);
            //scanf("%d", &funcionarioCadastrado[mudarFunc].telefone);
            printf("E-MAIL: \n");
            scanf("%s", &funcC[i].email);

            ok++;
        }
    }
    if (ok == 0) {
        printf("Não foi encontrado funcionário com o código %d.\n", mudarFunc);
    }
}