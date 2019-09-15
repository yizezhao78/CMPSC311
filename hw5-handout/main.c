/* Yanling Wang CMPSC311 hw5 Spring 2019 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define MAXLINE 100
/* print out helper messages */
void printHelp() {
  printf("help -- print this message.\n");
  printf("push n -- push value n to the beginning of the list.\n");
  printf("pop --  pop the head of the list and print its value.\n");
  printf("show -- show the whole list.\n");
  printf("count -- count number of nodes in a list.\n");
  printf("insert x y -- insert a node with value y after the node with value x.\n");
  printf("find n -- find the node with value n and move it to the head.\n");
  printf("remove n -- remove all nodes with value n.\n");
  printf("quit -- quit the program and destroy the whole list.\n");
}

/* print out detailed list nodes info */
void displayList(const listNode *list) {
  printf("list head: %p\n", list);
  while(list != NULL) {
    printf("node address: %p, value: %d, next: %p\n",list,
        list->value, list->next);
    list = list->next;
  }
  return;
}

/* add one new node with given value to the head of the list */
void push(listNode **listPtr, int value) {
  listNode *newNodePtr = (listNode *)malloc(sizeof(listNode));
  newNodePtr->value = value;
  newNodePtr->next = *listPtr;
  *listPtr = newNodePtr;
  return;
}

/* pop/delete the head node from the list and return its value */
int pop(listNode **listPtr) {
  int value = 0;
  listNode *tempPtr;
  if (*listPtr) {
    tempPtr = *listPtr;
    value = tempPtr->value;
    *listPtr = tempPtr->next;
    free(tempPtr);
  }
  return value;
}

/* delete all nodes in a list */
void destroyList(listNode **listPtr) {
  listNode *current = *listPtr;
  while(current != NULL) {
    *listPtr = current -> next;
    free(current);
    current = *listPtr;
  }
  return;
}
int main() {
  char command[20];
  char commandline[MAXLINE];
  listNode *list = NULL;
  int findValue;
  int value;
  int argcount;
  printf("List driver, enter help for help.\ncommand>");
  while (fgets(commandline, MAXLINE, stdin)) {
    sscanf(commandline, "%19s", command);
    if (!strcmp(command, "help")) {
      printHelp();
    }
    else if (!strcmp(command, "push")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        push(&list, value);
      }
      else {
        printf("Invalid argument for push.\n");
      }
    }
    else if (!strcmp(command, "pop")) {
      if (list == NULL) {
        printf("Error in pop: empty list.\n");
      }
      else {
        value = pop(&list);
        printf("Popped value = %d\n", value);
      }
    }
    else if (!strcmp(command, "show")) {
    }
    else if (!strcmp(command, "insert")) {
      argcount = sscanf(commandline, "%19s %d %d", command, &findValue, &value);
      if (argcount == 3) {
        insertAfter(&list, findValue, value);
      }
      else {
        printf("Invalid argument for insert.\n");
      }
    }
    else if (!strcmp(command, "find")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        findAndMove(&list, value);
      }
      else {
        printf("Invalid argument for insert.\n");
      }
    }
    else if (!strcmp(command, "remove")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        removeAll(&list, value);
      }
      else {
        printf("Invalid argument for remove.\n");
      }
    }
    else if (!strcmp(command, "count")) {
      printf("list has %d nodes.\n", countNodes(list));
    }
    else if (!strcmp(command, "quit")) {
      break;
    }
    else {
      printf("Invalid command.\n");
    }
    displayList(list);
    printf("command>");
  }
  destroyList(&list);
  printf("Good bye.\n");
  return 0;
}
