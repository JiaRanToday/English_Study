#include "Doublelinklist.h"

Status InitList(DoublyLinkList *list) {
  if (list == NULL) {
    return ERROR;
  }
  if (*list == NULL) {
    *list = (DoublyLinkList)malloc(sizeof(Node));
    if (*list == NULL) {
      return FALSE;
    }
  }
  (*list)->next = NULL;
  (*list)->prior = NULL;
  (*list)->data = -1;
  return TRUE;
}
Status InsertHead(DoublyLinkList *list, ElemType data) {
  if (*list == NULL) {
    return ERROR;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return FALSE;
  }
  newNode->data = data;
  newNode->next = (*list)->next;
  newNode->prior = *list;
  if ((*list)->next) {
    (*list)->next->prior = newNode;
  }
  (*list)->next = newNode;
  return TRUE;
}
Status InsertTail(DoublyLinkList *list, ElemType data) {
  if (*list == NULL) {
    return ERROR;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return FALSE;
  }
  DoublyLinkList step = *list;
  while (step->next) {
    step = step->next;
  }
  newNode->prior = step;
  newNode->next = NULL;
  newNode->data = data;
  step->next = newNode;
  return TRUE;
}
Status InsertLinklist(DoublyLinkList *list, int i, ElemType data) {
  if (i < 1 || *list == NULL) {
    return ERROR;
  }
  DoublyLinkList step = *list;
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return FALSE;
  }
  int index = 0;
  while (step->next && index < i - 1) {
    step = step->next;
    index++;
  }
  if (index < i - 1) {
    free(newNode);
    return FALSE;
  }
  newNode->next = step->next;
  newNode->prior = step;
  newNode->data = data;
  if (step->next != NULL) {
    step->next->prior = newNode;
  }
  step->next = newNode;
  return TRUE;
}
Status DeleteHead(DoublyLinkList *list) {
  if (*list == NULL || (*list)->next == NULL) {
    return ERROR;
  }
  DoublyLinkList delete = (*list)->next;
  (*list)->next = delete->next;
  delete->next->prior = *list;
  free(delete);
  return TRUE;
}
Status DeleteTail(DoublyLinkList *list) {
  if (*list == NULL || (*list)->next == NULL) {
    return ERROR;
  }
  DoublyLinkList step = *list;
  while (step->next) {
    step = step->next;
  }
  step->prior->next = NULL;
  free(step);
  return TRUE;
}
Status DeleteLinklist(DoublyLinkList *list, int i) {
  if (i < 1 || *list == NULL || (*list)->next == NULL) {
    return ERROR;
  }
  DoublyLinkList step = *list;
  int index = 0;
  while (step->next && index < i - 1) {
    step = step->next;
    index++;
  }
  if (index < i - 1) {
    return FALSE;
  }
  DoublyLinkList delete = step->next;
  step->next = delete->next;
  if (delete->next != NULL) {
    delete->next->prior = step;
  }
  if (i == 1) {
    *list = step->next;
  }
  free(delete);
  return TRUE;
}

Node *IndexSeek(DoublyLinkList *list, int i) {
  if (i < 1 || *list == NULL || (*list)->next == NULL) {
    return NULL;
  }
  DoublyLinkList step = *list;
  int index = 0;
  while (step && index < i) {
    step = step->next;
    index++;
  }
  if (index < i) {
    return NULL;
  }
  return step;
}
int NodeSeek(DoublyLinkList *list, Node *node) {
  if (*list == NULL || (*list)->next == NULL || node == NULL) {
    return -1;
  }
  DoublyLinkList step = *list;
  int index = 0;
  while (step) {
    if (step == node) {
      return index;
    }
    step = step->next;
    index++;
  }
  return -1;
}
Status NodeUpdate(DoublyLinkList *list, int i, ElemType data) {
  if (*list == NULL || (*list)->next == NULL) {
    return ERROR;
  }
  DoublyLinkList step = *list;
  int index = 0;
  while (step && index < i) {
    step = step->next;
    index++;
  }
  if (index < i)
    return FALSE;
  step->data = data;
  return TRUE;
}
