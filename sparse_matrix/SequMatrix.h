#ifndef MATRIX_SEQU_H
#define MATRIX_SEQU_H

#include "../DataStructureBase.h"

typedef struct _Element {
	int x;							//����Ԫ�ص���
	int y;							//����Ԫ�ص���
	double value;					//����Ԫ�ص�ֵ
}Element;

typedef struct _RLSMatrix {
	Element *data;					//�������Ԫ�ص�һά����
	int *rowpos;					//����ÿһ�е�һ������Ԫ����һλ�����λ��
	int row;						//���������
	int column;						//���������
	int num;						//�������Ԫ�صĸ���
}RLSMatrix;

Status SetMData(Element *data, int x, int y, double value);
//������Ԫ���ֵ��������������ֵ
Status CreatMatrix_Num(RLSMatrix *matrix);
//���ݷ���Ԫ�ظ�������ϡ�����
Status CreatMatrix_All(RLSMatrix *matrix);
//ֱ�������������Ԫ�ش���ϡ�����
Status SortMatrix(RLSMatrix *matrix);
//��ϡ�����matrix�ĳ�Աdata�еķ���Ԫ�ص����а���С�����˳������
Status InitMatrix(RLSMatrix *matrix);
//��ʼ��ϡ�����
Status DestroyMatrix(RLSMatrix *matrix);
//����ϡ�����
Status PrintMatrix(RLSMatrix matrix);
//��ӡϡ�����
Status isEqualMatrix(RLSMatrix matrix1, RLSMatrix matrix2);
//�ж����������Ƿ����
Status isSameMatrix(RLSMatrix matrix1, RLSMatrix matrix2);
//�ж����������Ƿ�����ͬһ������
Status CopyMatrix(RLSMatrix *result, RLSMatrix matrix);
//��ϡ�����matrix���Ƶõ�result
Status AddMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2);
//��ϡ�����ĺ�result=matrix1+matrix2
Status SubMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2);
//��ϡ�����Ĳ�result=matrix1-matrix2
Status ScalarMatrix(RLSMatrix *result, RLSMatrix matrix1, double num);
//��ϡ����������result=matrix1*num
Status MultMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2);
//��ϡ�����ĳ˻�result=matrix1*matrix2
Status TransMatrix(RLSMatrix *result, RLSMatrix matrix);
//��ϡ������ת��
Status PowMatrix(RLSMatrix *result, RLSMatrix matrix, int n);
//��ϡ�����matrix��n����result=matrix^n
Status minverse(double *value);
//���������Ĺ��ܺ�������ϡ������ÿ������Ԫ��ȡ��
Status MatrixTraverse(RLSMatrix *matrix, Status(*visit)(double*));
//���ζ�ϡ������ÿ������Ԫ�ص���visit()��һ������ʧ�ܣ������ʧ��
#endif
