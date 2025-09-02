#include <stdio.h>
#include <string.h>

#define STR_MAX 64

typedef struct {
    char estado;                 // 'A' a 'H'
    char codigo[STR_MAX];        // ex: A01
    char cidade[STR_MAX];        // nome da cidade
    int  populacao;              // habitantes
    float area;                  // km²
    float pib;                   // PIB total (mesma unidade para ambas as cartas)
    int  pontos_turisticos;      // quantidade
    float densidade;             // populacao / area
    float pib_per_capita;        // pib / populacao
} Carta;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void ler_string_linha(char *dest, int max) {
    if (fgets(dest, max, stdin)) {
        size_t n = strlen(dest);
        if (n > 0 && dest[n-1] == '\n') dest[n-1] = '\0';
    }
}

void cadastrar_carta(Carta *c, int indice) {
    printf("\n=== Cadastro da Carta %d ===\n", indice);

    printf("Estado (A-H): ");
    scanf(" %c", &c->estado);
    limpar_buffer();

    printf("Codigo da Carta (ex: A01): ");
    ler_string_linha(c->codigo, STR_MAX);

    printf("Nome da Cidade: ");
    ler_string_linha(c->cidade, STR_MAX);

    printf("Populacao (inteiro): ");
    scanf("%d", &c->populacao);

    printf("Area em km^2 (ex: 1234.56): ");
    scanf("%f", &c->area);

    printf("PIB total (ex: 1500000000.00): ");
    scanf("%f", &c->pib);

    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &c->pontos_turisticos);
    limpar_buffer();

    // Derivados (proteções simples contra divisões por zero)
    c->densidade = (c->area > 0.0f) ? (c->populacao / c->area) : 0.0f;
    c->pib_per_capita = (c->populacao > 0) ? (c->pib / c->populacao) : 0.0f;
}

void exibir_resumo(const Carta *c) {
    printf("\n-- %s (%s) --\n", c->cidade, c->codigo);
    printf("Estado: %c\n", c->estado);
    printf("Populacao: %d\n", c->populacao);
    printf("Area: %.2f km^2\n", c->area);
    printf("PIB: %.2f\n", c->pib);
    printf("Pontos Turisticos: %d\n", c->pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km^2\n", c->densidade);
    printf("PIB per capita: %.2f\n", c->pib_per_capita);
}

int comparar(const Carta *a, const Carta *b, int opcao, int *empate) {
    // Retorna:
    //  1 -> carta A vence
    // -1 -> carta B vence
    //  0 -> empate
    // opcao:
    // 1 pop, 2 area, 3 PIB, 4 pontos, 5 densidade, 6 PIB per capita
    float va = 0.0f, vb = 0.0f;

    switch (opcao) {
        case 1: va = (float)a->populacao;      vb = (float)b->populacao;      break;
        case 2: va = a->area;                  vb = b->area;                  break;
        case 3: va = a->pib;                   vb = b->pib;                   break;
        case 4: va = (float)a->pontos_turisticos; vb = (float)b->pontos_turisticos; break;
        case 5: va = a->densidade;             vb = b->densidade;             break;
        case 6: va = a->pib_per_capita;        vb = b->pib_per_capita;        break;
        default: *empate = 1; return 0;
    }

    if (va > vb) { *empate = 0; return 1; }
    if (vb > va) { *empate = 0; return -1; }

    *empate = 1;
    return 0;
}

void mostrar_menu() {
    printf("\n=== Selecione o atributo para comparar ===\n");
    printf("1 - Populacao (maior vence)\n");
    printf("2 - Area (maior vence)\n");
    printf("3 - PIB total (maior vence)\n");
    printf("4 - Pontos Turisticos (maior vence)\n");
    printf("5 - Densidade Populacional (maior vence)\n");
    printf("6 - PIB per capita (maior vence)\n");
    printf("Opcao: ");
}

int main() {
    Carta c1, c2;

    printf("===== Super Trunfo - Cidades (Comparacao de Cartas) =====\n");

    cadastrar_carta(&c1, 1);
    cadastrar_carta(&c2, 2);

    // Exibe um resumo das cartas cadastradas
    printf("\n===== Resumo das Cartas =====\n");
    exibir_resumo(&c1);
    exibir_resumo(&c2);

    int opcao, empate = 0;
    mostrar_menu();
    if (scanf("%d", &opcao) != 1) {
        printf("Entrada invalida.\n");
        return 0;
    }

    int resultado = comparar(&c1, &c2, opcao, &empate);

    printf("\n===== Resultado =====\n");
    if (empate) {
        printf("Empate no atributo escolhido.\n");
    } else if (resultado > 0) {
        printf("Vencedora: %s (%s)\n", c1.cidade, c1.codigo);
    } else if (resultado < 0) {
        printf("Vencedora: %s (%s)\n", c2.cidade, c2.codigo);
    } else {
        printf("Nao foi possivel comparar.\n");
    }

    return 0;
}
