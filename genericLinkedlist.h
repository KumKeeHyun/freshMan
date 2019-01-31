#pragma once
enum BOOL { FALSE, TRUE };

typedef struct node Node;
struct node {
	Node *next;
	Node *prev;
};

typedef struct list {
	Node *head;
	Node *tail;
	int size;
}List;

BOOL createList(List *lp);
/* 연결 리스트 초기화 */
BOOL addFirst(List *lp, void *data, size_t dataSize, void(*memCpy)(void *, void*));
/* head node 뒤에 node 추가(역순 저장) */
BOOL addLast(List *lp, void *data, size_t dataSize, void(*memCpy)(void *, void*));
/* tail node 앞에 node 추가(정순 저장) */
void displayList(List *lp, void(*dataPrint)(void *));
/* 리스트 내의 모든 데이터 출력 */
BOOL removeNode(List *lp, void *data, void(*dataFree)(void *), int(*compareData)(void *, void *));
/* data 노드 삭제 */
Node* searchNode(List *lp, void *data, int(*compareData)(void *, void *));
/* data와 일치하는 node 검색 */
void sortList(List *lp, int(*compareData)(void *, void *), void(*swapData)(void *, void *));
/* 노드 정렬 - 오름차순
 * sortList를 정상적으로 쓰려면 Linkedlist의 size가 int의 최대값보다 작아야함.
 */
void destroyList(List *lp, void(*dataFree)(void *));
/* 리스트 내의 모든 노드를 삭제 */

/*
 * 다음과 같은 보조함수 정의 필요
 * void dataMemCpy(void *vp1, void *vp2) - vp1에 vp2의 Memory를 Deep copy하는 함수
 * void dataPrint(void *vp) - vp의 Memory를 출력하는 함수
 * int dataCompare(void *vp1, void *vp2) - vp1이 크면 1, 같으면 0, 작으면 -1 return하는 함수
 * void dataSwap(void *vp1, void *vp2) - vp1과 vp2의 메모리를 Swap하는 함수
 * void dataFree(void *vp) - Data의 부가 Memory해제하는 함수, Data를 해제 X
 */