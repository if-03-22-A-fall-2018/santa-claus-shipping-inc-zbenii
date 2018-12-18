#include <stdlib.h>
#include "list.h"

struct _node {
  void* data;
  Node* next;
};

struct _list{
  Node* _head;
  Node* _tail;
};


List* list_create(){
  List* list=(List*)malloc(sizeof(struct _list));
  return list;
}

void list_delete(List *list){
  free(*list);
}

void list_add(List *list, void *data){

}

void list_insert_after(Node *node, void *data){

}

Node* list_get_first(List *list){

}

Node* list_get_next(Node *node){

}

void* list_get_data(Node *node){

}
