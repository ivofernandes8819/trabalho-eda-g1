/*!
 *  @file antenas.c
 *  @author Ivo Fernandes | 8819
 *  @date 2025-03-30
 *  @project Trabalho pratico EDA - Grupo I
 */

//#include "antenas.h"
#include "dados.h"
#include <stdbool.h>
#include <string.h>

/**
 * @brief Cria e inicializa uma nova lista ligada para armazenar antenas.
 * 
 * Esta função aloca memória para uma nova estrutura de lista ligada e 
 * inicializa o seu apontador head para NULL, indicando que a lista está vazia.
 * 
 * @return Um apontador para a nova lista ligada de antenas criada.
 */
ListaLigadaAntenas* criarLista() {
    ListaLigadaAntenas* lista = (ListaLigadaAntenas*)malloc(sizeof(ListaLigadaAntenas));
    lista->head = NULL;
    return lista;
}

/**
 * @brief insere uma nova antena em uma lista ligada de antenas.
 * 1. Aloca dinamicamente memória para uma nova antena usando `malloc`.
 * 2. Inicializa os campos da nova antena (`frequencia`, `x`, `y`) com os valores fornecidos como parâmetros.
 * 3. Faz o apontador `next` da nova antena apontar para o atual primeiro elemento da lista (ou seja, o antigo `head`).
 * 4. Atualiza o apontador `head` da lista para que ele aponte para a nova antena, tornando-a o novo primeiro elemento da lista. 
 * @param lista Apontador para a lista ligada de antenas.
 * @param frequencia Caractere representando a frequência da antena.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.*/

void inserirAntena(ListaLigadaAntenas* lista, char frequencia, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->next = lista->head;
    lista->head = nova;
}

/**
 * @brief Remove uma antena específica da lista ligada.
 * 
 * Esta função percorre a lista ligada de antenas e remove a antena que
 * corresponde aos parâmetros fornecidos (frequência, coordenada x e coordenada y).
 * 
 * @param lista Apontador para a lista ligada de antenas.
 * @param frequencia Caractere representando a frequência da antena a ser removida.
 * @param x Coordenada x da antena a ser removida.
 * @param y Coordenada y da antena a ser removida.
 * 
 * @note Se a antena não for encontrada, a lista permanece inalterada.
 */
void removerAntena(ListaLigadaAntenas* lista, int x, int y) {
    Antena* atual = lista->head, *anterior = NULL;
    while (atual) {
        if (atual->x == x && atual->y == y) {
            if (anterior) anterior->next = atual->next;
            else lista->head = atual->next;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
}

/**
 * @brief Lista antenas com base nas coordenadas do caractere no ficheiro.
 *
 * Esta função percorre um ficheiro contendo informações sobre antenas
 * @return Uma lista de antenas listadas pelo antenas.txt. + as inseridas pela função inserir
 *  TODO: não bate certo com a inserção na lista!
 */

void listarAntenas(ListaLigadaAntenas* lista) {
    Antena* atual = lista->head;
    printf("Lista de Antenas:\n");
    while (atual) {
        printf("Frequência: %c, Coordenadas: (%d, %d)\n", atual->frequencia, atual->x, atual->y);
        atual = atual->next;
    }
    printf("Fim da lista.\n");
}

/**
 * @brief Função que carrega items existentes no ficheiro.
 * A posição do caractere no ficheiro representa as suas coordenadas.
 *@note: aprimorar validações do ficheiro: vazio, formato fora do esperado.
 */
void carregarFicheiro(ListaLigadaAntenas* lista, const char* nomeFicheiro) {
    FILE* file = fopen(nomeFicheiro, "r");
    if (!file) return;
    
    char linha[256];
    int y = 0;
    while (fgets(linha, sizeof(linha), file)) {
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) {
            if ((linha[x] >= 'A' && linha[x] <= 'Z') || (linha[x] >= 'a' && linha[x] <= 'z') || linha[x] == '0') {
                inserirAntena(lista, linha[x], x, y);
            }
        }
        y++;
    }
    fclose(file);
}

/**
 * @brief Detecta o efeito nefasto causado por antenas com a mesma frequência
 *        localizadas na mesma linha (coordenada x).
 * 
 * Esta função percorre uma lista ligada de antenas e verifica se existem
 * múltiplas antenas com a mesma frequência e coordenada x.
 * 
 * @param lista apontador para a lista ligada de antenas (ListaLigadaAntenas).
 * 
 * @note Assumiu-se qie O efeito nefasto ocorre quando mais do que uma antena opera na mesma
 *       frequência e está localizada na mesma linha (coordenada x).
 */
void detectarEfeitoNefasto(ListaLigadaAntenas* lista) {
    Antena* a1 = lista->head;
    while (a1) {
        Antena* a2 = lista->head; // começa pela head
        int count = 0;
        while (a2) {
            if (a1->frequencia == a2->frequencia && a1->x == a2->x) {
                count++;
                if (count > 1) { // mais do que uma antena com a mesma coordenada X
                    printf("Efeito nefasto detectado:\n");
                    printf("Antena com Frequência: %c, Linha %d, Coordenadas: (%d, %d)\n", a1->frequencia,a1->x, a1->x, a1->y);
                    break;
                }
            }
            a2 = a2->next;
        }
        a1 = a1->next;
    }
}

/**
 * @brief grava dados no ficheiro binário
 * 
 * @note detetado que não funciona corretamente. TODO: fazer correção na próxima entrega
 */
bool gravarDadosFicheiro(const char* nomeFicheiro, ListaLigadaAntenas* lista) {
        if (lista == NULL || lista->head == NULL) return false;

        FILE* file = fopen(nomeFicheiro, "wb");
        if (!file) return false;

        Antena* atual = lista->head;
        while (atual) {
            fprintf(file, " %s \n", atual->frequencia);
            atual = atual->next;
        }

        fclose(file);
        return true;
}