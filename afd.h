#ifndef AFD_H_
#define AFD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct automato {
    char alfabeto[MAX];
    char estados[MAX];
    char finais[MAX];
    char transicoes[MAX][MAX];
} AFD;

// funcao usada para assegurar que a matriz de transicoes nao contenha lixo.
// pre-condicao: ponteiro para automato
// pos-condicao: matriz de transicoes preenchida com '-'
void preenche_matriz(AFD* afd);

// funcao usada para obter o indice de um estado a partir do nome
// pre-condicao: vetor de estados e o estado desejado
// pos-condicao: retorna o indice do estado no vetor, ou -1 se nao encontrado
int indice_estado(char* estados, char estado);

// com o arquivo aberto, carrega as informacoes do automato para a memoria
// pre-condicao: ponteiro para arquivo, ponteiro para automato
// pos-condicao: automato lido com alfabeto, estados, finais e transicoes
void ler_afd(FILE* f, AFD* afd);

// funcao usada para validar uma palavra a partir de um automato
// pre-condicao: automato, palavra a ser validada
// pos-condicao: 1 se aceita, 0 se rejeita
int valida_palavra(AFD afd, char* palavra);

// funcao usada para converter indice numerico de estado para letra
// pre-condicao: indice numerico (0 = S, 1 = A, ...)
// pos-condicao: letra correspondente ao estad
char estado_para_letra(int i);

// funcao que imprime a gramatica regular equivalente ao AFD
// pre-condicao: automato
// pos-condicao: gramatica regular formatada com producoes
void printar_gramatica(AFD afd);

#endif