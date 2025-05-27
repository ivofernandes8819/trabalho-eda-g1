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
    Antena* destino;
    float distancia;
    Ligacao* seguinte;
} Ligacao;

typedef struct Antena {
    char frequencia;
    // ponderar int em vez de float >> alterado para int
    int latitude;
    int longitude;
    Antena* seguinte;
    Ligacao* ligacoes;
}Antena;

typedef struct {
    Antena* listaAntenas;
} Grafo;

// Protótipos atualizados
void inicializarGrafo(Grafo* g);
Antena* criarAntena(char freq, int lat, int lon);
bool adicionarAntena(Grafo* g, Antena* a);
Ligacao* adicionarLigacao(Grafo* g, char freqOrigem, char freqDestino, float distancia);
void mostrarGrafo(const Grafo* g);


#endif
