#include "afd.h"
#include <string.h>

int main() {
    char nome_arquivo[MAX], palavra[MAX];
    AFD afd;
    FILE* f;
    int opcao, subopcao;

    while (1) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Inserir automato\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Entre com o nome do arquivo com o automato(sem o .txt): ");
                scanf("%s", nome_arquivo);
                strcat(nome_arquivo, ".txt");

                f = fopen(nome_arquivo, "r");
                if (f == NULL) {
                    printf("Arquivo nao encontrado\n");
                    break;
                }

                printf("Arquivo aberto com sucesso\n");

                ler_afd(f, &afd);
                fclose(f);
                printar_gramatica(afd);

                while (1) {
                    printf("\n--- SUBMENU AFD ---\n");
                    printf("1. Testar palavra\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &subopcao);

                    if (subopcao == 0)
                        break;

                    if (subopcao == 1) {
                        printf("Digite a palavra para validar: ");
                        scanf("%s", palavra);

                        if (valida_palavra(afd, palavra))
                            printf("ACEITA.\n");
                        else
                            printf("REJEITA\n");
                    } else {
                        printf("Opcao invalida.\n");
                    }
                }
                break;

            case 0:
                printf("Encerrando o programa...\n");
                return 0;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
