#include "genericQueue.h"

BOOL createQueue(Queue *qp, int size, size_t dataSize) {
	if (qp == NULL) return FALSE;
	qp->queue = calloc(size, dataSize);
	if (qp->queue != NULL) {
		qp->size = size;
		qp->front = 0;
		qp->rear = 0;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL isQueueEmpty(const Queue *qp) {
	if (qp == NULL) return FALSE;
	if (qp->front == qp->rear)
		return TRUE;
	else
		return FALSE;
}

BOOL isQueueFull(const Queue *qp) {
	if (qp == NULL) return FALSE;
	if (qp->front == ((qp->rear + 1) % qp->size))
		return TRUE;
	else
		return FALSE;
}

BOOL enqueue(Queue *qp, void *data, size_t dataSize, void(*dataMemCpy)(void *, void *)) {
	if (qp == NULL) return FALSE;
	if (isQueueFull(qp)) return FALSE;

	dataMemCpy((char *)qp->queue + (qp->rear * dataSize), data);
	qp->rear = (qp->rear + 1) % qp->size;
	return TRUE;
}

BOOL dequeue(Queue *qp, void *data, size_t dataSize, void(*dataMemCpy)(void *, void *)) {
	if (qp == NULL) return FALSE;
	if (isQueueEmpty(qp)) return FALSE;

	dataMemCpy(data, (char *)qp->queue + (qp->front * dataSize));
	qp->front = (qp->front + 1) % qp->size;
	return TRUE;
}

void printQueue(const Queue *qp, size_t dataSize, void(*dataPrint)(void *)) {
	if (qp == NULL) return;

	for (int i = qp->front; i != qp->rear; i = (i + 1) % qp->size) {
		dataPrint((char *)qp->queue + (i * dataSize));
	}
	printf("\n");
	return;
}

void destroyQueue(Queue *qp, size_t dataSize, void(*dataFree)(void *)) {
	if (qp == NULL) return;
	if (qp->queue != NULL) {
		for (int i = 0; i < qp->size; i++) {
			dataFree((char *)qp->queue + (i * dataSize));
		}
		free(qp->queue);
	}
	qp->queue = NULL;
	qp->size = qp->front = qp->rear = 0;
}