/*!
 *  @file Main.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-03-30
 *  @project Trabalho pratico EDA - Grupo I
 */

 #pragma once

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 
/*!
 *  Gere Elemento da lista Antenas
 */

 typedef struct Antena {
     char frequencia;
     int x, y;
     struct Antena* next;
 } Antena;
 

 /*!
 *  Gere a lista de elementos
 */
 typedef struct {
    Antena* head;
 } ListaLigadaAntenas;

 typedef struct AntenasFile {
    char frequencia;
    int x, y;
}AntenasFile;
 
 ListaLigadaAntenas* criarLista();
 void inserirAntena(ListaLigadaAntenas* lista, char frequencia, int x, int y);
 void removerAntena(ListaLigadaAntenas* lista, int x, int y);
 void listarAntenas(ListaLigadaAntenas* lista);
 void carregarFicheiro(ListaLigadaAntenas* lista, const char* nomeFicheiro);
 void detectarEfeitoNefasto(ListaLigadaAntenas* lista);
 bool gravarDadosFicheiro(const char* nomeFicheiro, ListaLigadaAntenas* lista);