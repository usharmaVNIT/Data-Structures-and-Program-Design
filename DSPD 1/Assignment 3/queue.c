//
//  queue.c
//  DSPD_Assignment3
//
//  Created by Official on 28/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include<stdlib.h>
#include "queue.h"



void init_Queue(Queue *q){
    q->head = NULL;
    q->tail = NULL;
}

int isEmpty_Queue(Queue *q){
    return q->tail == NULL;
}

void Enqueue(int s,Queue *q){
    Queue_Node *ptr = (Queue_Node*)malloc(sizeof(Queue_Node));
    ptr->val = s;
    ptr->next=NULL;
    if(isEmpty_Queue(q)==1){
        q->tail = q->head = ptr;
    }
    else{
        q->tail->next = ptr;
        q->tail = ptr;
    }
}

int Dequeue(Queue *q){
    int ans=-1;
    if(isEmpty_Queue(q)==0){
        ans = q->head->val;
        Queue_Node *ptr = q->head;
        q->head = q->head->next;
        if(q->head == NULL){
            q->tail = NULL;
        }
        free(ptr);
    }
    return ans;
}
