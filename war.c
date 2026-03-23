#include <stdio.h>

#define MAXT 5

int main() {
    
    struct Territorio {
        char nome[50];
        char cor_do_exercito[10];
        int numero_de_tropas;
    };

    struct Territorio vetor[MAXT];

    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);
        
        printf("Digite o nome: ");
        scanf("%s", vetor[i].nome); 
        
        printf("Digite a cor do exército: ");
        scanf("%s", vetor[i].cor_do_exercito);

        printf("Digite o número de tropas ocupantes: ");
        scanf("%d", &vetor[i].numero_de_tropas);
    }

    for (int i = 0; i < 5; i++) {
        printf("\n Território %d: %s | Ocupado com %d tropas pelo exército %s \n", i + 1, vetor[i].nome, vetor[i].numero_de_tropas, vetor[i].cor_do_exercito);
    }




    


    return 0;
}
