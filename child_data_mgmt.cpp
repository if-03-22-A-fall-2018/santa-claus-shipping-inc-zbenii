#include "child_data_mgmt.h"
#include <stdlib.h>

ChildDataMgmt* cdm_create(){

  ChildDataMgmt* newMgmt=(ChildDataMgmt*)malloc(sizeof (struct _childDataMgmt));
  return newMgmt;
}

void cdm_add_data(ChildDataMgmt *cdm, ChildData *data){

  Node* node=(Node*)malloc(sizeof(struct _node));
  node->data=data;

  if(cdm->childList->_head==0)
  {
    cdm->childList->_head=node;
  }
  else
  {
    node->next=cdm->childList->_head;
    cdm->childList->_head=node;
  }
}

Node* cdm_get_sorted_data(ChildDataMgmt *cdm){
return 0;
}

void cdm_delete(ChildDataMgmt *cdm){
free(cdm);
}
