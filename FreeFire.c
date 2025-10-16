// Nível Mestre — Ordenação + Busca Binária + Prioridade
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CAP 10

typedef enum { ORD_NENHUM=0, ORD_NOME=1, ORD_TIPO=2, ORD_PRIOR=3 } Criterio;

typedef struct {
    char nome[30];
    char tipo[20];
    int  quantidade;
    int  prioridade;  // 1..5
} Item;

void listar(const Item v[], int n) {
    puts("\n=== Itens da Mochila ===");
    if (n == 0) { puts("(vazio)"); return; }
    for (int i = 0; i < n; i++)
        printf("%2d) %-20s | %-10s | x%-3d | P:%d\n",
               i+1, v[i].nome, v[i].tipo, v[i].quantidade, v[i].prioridade);
}

int cmpNome(const Item *a, const Item *b) { return strcmp(a->nome, b->nome); }
int cmpTipo(const Item *a, const Item *b) { return strcmp(a->tipo, b->tipo); }
int cmpPrior(const Item *a, const Item *b) { return (b->prioridade - a->prioridade); } // maior primeiro

// insertion sort genérico com contador de comparações
long insertionSort(Item v[], int n, Criterio c) {
    long comps = 0;
    for (int i = 1; i < n; i++) {
        Item key = v[i];
        int j = i - 1;
        while (j >= 0) {
            int r = 0;
            if (c == ORD_NOME) r = cmpNome(&v[j], &key);
            else if (c == ORD_TIPO) r = cmpTipo(&v[j], &key);
            else r = cmpPrior(&v[j], &key);
            comps++;
            if (r <= 0) break;       // já está no lugar
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
    return comps;
}

// busca binária por nome (requer ordenado por nome asc)
int buscaBinariaNome(const Item v[], int n, const char *nome) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int r = strcmp(v[mid].nome, nome);
        if (r == 0) return mid;
        else if (r < 0) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main(void) {
    Item inv[CAP];
    int n = 0;
    Criterio ordenadoComo = ORD_NENHUM; // estado da ordenação atual

    int op;
    do {
        puts("\nMenu (Mestre)");
        puts("1-Adicionar  2-Remover  3-Listar");
        puts("4-Ordenar (nome/tipo/prioridade)");
        puts("5-Busca Binária por Nome (requer ordenado por nome)");
        puts("0-Sair");
        printf("Opção: ");
        if (scanf("%d", &op) != 1) return 0;

        if (op == 1) {
            if (n >= CAP) { puts("Mochila cheia."); continue; }
            printf("Nome: ");        scanf(" %29[^\n]", inv[n].nome);
            printf("Tipo: ");        scanf(" %19[^\n]", inv[n].tipo);
            printf("Quantidade: ");  scanf("%d", &inv[n].quantidade);
            printf("Prioridade (1..5): "); scanf("%d", &inv[n].prioridade);
            if (inv[n].quantidade < 0) inv[n].quantidade = 0;
            if (inv[n].prioridade < 1) inv[n].prioridade = 1;
            if (inv[n].prioridade > 5) inv[n].prioridade = 5;
            n++;
            ordenadoComo = ORD_NENHUM; // inserir quebra a ordenação
            listar(inv, n);
        } else if (op == 2) {
            if (n == 0) { puts("Mochila vazia."); continue; }
            char alvo[30];
            printf("Nome a remover: "); scanf(" %29[^\n]", alvo);
            int idx = -1;
            for (int i = 0; i < n; i++)
                if (strcmp(inv[i].nome, alvo) == 0) { idx = i; break; }
            if (idx < 0) puts("Item não encontrado.");
            else {
                for (int i = idx; i < n-1; i++) inv[i] = inv[i+1];
                n--; puts("Removido."); listar(inv, n);
            }
        } else if (op == 3) {
            listar(inv, n);
        } else if (op == 4) {
            int c;
            puts("Ordenar por: 1-Nome  2-Tipo  3-Prioridade");
            printf("Critério: ");
            if (scanf("%d", &c) != 1 || c < 1 || c > 3) { puts("Critério inválido."); continue; }
            Criterio crit = (Criterio)c;
            long comps = insertionSort(inv, n, crit);
            ordenadoComo = crit;
            listar(inv, n);
            printf("Comparações na ordenação: %ld\n", comps);
        } else if (op == 5) {
            if (ordenadoComo != ORD_NOME) {
                puts("A lista precisa estar ordenada por NOME para busca binária. Use a opção 4 primeiro (Nome).");
                continue;
            }
            if (n == 0) { puts("Mochila vazia."); continue; }
            char alvo[30];
            printf("Nome a buscar: "); scanf(" %29[^\n]", alvo);
            int idx = buscaBinariaNome(inv, n, alvo);
            if (idx < 0) puts("Item não encontrado.");
            else printf("Encontrado: %-20s | %-10s | x%-3d | P:%d\n",
                        inv[idx].nome, inv[idx].tipo, inv[idx].quantidade, inv[idx].prioridade);
        }
    } while (op != 0);

    puts("Saindo...");
    return 0;
}
