#ifndef LIST_H
#define LIST_H

#include "objects.h"

typedef struct Node {
    Object data;
    struct Node* next;
} Node;

void append(Node** head, Object obj);

void deleteById(Node** head, int id);

int find_unused_id(Node* head);

void freeList(Node* head);

#endif