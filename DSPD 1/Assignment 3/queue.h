//
//  queue.h
//  DSPD ASS 3
//
//  Created by Official on 30/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "Typedefs.h"


void init_Queue(Queue *q);

int isEmpty_Queue(Queue *q);

void Enqueue(int s,Queue *q);

int Dequeue(Queue *q);


#endif /* queue_h */
