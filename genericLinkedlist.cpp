#pragma warning (disable:4996)
#include "genericLinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------------
Function name	: createList - 연결 리스트 초기화
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: addFirst - head node 뒤에 node 추가(역순 저장)
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 추가할 데이터
				  dataSize - 추가적으로 할당할 데이터 크기
				  memCpy - 데이터를 deep copy하는 함수의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: addLast - tail node 앞에 node 추가(정순 저장)
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 추가할 데이터
				  dataSize - 추가적으로 할당할 데이터 크기
				  memCpy - 데이터를 deep copy하는 함수의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: displayList - 리스트 내의 모든 데이터 출력
Parameters		: lp - 리스트 관리 구조체의 주소
				  dataPrint - 부가적인 데이터를 출력해주는 함수의 주소
Returns			: 없음
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
Function name	: removeNode - data와 일치하는 첫 번째 노드 삭제
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 삭제할 데이터
				  dataFree - 데이터의 부가적인 메모리를 해제하는 함수의 주소
				  compareData - 두개의 데이터의 크기를 비교하는 함수의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
----------------------------------------------------------------------------------*/
BOOL removeNode(List *lp, void *data, void(*dataFree)(void *), int(*compareData)(void *, void *)) {
	if (lp == NULL)
		return FALSE;
	Node *sp = searchNode(lp, data, compareData);
	if (sp == NULL)
		return FALSE;
	sp->prev->next = sp->next;
	sp->next->prev = sp->prev;
	dataFree(sp + 1); // Data의 부가 Memory 해제
	free(sp); // Node + Data 해제
	--lp->size;

	return TRUE;
}

/*----------------------------------------------------------------------------------
Function name	: searchNode - data와 일치하는 첫 번째 node 검색
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 검색할 데이터
				  compareData - 두개의 데이터의 크기를 비교하는 함수의 주소
Returns			: 성공 - 검색된 노드의 주소 / 실패 - NULL pointer
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
Function name	: sortList - 노드 정렬(bubble sort)(오름차순)
Parameters		: lp - 리스트 관리 구조체의 주소
				  compareData - 두개의 데이터의 크기를 비교하는 함수의 주소
				  swapData - 두개의 데이터를 바꿔주는 함수의 주소
Returns			: 없음
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
Function name	: destroyList - 리스트 내의 모든 노드(head, tail 노드 포함)를 삭제
Parameters		: lp - 리스트 관리 구조체의 주소
				  dataFree - 데이터의 부가적인 메모리를 해제하는 함수의 주소
Returns			: 없음
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