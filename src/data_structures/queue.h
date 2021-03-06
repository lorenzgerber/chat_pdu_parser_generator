/*
 * queue.h
 *
 *
 *  Created on: Oct 1, 2017
 *     Authors: Lorenz Gerber, Niklas Königsson
 *
 *  Chat client server project
 *  5DV197 Datakom course
 *	GPLv3
 */

#ifndef SRC_DATA_STRUCTURES_QUEUE_H_
#define SRC_DATA_STRUCTURES_QUEUE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef void *data;

typedef void memFreeFunc(data);

typedef struct queue_element {
	struct queue_element *next;
	data data;
} queue_element;

typedef queue_element * queue_position;

typedef struct queue {
	queue_element *first;
	memFreeFunc *freeFunc;
} queue;

// create empty queue
queue *queue_empty(void);

// set mem handler
void queueSetMemHandler(queue *q, memFreeFunc *f);



// enqueue
int enqueue(queue *q, data d);

// IsEmpty
int is_empty(queue *q);

// get Front
data* front(queue *q);

// dequeue
int dequeue(queue *q);

void queue_free(queue *q);

#endif /* SRC_DATA_STRUCTURES_QUEUE_H_ */
