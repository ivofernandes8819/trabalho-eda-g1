/*!
 *  @file grafo_antenas.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-05-18
 *  @project Trabalho pratico EDA - Grupo II
 */
#include <stdio.h>
#include <stdlib.h>
#include "grafo_antenas.h"

// Define the structure Vertice
typedef struct Vertice {
    int x;
    int y;
    char freqAntena;
    bool visitado;
    struct AdjD* listaAdjacencias;
    struct Vertice* prox;
} Vertice;

// Define the structure AdjD
typedef struct AdjD {
    struct Vertice* destino;
    struct AdjD* prox;
} AdjD;

#pragma region Estruturas

typedef struct GraphD {
    struct Vertice* vertices; // Lista de vértices
    int numVertices;          // Número de vértices no grafo
} GraphD;

typedef struct Ligacao {
    struct Antena* destino;
    struct Ligacao* seguinte;
} Ligacao;

typedef struct Antena {
    char frequencia;
    int latitude;
    int longitude;
    int aux; // Variável auxiliar para indicar sucesso na alocação
    bool visitado; // Indica se a antena foi visitada
    struct Antena* seguinte;
    struct Ligacao* ligacoes;
} Antena;

typedef struct Grafo {
    Antena* listaAntenas;
} Grafo;

#pragma endregion

#pragma region grafos
/**
 * @brief Inicializa a estrutura do grafo de antenas
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
 * @param x   Latitude da antena.
 * @param y   Longitude da antena (apontador).
 * @return      Apontador para a nova estrutura Antena criada.
 */
    Antena* CriaVertice(char freq, int x, int y, bool visitado, int *aux) {
        Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
        *aux = 0;
        if (novaAntena != NULL) {
        novaAntena->frequencia = freq;
        novaAntena->latitude = x;
        novaAntena->longitude = y;
        novaAntena->visitado = false;
        novaAntena->seguinte = NULL;
        novaAntena->ligacoes = NULL;
        *aux =1; // indica que a alocação foi bem-sucedida
        } return novaAntena;
    }

// Função para criar uma Adjacência

    AdjD* CriaAdjacencia(Vertice* destino, int *aux) {
        AdjD* novaAdj = (AdjD*) malloc(sizeof(AdjD));
        *aux = 0;
        if (novaAdj != NULL) {
            novaAdj->destino = destino;
            novaAdj->prox = NULL;
            *aux = 1;
            return novaAdj;
        }
    }

    Vertice* InsereVertice(Vertice* novo, Vertice* inicio, int *res) {
        *res = 0;
        if (inicio == NULL ) {
            *res = 1;
            return novo;  // novo torna-se o inicio da lista se a lista estiver vazia
        }
        if (novo->x < inicio->x || (novo->x == inicio->x && novo->y < inicio->y)) {
            novo->prox = inicio;
            *res = 1;
            return novo; // inserir no inicio da lista
        }else{
            Vertice *antes = inicio;
            Vertice *depois = inicio;
        while (depois != NULL &&
                (depois->x < novo->x || (depois->x == novo->x && depois->y < novo->y))) {
                antes = depois;
                depois = depois->prox;
        }
            novo->prox = depois;
            antes->prox = novo;
            *res = 1;
            return inicio; // insere de forma ordenada
            }
    }

    Vertice* RemoveVertice(Vertice* inicio, int x, int y, int *aux){
        *aux = 0;
        Vertice* atual = inicio;
        Vertice* anterior = NULL;

        // Procura o vértice pretendido
        while (atual != NULL && !(atual->x == x && atual->y == y)) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual == NULL) {
            return inicio; // Vértice não encontrado
        }

        if (anterior == NULL) {
            inicio = atual->prox;  // Caso seja o primeiro vértice
        } else {
            anterior->prox = atual->prox;
        }

        // Reset visitado flag before freeing memory
        atual->visitado = false;

        // Ensure proper validation before freeing memory
        if (atual != NULL) {
            free(atual);
        }

        *aux = 1;
        return inicio;
    }

    // Procura  vértices em profundidade
    // IMplementado com base nos ficheiros das aulas
    Vertice* ProcuraProfundidade(Vertice* atual, int x, int y, int *res) {
        *res = 0;
        // Se o vértice atual for nulo ou já tiver sido visitado, retorna NULL
        if (atual == NULL || atual->visitado)
            return *res;
        // Marca o vértice atual como visitado
        atual->visitado = true;

        // Se encontrou o vértice nas coordenadas desejadas
        if (atual->x == x && atual->y == y)
            *res = 1;
            return res;
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
                printf("  -> Ligada à antena com frequência %c \n",
                    l->destino->frequencia);
                l = l->seguinte;
            }
            a = a->seguinte;
        }
    }

#pragma endregion

#pragma region Dados e Ficheiros

// **** implementado com a ajuda de AI ****
    GraphD* carregaGrafoficheiro(int argc, char* argv[]) {
        if (argc < 2) {
            printf("Erro: Caminho para o ficheiro não fornecido.\n");
            return NULL;
        }

        const char* filePath = argv[1];
        FILE* file = fopen(filePath, "r");
        if (file == NULL) {
            printf("Erro ao abrir o ficheiro %s\n", filePath);
            return NULL;
        }

        GraphD* graph = (GraphD*)malloc(sizeof(GraphD));
        if (graph == NULL) {
            printf("Erro ao alocar memória para o grafo\n");
            fclose(file);
            return NULL;
        }

        graph->vertices = NULL; // Inicializa a lista de vértices
        graph->numVertices = 0;

        int lat, lon, y;
        char freqAntena;

        while (fscanf(file, "%d %d %s %c", &lat, &lon, &freqAntena) == 4) {
            int aux;
            Vertice* novoVertice = CriaVertice(lat, lon, freqAntena, false, &aux);
            if (aux) {
                graph->vertices = InsereVertice(novoVertice, graph->vertices, &aux);
                graph->numVertices++;
            }
        }

        fclose(file);
        return graph;
    }

// **** Convertido do exemplo da aula + AI ****
    bool GravaBinário(char* fileName, GraphD* g) {
        FILE* file = fopen(fileName, "wb");
        if (!file) {
            return false;  // Erro ao abrir ficheiro
        }

        // Gravar vértices e adjacências
        Vertice* verticeAtual = g->vertices;
        while (verticeAtual) {
            // Gravar dados do vértice
            fwrite(&verticeAtual->x, sizeof(int), 1, file);
            fwrite(&verticeAtual->y, sizeof(int), 1, file);
            fwrite(&verticeAtual->freqAntena, sizeof(char), 1, file);

            // Gravar lista de adjacências para este vértice
            AdjD* currentAdj = verticeAtual->listaAdjacencias;
            while (currentAdj) {
                fwrite(&currentAdj->destino->x, sizeof(int), 1, file);
                fwrite(&currentAdj->destino->y, sizeof(int), 1, file);
                currentAdj = currentAdj->prox;
            }

            // Marcar fim de adjacências deste vértice
            int endMarker = -1;
            fwrite(&endMarker, sizeof(int), 1, file);

            // Próximo vértice
            verticeAtual = verticeAtual->prox;
        }

        fclose(file);
        return true;  // Sucesso
    }

#pragma endregion