#include <stdlib.h>
#include <string.h>

#include "lista.h"

void free_node(Node* node, void (*free_data)(void*)) {
    if (free_data != NULL && node->data != NULL) {
        free_data(node->data);
    }
    free(node);
}

void Lista_new(Lista *lista, int data_size, void (*free_data)(void *))
{
    lista->data_size = data_size;
    lista->size = 0;
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    lista->free_data = free_data;
}

void Lista_delete(Lista *lista)
{
    Node* current = lista->head;
    while (current != NULL) {
        Node* next = current->next;
        free_node(current, lista->free_data);
        current = next;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    lista->size = 0;
}

int Lista_isEmpty(Lista *lista)
{
    if (lista->size == 0) return 1;
    return 0;
}

int Lista_size(Lista *lista)
{
    return lista->size;
}

void Lista_pushFront(Lista* lista, void* valor) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return; // Tratamento de erro: falha na alocação de memória
    }
    newNode->data = malloc(lista->data_size);
    if (newNode->data == NULL) {
        free(newNode);
        return;
    }
    memcpy(newNode->data, valor, lista->data_size);

    newNode->next = lista->head;
    newNode->prev = NULL;

    if (lista->head != NULL) {
        lista->head->prev = newNode;
    } else {
        lista->tail = newNode; // Se a lista estava vazia, newNode = head e tail da lista
    }

    lista->head = newNode;
    lista->size++;
}

void Lista_pushBack(Lista* lista, void* valor) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = malloc(lista->data_size);
    if (newNode->data == NULL) {
        free(newNode);
        return;
    }
    memcpy(newNode->data, valor, lista->data_size);

    newNode->next = NULL;
    newNode->prev = lista->tail;

    if (lista->tail != NULL) {
        lista->tail->next = newNode;
    } else {
        lista->head = newNode;
    }

    lista->tail = newNode;
    lista->size++;
}

int Lista_search(Lista* lista, void* chave, void* dest, int (*cmp)(void*,void*)) {
    Node* current = lista->head;
    while (current != NULL) {
        if (cmp(current->data, chave) == 0) {
            memcpy(dest, current->data, lista->data_size);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void Lista_remove(Lista* lista, void* chave, int (*cmp)(void*,void*)) {
    Node* current = lista->head;
    while (current != NULL) {
        if (cmp(current->data, chave) == 0) {
            Node* next = current->next;
            Node* prev = current->prev;

            if (prev != NULL) {
                prev->next = next;
            } else {
                lista->head = next;
            }

            if (next != NULL) {
                next->prev = prev;
            } else {
                lista->tail = prev;
            }

            free_node(current, lista->free_data);
            lista->size--;
            return;
        }
        current = current->next;
    }
}

void Lista_first(Lista* lista) {
    lista->current = lista->head;
}

void Lista_last(Lista* lista) {
    lista->current = lista->tail;
}

int Lista_next(Lista* lista) {
    if (lista->current == NULL) {
        return 0;
    }
    lista->current = lista->current->next;
    return lista->current != NULL;
}

void Lista_current(Lista* lista, void* dest) {
    if (lista->current != NULL) {
        memcpy(dest, lista->current->data, lista->data_size);
    }
}

void Lista_insertAfter(Lista* lista, void* dado) {
    if (lista->current == NULL) {
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = malloc(lista->data_size);
    if (newNode->data == NULL) {
        free(newNode);
        return;
    }
    memcpy(newNode->data, dado, lista->data_size);

    newNode->next = lista->current->next;
    newNode->prev = lista->current;
    lista->current->next = newNode;

    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    } else {
        lista->tail = newNode;
    }

    lista->size++;
}

void Lista_removeCurrent(Lista* lista) {
    if (lista->current == NULL) {
        return;
    }

    Node* current = lista->current;
    Node* next = current->next;
    Node* prev = current->prev;

    if (prev != NULL) {
        prev->next = next;
    } else {
        lista->head = next;
    }

    if (next != NULL) {
        next->prev = prev;
    } else {
        lista->tail = prev;
    }

    free_node(current, lista->free_data);
    lista->size--;
}

int Lista_previous(Lista* lista) {
    if (lista->current == NULL) {
        return 0;
    }
    lista->current = lista->current->prev;
    return lista->current != NULL;
}

void Lista_insertBefore(Lista* lista, void* dado) {
    if (lista->current == NULL) {
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = malloc(lista->data_size);
    if (newNode->data == NULL) {
        free(newNode);
        return;
    }
    memcpy(newNode->data, dado, lista->data_size);

    newNode->next = lista->current;
    newNode->prev = lista->current->prev;
    lista->current->prev = newNode;

    if (newNode->prev != NULL) {
        newNode->prev->next = newNode;
    } else {
        lista->head = newNode;
    }

    lista->size++;
}