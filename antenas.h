/*!
 *  @file antenas.h
 *  @author Ivo Fernandes | 8819
 *  @date 2025-03-30
 *  @project Trabalho pratico EDA - Grupo I
 */
#pragma once

 #include "dados.h"
 
 ListaLigadaAntenas* criarLista();
 void inserirAntena(ListaLigadaAntenas* lista, char frequencia, int x, int y);
 void removerAntena(ListaLigadaAntenas* lista, int x, int y);
 void listarAntenas(ListaLigadaAntenas* lista);
 void carregarFicheiro(ListaLigadaAntenas* lista, const char* nomeFicheiro);
 void detectarEfeitoNefasto(ListaLigadaAntenas* lista);
 bool gravarDadosFicheiro(const char* nomeFicheiro, ListaLigadaAntenas* lista);