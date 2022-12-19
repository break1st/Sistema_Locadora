/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   cliente.c
 * Author: Breno
 *
 * Created on 2 de Outubro de 2022, 00:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"



// A função auxilia para validação do CPF

int aux(char ch) {
    return (int) (ch > 47 && ch < 58) ? ch - 48 : -1;
}



// A funão valida o cpf do cliente e o valida
// Parâmetros: CPF

int validaCPF(char *cpf) {
    int key_ = 10, result = 0, num;
    if (strlen(cpf) == 11) { //Se não tiver 11 digitos CPF invalido
        // Verificar se os digitos não são entradas sucessivas de mesmo digito e
        //se podem ser convertido para int
        int qtd = 0;
        for (int i = 0; i < 11; i++) {
            if ((num = aux(cpf[i])) == -1) return 1;
            for (int j = i + 1; j < 11; j++) {
                if (num == aux(cpf[j]) && aux(cpf[j]) != -1) {
                    qtd++;
                }
            }
            if (qtd == 10) {
                return 1;
            }
        }
        //Bloco para testar primerio digito
        for (int i = 0; i < 9; i++) {
            result += aux(cpf[i]) * key_;
            key_--;
        }
        //Verificar primeiro digito se valido entrar no if e verificar o proximo digito
        if (aux(cpf[9]) == (result * 10) % 11) {
            // verificar o proximo digito
            key_ = 11;
            result = 0;
            for (int i = 0; i < 10; i++) {
                result += aux(cpf[i]) * key_;
                key_--;
            }
            if (aux(cpf[10]) == (result * 10) % 11) {
                return 0;
            }
        }
    }
    return 1;
}


void carregarCliente(cliente **clienteC, int *c_cliente, int *tamCliente, int tipoDado){

    if(tipoDado == 1){
    FILE *y;
    y = fopen("clientes.txt", "r");

    if (y == NULL) {
        printf("Erro para abrir arquivo.\n");
        exit(1);
    }
    while (1) {

        if (feof(y)) {
            break;
        }

        if (*c_cliente == *tamCliente) {
            *tamCliente = *tamCliente + 1;
            (*clienteC) = (cliente *) (realloc((*clienteC), *tamCliente * sizeof(cliente)));
        }

        if ((*clienteC) == NULL) {
            printf("\nErro de alocacao de memoria.\n");
        }


        fscanf(y, "%d\n", &(*clienteC)[*c_cliente].codigoCliente);

        if (feof(y)) {
            break;
        }

        fgets((*clienteC)[*c_cliente].nome, 30, y);
        limpaString_cliente((*clienteC)[*c_cliente].nome);

        fgets((*clienteC)[*c_cliente].endereco, 60, y);
        limpaString_cliente((*clienteC)[*c_cliente].endereco);

        fgets((*clienteC)[*c_cliente].cpf, 13, y);
        limpaString_cliente((*clienteC)[*c_cliente].cpf);

        fgets((*clienteC)[*c_cliente].telefone, 17, y);
        limpaString_cliente((*clienteC)[*c_cliente].telefone);

        fgets((*clienteC)[*c_cliente].email, 40, y);
        limpaString_cliente((*clienteC)[*c_cliente].email);

        fgets((*clienteC)[*c_cliente].sexo, 15, y);
        limpaString_cliente((*clienteC)[*c_cliente].sexo);

        fgets((*clienteC)[*c_cliente].estadoCivil, 15, y);
        limpaString_cliente((*clienteC)[*c_cliente].estadoCivil);

        fgets((*clienteC)[*c_cliente].dataNascimento, 12, y);
        limpaString_cliente((*clienteC)[*c_cliente].dataNascimento);

        if (feof(y)) {
            break;
        }

        *c_cliente = *c_cliente + 1;
    }

    fclose(y);
}else{
    if(tipoDado == 2){

        FILE *y;
        y = fopen("clientes.bin", "r");

        if (y == NULL) {
            printf("Erro para abrir arquivo.\n");
            exit(1);
        }
        while (1) {

            if (feof(y)) {
                break;
            }

            if (*c_cliente == *tamCliente) {
                *tamCliente = *tamCliente + 1;
                (*clienteC) = (cliente *) (realloc((*clienteC), *tamCliente * sizeof(cliente)));
            }

            if ((*clienteC) == NULL) {
                printf("\nErro de alocacao de memoria.\n");
            }

            fread(&(*clienteC)[*c_cliente], sizeof(cliente), 1,y);

            if (feof(y)) {
                break;
            }

            *c_cliente = *c_cliente + 1;
        }

        fclose(y);

        }
    }

}



// A função cadastra novos clientes
// Parâmetros: array dinâmico de clientes, quantidade de clientes, tamanho da alocação de memória

void cadastro_cliente(cliente *clienteC, int *c_cliente, int *tamCliente, int tipoDado) {
    int codUnico = 0, i = 0, ok = 0;

    // abaixo é verificado se é necessário alocar mais espaço na memória e ela é alocada
    if (*c_cliente == *tamCliente) {
        *tamCliente = *tamCliente + 1;
        clienteC = (cliente *) (realloc(clienteC, *tamCliente * sizeof (cliente)));
    }
    if (clienteC == NULL) {
        printf("/nErro de alocacao de memoria.");
    }

    system("clear");
    printf("Codigo (Unico): ");
    scanf("%d", &codUnico);

    // abaixo é verifica se já existe algum cliente com o código informado
    for (i = 0; i < *c_cliente; i++) {
        if (codUnico == clienteC[i].codigoCliente) {
            printf("Ja existe um cliente com esse codigo. Exclua o cliente existente ou escolha um novo codigo.\n");
            ok++;
            return;
        }
    }
    if (ok == 0) {
        clienteC[*c_cliente].codigoCliente = codUnico;
    }

    printf("Nome: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].nome);
    printf("Endereco: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].endereco);
    printf("CPF: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].cpf);

    // abaixo é feita a validação do cpf
    while (validaCPF(clienteC[*c_cliente].cpf) != 0) {
        printf("CPF invalido. Informe um CPF valido.\n");
        printf("CPF: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]s", &clienteC[*c_cliente].cpf);
    }

    printf("Telefone: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].telefone);
    printf("E-mail: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].email);
    printf("Sexo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].sexo);
    printf("Estado Civil: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].estadoCivil);
    printf("Data de nascimento: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", &clienteC[*c_cliente].dataNascimento);
    // abaixo é chamada a função para gravar os dados no arquivo txt
    gravar_cliente(clienteC, *c_cliente, tipoDado);
    // é incrementado 1 ao número de clientes cadastrados
    *c_cliente = *c_cliente + 1;
}



// a função abaixo grava os clientes no arquivo txt
// Parâmetros: array dinâmico de clientes e número do cliente cadastrado

void gravar_cliente(cliente *clienteC, int i, int tipoDado) {

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("clientes.txt", "a");
        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", clienteC[i].codigoCliente,
                clienteC[i].nome,
                clienteC[i].endereco,
                clienteC[i].cpf,
                clienteC[i].telefone,
                clienteC[i].email,
                clienteC[i].sexo,
                clienteC[i].estadoCivil,
                clienteC[i].dataNascimento);

        fclose(file);



    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("clientes.bin", "a");
            fwrite(&clienteC[i], sizeof(cliente), 1, file);

            fclose(file);
        }
    }
}



// a função abaixa grava os dados no arquivo txt após mudança de dados ou exclusão de algum cliente
// Parâmetros: array dinâmico de clientes e número de clientes cadastrados

void regravar_cliente(cliente *clienteC, int k, int tipoDado) {
    int i = 0;

    if (tipoDado == 1) {
        FILE *file;

        file = fopen("clientes.txt", "w");
        for (i = 0; i < k; i++) {
            fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", clienteC[i].codigoCliente,
                    clienteC[i].nome,
                    clienteC[i].endereco,
                    clienteC[i].cpf,
                    clienteC[i].telefone,
                    clienteC[i].email,
                    clienteC[i].sexo,
                    clienteC[i].estadoCivil,
                    clienteC[i].dataNascimento);
        }
        fclose(file);



    }else{
        if(tipoDado == 2){
            FILE *file;

            file = fopen("clientes.bin", "w");
            for (i = 0; i < k; i++) {
                fwrite(&clienteC[i], sizeof(cliente), 1, file);
            }
            fclose(file);

        }
    }
}



// a função abaixo remove o espaço dado no final de cada string

void limpaString_cliente(char *a) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '\n') {
            a[i] = '\0';
            break;
        }
    }
}



// A função abaixo carrega os clientes cadastrados no arquivo txt - NÂO TÁ FUNCIONANDO
// Parâmetros: array dinâmico de clientes, tamanho da memoria alocada por referencia e quantidade de clientes cadastrados por referencia

void carregar_cliente(cliente *clienteC, int *tamCliente, int *c_cliente) {

    FILE *p;
    p = fopen("clientes.txt", "r");

    if (p == NULL) {
        printf("Erro para abrir arquivo.\n");
        exit(1);
    }
    while (!feof(p)) {
        //if (!filelength(fileno(f))) {
        //break;
        //}
        fscanf(p, "%d\n", &clienteC[*c_cliente].codigoCliente);

        fgets(clienteC[*c_cliente].nome, 30, p);
        limpaString_cliente(clienteC[*c_cliente].nome);

        fgets(clienteC[*c_cliente].endereco, 60, p);
        limpaString_cliente(clienteC[*c_cliente].endereco);

        fgets(clienteC[*c_cliente].cpf, 13, p);
        limpaString_cliente(clienteC[*c_cliente].cpf);

        fgets(clienteC[*c_cliente].telefone, 20, p);
        limpaString_cliente(clienteC[*c_cliente].telefone);

        fgets(clienteC[*c_cliente].email, 40, p);
        limpaString_cliente(clienteC[*c_cliente].email);

        fgets(clienteC[*c_cliente].sexo, 15, p);
        limpaString_cliente(clienteC[*c_cliente].sexo);

        fgets(clienteC[*c_cliente].estadoCivil, 15, p);
        limpaString_cliente(clienteC[*c_cliente].estadoCivil);

        fgets(clienteC[*c_cliente].dataNascimento, 12, p);
        limpaString_cliente(clienteC[*c_cliente].dataNascimento);

        *c_cliente = *c_cliente + 1;
    }
    fclose(p);
}



// a função abaixo lista os clientes cadastrados
// Parâmetros: array dinâmico de clientes e número de clientes cadastrados

void lista_cliente(cliente *clienteC, int c_cliente) {
    int i = 0, op = 0, ok = 0;


    if (c_cliente == 0) {
        printf("Não existem clientes cadastrados.\n");
        return;
    }

    system("clear");
    printf("Código (UNICO): %d \n", clienteC[i].codigoCliente);
    printf("Nome: %s \n", clienteC[i].nome);
    printf("Endereço: %s \n", clienteC[i].endereco);
    printf("Cpf: %s \n", clienteC[i].cpf);
    printf("Telefone: %s \n", clienteC[i].telefone);
    printf("E-mail: %s \n", clienteC[i].email);
    printf("Sexo: %s \n", clienteC[i].sexo);
    printf("Estado civil: %s \n", clienteC[i].estadoCivil);
    printf("Data de nascimento: %s \n", clienteC[i].dataNascimento);
    printf("\n");

    printf("Digite 1 para avançar para o próximo cliente:\n");
    printf("Digite 2 para voltar para o cliente anterior:\n");
    printf("Digite 3 para voltar ao menu anterior:\n");
    printf(">> ");
    scanf("%d", &op);
    system("cls");
    while (op != 3) {
        if (op == 1) {

            i++;
            if (i == c_cliente) {
                printf("Este é o último cliente cadastrado.\n");
                break;
            }
            system("clear");
            printf("Código (UNICO): %d \n", clienteC[i].codigoCliente);
            printf("Nome: %s \n", clienteC[i].nome);
            printf("Endereço: %s \n", clienteC[i].endereco);
            printf("Cpf: %s \n", clienteC[i].cpf);
            printf("Telefone: %s \n", clienteC[i].telefone);
            printf("E-mail: %s \n", clienteC[i].email);
            printf("Sexo: %s \n", clienteC[i].sexo);
            printf("Estado civil: %s \n", clienteC[i].estadoCivil);
            printf("Data de nascimento: %s \n", clienteC[i].dataNascimento);
            printf("\n");
        } else {
            if (op == 2) {
                i--;

                if (i < 0) {
                    printf("Este é o primeiro cliente cadastrado.\n");
                    break;
                }
                system("clear");
                printf("Código (UNICO): %d \n", clienteC[i].codigoCliente);
                printf("Nome: %s \n", clienteC[i].nome);
                printf("Endereço: %s \n", clienteC[i].endereco);
                printf("Cpf: %s \n", clienteC[i].cpf);
                printf("Telefone: %s \n", clienteC[i].telefone);
                printf("E-mail: %s \n", clienteC[i].email);
                printf("Sexo: %s \n", clienteC[i].sexo);
                printf("Estado civil: %s \n", clienteC[i].estadoCivil);
                printf("Data de nascimento: %s \n", clienteC[i].dataNascimento);
                printf("\n");

            }
        }
        printf("Digite 1 para avançar para o próximo cliente:\n");
        printf("Digite 2 para voltar para o cliente anterior:\n");
        printf("Digite 3 para voltar ao menu anterior:\n");
        scanf("%d", &op);
    }
}



// a função abaixo altera dados do cliente desejado
// Parâmetros: array dinamico de clientes e quantidade de clientes cadastrados

void mudar_cliente(cliente *clienteC, int c_cliente) {
    int i = 0, mudarCliente = 0, ok = 0, codUnico = 0, k = 0;

    system("clear");
    printf("Informe o codigo do cliente que deseja alterar o cadastro: ");
    scanf("%d", &mudarCliente);
    for (i = 0; i < c_cliente; i++) {
        if (clienteC[i].codigoCliente == mudarCliente) {

            printf("\nNOME: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &clienteC[i].nome);
            printf("\nENDERECO: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &clienteC[i].endereco);
            printf("\nCPF: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &clienteC[i].cpf);
            printf("\nTELEFONE: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &clienteC[i].telefone);
            printf("\nE-MAIL: ");
            setbuf(stdin, NULL);
            scanf("%s", &clienteC[i].email);
            printf("\nSEXO: ");
            setbuf(stdin, NULL);
            scanf("%s", &clienteC[i].sexo);
            printf("\nESTADO CIVIL: ");
            setbuf(stdin, NULL);
            scanf("%s", &clienteC[i].estadoCivil);
            printf("\nDATA DE NASCIMENTO: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", &clienteC[i].dataNascimento);
            ok++;
        }
    }
    if (ok == 0) {
        printf("Não foi encontrado cliente com código %d.\n", mudarCliente);
    }
}



// a função abaixo remove o cadastro de clientes
// Parâmetros: array dinâmico de clientes e quantidade de clientes cadastrados

void remove_cliente(cliente **clienteC, int *c_cliente) {
    int codExcluir = 0, codigoTemp = 0, i, j, k, ok = 0, pos = 0;
    char nomeTemp[30], enderecoTemp[60], cpfTemp[13], telTemp[20], emailTemp[40], sexoTemp[15], estadoTemp[30], dataTemp[12];

    system("clear");
    printf("Informe o codigo do cliente que deseja excluir os dados: ");
    setbuf(stdin, NULL);
    scanf("%d", &codExcluir);
    // abaixo é verificado se existe algum cliente com o código informado
    for (i = 0; i < *c_cliente; i++) {
        if ((*clienteC)[i].codigoCliente == codExcluir) {
            pos = i;
            ok++;
            break;
        }
    }
    if (pos == *c_cliente - 1) {
        *c_cliente = *c_cliente - 1;
        return;
    } else {
        for (j = pos; j < *c_cliente; j++) {
            if (j + 1 < *c_cliente && ok == 1) {
                (*clienteC)[j].codigoCliente = (*clienteC)[j+1].codigoCliente;
                strcpy((*clienteC)[j].nome, (*clienteC)[j+1].nome);
                strcpy((*clienteC)[j].endereco, (*clienteC)[j+1].endereco);
                strcpy((*clienteC)[j].cpf, (*clienteC)[j+1].cpf);
                strcpy((*clienteC)[j].telefone, (*clienteC)[j+1].telefone);
                strcpy((*clienteC)[j].email, (*clienteC)[j+1].email);
                strcpy((*clienteC)[j].sexo, (*clienteC)[j+1].sexo);
                strcpy((*clienteC)[j].estadoCivil, (*clienteC)[j+1].estadoCivil);
                strcpy((*clienteC)[j].dataNascimento, (*clienteC)[j+1].dataNascimento);

            }
        }
    }
    *c_cliente = *c_cliente - 1;

    if (ok == 0) {
        printf("Não foi encontrado nenhum cliente com o codigo %d.\n", codExcluir);
        return;
    }

}



// a função abaixo imprime um menu de opção na tela

int menucliente() {

    printf("\n%c", 201);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    printf("%c", 186);
    printf("                        CLIENTE                         %c\n", 186);
    printf("%c", 204);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
    printf("%c    1 - Cadastrar cliente                               %c\n", 186, 186);
    printf("%c    2 - Alterar cliente                                 %c\n", 186, 186);
    printf("%c    3 - Visualizar clientes                             %c\n", 186, 186);
    printf("%c    4 - Excluir cliente                                 %c\n", 186, 186);
    printf("%c    5 - Sair                                            %c\n", 186, 186);
    printf("%c", 200);
    for (int i = 0; i < 56; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("%c ", 175);

}