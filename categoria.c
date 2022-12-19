/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "categoria.h"


// A função abaixo carrega as categorias cadastradas no arquivo txt - NÂO TÁ FUNCIONANDO
// Parâmetros: array dinâmico de categorias, tamanho da memoria alocada por referencia e quantidade de categorias cadastradas por referencia
void carregarCat(categoria **categoriaC, int *c_cat, int *tamCat, int tipoDado) {

    if (tipoDado == 1) {
        FILE *u;
        u = fopen("categorias.txt", "r");

        if (u == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(u)) {
                break;
            }

            if (*c_cat == *tamCat) {
                *tamCat = *tamCat + 1;
                (*categoriaC) = (categoria *) (realloc((*categoriaC), *tamCat * sizeof(categoria)));
            }

            if (categoriaC == NULL) {
                printf("\nErro de alocacao de memoria.\n");
            }

            fscanf(u, "%d\n", &(*categoriaC)[*c_cat].codigo);

            if (feof(u)) {
                break;
            }

            fgets((*categoriaC)[*c_cat].descricao, 50, u);
            limpaString_cat((*categoriaC)[*c_cat].descricao);
            fscanf(u, "%f\n", &(*categoriaC)[*c_cat].valorLocacao);
            fscanf(u, "%d\n", &(*categoriaC)[*c_cat].ativo);

            *c_cat = *c_cat + 1;

            if (feof(u)) {
                break;
            }

        }
        fclose(u);
    } else {
        if(tipoDado == 2){

            FILE *u;
            u = fopen("categorias.bin", "r");

            if (u == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(u)) {
                    break;
                }

                if (*c_cat == *tamCat) {
                    *tamCat = *tamCat + 1;
                    (*categoriaC) = (categoria *) (realloc((*categoriaC), *tamCat * sizeof(categoria)));
                }

                if ((*categoriaC) == NULL) {
                    printf("\nErro de alocacao de memoria.\n");
                }

                fread(&(*categoriaC)[*c_cat], sizeof(categoria), 1,u);

                if (feof(u)) {
                    break;
                }

                *c_cat = *c_cat + 1;

                if (feof(u)) {
                    break;
                }

            }
            fclose(u);

        }
    }

}


// a função abaixa grava os dados no arquivo txt
// Parâmetros: Array dinâmico de categorias e número de categorias cadastradas
void gravar_cat(categoria *categoriaC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("categorias.txt", "a");
        fprintf(file, "%d\n%s\n%.2f\n%d\n", categoriaC[i].codigo,
                categoriaC[i].descricao,
                categoriaC[i].valorLocacao,
                categoriaC[i].ativo);

        fclose(file);

    }else{
        if(tipoDado == 2){

            FILE *file;

            file = fopen("categorias.bin", "a");

            fwrite(&categoriaC[i], sizeof(categoria), 1,file);

            fclose(file);

        }
    }
}



// a função abaixa grava os dados no arquivo txt após mudança de dados ou exclusão de alguma categoria
// Parâmetros: array dinâmico de categorias e número de categorias cadastradas
void regravar_cat(categoria *categoriaC, int k, int tipoDado) {
    int i = 0;

    if (tipoDado == 1) {

        FILE *file;

        file = fopen("categorias.txt", "w");
        for (i = 0; i < k; i++) {
            fprintf(file, "%d\n%s\n%.2f\n%d\n", categoriaC[i].codigo,
                    categoriaC[i].descricao,
                    categoriaC[i].valorLocacao,
                    categoriaC[i].ativo);
        }
        fclose(file);

    }else{
        if(tipoDado == 2){

            FILE *file;

            file = fopen("categorias.bin", "w");
            for (i = 0; i < k; i++) {
                fwrite(&categoriaC[i], sizeof(categoria), 1,file);
            }
            fclose(file);

        }
    }
}



// a função abaixo cadastra uma nova categoria
// Parâmetros: array dinamica de categorias, quantidade de categorias cadastrados por referencia e tamanho da memoria alocada para categorias por referencia
void cadastra_cat(categoria *categoriaC, int *c_cat, int *tamCat, int tipoDado) {
    int i = 0, codUnico = 0, ok = 0;

    if (*c_cat == *tamCat) {
        *tamCat = *tamCat + 1;
        categoriaC = (categoria *) (realloc(categoriaC, *tamCat * sizeof (categoria)));
    }

    if (categoriaC == NULL) {
        printf("\nErro de alocacao de memoria.\n");
    }

    system("clear");
    printf("Codigo (Unico): ");
    setbuf(stdin, NULL);
    scanf("%d", &codUnico);

    for (i = 0; i < *c_cat; i++) {
        if (codUnico == categoriaC[i].codigo) {
            printf("Já existe uma categoria com esse código. Exclua a categoria já existente ou escolha um novo código.\n");
            ok++;
            return;
        }
    }

    if (ok == 0) {
        categoriaC[*c_cat].codigo = codUnico;
    }

    printf("Descricao: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &categoriaC[*c_cat].descricao);
    printf("Valor locacao: ");
    setbuf(stdin, NULL);
    scanf("%f", &categoriaC[*c_cat].valorLocacao);
    categoriaC[*c_cat].ativo = 1;
    gravar_cat(categoriaC, *c_cat, tipoDado);
    *c_cat = *c_cat + 1;
}



// a função abaixo altera dados da categoria desejada
// Parâmetros: array dinamica de categorias e quantidade de categorias cadastrados
void mudar_cat(categoria *categoriaC, int c_cat) {
    int codCat = 0, ok = 0, i = 0;

    system("clear");
    printf("Informe o codigo da categoria que deseja alterar o cadastro: ");
    scanf("%d", &codCat);
    for (i = 0; i < c_cat; i++) {
        if (categoriaC[i].codigo == codCat) {
            //            printf("CÓDIGO (UNICO): \n");
            //            scanf("%d", &categoriaC[codCat].codigo);
            printf("Descricao: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &categoriaC[i].descricao);
            printf("Valor Locacao: ");
            scanf("%f", &categoriaC[i].valorLocacao);
            ok++;
        }
    }
    if (ok == 0) {
        printf("A categoria com código %d não foi encontrada.", codCat);
    }
}



// a função abaixo limpa o final de cada string
// Parâmetro: string
void limpaString_cat(char *a) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '\n') {
            a[i] = '\0';
            break;
        }
    }
}

void cabecalho_cat() {
    printf("----------- CADASTRO DE CATEGORIA -----------\n");
}



// a função abaixo lista as categorias cadastradas
// Parâmetros: array dinamico de categoria e numero de categoria cadastradas
void lista_cat(categoria *categoriaC, int c_cat) {
    int i = 0, k = 0, op = 0, achou = 0;

    if (c_cat == 0) {
        printf("Não existem categorias cadastradas.\n");
        return;
    }

    system("cls");
    for (i = 0; i < c_cat;) {
        if (categoriaC[i].ativo == 1) {
            printf("Codigo (Unico): %d \n", categoriaC[i].codigo);
            printf("Descricao: %s \n", categoriaC[i].descricao);
            printf("Valor locacao: %.2f \n\n", categoriaC[i].valorLocacao);

            printf("1 - Avancar para a proxima categoria\n");
            printf("2 - Voltar para a categoria anterior\n");
            printf("3 - Sair\n");
            printf(">> ");
            scanf("%d", &op);
            system("cls");
        }
        if (op == 1) {
            i++;
            if (i == c_cat) {
                printf("Esta e a ultima categoria cadastrada.\n");
                break;
            }
        } else {
            if (op == 2) {
                i--;
                if (i < 0) {
                    printf("Esta e a primeira categoria cadastrada.\n");
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



// a função abaixo verifica se a categoria informada no cadastro do filme existe
// Parâmetros: array dinamico da categoria, quantidade de categorias cadastradas e codigo da categoria informado no cadastro do filme
int verifica_cat(categoria *categoriaC, int c_cat, int cod, float *valor) {
    int i = 0, ok = 0;

    for (i = 0; i < c_cat; i++) {
        if (categoriaC[i].codigo == cod) {
            ok++;
            *valor = categoriaC[i].valorLocacao;
        }
    }

    if (ok == 1) {
        return 1;
    } else {
        return 0;
    }

}



// a função abaixo remove uma categoria cadastrada
// Parâmetros: array dinamico de categoria e quantidade de categorias cadastradas por referencia
void remove_cat(categoria *categoriaC, int *c_cat) {
    int codExcluir = 0, codTemp = 0, descricaoTemp[50], i, j, k, ok = 0;
    float valorTemp = 0;

    system("clear");
    printf("Informe o codigo da categoria que deseja excluir os dados: ");
    scanf("%d", &codExcluir);
    for (i = 0; i < *c_cat; i++) {
        //        if (categoriaC[i].codigo == codExcluir) {
        //            j = i;
        //            ok++;
        //        }
        if (categoriaC[i].codigo == codExcluir) {
            categoriaC[i].ativo = 0;
            return;
        }
    }
    if (ok == 0) {
        printf("Nao foi encontrada nenhuma categoria com o codigo %d.\n", codExcluir);
        return;
    }

}



// a função abaixo imprime um menu de opção na tela
int menucat() {

    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                      CATEGORIA                         %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Cadastrar categoria                             %c\n", 186, 186);
    printf("%c    2 - Alterar categoria                               %c\n", 186, 186);
    printf("%c    3 - Visualizar categorias                           %c\n", 186, 186);
    printf("%c    4 - Excluir categoria                               %c\n", 186, 186);
    printf("%c    5 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);

}