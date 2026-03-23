#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor_do_exercito[10];
    int numero_de_tropas;
};

struct Jogador {
    char nome[50];
    char cor[10];
    char* missao;
    int conquistas;
};

void liberarMemoria(struct Territorio* vetor) {
    if (vetor != NULL) {
        free(vetor);
        printf("\nMemória liberada\n");
    };
};

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dado_defensor;
    int dado_atacante;

    dado_defensor = (rand() % 6) + 1;
    dado_atacante = (rand() % 6) + 1;

    if (dado_defensor >= dado_atacante) {
        printf("Exército defensor ganhou!");
        atacante->numero_de_tropas--;
    }
    else {
        printf("Exército atacante ganhou!");
        defensor->numero_de_tropas--;

        if (defensor->numero_de_tropas <= 0) {
            printf("O território %s foi conquistado pelo exército %s \n", defensor->nome, atacante->cor_do_exercito);

            strcpy(defensor->cor_do_exercito, atacante->cor_do_exercito);

            int tropas_atacantes = atacante->numero_de_tropas / 2;

            defensor->numero_de_tropas = tropas_atacantes;
            atacante->numero_de_tropas -= tropas_atacantes;

            printf("O território %s foi ocupado pelo exército %s com %d tropas.\n", defensor->nome, defensor->cor_do_exercito, tropas_atacantes);
        }
    }
}

void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
};

int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* cor_jogador) {
    int contagem = 0;

    // Percorre o "mapa" (seu vetor de territórios)
    for (int i = 0; i < tamanho; i++) {
        // Se o território pertence ao jogador (mesma cor)
        if (strcmp(mapa[i].cor_do_exercito, cor_jogador) == 0) {
            contagem++;
        }
    }

    // Lógica simples: se conquistou 3 ou mais, missão cumprida!
    if (contagem >= 3) {
        return 1; // Ganhou!
    }
    
    return 0; 
};

int main() {

    srand(time(NULL));

    // char* aponta para o tamanho exato de cada frase, economiza memoria
    // const não deixa ninguém mudar o texto
    const char* missoes[] = {
        "Conquiste 3/4 dos territórios",
        "Elimine todo o exército preto",
        "Elimine todo o exército branco",
        "Conquiste 3 territórios seguidos",
        "Conquiste todos os territórios"
    };

    int numero_jogadores;
    printf("Quantos jogadores vão jogar?");
    scanf("%d", &numero_jogadores);

    struct Jogador* jogadores = (struct Jogador*) malloc(numero_jogadores * sizeof(struct Jogador));

// 2. Loop para configurar cada JOGADOR
    for (int i = 0; i < numero_jogadores; i++) {
        printf("\nNome do Jogador %d: ", i + 1);
        scanf("%s", jogadores[i].nome);
        printf("Cor do exército de %s: ", jogadores[i].nome);
        scanf("%s", jogadores[i].cor);

        // REQUISITO: Armazenamento dinâmico da missão
        // Alocamos 100 caracteres para guardar o texto da missão
        jogadores[i].missao = (char*) malloc(100 * sizeof(char));

        // REQUISITO: Chamar a função de sorteio
        atribuirMissao(jogadores[i].missao, missoes, 5);

        printf("Missao de %s: %s\n", jogadores[i].nome, jogadores[i].missao);
    };

    int tquantidade;
    printf("Com quantos territórios quer jogar?");
    scanf(" %d", &tquantidade);

    // Sorteia um índice de 0 a 4
    int missao_sorteada = rand() % 5;

    printf("\nSeu objetivo é: %s\n", missoes[missao_sorteada]);

    struct Territorio *vetor;

    vetor = (struct Territorio *) malloc(tquantidade * sizeof(struct Territorio));

    if (vetor == NULL) {
        printf("Memória insuficiente!");
        return 1;
    }

    for (int i = 0; i < tquantidade; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);
        
        printf("Digite o nome: ");
        scanf(" %s", vetor[i].nome); 
        
        printf("Digite a cor do exército: ");
        scanf(" %s", vetor[i].cor_do_exercito);

        printf("Digite o número de tropas ocupantes: ");
        scanf(" %d", &vetor[i].numero_de_tropas);
    }

    for (int i = 0; i < tquantidade; i++) {
        printf("\n Território %d: %s | Ocupado com %d tropas pelo exército %s \n", i + 1, vetor[i].nome, vetor[i].numero_de_tropas, vetor[i].cor_do_exercito);
    }
    
    // Vamos testar se o Jogador 1 (índice 0) ganhou
    if (verificarMissao(jogadores[0].missao, vetor, tquantidade, jogadores[0].cor)) {
        printf("\nO JOGADOR %s VENCEU O JOGO!\n", jogadores[0].nome);
    }

    // 4. LIMPEZA TOTAL (Regra de ouro do estágio!)
    // Primeiro limpamos as missões de cada jogador
    for (int i = 0; i < numero_jogadores; i++) {
        free(jogadores[i].missao);
    }
    // Depois limpamos os vetores principais
    free(jogadores);
    liberarMemoria(vetor);

    return 0;
}
