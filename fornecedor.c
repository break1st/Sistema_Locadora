/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   fornecedores.c
 * Author: Breno
 *
 * Created on 1 de Outubro de 2022, 16:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"
#include <io.h>



// A função abaixo carrega os fornecedores cadastrados no arquivo txt - NÂO TÁ FUNCIONANDO
// Parâmetros: array dinâmico de fornecedores, tamanho da memoria alocada por referencia e quantidade de fornecedores cadastrados por referencia

void carregarForn(fornecedor **fornecedorC, int *c_forn, int *tamForn, int tipoDado) {

    if (tipoDado == 1) {
        FILE *q;
        q = fopen("fornecedores.txt", "r");

        if (q == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }

        while (1) {

            if (feof(q)) {
                break;
            }

            if (*c_forn == *tamForn) {
                *tamForn = *tamForn + 1;
                (*fornecedorC) = (fornecedor *) (realloc((*fornecedorC), *tamForn * sizeof(fornecedor)));
            }
            if ((*fornecedorC) == NULL) {
                printf("/nErro de alocacao de memoria.");
            }

            fscanf(q, "%d\n", &(*fornecedorC)[*c_forn].codigo);

            if (feof(q)) {
                break;
            }

            fgets((*fornecedorC)[*c_forn].nomeFantasia, 40, q);
            limpaString_forn((*fornecedorC)[*c_forn].nomeFantasia);

            fgets((*fornecedorC)[*c_forn].razaoSocial, 40, q);
            limpaString_forn((*fornecedorC)[*c_forn].razaoSocial);

            fgets((*fornecedorC)[*c_forn].inscricaoEst, 17, q);
            limpaString_forn((*fornecedorC)[*c_forn].inscricaoEst);

            fgets((*fornecedorC)[*c_forn].cnpj, 17, q);
            limpaString_forn((*fornecedorC)[*c_forn].cnpj);

            fgets((*fornecedorC)[*c_forn].endereco, 60, q);
            limpaString_forn((*fornecedorC)[*c_forn].endereco);

            fgets((*fornecedorC)[*c_forn].tel, 14, q);
            limpaString_forn((*fornecedorC)[*c_forn].tel);

            fgets((*fornecedorC)[*c_forn].email, 30, q);
            limpaString_forn((*fornecedorC)[*c_forn].email);

            *c_forn = *c_forn + 1;

            if (feof(q)) {
                break;
            }

        }

        fclose(q);
    }else{
        if(tipoDado == 2){

            FILE *q;
            q = fopen("fornecedores.bin", "r");

            if (q == NULL) {
                printf("Erro para abrir arquivo.\n");
                exit(1);
            }

            while (1) {

                if (feof(q)) {
                    break;
                }

                if (*c_forn == *tamForn) {
                    *tamForn = *tamForn + 1;
                    (*fornecedorC) = (fornecedor *) (realloc((*fornecedorC), *tamForn * sizeof(fornecedor)));
                }
                if ((*fornecedorC) == NULL) {
                    printf("/nErro de alocacao de memoria.");
                }

                fread(&(*fornecedorC)[*c_forn], sizeof(fornecedor), 1,q);

                if (feof(q)) {
                    break;
                }

                *c_forn = *c_forn + 1;

                if (feof(q)) {
                    break;
                }

            }

            fclose(q);

        }
    }
}



//  a função abaixa grava os dados no arquivo txt após cadastro de fornecedor
// Parâmetros: array dinâmico de fornecedores e numero do fornecedor cadastrado

void gravar_forn(fornecedor *fornecedorC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("fornecedores.txt", "a");
        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", fornecedorC[i].codigo,
                fornecedorC[i].nomeFantasia,
                fornecedorC[i].razaoSocial,
                fornecedorC[i].inscricaoEst,
                fornecedorC[i].cnpj,
                fornecedorC[i].endereco,
                fornecedorC[i].tel,
                fornecedorC[i].email);

        fclose(file);



    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("fornecedores.bin", "a");

            fwrite(&fornecedorC[i], sizeof(fornecedor), 1, file);

            fclose(file);
        }
    }
}



// a função abaixa grava os dados no arquivo txt após mudança de dados ou exclusão de algum fornecedor
// Parâmetros: array dinâmico de fornecedores e número de fornecedores cadastrados

void regravar_forn(fornecedor *fornecedorC, int k, int tipoDado) {
    int i = 0;

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("fornecedores.txt", "w");
        for (i = 0; i < k; i++) {
            fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", fornecedorC[i].codigo,
                    fornecedorC[i].nomeFantasia,
                    fornecedorC[i].razaoSocial,
                    fornecedorC[i].inscricaoEst,
                    fornecedorC[i].cnpj,
                    fornecedorC[i].endereco,
                    fornecedorC[i].tel,
                    fornecedorC[i].email);
        }

        fclose(file);


    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("fornecedores.bin", "w");
            for (i = 0; i < k; i++) {
                fwrite(&fornecedorC[i], sizeof(fornecedor), 1, file);
            }

            fclose(file);
        }
    }
}



// a função abaixo cadastra um novo fornecedor
// Parâmetros: array dinamico de fornecedores, quantidade de fornecedores cadastrados e tamanho da memória alocada para fornecedores

void cadastro_forn(fornecedor *fornecedorC, int *c_forn, int *tamForn, int tipoDado) {
    int codUnico = 0, i, ok = 0;

    //alocaMemoria_fornecedor(&fornecedorCadastrado, &c_fornecedor, &tamanhoFornecedor);

    if (*c_forn == *tamForn) {
        *tamForn = *tamForn + 1;
        fornecedorC = (fornecedor *) (realloc(fornecedorC, *tamForn * sizeof (fornecedor)));
    }
    if (fornecedorC == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

    system("clear");
    printf("Codigo (Unico): ");
    scanf("%d", &codUnico);

    for (i = 0; i < *c_forn; i++) {
        if (codUnico == fornecedorC[i].codigo) {
            printf("Já existe um fornecedor com esse código. Exclua o fornecedor existente ou escolha um novo código. \n");
            ok++;
            return;
        }
    }

    if (ok == 0) {
        fornecedorC[i].codigo = codUnico;
    }
    printf("Nome fantasia: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].nomeFantasia);
    printf("Razao social: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].razaoSocial);
    printf("Inscricao estadual: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].inscricaoEst);
    printf("CNPJ: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].cnpj);

    while (validaCNPJ(fornecedorC[*c_forn].cnpj) != 0) {
        printf("CNPJ inválido. Informe um CNPJ válido.\n");
        printf("CNPJ: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]s", &fornecedorC[*c_forn].cnpj);
    }

    printf("Endereco completo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].endereco);
    printf("Telefone: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].tel);
    printf("E-mail: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", fornecedorC[*c_forn].email);
    gravar_forn(fornecedorC, *c_forn, tipoDado);
    *c_forn = *c_forn + 1;
}



// a função abaixo altera dados do fornecedor desejado
// Parâmetros: array dinamico de fornecedores e quantidade de fornecedores cadastrados

void mudar_forn(fornecedor *fornecedorC, int c_forn) {
    int i = 0, ok = 0, codForn = 0;

    system("clear");
    printf("Informe o código do fornecedor que deseja alterar o cadastro: ");
    scanf("%d", &codForn);
    for (i = 0; i < c_forn; i++) {
        if (fornecedorC[i].codigo == codForn) {

            printf("Nome fantasia: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].nomeFantasia);
            printf("Razao social: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].razaoSocial);
            printf("Inscricao estadual: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].inscricaoEst);
            printf("CNPJ: \n");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].cnpj);

            while (validaCNPJ(fornecedorC[i].cnpj) != 0) {
                printf("CNPJ inválido. Informe um CNPJ válido.\n");
                printf("CNPJ: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]s", &fornecedorC[i].cnpj);
            }

            printf("Endereco completo: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].endereco);
            printf("Telefone: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].tel);
            printf("E-mail: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", fornecedorC[i].email);

            ok++;
        }
    }
    if (ok == 0) {
        printf("Não foi encontrado fornecedor com o código %d.\n", codForn);
    }
}



// a função abaixo remove o espaço dado no final de cada string
// Parâmetro: string

void limpaString_forn(char *a) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '\n') {
            a[i] = '\0';
            break;
        }
    }
}



// a função abaixo lista os fornecedores cadastrados
// Parâmetros: array dinâmico de fornecedores e número de fornecedores cadastrados

void lista_forn(fornecedor *fornecedorC, int c_forn) {
    int i, op = 0;

    if (c_forn == 0) {
        printf("Não existem fornecedores cadastrados.\n");
        return;
    }

    system("clear");
    for (i = 0; i < c_forn;) {
        printf("Codigo (Unico): %d \n", fornecedorC[i].codigo);
        printf("Nome fantasia: %s \n", fornecedorC[i].nomeFantasia);
        printf("Razao social: %s \n", fornecedorC[i].razaoSocial);
        printf("Inscricao estadual: %s \n", fornecedorC[i].inscricaoEst);
        printf("CNPJ: %s \n", fornecedorC[i].cnpj);
        printf("Endereco: %s \n", fornecedorC[i].endereco);
        printf("Telefone: %s \n", fornecedorC[i].tel);
        printf("E-mail: %s \n", fornecedorC[i].email);
        printf("\n");

        printf("1 - Avançar para o próximo fornecedor:\n");
        printf("2 - Voltar para o filme fornecedor:\n");
        printf("3 - Sair\n");
        printf(">> ");
        scanf("%d", &op);
        system("cls");
        if (op == 1) {
            i++;
            if (i == c_forn) {
                printf("Este é o última fornecedor cadastrado.\n");
                break;
            }
        } else {
            if (op == 2) {
                i--;
                if (i < 0) {
                    printf("Este é o primeiro fornecedor cadastrado.\n");
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




// a função abaixo imprime um menu de opção na tela

void menuforn() {

    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                       FORNECEDOR                       %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Cadastrar fornecedor                            %c\n", 186, 186);
    printf("%c    2 - Alterar fornecedor                              %c\n", 186, 186);
    printf("%c    3 - Visualizar fornecedores                         %c\n", 186, 186);
    printf("%c    4 - Excluir fornecedor                              %c\n", 186, 186);
    printf("%c    5 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);

}



// a função abaixo remove algum fornecedor cadastrado
// Parâmetros: array dinâmico de clientes e quantidade de clientes cadastrados
void remove_forn(fornecedor *fornecedorC, int *c_forn) {
    int codExcluir = 0, codigoTemp, i, j, k, ok = 0, pos = 0;
    char nomeFanTemp[40], razaoSocialTemp[40], enderecoTemp[60], cnpjTemp[17], EstTemp[17], telTemp[20], emailTemp[40];

    system("clear");
    printf("Informe o codigo do fornecedor que deseja excluir os dados: ");
    scanf("%d", &codExcluir);
    // abaixo é verificado se existe algum fornecedor com o código informado
    for (i = 0; i < *c_forn; i++) {
        if (fornecedorC[i].codigo == codExcluir) {
            pos = i;
            ok++;
            break;
        }
    }
    if (pos == *c_forn - 1) {
        *c_forn = *c_forn - 1;
        return;
    } else {
        for (j = pos; j < *c_forn; j++) {
            if (j + 1 < *c_forn && ok == 1) {
            fornecedorC[j].codigo = fornecedorC[j + 1].codigo;
            strcpy(fornecedorC[j].nomeFantasia, fornecedorC[j + 1].nomeFantasia);
            strcpy(fornecedorC[j].razaoSocial, fornecedorC[j + 1].razaoSocial);
            strcpy(fornecedorC[j].inscricaoEst, fornecedorC[j + 1].inscricaoEst);
            strcpy(fornecedorC[j].cnpj, fornecedorC[j + 1].cnpj);
            strcpy(fornecedorC[j].endereco, fornecedorC[j + 1].endereco);
            strcpy(fornecedorC[j].tel, fornecedorC[j + 1].tel);
            strcpy(fornecedorC[j].email, fornecedorC[j + 1].email);

        }
    }
}
*c_forn = *c_forn - 1;

if (ok == 0) {
    printf("Não foi encontrado nenhum fornecedor com o codigo %d.\n", codExcluir);
    return;
    }
}

void cabecalho_forn() {
    printf("----------- CADASTRO DE FORNECEDOR -----------\n");
}



// a função abaixo auxilia para a validação do CNPJ

int aux_(char ch) {
    return (int) (ch > 47 && ch < 58) ? ch - 48 : -1;
}



// a função abaixo valida o CNPJ

int validaCNPJ(char *CNPJ) {
    int soma, dig;
    //Primeiro Digito Verificador
    //Obter Soma
    if (strlen(CNPJ) == 14) {
        soma = ((aux_(CNPJ[0])* 5) +
                (aux_(CNPJ[1])* 4) +
                (aux_(CNPJ[2]) * 3) +
                (aux_(CNPJ[3]) * 2) +
                (aux_(CNPJ[4]) * 9) +
                (aux_(CNPJ[5]) * 8) +
                (aux_(CNPJ[6]) * 7) +
                (aux_(CNPJ[7]) * 6) +
                (aux_(CNPJ[8]) * 5) +
                (aux_(CNPJ[9]) * 4) +
                (aux_(CNPJ[10]) * 3) +
                (aux_(CNPJ[11]) * 2));
        //Verificar se o primeiro digito verificador é valido
        if ((dig = 11 - (soma % 11)) == aux_(CNPJ[12])) { //Subtrair base 11 do resto da divisão por 11
            soma = ((aux_(CNPJ[0])* 6) +
                    (aux_(CNPJ[1])* 5)+
                    (aux_(CNPJ[2]) * 4) +
                    (aux_(CNPJ[3]) * 3) +
                    (aux_(CNPJ[4]) * 2) +
                    (aux_(CNPJ[5]) * 9) +
                    (aux_(CNPJ[6]) * 8) +
                    (aux_(CNPJ[7]) * 7) +
                    (aux_(CNPJ[8]) * 6) +
                    (aux_(CNPJ[9]) * 5) +
                    (aux_(CNPJ[10]) * 4) +
                    (aux_(CNPJ[11]) * 3) +
                    (aux_(CNPJ[12]) * 2));
            if ((dig = 11 - (soma % 11)) == aux_(CNPJ[13])) {
                return 0;
            } else {
                return 1;
            }
        }
    }
    return 1;
}

