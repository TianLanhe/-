#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define ERROR 0
#define OK 1
#define Status int
#define MAX_ARRAY_DIM 8
typedef int ElemType;
typedef struct {
	ElemType *base;					//����Ԫ���׵�ַ
	int dim;						//����ά��
	int *bounds;					//����ά���׵�ַ�����䳤��Ϊdim�����飬ÿ��Ԫ��Ϊÿһλά�ȵĳ���
	int *constants;					//����ӳ���������׵�ַ
}Array;
Status InitArray(Array *arr,int dim,...);
//��ά��dim�����ĸ�ά���ȺϷ���������Ӧ������arr��������OK
Status DestroyArray(Array *arr);
//��������arr
Status Value(Array arr,ElemType *e,...);
//arr��nά���飬eΪԪ�ر����������n���±�ֵ�������±겻Խ�磬��e��ֵΪ��ָ����arr��Ԫ��ֵ��������OK
Status Assign(Array *arr,ElemType e,...);
//arr��nά���飬eΪԪ�ر����������n���±�ֵ�������±겻Խ�磬��e��ֵ������ָ����arr��Ԫ�أ�������OK
Status InitArray(Array *arr,int dim,...){	//dim��ʾά��������������dim����������ʾÿһά�ĳ���
	int i,elemnum;
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM)return ERROR;
	arr->dim=dim;
	arr->bounds=(int *)malloc(sizeof(int)*dim); //bounds�ǳ���Ϊdim�����飬��ÿһά�ȵĳ���
	if(!arr->bounds)return ERROR;
	arr->constants=(int *)malloc(sizeof(int)*dim);
	if(!arr->constants)return ERROR;
	va_start(ap,dim);
	for(i=0,elemnum=1;i<dim;i++){
		arr->bounds[i]=va_arg(ap,int);
		elemnum*=arr->bounds[i];			//�����ܸ�������ÿһά������ˣ��������
	}
	va_end(ap);
	arr->base=(ElemType *)calloc(elemnum,sizeof(ElemType));
	if(!arr->base)return ERROR;
	arr->constants[dim-1]=1;			//������ά��Ϊ3��ÿά����Ϊ[3][4][3]����constants����Ϊ3��Ԫ������Ϊ{4*3,3,1}
	for(i=dim-2;i>=0;i--)arr->constants[i]=arr->bounds[i+1]*arr->constants[i+1];//��ʾÿһά��Ȩ������ά��Խ12��Ԫ�أ��ڶ�ά��Խ3��ά�ȣ��Դ�����
	return OK;
}
Status DestroyArray(Array *arr){
	if(!arr->base)return ERROR;
	free(arr->base);
	arr->base=NULL;
	if(!arr->bounds)return ERROR;
	free(arr->bounds);
	arr->bounds=NULL;
	if(!arr->constants)return ERROR;
	free(arr->constants);
	arr->constants=NULL;
	arr->dim=0;
	return OK;
}
Status Value(Array arr,ElemType *e,...){
	int i;
	int bounds;
	ElemType *add;
	va_list ap;
	va_start(ap,e);						//��e֮��Ĳ�����ַ����ap��
	for(i=0,add=arr.base;i<arr.dim;i++){
		bounds=va_arg(ap,int);			//��ȡ��ÿά�ĳ���bounds�����жϺϷ���
		if(bounds<0||bounds>arr.bounds[i]-1)return ERROR;
		add+=arr.constants[i]*bounds;		//ȷ���Ǹ���ַ����[1][1][1]����add=1*12+1*3+1*1=16.
	}
	va_end(ap);
	*e=*add;
	return OK;
}
Status Assign(Array *arr,ElemType e,...){
	int i;
	int bounds;
	ElemType *add;
	va_list ap;
	va_start(ap,e);
	for(i=0,add=arr->base;i<arr->dim;i++){
		bounds=va_arg(ap,int);
		if(bounds<0||bounds>arr->bounds[i]-1)return ERROR;
		add+=arr->constants[i]*bounds;
	}
	va_end(ap);
	*add=e;
	return OK;
}
int main(){
	Array arr;
	InitArray(&arr,3,4,3,2);
	printf("%d\n",*(arr.base+9));
	if(!Assign(&arr,15,1,3,1))printf("yes\n");;
	printf("%d\n",*(arr.base+9));
	printf("%d %d %d\n",arr.bounds[0],arr.bounds[1],arr.bounds[2]);

	return 0;
}
