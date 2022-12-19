/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   categoria.h
 * Author: Alunos
 *
 * Created on 22 de Setembro de 2022, 14:12
 */

#ifndef CATEGORIA_H
#define CATEGORIA_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* CATEGORIA_H */

typedef struct {
    int codigo;
    char descricao[50];
    float valorLocacao;
    int ativo;
} categoria;

// função responsável por carregar dados das categorias dos arquivos txt ou bin
void carregarCat(categoria **categoriaC, int *c_cat, int *tamCat, int tipoDado);

// função responsável por gravar dados das categorias nos arquivos txt ou bin
void gravar_cat(categoria *categoriaC, int i, int tipoDado);

// função responsável por verificar se ja existe categoria com o codigo informado
int verifica_cat(categoria *categoriaC, int c_cat, int cod, float *valor);

// função responsável por gravar dados das categorias nos arquivos txt ou bin após alterações
void regravar_cat(categoria *categoriaC, int k, int tipoDado);

// função responsável por cadastrar novas categorias
void cadastra_cat(categoria *categoriaC, int *c_cat, int *tamCat, int tipoDado);

// função responsável por alterar dados de categorias cadastradas
void mudar_cat(categoria *categoriaC, int c_cat);

// função responsável por tratar e limpar caracteres indesejados no final de strings
void limpaString_cat(char *a);

// função responsável por listar categorias cadastradas
void lista_cat(categoria *categoriaC, int c_cat);

// função responsável por excluir categorias
void remove_cat(categoria *categoriaC, int *c_cat);

// função responsável por imprimir menu na tela
int menucat();