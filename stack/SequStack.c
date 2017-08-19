#include <stdio.h>
#include <stdlib.h>
#include "SequStack.h"

Status InitStack(SqStack *stack) {
	if (!stack)
		return ERROR;
	stack->base = (SElemType*)malloc(sizeof(SElemType)*INITSIZE);
	if (!stack->base)
		return OVERFLOW;
	stack->top = stack->base;
	stack->capacity = INITSIZE;
	return OK;
}
Status DestroyStack(SqStack *stack) {
	if (!stack)
		return ERROR;
	free(stack->base);
	stack->base = stack->top = NULL;
	stack->capacity = 0;
	return OK;
}
Status ClearStack(SqStack *stack){
	if(!stack)
		return ERROR;
	stack->top = stack->base;
	return OK;
}
Status StackEmpty(SqStack stack) {
	return stack.top == stack.base ? true : false;
}
int StackLength(SqStack stack) {
	return stack.top - stack.base;
}
Status GetTop(SqStack stack, SElemType *e) {
	if (StackEmpty(stack))		//��ջ�򷵻�ERROR
		return ERROR;
	*e = *(stack.top - 1);
	return OK;
}
Status Pop(SqStack *stack, SElemType *e) {
	if (GetTop(*stack, e) == ERROR)
		return ERROR;
	--stack->top;
	return OK;
}
Status Push(SqStack *stack, SElemType e) {
	if (StackLength(*stack) == stack->capacity) {	//ջ������չ
		stack->base = (SElemType*)realloc(stack->base, sizeof(SElemType)*(INCREMENT + stack->capacity));
		if (!stack->base)
			return OVERFLOW;
		stack->top = stack->base + stack->capacity;
		stack->capacity += INCREMENT;
	}
	*stack->top = e;
	stack->top++;
	return OK;
}
Status StackTraverse(SqStack stack, Status(*visit)(SElemType)) {
	SElemType *ptr;
	if (StackEmpty(stack))return ERROR;		//��ջ�򷵻�ERROR	
	for (ptr = stack.base; ptr < stack.top; ++ptr)	//��ջ�׵�ջ�����α���ÿ��Ԫ��
		if (visit(*ptr) == ERROR)
			return ERROR;
	return OK;
}
