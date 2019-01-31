#pragma warning (disable:4996)
#include "genericLinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------------
Function name	: createList - ���� ����Ʈ �ʱ�ȭ
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL createList(List *lp) {
	if (lp == NULL)
		return FALSE;
	lp->head = (Node *)calloc(1, sizeof(Node));
	if (lp->head == NULL)
		return FALSE;
	lp->tail = (Node *)calloc(1, sizeof(Node));
	if (lp->tail == NULL) {
		free(lp->head);
		lp->head = NULL;
		return FALSE;
	}
	lp->head->next = lp->tail;
	lp->head->prev = lp->head;
	lp->tail->next = lp->tail;
	lp->tail->prev = lp->head;
	lp->size = 0;

	return TRUE;
}

/*----------------------------------------------------------------------------------
Function name	: addFirst - head node �ڿ� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
				  dataSize - �߰������� �Ҵ��� ������ ũ��
				  memCpy - �����͸� deep copy�ϴ� �Լ��� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL addFirst(List *lp, void *data, size_t dataSize, void(*memCpy)(void *, void*)) {
	if (lp == NULL)
		return FALSE;
	Node *newp = (Node *)calloc(1, sizeof(Node) + dataSize);
	if (newp == NULL)
		return FALSE;
	newp->next = lp->head->next;
	newp->prev = lp->head;
	lp->head->next->prev = newp;
	lp->head->next = newp;
	memCpy(newp + 1, data);
	++lp->size;

	return TRUE;
}

/*----------------------------------------------------------------------------------
Function name	: addLast - tail node �տ� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
				  dataSize - �߰������� �Ҵ��� ������ ũ��
				  memCpy - �����͸� deep copy�ϴ� �Լ��� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL addLast(List *lp, void *data, size_t dataSize, void(*memCpy)(void *, void*)) {
	if (lp == NULL)
		return FALSE;
	Node *newp = (Node *)calloc(1, sizeof(Node) + dataSize);
	if (newp == NULL)
		return FALSE;
	newp->next = lp->tail;
	newp->prev = lp->tail->prev;
	lp->tail->prev->next = newp;
	lp->tail->prev = newp;
	memCpy(newp + 1, data);
	++lp->size;

	return TRUE;
}

/*----------------------------------------------------------------------------------
Function name	: displayList - ����Ʈ ���� ��� ������ ���
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  dataPrint - �ΰ����� �����͸� ������ִ� �Լ��� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void displayList(List *lp, void(*dataPrint)(void *)) {
	if (lp == NULL)
		return;
	Node *dp = lp->head->next;
	while (dp != lp->tail) {
		dataPrint(dp + 1);
		dp = dp->next;
	}

	return;
}

/*----------------------------------------------------------------------------------
Function name	: removeNode - data�� ��ġ�ϴ� ù ��° ��� ����
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - ������ ������
				  dataFree - �������� �ΰ����� �޸𸮸� �����ϴ� �Լ��� �ּ�
				  compareData - �ΰ��� �������� ũ�⸦ ���ϴ� �Լ��� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL removeNode(List *lp, void *data, void(*dataFree)(void *), int(*compareData)(void *, void *)) {
	if (lp == NULL)
		return FALSE;
	Node *sp = searchNode(lp, data, compareData);
	if (sp == NULL)
		return FALSE;
	sp->prev->next = sp->next;
	sp->next->prev = sp->prev;
	dataFree(sp + 1); // Data�� �ΰ� Memory ����
	free(sp); // Node + Data ����
	--lp->size;

	return TRUE;
}

/*----------------------------------------------------------------------------------
Function name	: searchNode - data�� ��ġ�ϴ� ù ��° node �˻�
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �˻��� ������
				  compareData - �ΰ��� �������� ũ�⸦ ���ϴ� �Լ��� �ּ�
Returns			: ���� - �˻��� ����� �ּ� / ���� - NULL pointer
----------------------------------------------------------------------------------*/
Node* searchNode(List *lp, void *data, int(*compareData)(void *, void *)) {
	if (lp == NULL)
		return NULL;
	Node *sp = lp->head->next;
	while (sp != lp->tail) {
		if (compareData(sp + 1, data) == 0)
			return sp;
		sp = sp->next;
	}

	return NULL;
}

/*----------------------------------------------------------------------------------
Function name	: sortList - ��� ����(bubble sort)(��������)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  compareData - �ΰ��� �������� ũ�⸦ ���ϴ� �Լ��� �ּ�
				  swapData - �ΰ��� �����͸� �ٲ��ִ� �Լ��� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void sortList(List *lp, int(*compareData)(void *, void *), void(*swapData)(void *, void *)) {
	Node *temp;
	for (int i = lp->size - 1; i > 0; i--) {
		temp = lp->head->next;
		for (int j = 0; j < i; j++) {
			if (compareData(temp + 1, temp->next + 1) > 0) {
				swapData(temp + 1, temp->next + 1);
			}
			temp = temp->next;
		}
	}
	/*
	temp = lp->head->next;
	while (temp->next != lp->tail){

	}
	*/

	return;
}

/*----------------------------------------------------------------------------------
Function name	: destroyList - ����Ʈ ���� ��� ���(head, tail ��� ����)�� ����
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  dataFree - �������� �ΰ����� �޸𸮸� �����ϴ� �Լ��� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void destroyList(List *lp, void(*dataFree)(void *)) {
	if (lp == NULL)
		return;
	Node *dp, *tp = lp->head->next;
	while (tp != lp->tail) {
		dp = tp;
		tp = tp->next;
		dataFree(dp + 1);
		free(dp);
	}
	free(lp->head);
	free(lp->tail);
	lp->head = NULL;
	lp->tail = NULL;
	lp->size = 0;

	return;
}