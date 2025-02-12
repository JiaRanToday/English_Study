#include "Doublelinklist.h"
#include <stdio.h>
/*
typedef int ElemType;
typedef struct Node {
  ElemType data;
  struct Node *prior;
  struct Node *next;
} Node;

typedef Node *DoublyLinkList;
typedef enum { ERROR = -1, FALSE, TRUE } Status;

Status InitList(DoublyLinkList *list);
Status InsertHead(DoublyLinkList *list, ElemType data);
Status InsertTail(DoublyLinkList *list, ElemType data);
Status InsertLinklist(DoublyLinkList *list, int i, ElemType data);
Status DeleteHead(DoublyLinkList *list);
Status DeleteTail(DoublyLinkList *list);
Status DeleteLinklist(DoublyLinkList *list, int i);
Node *IndexSeek(DoublyLinkList *list, int i);
int NodeSeek(DoublyLinkList *list, Node *node);
Status NodeUpdate(DoublyLinkList *list, int i, ElemType data);
*/

void init_myworld() {
  printf("Creating the Portal to the World!\r\n");
  DoublyLinkList PortalToTheWorld;
  InitList(&PortalToTheWorld);

  printf("the Portal has been created!\r\n");
  printf("Creating the");
}
