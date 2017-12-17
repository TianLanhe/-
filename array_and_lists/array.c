#include "Array.h"
#include <stdlib.h>
#include <stdarg.h>

Status InitArray(Array *arr, int dim, ...) {	//dim��ʾά��������������dim����������ʾÿһά�ĳ���
	int i, elemnum;
	va_list ap;

	CHECK_ERROR(dim >= 1 && dim <= MAX_ARRAY_DIM);

	arr->dim = dim;
	arr->bounds = (int *)malloc(sizeof(int)*dim); //bounds�ǳ���Ϊdim�����飬��ÿһά�ȵĳ���
	CHECK_OVERFLOW(arr->bounds);

	arr->constants = (int *)malloc(sizeof(int)*dim);
	CHECK_OVERFLOW(arr->constants);

	va_start(ap, dim);
	for (i = 0, elemnum = 1; i < dim; i++) {
		arr->bounds[i] = va_arg(ap, int);
		CHECK_ERROR(arr->bounds[i] > 0);

		elemnum *= arr->bounds[i];			//�����ܸ�������ÿһά������ˣ��������
	}
	va_end(ap);

	arr->base = (ElemType *)calloc(elemnum, sizeof(ElemType));
	CHECK_OVERFLOW(arr->base);

	arr->constants[dim - 1] = 1;			//������ά��Ϊ3��ÿά����Ϊ[3][4][3]����constants����Ϊ3��Ԫ������Ϊ{4*3,3,1}
	for (i = dim - 2; i >= 0; i--)				//��ʾÿһά��Ȩ������ά��Խ12��Ԫ�أ��ڶ�ά��Խ3��ά�ȣ��Դ�����
		arr->constants[i] = arr->bounds[i + 1] * arr->constants[i + 1];

	return OK;
}

Status DestroyArray(Array *arr) {
	CHECK_ERROR(arr->base);
	free(arr->base);
	arr->base = NULL;

	CHECK_ERROR(arr->bounds);
	free(arr->bounds);
	arr->bounds = NULL;

	CHECK_ERROR(arr->constants);
	free(arr->constants);
	arr->constants = NULL;

	arr->dim = 0;
	return OK;
}

Status Value(Array arr, ElemType *e, ...) {
	int i;
	int bounds;
	ElemType *add;
	va_list ap;

	va_start(ap, e);						//��e֮��Ĳ�����ַ����ap��
	for (i = 0, add = arr.base; i < arr.dim; i++) {
		bounds = va_arg(ap, int);			//��ȡ��ÿά�ĳ���bounds�����жϺϷ���
		CHECK_ERROR(bounds >= 0 && bounds <= arr.bounds[i] - 1);

		add += arr.constants[i] * bounds;		//ȷ���Ǹ���ַ����[1][1][1]����add=1*12+1*3+1*1=16.
	}
	va_end(ap);

	*e = *add;
	return OK;
}

Status Assign(Array *arr, ElemType e, ...) {
	int i;
	int bounds;
	ElemType *add;
	va_list ap;

	va_start(ap, e);
	for (i = 0, add = arr->base; i < arr->dim; i++) {
		bounds = va_arg(ap, int);
		CHECK_ERROR(bounds >= 0 && bounds <= arr.bounds[i] - 1);
		add += arr->constants[i] * bounds;
	}
	va_end(ap);

	*add = e;
	return OK;
}
