#pragma once
enum BOOL { FALSE, TRUE };

typedef struct _stack {
	void *stack;		/* stack���� ���Ǵ� �����Ҵ� �迭�� ����Ű�� ������ ���� */
	int size;		/* ������ ũ��(size) */
	int top;		/* ������ ��,�ⱸ ��ġ���� ���� */
}Stack;

BOOL createStack(Stack *sPtr, int size, size_t dataSize);		/* ���� �޸� �Ҵ� �� ��� �ʱ�ȭ �Լ� */
BOOL isStackFull(Stack *sPtr);		/* ������ �� ���ִ��� �˻� */
BOOL isStackEmpty(Stack *sPtr);		/* ������ ������ ����ִ°� �˻� */
BOOL push(Stack *sPtr, void *inData, size_t dataSize, void(*dataMemCpy)(void *, void *));			/* ���ÿ� ������ �����ϴ� �Լ� */
BOOL pop(Stack *sPtr, void *popData, size_t dataSize, void(*dataMemCpy)(void *, void *), void(*dataFree)(void *));			/* ���ÿ��� �����͸� ������ �Լ� */
void printStack(const Stack*sPtr, size_t dataSize, void(*dataPrint)(void *));		/* ���� ���� ��� �����͸� ����ϴ� �Լ� */
void destroyStack(Stack *sPtr, size_t dataSize, void(*dataFree)(void *));			/* ���� �޸� ���� �Լ� */
