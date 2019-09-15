/* Yanling Wang CMPSC311 hw5 Spring 2019 */
#ifndef LIST_H
#define LIST_H
typedef struct listNode {
  int value;
  struct listNode *next;
} listNode;
void displayList(const listNode *list); 
void push(listNode **listPtr, int value);
int pop(listNode **listPtr); 
void destroyList(listNode **listPtr);
int countNodes(const listNode *list);
void insertAfter(listNode **listPtr, int findValue, int value);
void findAndMove(listNode **listPtr, int findValue);
void removeAll(listNode **listPtr, int findValue);

#endif //LIST_H
