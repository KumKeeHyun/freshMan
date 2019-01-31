#pragma once
#include <stdio.h>
#include <stdlib.h>

enum BOOL { FALSE, TRUE };

typedef struct queue {
	void *queue;
	int size;
	int front, rear;
}Queue;

BOOL createQueue(Queue *qp, int size, size_t dataSize);
BOOL isQueueEmpty(const Queue *qp);
BOOL isQueueFull(const Queue *qp);
BOOL enqueue(Queue *qp, void *data, size_t dataSize, void(*dataMemCpy)(void *, void *));
BOOL dequeue(Queue *qp, void *data, size_t dataSize, void(*dataMemCpy)(void *, void *));
void printQueue(const Queue *qp, size_t dataSize, void(*dataPrint)(void *));
void destroyQueue(Queue *qp, size_t dataSize, void(*dataFree)(void *));