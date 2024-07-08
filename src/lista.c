#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void Lista_new(Lista *lista, int data_size, void (*free_data)(void *)) {
  lista->current = NULL;
  lista->head = NULL;
  lista->tail = NULL;
  lista->size = 0;
  lista->free = free_data;
}

void Lista_delete(Lista *lista) { Lista_new(lista, 0, lista->free); }

int Lista_isEmpty(Lista *lista) {
  if (lista->head == NULL)
    return 1;
  return 0;
}

int Lista_size(Lista *lista) { return lista->size; }

void Lista_pushFront(Lista *lista, void *valor) {
  ListaNodo *new = (ListaNodo *)malloc(sizeof(ListaNodo));
  new->valor = valor;
  new->next = lista->head;
  if (lista->head == NULL)
    lista->tail = new;
  lista->head = new;
  lista->size++;
}

void Lista_pushBack(Lista *lista, void *valor) {
  ListaNodo *new = (ListaNodo *)malloc(sizeof(ListaNodo));
  new->valor = valor;
  new->next = NULL;

  if (lista->head == NULL) {
    lista->head = new;
    lista->tail = new;
  } else {
    lista->tail->next = new;
    lista->tail = new;
  }

  lista->size++;
}
