#include "genericStack.h"
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------------
Function name	: createStack - 지정된 크기의 스택을 생성하는 함수
Parameters		: sPtr - 스택관리 구조체의 주소
				  size - 스택의 크기
				  dataSize - 스택에 저장할 데이터의 크기
Returns			: 성공 - TRUE / 실패 - FALSE
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

	return TRUE;  // 리턴값은 수정해주세요.
}
/*-----------------------------------------------------------------------------------
Function name	: isStackFull - 스택이 꽉 차있는지 검사
Parameters		: sPtr - 스택관리 구조체의 주소
Returns			: 스택이 꽉 차있으면 TRUE, 아니면 FALSE 리턴
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
Function name	: isStackEmpty - 스택이 완전히 비어있는지 검사
Parameters		: sp - 스택관리 구조체의 주소
Returns			: 스택이 완전히 비어있으면 TRUE, 아니면 FALSE 리턴
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
Function name	: push - 스택에 데이터 하나를 저장함
Parameters		: sp - 스택관리 구조체의 주소
				  inData - 스택에 저장할 데이터
				  dataSize - 스택에 저장할 데이터의 크기
				  datamemCpy - 데이터의 Memory를 복사하는 함수의 주소
Returns			: 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
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
Function name	: pop - 스택에서 데이터 하나를 꺼냄
Parameters		: sPtr - 스택관리 구조체의 주소
				  popData -  꺼낸 데이터를 저장할 기억공간의 주소
				  dataSize - 스택에 저장할 데이터의 크기
				  datamemCpy - 데이터의 Memory를 복사하는 함수의 주소
Returns			: 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
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
Function name	: printStack - 스택의 모든 데이터 출력(pop하면 나오는 순서대로 출력)
Parameters		: sPtr - 스택관리 구조체의 주소
				  dataSize - 스택에 저장할 데이터의 크기
				  dataPrint - 데이터의 Memory를 읽어서 출력하는 함수의 주소
Returns			: 없음
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
Function name	: destroyStack -  스택 소멸 함수
Parameters		: sPtr - 스택관리 구조체의 주소
				  dataSize - 스택에 저장할 데이터의 크기
				  dataFree - 데이터의 Memory를 초기화하는 함수의 주소
Returns			: 없음
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