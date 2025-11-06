#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para listar territórios
void listarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Lista de Territórios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n%s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("Erro: o território atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    // Simulação de dados de ataque e defesa (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");

        // Metade das tropas do atacante são transferidas
        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor); // muda o controle do território
        atacante->tropas -= tropasTransferidas;

        printf("O território %s foi conquistado!\n", defensor->nome);
    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; // atacante perde uma tropa
    }

    // Exibir o resultado atualizado
    printf("\n--- Resultado Após o Ataque ---\n");
    printf("%s (%s): %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%s (%s): %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}

// Função principal
int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int qtdTerritorios;
    int opcao;
    Territorio *mapa = NULL;

    printf("Informe o número de territórios a serem cadastrados: ");
    scanf("%d", &qtdTerritorios);

    // Alocação dinâmica de memória
    mapa = (Territorio *)calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtdTerritorios);

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Listar territórios\n");
        printf("2 - Atacar território\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarTerritorios(mapa, qtdTerritorios);
                break;

            case 2: {
                int idxAtacante, idxDefensor;

                listarTerritorios(mapa, qtdTerritorios);

                printf("\nEscolha o número do território atacante: ");
                scanf("%d", &idxAtacante);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &idxDefensor);

                if (idxAtacante < 1 || idxAtacante > qtdTerritorios ||
                    idxDefensor < 1 || idxDefensor > qtdTerritorios ||
                    idxAtacante == idxDefensor) {
                    printf("Escolha inválida!\n");
                } else {
                    atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
                }
                break;
            }

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
