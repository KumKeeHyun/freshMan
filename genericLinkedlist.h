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
/* ���� ����Ʈ �ʱ�ȭ */
BOOL addFirst(List *lp, void *data, size_t dataSize, void(*memCpy)(void *, void*));
/* head node �ڿ� node �߰�(���� ����) */
BOOL addLast(List *lp, void *data, size_t dataSize, void(*memCpy)(void *, void*));
/* tail node �տ� node �߰�(���� ����) */
void displayList(List *lp, void(*dataPrint)(void *));
/* ����Ʈ ���� ��� ������ ��� */
BOOL removeNode(List *lp, void *data, void(*dataFree)(void *), int(*compareData)(void *, void *));
/* data ��� ���� */
Node* searchNode(List *lp, void *data, int(*compareData)(void *, void *));
/* data�� ��ġ�ϴ� node �˻� */
void sortList(List *lp, int(*compareData)(void *, void *), void(*swapData)(void *, void *));
/* ��� ���� - ��������
 * sortList�� ���������� ������ Linkedlist�� size�� int�� �ִ밪���� �۾ƾ���.
 */
void destroyList(List *lp, void(*dataFree)(void *));
/* ����Ʈ ���� ��� ��带 ���� */

/*
 * ������ ���� �����Լ� ���� �ʿ�
 * void dataMemCpy(void *vp1, void *vp2) - vp1�� vp2�� Memory�� Deep copy�ϴ� �Լ�
 * void dataPrint(void *vp) - vp�� Memory�� ����ϴ� �Լ�
 * int dataCompare(void *vp1, void *vp2) - vp1�� ũ�� 1, ������ 0, ������ -1 return�ϴ� �Լ�
 * void dataSwap(void *vp1, void *vp2) - vp1�� vp2�� �޸𸮸� Swap�ϴ� �Լ�
 * void dataFree(void *vp) - Data�� �ΰ� Memory�����ϴ� �Լ�, Data�� ���� X
 */