/*!
 *  @file grafo_antenas.h
 *  @author Ivo Fernandes | 8819
 *  @date 2025-05-18
 *  @project Trabalho pratico EDA - Grupo II
 */

#pragma once

#include <stdbool.h>

#ifndef GRAFO_H
#define GRAFO_H

#pragma region Estruturas

typedef struct Ligacao {
    // apontador para a struct antena
    // indica antena destino da ligação
    Antena* destino;
    float distancia;
    Ligacao* seguinte;
} Ligacao;

typedef struct Antena {
    char frequencia;
    int latitude;
    int longitude;
    // apontador para criar lista ligada de antenas
    // cada antena aponta para a prox da lista
    Antena* seguinte;
    // apontador que referencia inicio da lista ligada de ligações
    Ligacao* ligacoes;
}Antena;

typedef struct {
    // início da lista ligada de antenas
    Antena* listaAntenas;
} Grafo;

#pragma endregion

#endif // GRAFO_H

#pragma region protótipos

/**
 * @brief Inicializa o grafo, configurando seus valores iniciais.
 */
void inicializarGrafo(Grafo* g);

/**
 * @brief Exibe as informações do grafo.
 */
void mostrarGrafo(const Grafo* g);

/**
 * @brief Cria um vértice/antena com os parâmetros fornecidos.
 */
Antena* CriaVertice(char freq, int x, int y, bool visitado, int *aux);

/**
 * @brief Cria uma adjacência entre vértices.
 */
AdjD* CriaAdjacencia(Vertice* destino, int *aux);

/**
 * @brief Insere um novo vértice/antena na lista de vértices.
 */
Vertice* InsereVertice(Vertice* novo, Vertice* inicio, int *aux);

/**
 * @brief Remove um vértice/antena da lista de vértices com base nas coordenadas.
 */
Vertice* RemoveVertice(Vertice* inicio, int x, int y, int* aux);

/**
 * @brief Procura um vértice na lista de vértices utilizando busca em profundidade.
 */
Vertice* ProcuraProfundidade(Vertice* atual, int xAlvo, int yAlvo, int* aux);

/**
 * @brief Grava o grafo num ficheiro binário.
 */
bool GravaBinário(char* fileName, GraphD* g);

#pragma endregion
