#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "list.h"

typedef struct ListType {
  Node * head;
  Node * last;
  int length;
} ListType;

List ListInit(void){
  List list;
  list = (ListType*)malloc(sizeof(ListType));
  if(!list){return NULL;}

  list->last = NULL;
  list->head = NULL;
  list->length = 0;

  return list;
}

void ListPrepend(List list, void * data){
  Node * node;
  node = (Node*)malloc(sizeof(Node));
  if(!node){return;}

  node->data = data;
  node->next = NULL;

  if(list->head == NULL){
    list->head = node;
    list->last = node;
    return;
  }

  node->next = list->head;
  list->head = node;
  list->length++;
  return;
}

void ListPop(List list){
  if(list->head == NULL){
    return;
  }
  printf("pop list\n");
  Node * node = list->head;
  list->head = list->head->next;
  free(node);
  return;
}

void ListAppend(List list, void * data){
  Node * node;
  node = (Node*)malloc(sizeof(Node));
  if(!node){return;}

  node->data = data;
  node->next = NULL;

  if(list->head == NULL){
    list->head = node;
    list->last = node;
    return;
  }

  list->last->next = node;
  list->last = node;
  list->length++;
  return;
}

Node * ListHead(List list){
  return list->head;
}

List ListTail(List list){
  List tail;
  tail = (ListType*)malloc(sizeof(ListType));
  if(!tail){return NULL;}

  tail->last = NULL;
  tail->head = NULL;
  tail->length = 0;

  if(list->head == NULL || list->head->next == NULL){
    return tail;
  }

  tail->head = list->head->next;
  tail->last = list->last;
  tail->length = list->length - 1;

  return tail;
}

int ListIsEmpty(List list){
  if(list->head == NULL){
    return 1;
  }
  return 0;
}
