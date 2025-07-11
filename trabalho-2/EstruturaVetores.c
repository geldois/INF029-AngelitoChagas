//
// Created by chaga on 09/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct {
    int *dados;
    int tamanho;
    int qtd;
} Estrutura;

Estrutura estruturas[TAM];

int ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    return SUCESSO;
}

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

int comparar(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int r = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (r != SUCESSO)
        return r;
    Estrutura *e = &estruturas[posicao - 1];
    qsort(vetorAux, e->qtd, sizeof(int), comparar);
    return SUCESSO;
}

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

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No *p = inicio->prox;
    int i = 0;
    while (p) {
        vetorAux[i++] = p->conteudo;
        p = p->prox;
    }
}

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

void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        estruturas[i].dados = NULL;
        estruturas[i].tamanho = 0;
        estruturas[i].qtd = 0;
    }
}

void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (estruturas[i].dados != NULL) {
            free(estruturas[i].dados);
            estruturas[i].dados = NULL;
        }
    }
}
