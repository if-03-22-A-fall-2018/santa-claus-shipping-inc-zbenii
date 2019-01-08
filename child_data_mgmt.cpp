#include "child_data_mgmt.h"
#include <stdlib.h>

struct _childDataMgmt{
  List *childList;
};

ChildDataMgmt* cdm_create(){

  ChildDataMgmt* newMgmt=(ChildDataMgmt*)malloc(sizeof (struct _childDataMgmt));
  newMgmt->childList=list_create();
  return newMgmt;
}

void cdm_add_data(ChildDataMgmt *cdm, ChildData *data){

  Node* currentNode = list_get_first(cdm->childList);
  Node* lastCityNode = 0;

   while(currentNode != 0){
     if(((ChildData*)list_get_data(currentNode))->city == data->city){
       lastCityNode = currentNode;
     }

     else if((list_get_next(currentNode) == 0) && (lastCityNode == 0)){
       lastCityNode = currentNode;
     }

     currentNode = list_get_next(currentNode);
   }

   if(lastCityNode == 0){
     list_add(cdm->childList, data);
   }
   
   else{
     list_insert_after(lastCityNode, data);
 }

}

Node* cdm_get_sorted_data(ChildDataMgmt *cdm){
return 0;
}

void cdm_delete(ChildDataMgmt *cdm){
free(cdm);
}
