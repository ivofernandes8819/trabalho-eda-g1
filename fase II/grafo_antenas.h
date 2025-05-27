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


typedef struct Ligacao {
    // apontador para a struct antena
    // indica antena destino da ligação
    Antena* destino;
    float distancia;
    Ligacao* seguinte;
} Ligacao;

typedef struct Antena {
    char frequencia;
    // ponderar int em vez de float >> alterado para int
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

// Protótipos atualizados
void inicializarGrafo(Grafo* g);
Antena* criarAntena(char freq, int lat, int lon);
bool adicionarAntena(Grafo* g, Antena* a);
Ligacao* adicionarLigacao(Grafo* g, char freqOrigem, char freqDestino, float distancia);
void mostrarGrafo(const Grafo* g);


#endif
