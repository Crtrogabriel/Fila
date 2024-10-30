#include <stdio.h>
#include <stdlib.h>

struct Lista {
    int info;
    struct Lista *prox;
};

struct Lista* criaLista() { return NULL; }

struct Lista* inserirOrdenado(struct Lista *lista, int i) {
    struct Lista* novo = (struct Lista*) malloc(sizeof(struct Lista));
    novo->info = i;
    struct Lista* ant = NULL;
    struct Lista* p = lista;
    while (p != NULL && p->info < i) {
        ant = p;
        p = p->prox;
    }
    if (ant == NULL) {
        novo->prox = lista;
        lista = novo;
    } else {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return lista;
}

void imprimeLista(struct Lista *lista) {
    struct Lista *p;
    printf("Lista de elementos:\n");
    for (p = lista; p != NULL; p = p->prox) {
        printf("%d\n", p->info);
    }
}

int verificarVazia(struct Lista *lista) { return (lista == NULL); }

struct Lista* buscaLista(struct Lista *lista, int v) {
    struct Lista *p;
    for (p = lista; p != NULL; p = p->prox) {
        if (p->info == v) {
            return p;
        }
    }
    return NULL;
}

struct Lista* retiraLista(struct Lista *lista, int v) {
    struct Lista *ant = NULL;
    struct Lista *p = lista;
    while (p != NULL && p->info != v) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        return lista;
    }
    if (ant == NULL) {
        lista = p->prox;
    } else {
        ant->prox = p->prox;
    }
    free(p);
    return lista;
}

void liberaLista(struct Lista *lista) {
    struct Lista *p = lista;
    while (p != NULL) {
        struct Lista *t = p->prox;
        free(p);
        p = t;
    }
}

int main() {
    struct Lista* lista = criaLista();
    int opcao, valor;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir elemento em ordem\n");
        printf("2. Exibir lista\n");
        printf("3. Buscar elemento\n");
        printf("4. Remover elemento\n");
        printf("5. Verificar se a lista está vazia\n");
        printf("6. Liberar lista e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                lista = inserirOrdenado(lista, valor);
                printf("Elemento inserido!\n");
                break;
            case 2:
                imprimeLista(lista);
                break;
            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                struct Lista* busca = buscaLista(lista, valor);
                if (busca) {
                    printf("Elemento %d encontrado na lista.\n", valor);
                } else {
                    printf("Elemento %d não encontrado na lista.\n", valor);
                }
                break;
            case 4:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                lista = retiraLista(lista, valor);
                printf("Elemento removido, se presente.\n");
                break;
            case 5:
                if (verificarVazia(lista)) {
                    printf("A lista está vazia.\n");
                } else {
                    printf("A lista não está vazia.\n");
                }
                break;
            case 6:
                liberaLista(lista);
                printf("Lista liberada. Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);
    return 0;
}