#ifndef DOUBLELINKLIST_H_
#define DOUBLELINKLIST_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif // !DOUBLELINKLIST_H_
