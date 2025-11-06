#include <stdio.h>
#include <string.h>

// definindo constante para limitar tamanho do array
#define MAX_TERRITORIOS 4

// Definindo struct do Território
struct Territorio {
    char nome[50];
    char cor[30];
    int qtdTropas;
};

int main() {
    struct Territorio territorios[MAX_TERRITORIOS]; // definindo array do tamanho do tipo Territorio da constante MAX_TERRITORIOS 
    int opcao; // salva opção selecionada pelo usuario
    int contador = 0; // salva quantos territórios já foram cadastrados

    // declara laço do-while, para repetir solicitações de entrada para o usuario
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Cadastrar territorio\n");
        printf("2 - Listar territorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // escolha cadastrar territorio
                if (contador < MAX_TERRITORIOS) {
                    printf("\n--- Cadastro do Territorio %d ---\n", contador + 1);

                    printf("Nome: ");
                    scanf(" %[^\n]", territorios[contador].nome);

                    printf("Cor: ");
                    scanf(" %[^\n]", territorios[contador].cor);

                    printf("Quantidade de Tropas: ");
                    scanf("%d", &territorios[contador].qtdTropas);

                    contador++;
                    printf("Territorio cadastrado com sucesso!\n");
                } else {
                    printf("Limite de %d territorios atingido!\n", MAX_TERRITORIOS);
                }
                break;

            case 2: // escolha visualizar territorios cadastrados
                if (contador == 0) {
                    printf("\nNenhum territorio cadastrado ainda.\n");
                } else {
                    printf("\n=== Lista de Territorios Cadastrados ===\n");
                    for (int i = 0; i < contador; i++) {
                        printf("\nTerritorio %d:\n", i + 1);
                        printf("Nome: %s\n", territorios[i].nome);
                        printf("Cor: %s\n", territorios[i].cor);
                        printf("Quantidade de Tropas: %d\n", territorios[i].qtdTropas);
                    }
                }
                break;

            case 0: // escolha sair
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}