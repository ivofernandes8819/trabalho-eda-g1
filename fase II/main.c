/*!
 *  @file main.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-05-18
 *  @project Trabalho pratico EDA - Grupo II
 */
#include <stdio.h>
#include "grafo_antenas.h"
#include "grafo_antenas.c"

int main() {
    Grafo redeAntenas;
    inicializarGrafo(&redeAntenas);

    // Adicionar antenas usando frequências como identificador
    CriaVertice(&redeAntenas, 'A', 40, 8, "Antena A");
    CriaVertice(&redeAntenas, 'B', 41, 8, "Antena B");
    CriaVertice(&redeAntenas, 'C', 42, 9, "Antena C");

    // Adicionar ligações entre antenas com base na frequência
    CriaAdjacencia(&redeAntenas, 'A');
    CriaAdjacencia(&redeAntenas, 'B');
    CriaAdjacencia(&redeAntenas, 'C');
    CriaAdjacencia(&redeAntenas, 'A');

    // Mostrar o grafo
    mostrarGrafo(&redeAntenas);

    // Guardar num ficheiro binário -- NAO IMPLEMENTADO
    carregaGrafoficheiro("rede_antenas.txt", &redeAntenas);

    // Gravar o grafo em formato binário
    GravaBinário("rede_antenas.bin", &redeAntenas);
    return 0;

    // Procurar grafos em profundidade
    int resultado;
    Vertice* encontrado = ProcuraProfundidade(redeAntenas.listaAntenas, 41, 8, &resultado);
    if (resultado) {
        printf("Antena encontrada: Frequência = %c, Latitude = %d, Longitude = %d\n",
               encontrado->freqAntena, encontrado->x, encontrado->y);
    } else {
        printf("Antena não encontrada.\n");
    }
}
