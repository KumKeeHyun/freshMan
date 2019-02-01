#include "genericStack.h"
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------------
Function name	: createStack - ������ ũ���� ������ �����ϴ� �Լ�
Parameters		: sPtr - ���ð��� ����ü�� �ּ�
				  size - ������ ũ��
				  dataSize - ���ÿ� ������ �������� ũ��
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL createStack(Stack *sPtr, int size, size_t dataSize)
{
	if (sPtr == NULL) return FALSE;

	sPtr->stack = calloc(size, dataSize);
	if (sPtr->stack == NULL) {
		return FALSE;
	}
	sPtr->size = size;
	sPtr->top = 0;

	return TRUE;  // ���ϰ��� �������ּ���.
}
/*-----------------------------------------------------------------------------------
Function name	: isStackFull - ������ �� ���ִ��� �˻�
Parameters		: sPtr - ���ð��� ����ü�� �ּ�
Returns			: ������ �� �������� TRUE, �ƴϸ� FALSE ����
-----------------------------------------------------------------------------------*/
BOOL isStackFull(Stack *sPtr)
{
	if (sPtr == NULL) return FALSE;

	if (sPtr->top >= sPtr->size)
		return TRUE;
	else
		return FALSE;
}
/*-----------------------------------------------------------------------------------
Function name	: isStackEmpty - ������ ������ ����ִ��� �˻�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ������ ������ ��������� TRUE, �ƴϸ� FALSE ����
-----------------------------------------------------------------------------------*/
BOOL isStackEmpty(Stack *sPtr)
{
	if (sPtr == NULL) return FALSE;

	if (sPtr->top <= 0)
		return TRUE;
	else
		return FALSE;
}
/*--------------------------------------------------------------------------------------
Function name	: push - ���ÿ� ������ �ϳ��� ������
Parameters		: sp - ���ð��� ����ü�� �ּ�
				  inData - ���ÿ� ������ ������
				  dataSize - ���ÿ� ������ �������� ũ��
				  datamemCpy - �������� Memory�� �����ϴ� �Լ��� �ּ�
Returns			: ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL push(Stack *sPtr, void *inData, size_t dataSize, void(*dataMemCpy)(void *, void *))
{
	if (sPtr == NULL) return FALSE;

	if (!isStackFull(sPtr)) {
		dataMemCpy((char *)sPtr->stack + (sPtr->top++ * dataSize), inData);
		return TRUE;
	}
	else
		return FALSE;
}
/*--------------------------------------------------------------------------------------
Function name	: pop - ���ÿ��� ������ �ϳ��� ����
Parameters		: sPtr - ���ð��� ����ü�� �ּ�
				  popData -  ���� �����͸� ������ �������� �ּ�
				  dataSize - ���ÿ� ������ �������� ũ��
				  datamemCpy - �������� Memory�� �����ϴ� �Լ��� �ּ�
Returns			: ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL pop(Stack *sPtr, void *popData, size_t dataSize, void(*dataMemCpy)(void *, void *), void(*dataFree)(void *))
{
	if (sPtr == NULL) return FALSE;

	if (!isStackEmpty(sPtr)) {
		dataMemCpy(popData, (char *)sPtr->stack + (--sPtr->top * dataSize));
		dataFree((char *)sPtr->stack + (sPtr->top * dataSize));
		return TRUE;
	}
	else
		return FALSE;
}
/*--------------------------------------------------------------------------------------
Function name	: printStack - ������ ��� ������ ���(pop�ϸ� ������ ������� ���)
Parameters		: sPtr - ���ð��� ����ü�� �ּ�
				  dataSize - ���ÿ� ������ �������� ũ��
				  dataPrint - �������� Memory�� �о ����ϴ� �Լ��� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void printStack(const Stack*sPtr, size_t dataSize, void(*dataPrint)(void *))
{
	if (sPtr == NULL) return;

	for (int i = sPtr->top - 1; i >= 0; i--) {
		dataPrint((char *)sPtr->stack + i * dataSize);
	}
	return;
}
/*--------------------------------------------------------------------------------------
Function name	: destroyStack -  ���� �Ҹ� �Լ�
Parameters		: sPtr - ���ð��� ����ü�� �ּ�
				  dataSize - ���ÿ� ������ �������� ũ��
				  dataFree - �������� Memory�� �ʱ�ȭ�ϴ� �Լ��� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sPtr, size_t dataSize, void(*dataFree)(void *))
{
	if (sPtr == NULL) return;
	if (sPtr->stack == NULL) return;
	for (int i = 0; i < sPtr->size; i++) {
		dataFree((char *)sPtr->stack + i * dataSize);
	}
	free(sPtr->stack);
	sPtr->stack = NULL;
	sPtr->size = 0;
	sPtr->top = 0;

	return;
}