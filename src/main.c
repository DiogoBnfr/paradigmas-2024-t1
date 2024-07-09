#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int int_cmp(void* a, void* b) {
    int* p1 = (int*)a;
    int* p2 = (int*)b;
    return (*p1 - *p2);
}

void free_int(void* data) {
    free(data);
}

void Lista_status(Lista* lista) {
    if(Lista_isEmpty(lista)) {
            printf("A lista está vazia.\n");
        } else {
            printf("A lista contém um ou mais itens.\n");
        }
    printf("Tamanho da lista: %d\n", Lista_size(lista));
}

int main() {
    Lista lista;
    Lista_new(&lista, sizeof(int), free_int);

    printf("Inserindo elementos no início da lista. . .\n");
    for (int i = 1; i <= 5; ++i) {
        Lista_pushFront(&lista, &i);
    }

    Lista_status(&lista);

    printf("Inserindo elementos no final da lista. . .\n");
    for (int i = 6; i <= 10; ++i) {
        Lista_pushBack(&lista, &i);
    }

    Lista_status(&lista);

    int chave = 3;
    int encontrado;
    printf("Buscando o valor %d na lista. . .\n", chave);
    encontrado = Lista_search(&lista, &chave, &chave, int_cmp);
    if (encontrado) {
        printf("Valor %d encontrado na lista.\n", chave);
    } else {
        printf("Valor %d não encontrado na lista.\n", chave);
    }

    chave = 16;
    printf("Buscando o valor %d na lista. . .\n", chave);
    encontrado = Lista_search(&lista, &chave, &chave, int_cmp);
    if (encontrado) {
        printf("Valor %d encontrado na lista.\n", chave);
    } else {
        printf("Valor %d não encontrado na lista.\n", chave);
    }

    int chave_remover = 7;
    printf("Removendo o valor %d da lista. . .\n", chave_remover);
    Lista_remove(&lista, &chave_remover, int_cmp);

    chave_remover = 11;
    printf("Removendo o valor %d da lista. . .\n", chave_remover);
    Lista_remove(&lista, &chave_remover, int_cmp);

    Lista_status(&lista);

    Lista_first(&lista);
    int dest;
    Lista_current(&lista, &dest);
    while (1) {
        printf("%d ", dest);
        Lista_current(&lista, &dest);
        if (Lista_next(&lista) == 0) break;
    }
    printf("\n");

    Lista_first(&lista);
    Lista_current(&lista, &dest);
    printf("Elemento atual: %d\n", dest);

    int valor_inserir = 99;
    printf("Inserindo o valor %d após o elemento atual. . .\n", valor_inserir);
    Lista_first(&lista);
    Lista_next(&lista);
    Lista_insertAfter(&lista, &valor_inserir);

    Lista_first(&lista);
    Lista_current(&lista, &dest);
    while (1) {
        printf("%d ", dest);
        Lista_current(&lista, &dest);
        if (Lista_next(&lista) == 0) break;
    }
    printf("\n");

    Lista_delete(&lista);

    Lista_status(&lista);

    return 0;
}