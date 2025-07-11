//
// Created by chaga on 10/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

int comparar(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

typedef struct {
    int *dados;
    int tamanho;
    int qtd;
} Estrutura;

Estrutura estruturas[TAM];

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    return SUCESSO;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    int index = posicao - 1;
    if (estruturas[index].dados != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;

    estruturas[index].dados = malloc(tamanho * sizeof(int));
    if (estruturas[index].dados == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    estruturas[index].tamanho = tamanho;
    estruturas[index].qtd = 0;
    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    Estrutura *e = &estruturas[posicao - 1];
    if (e->dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (e->qtd >= e->tamanho)
        return SEM_ESPACO;

    e->dados[e->qtd++] = valor;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9, ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    Estrutura *e = &estruturas[posicao - 1];
    if (e->dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (e->qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    e->qtd--;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    Estrutura *e = &estruturas[posicao - 1];
    if (e->dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (e->qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int i, encontrado = 0;
    for (i = 0; i < e->qtd; i++) {
        if (e->dados[i] == valor) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        return NUMERO_INEXISTENTE;

    for (; i < e->qtd - 1; i++) {
        e->dados[i] = e->dados[i + 1];
    }
    e->qtd--;
    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;

    Estrutura *e = &estruturas[posicao - 1];
    if (e->dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < e->qtd; i++)
        vetorAux[i] = e->dados[i];

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int r = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (r != SUCESSO)
        return r;
    Estrutura *e = &estruturas[posicao - 1];
    qsort(vetorAux, e->qtd, sizeof(int), comparar);
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int k = 0, temDados = 0;
    for (int i = 0; i < TAM; i++) {
        if (estruturas[i].dados != NULL && estruturas[i].qtd > 0) {
            temDados = 1;
            for (int j = 0; j < estruturas[i].qtd; j++) {
                vetorAux[k++] = estruturas[i].dados[j];
            }
        }
    }
    return temDados ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int r = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (r != SUCESSO)
        return r;

    int total = 0;
    for (int i = 0; i < TAM; i++)
        if (estruturas[i].dados != NULL)
            total += estruturas[i].qtd;

    qsort(vetorAux, total, sizeof(int), comparar);
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    Estrutura *e = &estruturas[posicao - 1];
    if (e->dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (e->tamanho + novoTamanho < 1)
        return NOVO_TAMANHO_INVALIDO;

    int *novo = realloc(e->dados, (e->tamanho + novoTamanho) * sizeof(int));
    if (!novo)
        return SEM_ESPACO_DE_MEMORIA;

    e->dados = novo;
    e->tamanho += novoTamanho;
    if (e->qtd > e->tamanho)
        e->qtd = e->tamanho;
    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correspondente à quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (ehPosicaoValida(posicao) != SUCESSO)
        return POSICAO_INVALIDA;
    Estrutura *e = &estruturas[posicao - 1];
    if (e->dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (e->qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    return e->qtd;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *cabeca = malloc(sizeof(No));
    if (!cabeca) return NULL;
    cabeca->prox = NULL;
    No *atual = cabeca;
    for (int i = 0; i < TAM; i++) {
        if (estruturas[i].dados != NULL && estruturas[i].qtd > 0) {
            for (int j = 0; j < estruturas[i].qtd; j++) {
                No *novo = malloc(sizeof(No));
                if (!novo) continue;
                novo->conteudo = estruturas[i].dados[j];
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
            }
        }
    }
    return cabeca;
}

/*
Objetivo: retorna os números da lista encadeada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No *p = inicio->prox;
    int i = 0;
    while (p) {
        vetorAux[i++] = p->conteudo;
        p = p->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *p = *inicio;
    while (p) {
        No *aux = p;
        p = p->prox;
        free(aux);
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao início do programa
*/
void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        estruturas[i].dados = NULL;
        estruturas[i].tamanho = 0;
        estruturas[i].qtd = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.
*/
void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (estruturas[i].dados != NULL) {
            free(estruturas[i].dados);
            estruturas[i].dados = NULL;
        }
    }
}
