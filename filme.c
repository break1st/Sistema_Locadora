/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
//#include "locadora.h"
//#include "categoria.h"
#include <unistd.h>
#include <io.h>



// A função abaixo carrega os filmes cadastrados no arquivo txt - NÂO TÁ FUNCIONANDO
// Parâmetros: array dinâmico de filmes, tamanho da memoria alocada por referencia e quantidade de filmes cadastrados por referencia

void carregarFilme(filme **filmeC, int *c_filme, int *tamFilme, int tipoDado) {

    if(tipoDado == 1) {
        FILE *p;
        p = fopen("filmes.txt", "r");

        if (p == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(p)) {
                break;
            }

            if (*c_filme == *tamFilme) {
                *tamFilme = *tamFilme + 1;
                (*filmeC) = (filme *) (realloc((*filmeC), *tamFilme * sizeof(filme)));
            }
            if ((*filmeC) == NULL) {
                printf("/nErro de alocacao de memoria.");
            }

            fscanf(p, "%d\n", &(*filmeC)[*c_filme].codigoFilme);

            if (feof(p)) {
                break;
            }

            fgets((*filmeC)[*c_filme].descricao, 50, p);
            fscanf(p, "%f\n", &(*filmeC)[*c_filme].valor);
            limpaString_filme((*filmeC)[*c_filme].descricao);
            fscanf(p, "%d\n", &(*filmeC)[*c_filme].exemplarFilme);
            fscanf(p, "%d\n", &(*filmeC)[*c_filme].codigoCategoria);
            fgets((*filmeC)[*c_filme].lingua, 50, p);
            limpaString_filme((*filmeC)[*c_filme].lingua);
            fscanf(p, "%d\n", &(*filmeC)[*c_filme].exLocados);
            fscanf(p, "%d\n", &(*filmeC)[*c_filme].pendente);

            *c_filme = *c_filme + 1;

            if (feof(p)) {
                break;
            }

        }


        fclose(p);
    }else{
        if(tipoDado == 2){

            FILE *d;
            d = fopen("filmes.bin", "r");

            if (d == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(d)) {
                    break;
                }

                if (*c_filme == *tamFilme) {
                    *tamFilme = *tamFilme + 1;
                    (*filmeC) = (filme *) (realloc((*filmeC), *tamFilme * sizeof(filme)));
                }

                if ((*filmeC) == NULL) {
                    printf("\nErro de alocacao de memoria.");
                }

                //filme new;
                fread(&(*filmeC)[*c_filme], sizeof(filme), 1,d);
                //(*filmeC)[*c_filme] = new;
                if (feof(d)) {
                    break;
                }

                *c_filme = *c_filme + 1;

                if (feof(d)) {
                    break;
                }

            }
            fclose(d);

        }
    }

}



// a função abaixo cadastra um novo filme
// Parâmetros: array dinamico de filmes, quantidade de filmes cadastrados e tamanho da memória alocada para filmes

void cadastra_filme(filme *filmeC, int *c_filme, int *tamFilme, categoria *categoriaC, int c_cat, int tipoDado) {

    int codUnico = 0, ok = 0, i, codCat = 0, verify = 0, op = 0;
    float valor = 0;

    if (*c_filme == *tamFilme) {
        *tamFilme = *tamFilme + 1;
        filmeC = (filme *) (realloc(filmeC, *tamFilme * sizeof(filme)));
    }
    if (filmeC == NULL) {
        printf("/nErro de alocacao de memoria.");
    }


    system("cls");
    printf("Codigo (Unico): \n");
    scanf("%d", &codUnico);

    for (i = 0; i < *c_filme; i++) {
        if (codUnico == filmeC[i].codigoFilme) {
            printf("Ja existe um filme com esse codigo. Exclua o filme existente ou escolha um novo codigo.\n\n");
            ok++;
            return;
        }
    }

    if (ok == 0) {
        filmeC[*c_filme].codigoFilme = codUnico;
    }

    printf("Descricao: \n");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &filmeC[*c_filme].descricao);
    printf("Exemplares: \n");
    setbuf(stdin, NULL);
    scanf("%d", &filmeC[*c_filme].exemplarFilme);
    for(i=0; i < c_cat; i++) {
        printf("Categorias: (%d) %s", categoriaC[i].codigo, categoriaC[i].descricao);
        printf("\n");
    }
    printf("Codigo da categoria: \n");
    setbuf(stdin, NULL);
    scanf("%d", &codCat);
    filmeC[*c_filme].exLocados = 0;
    filmeC[*c_filme].pendente = 1;
    while (verify != 1) {
        if (verifica_cat(categoriaC, c_cat, codCat, &valor) == 1) {
            filmeC[*c_filme].codigoCategoria = codCat;
            filmeC[*c_filme].valor = valor;
            verify++;
        } else {
            if (verifica_cat(categoriaC, c_cat, codCat, &valor) == 0) {
                printf("Não existe uma categoria com codigo %d.\nCadastre a categoria ou escolha outra.\nSair:................ 1\nTentar novamente:.... 2\n",
                       codCat);
                scanf("%d", &op);
                if (op == 1) {
                    return;
                } else {
                    if (op == 2) {
                        printf("Codigo da categoria: \n");
                        setbuf(stdin, NULL);
                        scanf("%d", &codCat);
                    } else {
                        printf("Opcão inválida.\n");
                    }
                }
            }
        }
    }


    printf("Lingua: \n");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &filmeC[*c_filme].lingua);
    gravar_filme(filmeC, *c_filme, tipoDado);

    //filmeC[*c_filme].pendente = 1;

    *c_filme = *c_filme + 1;

}



// a função abaixo altera dados do filme desejado
// Parâmetros: array dinamico de filmes e quantidade de filmes cadastrados

void mudar_filme(filme *filmeC, int c_filme, categoria *categoriaC, int c_cat) {
    int mudarFilme = 0, codUnico = 0, k = 0, codCat, ok = 0, verify = 0, i, op = 0;
    float valor = 0;
    system("cls");
    printf("Informe o codigo do filme que deseja alterar o cadastro: ");
    scanf("%d", &mudarFilme);
    for (i = 0; i < c_filme; i++) {
        if (filmeC[i].codigoFilme == mudarFilme) {

            printf("Descricao: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &filmeC[i].descricao);
            printf("Exemplares: ");
            scanf("%d", &filmeC[i].exemplarFilme);
            for(int j=0; j < c_cat; j++) {
                printf("Categorias: (%d) %s", categoriaC[j].codigo, categoriaC[j].descricao);
                printf("\n");
            }
            printf("Codigo da categoria: ");
            scanf("%d", &codCat);

            while (verify != 1) {
                if (verifica_cat(categoriaC, c_cat, codCat, &valor) == 1) {
                    filmeC[i].codigoCategoria = codCat;
                    filmeC[i].valor = valor;
                    verify++;
                } else {
                    if (verifica_cat(categoriaC, c_cat, codCat, &valor) == 0) {
                        printf("Não existe uma categoria com codigo %d.\nCadastre a categoria ou escolha outra.\nSair:................ 1\nTentar novamente:.... 2\n", codCat);
                        scanf("%d", &op);
                        if (op == 1) {
                            return;
                        } else {
                            if (op == 2) {
                                printf("Codigo da categoria: ");
                                setbuf(stdin, NULL);
                                scanf("%d", &codCat);
                            } else {
                                printf("Opcão inválida.\n");
                            }
                        }
                    }
                }
            }

            printf("Lingua: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &filmeC[i].lingua);
            ok++;
        }
    }
    if (ok == 0) {
        printf("O filme com o codigo %d não foi encontrado.", mudarFilme);
    }
}



// a função abaixo lista os filmes cadastrados
// Parâmetros: array dinâmico de filmes e número de filmes cadastrados
void lista_filme(filme *filmeC, int c_filme) {
    int i = 0, op = 0, k = 0;

    if (c_filme == 0) {
        printf("Não existem filmes cadastrados.\n");
        return;
    }

    for(i=0; i < c_filme;) {
        system("cls");
        printf("Codigo: %d\n", filmeC[i].codigoFilme);
        printf("Descricao: %s\n", filmeC[i].descricao);
        printf("Valor: %.2f\n", filmeC[i].valor);
        printf("Exemplares: %d\n", filmeC[i].exemplarFilme);
        printf("Codigo da categoria: %d\n", filmeC[i].codigoCategoria);
        printf("Lingua: %s\n", filmeC[i].lingua);
        //printf("\n");

        printf("1 - Avançar para o proximo filme\n");
        printf("2 - Voltar para o filme anterior\n");
        printf("3 - Sair\n");
        printf(">> ");
        scanf("%d", &op);
        if (op == 1) {
            i++;
            if (i == c_filme) {
                printf("Este é o ultimo filme cadastrado.\n");
                break;
            }
        } else {
            if (op == 2) {
                i--;
                if (i < 0) {
                    printf("Este é o primeiro filme cadastrado.\n");
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



//  a função abaixa grava os dados no arquivo txt após cadastro de filme
// Parâmetros: array dinâmico de filmes e numero do filme cadastrado

void gravar_filme(filme *filmeC, int i, int tipoDado) {

   if (tipoDado == 1) {
        FILE *file;

        file = fopen("filmes.txt", "a");
       fprintf(file, "%d\n%s\n%f\n%d\n%d\n%s\n%d\n%d\n", filmeC[i].codigoFilme,
               filmeC[i].descricao,
               filmeC[i].valor,
               filmeC[i].exemplarFilme,
               filmeC[i].codigoCategoria,
               filmeC[i].lingua,
               filmeC[i].exLocados,
               filmeC[i].pendente);

        fclose(file);
    }else{
        if(tipoDado == 2){

            FILE *file;

            file = fopen("filmes.bin", "ab");
            filme new;
            new = filmeC[i];
            fwrite(&new, sizeof(filme), 1,file);

            fclose(file);
        }
    }
}

//fwrite(&(*filmeC)[*c_filme], sizeof(filme), 1,p);

// a função abaixa grava os dados no arquivo txt após mudança de dados ou exclusão de algum filme
// Parâmetros: array dinâmico de filmes e número de filmes cadastrados

void regravar_filme(filme *filmeC, int k, int tipoDado) {
    int i = 0;

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("filmes.txt", "w");
        for (i = 0; i < k; i++) {
            fprintf(file, "%d\n%s\n%f\n%d\n%d\n%s\n%d\n%d\n", filmeC[i].codigoFilme,
                    filmeC[i].descricao,
                    filmeC[i].valor,
                    filmeC[i].exemplarFilme,
                    filmeC[i].codigoCategoria,
                    filmeC[i].lingua,
                    filmeC[i].exLocados,
                    filmeC[i].pendente);
        }

        fclose(file);
    }else{
        if(tipoDado == 2){

            FILE *file;

            file = fopen("filmes.bin", "w");
            for (i = 0; i < k; i++) {
                fwrite(&filmeC[i], sizeof(filme), 1, file);
            }
            fclose(file);
        }
    }
}




// a função abaixo remove o espaço dado no final de cada string
// Parâmetro: string

void limpaString_filme(char *a) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '\n') {
            a[i] = '\0';
            break;
        }
    }
}



// a função abaixo remove algum filme cadastrado
// Parâmetros: array dinâmico de filmes e quantidade de filmes cadastrados

void remove_filme(filme **filmeC, int *c_filme) {
    int codExcluir = 0, codigoTemp = 0, exemplarTemp = 0, locadosTemp = 0, pendenteTemp = 0,categoriaTemp = 0, i = 0, j = 0, k = 0, ok = 0, u = 0;
    int pos = 0;
    char descricaoTemp[50], linguaTemp[10];
    char temp[4];
    filme new[*c_filme];

    system("cls");
    printf("Informe o codigo do filme que deseja excluir os dados: ");
    setbuf(stdin, NULL);
    scanf("%d", &codExcluir);

    //scanf("%s", temp);
    //codExcluir = strtol(temp, NULL, 10);
    for (i = 0; i < *c_filme; i++) {
        if ((*filmeC)[i].codigoFilme == codExcluir) {
            pos = i;
            ok++;
            break;
        }
    }
    if (pos == *c_filme - 1) {
        *c_filme = *c_filme - 1;
        return;
    } else {
        for (j = pos; j < *c_filme; j++) {
            if (j + 1 < *c_filme && ok == 1) {
                (*filmeC)[j].codigoFilme = (*filmeC)[j + 1].codigoFilme;
                strcpy((*filmeC)[j].descricao, (*filmeC)[j + 1].descricao);
                (*filmeC)[j].codigoCategoria = (*filmeC)[j + 1].codigoCategoria;
                (*filmeC)[j].exemplarFilme = (*filmeC)[j + 1].exemplarFilme;
                (*filmeC)[j].exLocados = (*filmeC)[j + 1].exLocados;
                (*filmeC)[j].pendente = (*filmeC)[j + 1].pendente;
                strcpy((*filmeC)[j].lingua, (*filmeC)[j + 1].lingua);

            }
        }
    }
    *c_filme = *c_filme - 1;
//
//
//
//
//
//                for (u = j; u < *c_filme; u++) {
//                    k = u + 1;
//                    codigoTemp = (*filmeC)[k].codigoFilme;
//                    strcpy(descricaoTemp, (*filmeC)[k].descricao);
//                    exemplarTemp = (*filmeC)[k].exemplarFilme;
//                    categoriaTemp = (*filmeC)[k].codigoCategoria;
//                    locadosTemp = (*filmeC)[k].exLocados;
//                    pendenteTemp = (*filmeC)[k].pendente;
//                    strcpy(linguaTemp, (*filmeC)[k].lingua);
//                    (*filmeC)[u].codigoFilme = codigoTemp;
//                    strcpy((*filmeC)[u].descricao, descricaoTemp);
//                    (*filmeC)[u].exLocados = locadosTemp;
//                    (*filmeC)[u].pendente = pendenteTemp;
//                    (*filmeC)[u].exemplarFilme = exemplarTemp;
//                    (*filmeC)[u].codigoCategoria = categoriaTemp;
//                    strcpy((*filmeC)[u].lingua, linguaTemp);
//                }
//                *c_filme = *c_filme - 1;
//
//            }
//        }
//    }

    if (ok == 0) {
        printf("Não foi encontrado nenhum filme com o codigo %d.\n", codExcluir);
        return;
    }
}



// a função abaixo imprime um menu de opções na tela

void menufilme() {

    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                         FILME                          %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Cadastrar filme                                 %c\n", 186, 186);
    printf("%c    2 - Alterar filme                                   %c\n", 186, 186);
    printf("%c    3 - Visualizar filmes                               %c\n", 186, 186);
    printf("%c    4 - Excluir filme                                   %c\n", 186, 186);
    printf("%c    5 - Comprar filme                                   %c\n", 186, 186);
    printf("%c    6 - Filmes comprados                                %c\n", 186, 186);
    printf("%c    7 - Cadastros pendentes                             %c\n", 186, 186);
    printf("%c    8 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);

}



void cadastroPendentes(filme *filmeC, int c_filme, int *c_pendente, categoria *categoriaC, int c_cat, int tipoDado) {
    int i, op = 0, pos, codUnico, ok = 0, j, okCod = 0, codCat = 0, verify = 0, cont = 0;
    float valor = 0;

    if(*c_pendente == 0){
        printf("Nao existem cadastros pendentes.\n");
        return;
    }

    for (i = 0; i < c_filme; i++) {
        if (filmeC[i].pendente == 0) {
            printf("\nNOME: %s \n", filmeC[i].descricao);
            printf("EXEMPLARES: %d \n\n", filmeC[i].exemplarFilme);
            printf("Digite 1 para editar o cadastro:\n");
            printf("Digite 2 para avançar para o proximo filme:\n");
            printf("Digite 3 para voltar ao menu anterior:\n");
            scanf("%d", &op);
            cont++;
            pos = i;
            while (op != 3) {
                if (op == 1) {
                    //pos = i;
                    printf("\nNOME: %s \n", filmeC[pos].descricao);
                    printf("EXEMPLARES: %d \n", filmeC[pos].exemplarFilme);

                    printf("CODIGO: ");
                    scanf("%d", &codUnico);

                    while (okCod == 0) {
                        for (j = 0; j < c_filme; j++) {
                            if (codUnico == filmeC[j].codigoFilme) {
                                printf("Ja existe um filme com esse codigo. Exclua o filme existente ou escolha um novo codigo.\n\n");
                                ok++;
                                //return;
                            }
                        }

                        if (ok == 0) {
                            filmeC[pos].codigoFilme = codUnico;
                            okCod = 1;
                        } else {
                            printf("CODIGO (Digite 0 para sair do cadastro): ");
                            scanf("%d", &codUnico);
                            ok = 0;
                            if (codUnico == 0) {
                                return;
                            }
                        }
                    }
                    for(int j=0; j< c_cat; j++) {
                        printf("Categorias: (%d) %s", categoriaC[j].codigo, categoriaC[j].descricao);
                        printf("\n");
                    }
                    printf("CODIGO DA CATEGORIA: ");
                    scanf("%d", &codCat);

                    while (verify != 1) {
                        if (verifica_cat(categoriaC, c_cat, codCat, &valor) == 1) {
                            filmeC[pos].codigoCategoria = codCat;
                            verify++;
                        } else {
                            if (verifica_cat(categoriaC, c_cat, codCat, &valor) == 0) {
                                printf("Nao existe uma categoria com codigo %d.\nCadastre a categoria ou escolha outra.\nSair:................ 1\nTentar novamente:.... 2\n",
                                       codCat);
                                scanf("%d", &op);
                                if (op == 1) {
                                    return;
                                } else {
                                    if (op == 2) {
                                        printf("Codigo da categoria: \n");
                                        setbuf(stdin, NULL);
                                        scanf("%d", &codCat);
                                    } else {
                                        printf("Opcao invalida.\n");
                                    }
                                }
                            }
                        }
                    }

                    printf("LINGUA: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]s", filmeC[pos].lingua);
                    filmeC[pos].pendente = 1;
                    regravar_filme(filmeC, c_filme, tipoDado);
                    *c_pendente = *c_pendente - 1;
                    return;
                } else {
                    if (op == 2) {
                        cont++;
                        if(cont > *c_pendente){
                            printf("Esse e o ultimo filme pendente.\n");
                            return;
                        }

                        for (i = pos + 1; i < c_filme; i++) {
                            if (filmeC[i].pendente == 0) {
                                printf("\nNOME: %s \n", filmeC[i].descricao);
                                printf("EXEMPLARES: %d \n\n", filmeC[i].exemplarFilme);
                                printf("Digite 1 para editar o cadastro:\n");
                                printf("Digite 2 para avançar para o proximo filme:\n");
                                printf("Digite 3 para voltar ao menu anterior:\n");
                                scanf("%d", &op);
                                pos = i;

                            }
                        }
                    }
                }
            }
        }
    }
}

