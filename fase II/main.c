/*!
 *  @file main.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-05-18
 *  @project Trabalho pratico EDA - Grupo II
 */
#include <stdio.h>
#include "grafo_antenas.h"

int main() {
    Grafo redeAntenas;
    inicializarGrafo(&redeAntenas);

    // Adicionar antenas usando frequências como identificador
    adicionarAntena(&redeAntenas, criarAntena('A', 40.123, -8.456));
    adicionarAntena(&redeAntenas, criarAntena('B', 40.124, -8.457));
    adicionarAntena(&redeAntenas, criarAntena('C', 40.125, -8.458));

    // Adicionar ligações entre antenas com base na frequência
    adicionarLigacao(&redeAntenas, 'A', 'B', 2);
    adicionarLigacao(&redeAntenas, 'B', 'C', 3);
    adicionarLigacao(&redeAntenas, 'A', 'C', 1);

    // Mostrar o grafo
    mostrarGrafo(&redeAntenas);

    // Guardar num ficheiro binário -- NAO IMPLEMENTADO

    return 0;
}
