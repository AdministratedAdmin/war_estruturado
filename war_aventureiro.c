#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor_do_exercito[10];
    int numero_de_tropas;
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

            printf("O território %s foi ocupado pelo exército %s com %d tropa.\n", defensor->nome, defensor->cor_do_exercito, 1);
        }
    }
}

int main() {

    int tquantidade;
    printf("Com quantos territórios quer jogar?");
    scanf(" %d", &tquantidade);

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
    
    atacar(&vetor[0], &vetor[1]); // funcao de ataque
    liberarMemoria(vetor);

    return 0;
}
