//=================================================================
// Implementation for DLL module.
//
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

//===========================
/* Creating nodes and lists */
//===========================

LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

DLinkedList* create_dlinkedlist(CompareFunction compare) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->compare = compare;
    return newList;
}

//============================
/* Accessing nodes and lists */
//============================

int getSize(DLinkedList* dLinkedList){
    return dLinkedList->size;
}

LLNode* getHead(DLinkedList* dLinkedList){
    return dLinkedList->head;
}

LLNode* getTail(DLinkedList* dLinkedList){
    return dLinkedList->tail;
}

LLNode* getNext(LLNode* node){
    return node->next;
}

LLNode* getPrev(LLNode* node){
    return node-> prev;
}

void* getData(LLNode* node){
    return node-> data;
}

//============================
/* Inserting nodes into lists */
//============================

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
    // Create new node with DATA //
    LLNode* nextNode = create_llnode(data);
        if(prev_node->next){
            nextNode->next = prev_node->next;
            prev_node->next->prev = nextNode;
            prev_node->next = nextNode;
            nextNode->prev = prev_node;
        } else {
            prev_node->next = nextNode;
            nextNode->prev = prev_node;
            dLinkedList->tail = nextNode;
        }
        // Increment the size of DLINKEDLIST //
        dLinkedList->size++;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
    LLNode* prevNode = create_llnode(data);
//    printf("next_node->prev is %d\n\r",next_node->prev);
        if(next_node->prev!=NULL){
            prevNode->next = next_node;
            next_node->prev->next = next_node;
            prevNode->prev = next_node->prev;
            next_node->prev = prevNode;
        } else {
//            printf("inserting at the head\n\r");
            prevNode->next = next_node;
            next_node->prev = prevNode;
            dLinkedList->head = prevNode;
            
        }
        dLinkedList->size = dLinkedList->size + 1;
}


void insertHead(DLinkedList* dLinkedList, void* data){
    if (dLinkedList->head == NULL) {
        LLNode* headNode = create_llnode(data);
        dLinkedList->head = headNode;
        dLinkedList->tail = headNode;
        dLinkedList->size++;
        //printf("inserting the first head\n\r");
        return;
    } else {
        //printf("Calling insertBefore\n\r");
        insertBefore(dLinkedList, dLinkedList->head, data);
        return;
    }
}

void insertTail(DLinkedList* dLinkedList, void* data){
    LLNode* tailNode = create_llnode(data);
    if (dLinkedList->tail == NULL) {
        dLinkedList->tail = tailNode;
        dLinkedList->head = tailNode;
        dLinkedList->size++;
        return;
    } else {
        insertAfter(dLinkedList, dLinkedList->tail, data);
        return;
    }

}

//============================
/* Looking up nodes in lists */
//============================

LLNode* findNode(DLinkedList* dLinkedList, void* data){
    LLNode* node = dLinkedList->head;
    while(node){
        //printf("node data is %d, data is %d\n\r", *(int*)node->data, *(int*)data);
        dLinkedList->compare(data, node->data);
        if(dLinkedList->compare(data, node->data))
        {
            printf("node found");
            return node;
        }
        node = node->next;
    }

    //printf("data not found \n\r");
    return NULL;

}

//===========================
/* Deleting nodes and lists */
//===========================

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
    // Update pointer //
    if(dLinkedList->size==1){
        dLinkedList->head = NULL;
        dLinkedList->tail = NULL;
    }
    // NULL - NODE(HEAD*) - NEXT_NODE //
    else if(dLinkedList->head==Node){
        dLinkedList->head = Node->next;
        Node->next->prev = NULL;
    }
    // PREV_NODE - NODE(TAIL*) - NULL //
    else if(dLinkedList->tail==Node){
        dLinkedList->tail = Node->prev;
        Node->prev->next = NULL;
    }
    // PREV_NODE - NODE - NEXT_NODE //
    else{
        Node->prev->next = Node->next;
        Node->next->prev = Node->prev;
    }

    // Decrement the size of DLINKEDLIST //
    dLinkedList->size--;

    // Release memory //
    free(Node);
}

void destroyList(DLinkedList* dLinkedList){
    LLNode* curr = dLinkedList->head;
    
    while (curr != NULL){
        LLNode* next = curr->next;
        free(curr);
        curr = next;

    } free(dLinkedList);
}

//==================
/* Reversing lists */
//==================

void reverse(DLinkedList* dLinkedList){
    LLNode* curr = dLinkedList->head;
    LLNode* next;
    LLNode* prev;
    while (curr != NULL) {
        if(curr->prev == NULL)
        {
            dLinkedList->tail = curr;
        }
        else if(curr-> next == NULL)
        {
            dLinkedList->head = curr;
        }
        next = curr->next;
        prev = curr->prev;
        curr->next = prev;
        curr->prev = next;
        curr = next;

    }
} 