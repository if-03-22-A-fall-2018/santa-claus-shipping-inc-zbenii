#include <stdlib.h>
#include "list.h"

struct _node {
  void* data;
  struct _node* next;
};

struct _list{
  Node* _head;
};


List* list_create(){
  List* list=(List*)malloc(sizeof(struct _list));
  return list;
}

void list_delete(List *list){
  free(list);
}

void list_add(List *list, void *data){

  Node* node=(Node*)malloc(sizeof(struct _node));
  node->data=data;

  if(list->_head==0){list->_head=node;}
  else
  {
    node->next=list->_head;
    list->_head=node;
  }

}

void list_insert_after(Node *node, void *data){
  Node* newNode=(Node*)malloc(sizeof(struct _node));
  newNode->data=data;

  newNode->next=node->next;
  node->next=newNode;


}

Node* list_get_first(List *list){
return list->_head;
}

Node* list_get_next(Node *node){
return node->next;
}

void* list_get_data(Node *node){
 return node->data;
}
