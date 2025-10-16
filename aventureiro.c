// Nível Aventureiro — Inventário com Busca Sequencial
#include <stdio.h>
#include <string.h>

#define CAP 10

typedef struct {
    char nome[30];
    char tipo[20];
    int  quantidade;
} Item;

void listar(const Item v[], int n) {
    puts("\n=== Itens da Mochila ===");
    if (n == 0) { puts("(vazio)"); return; }
    for (int i = 0; i < n; i++)
        printf("%2d) %-28s | %-12s | x%d\n", i+1, v[i].nome, v[i].tipo, v[i].quantidade);
}

int buscarSequencial(const Item v[], int n, const char *nome) {
    for (int i = 0; i < n; i++)
        if (strcmp(v[i].nome, nome) == 0) return i;
    return -1;
}

int main(void) {
    Item inv[CAP];
    int n = 0, op;

    do {
        puts("\nMenu (Aventureiro)");
        puts("1-Adicionar  2-Remover  3-Listar  4-Buscar por nome  0-Sair");
        printf("Opção: ");
        if (scanf("%d", &op) != 1) return 0;

        if (op == 1) {
            if (n >= CAP) { puts("Mochila cheia."); continue; }
            printf("Nome: ");  scanf(" %29[^\n]", inv[n].nome);
            printf("Tipo: ");  scanf(" %19[^\n]", inv[n].tipo);
            printf("Quantidade: "); scanf("%d", &inv[n].quantidade);
            if (inv[n].quantidade < 0) inv[n].quantidade = 0;
            n++; listar(inv, n);
        } else if (op == 2) {
            if (n == 0) { puts("Mochila vazia."); continue; }
            char alvo[30];
            printf("Nome a remover: "); scanf(" %29[^\n]", alvo);
            int idx = buscarSequencial(inv, n, alvo);
            if (idx < 0) puts("Item não encontrado.");
            else {
                for (int i = idx; i < n-1; i++) inv[i] = inv[i+1];
                n--; puts("Removido."); listar(inv, n);
            }
        } else if (op == 3) {
            listar(inv, n);
        } else if (op == 4) {
            if (n == 0) { puts("Mochila vazia."); continue; }
            char alvo[30];
            printf("Nome a buscar: "); scanf(" %29[^\n]", alvo);
            int idx = buscarSequencial(inv, n, alvo);
            if (idx < 0) puts("Item não encontrado.");
            else {
                printf("Encontrado: Nome='%-s' | Tipo='%-s' | Qtde=%d\n",
                       inv[idx].nome, inv[idx].tipo, inv[idx].quantidade);
            }
        }
    } while (op != 0);

    puts("Saindo...");
    return 0;
}
