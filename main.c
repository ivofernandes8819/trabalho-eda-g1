/*!
 *  @file Main.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-03-30
 *  @project Trabalho pratico EDA - Grupo I
 */

#include "antenas.h"
#include "antenas.c"
#include <stdio.h>

int main() {

    # pragma region CRIAR_LISTA
    
    // CRIA LISTA LIGADA ANTENA
    ListaLigadaAntenas* lista = criarLista();
    // ** CARREGA FICHEIRO
    carregarFicheiro(lista, "/Users/ivofernandes/Documents/PERSONAL/LESI/PROJECTS/a8819/antenas.txt");

    #pragma endregion

    #pragma region INSERIR_ANTENAS

    // ** INSERIR ANTENAS
/*  inserirAntena(lista, 'A', 4, 5);
    inserirAntena(lista, 'Z', 4, 7); 
    inserirAntena(lista, 'B', 6, 7); 
    inserirAntena(lista, 'C', 5, 9); */

    #pragma endregion

    #pragma region LISTAR_ANTENAS

    // ** LISTAR ANTENAS **
    listarAntenas(lista); // verifica ficheiro é bem carregado após inserir

    #pragma endregion

    #pragma region REMOVER_ANTENAS

    // ** REMOVER ANTENAS **
    removerAntena(lista, 0, 4 ); // paarametros: coordenadas a remover
    listarAntenas(lista); // verificar que a antena foi removida 

    #pragma endregion

    #pragma region NEFASTO
    
    // ** EFEITO NEFASTO **
    //detectarEfeitoNefasto(lista);

    #pragma endregion

    #pragma region GRAVAR_FICHEIRO
    // ** GRAVAR DADOS FICHEIRO **
    //gravarDadosFicheiro("/Users/ivofernandes/Documents/PERSONAL/LESI/PROJECTS/a8819/antenas_out.txt", lista);
    #pragma endregion
    
    return 0;
}