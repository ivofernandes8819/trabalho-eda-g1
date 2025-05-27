/*!
 *  @file grafo_antenas.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-05-18
 *  @project Trabalho pratico EDA - Grupo II
 */
#include <stdio.h>
#include <stdlib.h>
#include "grafo_antenas.h"

#pragma region Estruturas

typedef struct Ligacao {
    struct Antena* destino;
    float distancia;
    struct Ligacao* seguinte;
} Ligacao;

typedef struct Antena {
    char frequencia;
    int latitude;
    int longitude;
    struct Antena* seguinte;
    struct Ligacao* ligacoes;
} Antena;

typedef struct Grafo {
    Antena* listaAntenas;
} Grafo;

#pragma endregion

#pragma region grafos
/**
 * @brief Inicializa a estrutura do grafo de antenas a partir de um ficheiro.
 *
 *
  */

void inicializarGrafo(Grafo* g) {
    g->listaAntenas = NULL;
}

#pragma endregion

#pragma region operações antenas

/**
 * @brief Cria uma nova antena com a frequência, latitude e longitude especificadas.
 *
 * Esta função aloca memória para uma nova estrutura Antena, inicializa os seus campos
 * com os valores fornecidos e define os apontadores 'seguinte' e 'ligacoes' como NULL.
 *
 * @param freq  Caractere representando a frequência da antena.
 * @param lat   Latitude da antena.
 * @param lon   Longitude da antena (apontador).
 * @return      Apontador para a nova estrutura Antena criada.
 */
Antena* criarAntena(char freq, int lat, int lon) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    nova->frequencia = freq;
    nova->latitude = lat;
    nova->longitude = lon;
    nova->seguinte = NULL;
    nova->ligacoes = NULL;
    return nova;
}

/**
 * @brief Adiciona uma antena ao grafo.
 *
 * Esta função insere uma nova antena na lista ligada de antenas do grafo.
 * A antena é inserida no início da lista.
 *
 * @param g Apontador para o grafo onde a antena será adicionada.
 * @param a Apontador para a antena a ser adicionada.
 * @return true se a antena foi adicionada com sucesso, false caso contrário.
 */
bool adicionarAntena(Grafo* g, Antena* a) {
    if (!a) return false;
    a->seguinte = g->listaAntenas;
    g->listaAntenas = a;
    return true;
    // TODO:
    // falta aqui adicionar o resultado >> passar um int e retornar Antena*
}


/**
 * @brief Adiciona uma ligação entre duas antenas no grafo.
 *
 * Esta função cria uma ligação  entre duas antenas especificadas
 * pelas suas frequências. A ligação inclui a distância entre as antenas.
 *
 * @param g Apontador para o grafo onde as antenas estão localizadas.
 * @param freqOrigem Frequência da antena de origem.
 * @param freqDestino Frequência da antena de destino.
 * @param distancia Distância entre as antenas.
 * @return true se a ligação foi adicionada com sucesso, false caso contrário.
 */
Ligacao* adicionarLigacao(Grafo* g, char freqOrigem, char freqDestino, float distancia) {
    Antena* origem = procurarAntena(g, freqOrigem);
    Antena* destino = procurarAntena(g, freqDestino);
    // verifica se origem ou destino são nulos
    if (!origem || !destino) return false;

    // verificar que frequencia origem/destino são as mesmas
    if (origem->frequencia == destino->frequencia){

    Ligacao* novaLig = (Ligacao*)malloc(sizeof(Ligacao));
    novaLig->destino = destino;
    novaLig->distancia = distancia;
    novaLig->seguinte = origem->ligacoes;
    origem->ligacoes = novaLig;

    // ligação inversa
    Ligacao* ligInv = (Ligacao*)malloc(sizeof(Ligacao));
    ligInv->destino = origem;
    ligInv->distancia = distancia;
    ligInv->seguinte = destino->ligacoes;
    destino->ligacoes = ligInv;
    }

    return true;
}

#pragma endregion

#pragma region exibir dados

/**
 * @brief Mostra o grafo de antenas.
 *
 * Esta função percorre a lista ligada de antenas no grafo e imprime as informações
 * de cada antena, incluindo as suas ligações e distâncias.
 *
 * @param g Apontador para o grafo a ser mostrado.
 */
void mostrarGrafo(const Grafo* g) {
    Antena* a = g->listaAntenas;
    while (a) {
        printf("Antena: Frequência = %c , Latitude = %.4d, Longitude = %.4d\n",
               a->frequencia, a->latitude, a->longitude);
        Ligacao* l = a->ligacoes;
        while (l) {
            printf("  -> Ligada à antena com frequência %c  (Distância = %.2f km)\n",
                   l->destino->frequencia, l->distancia);
            l = l->seguinte;
        }
        a = a->seguinte;
    }
}

#pragma endregion

// NOTA: Função Não implementada
// bool guardarGrafoBinario(const Grafo* g, const char* nomeFicheiro) {
//     FILE* fp = fopen(nomeFicheiro, "wb");
//     if (!fp) {
//         perror("Erro ao abrir o ficheiro");
//         return false;
//     }
//         //TODO: falta implementar
//             }
        
//             fclose(fp);
//             return true;
//         }
