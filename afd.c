#include "afd.h"

// funcao usada para assegurar que a matriz de transicoes nao contenha lixo.
// pre-condicao: ponteiro para automato
// pos-condicao: matriz de transicoes preenchida com '-'
void preenche_matriz(AFD* afd) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            afd->transicoes[i][j] = '-';
}

// funcao usada para obter o indice de um estado a partir do nome
// pre-condicao: vetor de estados e o estado desejado
// pos-condicao: retorna o indice do estado no vetor, ou -1 se nao encontrado
int indice_estado(char* estados, char estado) {
    for (int i = 0; i < strlen(estados); i++) {
        if (estados[i] == estado) return i;
    }
    return -1;
}

// com o arquivo aberto, carrega as informacoes do automato para a memoria
// pre-condicao: ponteiro para arquivo, ponteiro para automato
// pos-condicao: automato lido com alfabeto, estados, finais e transicoes
void ler_afd(FILE* f, AFD* afd) {
    char linha[MAX];
    char estado1[10], estado2[10];
    char caracter;
    int origem, destino;

    // Lê o alfabeto
    fscanf(f, "alfabeto={");
    int i = 0;
    while (1) {
        fscanf(f, "%c", &caracter);
        if (caracter == '}') break;
        if (caracter != ',' && caracter != '\n') {
            afd->alfabeto[i++] = caracter;
        }
    }
    afd->alfabeto[i] = '\0';

    // Lê os estados
    fscanf(f, "\nestados={");
    i = 0;
    while (1) {
        fscanf(f, "%c", &caracter);
        if (caracter == '}') break;
        if (caracter != ',' && caracter != '\n' && caracter != 'q') {
            afd->estados[i++] = caracter;
        }
    }
    afd->estados[i] = '\0';

    // Lê os finais
    fscanf(f, "\nfinais={");
    i = 0;
    while (1) {
        fscanf(f, "%c", &caracter);
        if (caracter == '}') break;
        if (caracter != ',' && caracter != '\n' && caracter != 'q') {
            afd->finais[i++] = caracter;
        }
    }
    afd->finais[i] = '\0';

    // Preenche a matriz de transições
    preenche_matriz(afd);

    // Lê as transições
    while (fscanf(f, "\n(%[^,],%c)= q%[^\n]", estado1, &caracter, estado2) == 3) {
        origem = estado1[1] - '0';   // q0 -> 0
        destino = estado2[0] - '0';  // q1 -> 1
        afd->transicoes[origem][destino] = caracter;
    }
}

// funcao usada para validar uma palavra a partir de um automato
// pre-condicao: automato, palavra a ser validada
// pos-condicao: 1 se aceita, 0 se rejeita
int valida_palavra(AFD afd, char* palavra) {
    int atual = 0;
    int i, j, k;
    char caracter, final;

    for (i = 0; i <= strlen(palavra); i++) {
        caracter = palavra[i];
        printf("[q%d] %s\n", atual, &palavra[i]);

        if (caracter == '\0') {
            final = atual + '0';
            for (k = 0; k < strlen(afd.finais); k++) {
                if (afd.finais[k] == final)
                    return 1;
            }
            return 0;
        }

        for (j = 0; j < strlen(afd.estados); j++) {
            if (afd.transicoes[atual][j] == caracter) {
                atual = j;
                break;
            }
        }

        if (j == strlen(afd.estados)) {
            for (k = 0; k < strlen(afd.estados); k++) {
                if (afd.transicoes[atual][k] == '@') {
                    atual = k;
                    i--;
                    break;
                }
            }
            if (k == strlen(afd.estados)) return 0;
        }
    }
    return 0;
}

// funcao usada para converter indice numerico de estado para letra
// pre-condicao: indice numerico (0 = S, 1 = A, ...)
// pos-condicao: letra correspondente ao estad
char estado_para_letra(int i) {
    return (i == 0) ? 'S' : ('A' + (i - 1));
}

// funcao que imprime a gramatica regular equivalente ao AFD
// pre-condicao: automato
// pos-condicao: gramatica regular formatada com producoes
void printar_gramatica(AFD afd) {
    printf("\nGramatica Regular:\n");

    int n_estados = strlen(afd.estados);

    for (int i = 0; i < n_estados; i++) {
        char estadoOrigem = estado_para_letra(i);
        int primeira = 1;
        printf("%c ->", estadoOrigem);

        for (int j = 0; j < n_estados; j++) {
            char simbolo = afd.transicoes[i][j];

            if (simbolo != '-') {
                if (!primeira)
                    printf(" |");

                char estadoDestino = estado_para_letra(j);

                if (simbolo == '@') {
                    printf(" %c", estadoDestino);
                } else {
                    // Verifica se destino é final
                    int ehFinal = 0;
                    for (int k = 0; k < strlen(afd.finais); k++) {
                        if (afd.finais[k] == afd.estados[j])
                            ehFinal = 1;
                    }

                    if (ehFinal)
                        printf(" %c%c | %c", simbolo, estadoDestino, simbolo);
                    else
                        printf(" %c%c", simbolo, estadoDestino);
                }

                primeira = 0;
            }
        }

        // Produção para palavra vazia se o estado for final
        for (int k = 0; k < strlen(afd.finais); k++) {
            if (afd.finais[k] == afd.estados[i]) {
                if (!primeira) printf(" |");
                printf(" @");
                break;
            }
        }

        printf("\n");
    }
}