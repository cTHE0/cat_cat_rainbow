#include "objects.h"
#include "list.h"

void append(Node** head, Object obj) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = obj;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void deleteById(Node** head, int id) {
    Node* temp = *head;
    Node* prev = NULL;

    while (temp != NULL && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return; // Pas trouvé

    if (prev == NULL) { // Premier élément
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

int find_unused_id(Node* head) {
    /* ATTENTION, numérotation à partir de 1 !! */
    int id = 1;
    int found;

    while (1) {
        found = 0;
        Node* current = head;
        while (current != NULL) {
            if (current->data.id == id) {
                found = 1;
                break;
            }
            current = current->next;
        }
        if (!found) return id;
        id++;
    }
}


void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
