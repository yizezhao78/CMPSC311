/* Yanling Wang CMPSC311 hw5 Spring 2019 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int countNodes(const listNode *list) {
  //keep adding 1 to count and currentNode=nextNode until currentNode is NULL
  int count = 0;
  const listNode* currentNode = list;
  while (currentNode != NULL){
    currentNode = currentNode->next;
    count++;
  }
  return count;
}

void insertAfter(listNode **listPtr, int findValue, int value) {
// First find the node with the value findValue
  struct listNode* currentNode = *listPtr;
  struct listNode* prevNode = NULL;
  while (currentNode != NULL){
    if (currentNode->value == findValue){
      prevNode = currentNode;
      break;
    }
    currentNode = currentNode->next;
  }

  //Then put the new node between prevNode and prevNode->next
  struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));

  //When the list is empty
  if (*listPtr == NULL){
    *listPtr = newNode;
    newNode->next = NULL;
    newNode->value = value;
  }

  //When the previous node can't be found
  else if (prevNode == NULL){
    struct listNode* currentNode2 = *listPtr;
    while (currentNode2->next != NULL){
      currentNode2 = currentNode2->next;
    }
    currentNode2->next = newNode;
    newNode->next = NULL;
    newNode->value = value;
  }
  //When find the previous node
  else{
    newNode->value = value;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
  }
  return;
}

void findAndMove(listNode **listPtr, int findValue) {
  struct listNode* currentNode = *listPtr;
  struct listNode* previousNode = NULL;
  //If list is empty do nothing
  if (currentNode == NULL){
    return;
  }
  //Loop from the start
  while(1){
    //When find the node with value 'findValue'
    if (currentNode->value == findValue){
      //First node is target node
      if (previousNode == NULL){
        *listPtr = currentNode;
      }
      //Not the first one is target node
      else{
        previousNode->next = currentNode->next;
        currentNode->next = *listPtr;
        *listPtr = currentNode;
      }
      break;
    }

    //If only one node in the list do nothing
    if (currentNode->next == NULL){
      break;
    }

    else{
      previousNode = currentNode;
      currentNode = currentNode->next;
    }

  }
  return;
}

// void findAndMove(listNode **listPtr, int findValue) {
//   struct listNode* currentNode = *listPtr;
//   struct listNode* tempNode = NULL;
//   struct listNode* nextNode = NULL;
//
//   //When 'findValue' is in the first node
//   if ((*listPtr)->value == findValue){
//     return;
//   }
//   //Find the node with the value 'findValue'
//   while (currentNode != NULL){
//     if (currentNode->value == findValue){
//       tempNode = currentNode;
//       break;
//     }
//     currentNode = currentNode->next;
//     //nextNode = currentNode->next;
//   }
//
//   //When can't find the node with value 'findValue'
//   if (tempNode == NULL){
//     return;
//   }
//
//   //When you can find a node with value 'findValue'
//   //First delete that node
//   if ((tempNode != NULL) && (nextNode != NULL)){
//     struct listNode* currentNode3 = *listPtr;
//     while (currentNode3->next != currentNode){
//       currentNode3 = currentNode3->next;
//     }
//     currentNode3->next = currentNode->next;
//
//   }
//   //Last node case
//   else if ((tempNode != NULL) && (nextNode == NULL)){
//     struct listNode* currentNode2 = *listPtr;
//     while (currentNode2->next->next != NULL){
//       currentNode2 = currentNode2->next;
//     }
//     currentNode2->next = NULL;
//   }
//
//   //Then push that node into the list
//   listNode *newNodePtr = (listNode *)malloc(sizeof(listNode));
//   newNodePtr->value = findValue;
//   newNodePtr->next = *listPtr;
//   *listPtr = newNodePtr;
//
// }



void removeAll(listNode **listPtr, int findValue) {
  struct listNode* currentNode = *listPtr;
  struct listNode* previousNode = NULL;
  //Loop till the last node
  while (currentNode != NULL && currentNode->next != NULL){
    //If the first node has value 'findValue'
    if (previousNode == NULL && currentNode->value == findValue){
      *listPtr = currentNode -> next;
      free(currentNode);
      previousNode = currentNode;
      currentNode = *listPtr;
    }
    //if later nodes hace value 'findValue'
    else if (previousNode != NULL && currentNode->value == findValue){
      previousNode -> next = currentNode->next;
      currentNode = previousNode->next;
    }
    //Keep the loop going
    else{
      previousNode = currentNode;
      currentNode = currentNode->next;
  }
  }
  //Condition when the last node has value 'findValue'
  if (currentNode->next == NULL){
    if (currentNode->value == findValue){
      //If there are multiple nodes in the list
      if (previousNode != NULL){
        previousNode->next = NULL;
      }
      //If there is only one node in the list
      else{
        *listPtr = NULL;
      }
    }
  }

}
