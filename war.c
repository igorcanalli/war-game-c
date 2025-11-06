#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ---------- DECLARAÇÕES DE FUNÇÕES ----------
void cadastrarTerritorios(Territorio *mapa, int qtd);
void listarTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho, char *corJogador);
void liberarMemoria(Territorio *mapa, char *missao1, char *missao2);

// ---------- FUNÇÕES DE JOGO ----------

// Cadastra territórios dinamicamente
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

// Lista os territórios
void listarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Lista de Territórios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque (simula rolagem de dados)
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

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");

        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
        atacante->tropas -= tropasTransferidas;

        printf("O território %s foi conquistado!\n", defensor->nome);
    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }

    printf("\n--- Resultado Após o Ataque ---\n");
    printf("%s (%s): %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%s (%s): %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
}

// ---------- SISTEMA DE MISSÕES ----------

// Atribui missão aleatória ao jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Verifica se a missão foi cumprida (simples para demonstração)
int verificarMissao(char *missao, Territorio *mapa, int tamanho, char *corJogador) {
    // Missão 1: Conquistar 3 territórios
    if (strstr(missao, "3 territórios")) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                count++;
        }
        return count >= 3;
    }

    // Missão 2: Eliminar a cor vermelha
    if (strstr(missao, "vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0)
                return 0;
        }
        return 1;
    }

    // Missão 3: Conquistar 2 territórios seguidos
    if (strstr(missao, "2 territórios seguidos")) {
        for (int i = 0; i < tamanho - 1; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                strcmp(mapa[i + 1].cor, corJogador) == 0)
                return 1;
        }
    }

    // Missão 4: Ter mais de 10 tropas em um território
    if (strstr(missao, "10 tropas")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10)
                return 1;
        }
    }

    // Missão 5: Conquistar qualquer território azul
    if (strstr(missao, "território azul")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                strstr(mapa[i].nome, "Azul"))
                return 1;
        }
    }

    return 0;
}

// Libera toda a memória alocada
void liberarMemoria(Territorio *mapa, char *missao1, char *missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\nMemória liberada com sucesso.\n");
}

// ---------- FUNÇÃO PRINCIPAL ----------

int main() {
    srand(time(NULL));

    int qtdTerritorios;
    int opcao;
    Territorio *mapa = NULL;

    printf("Informe o número de territórios a serem cadastrados: ");
    scanf("%d", &qtdTerritorios);

    mapa = (Territorio *)calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtdTerritorios);

    // Missões pré-definidas
    char *missoes[] = {
        "Conquistar 3 territórios.",
        "Eliminar todas as tropas da cor vermelha.",
        "Conquistar 2 territórios seguidos.",
        "Ter mais de 10 tropas em um território.",
        "Conquistar qualquer território azul."
    };
    int totalMissoes = 5;

    // Aloca missão dinamicamente para dois jogadores
    char *missaoJogador1 = (char *)malloc(100 * sizeof(char));
    char *missaoJogador2 = (char *)malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n--- Missões Sorteadas ---\n");
    printf("Jogador 1: %s\n", missaoJogador1);
    printf("Jogador 2: %s\n", missaoJogador2);

    // Loop principal
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

                    // Após o ataque, verifica se algum jogador venceu
                    if (verificarMissao(missaoJogador1, mapa, qtdTerritorios, "azul")) {
                        printf("\n🎉 Jogador 1 (azul) venceu! Missão cumprida: %s\n", missaoJogador1);
                        opcao = 0;
                    } else if (verificarMissao(missaoJogador2, mapa, qtdTerritorios, "vermelha")) {
                        printf("\n🎉 Jogador 2 (vermelha) venceu! Missão cumprida: %s\n", missaoJogador2);
                        opcao = 0;
                    }
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

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    return 0;
}
