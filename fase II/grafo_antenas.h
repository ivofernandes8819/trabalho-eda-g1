/*!
 *  @file grafo_antenas.h
 *  @author Ivo Fernandes | 8819
 *  @date 2025-05-18
 *  @project Trabalho pratico EDA - Grupo II
 */
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
    float latitude;
    float longitude;
    Antena* seguinte;
    Ligacao* ligacoes;
}Antena;

typedef struct {
    Antena* listaAntenas;
} Grafo;

// Protótipos atualizados
void inicializarGrafo(Grafo* g);
Antena* criarAntena(float freq, float lat, float lon);
bool adicionarAntena(Grafo* g, Antena* a);
bool adicionarLigacao(Grafo* g, float freqOrigem, float freqDestino, float distancia);
void mostrarGrafo(const Grafo* g);


#endif
