#ifndef SORTING_H
#define SORTING_H

void creatarr(int **a, int n, int ran);
//��ʼ����̬����,Ϊa���䳤Ϊn�����֣����ݴ�С������[0,ran)��
//������int *a;
//      creatarr(&a,100,1000)   ����100��������0��1000�Ķ�̬����
void display(int a[], int n);
//��ӡ���������
void SelectSort(int a[], int n);
//ѡ������
void BubbleSort(int a[], int n);
//ð������
void InsertSort(int a[], int n);
//��������
void BinInsertSort(int a[], int n);
//�۰��������
void ShellSort(int a[], int n);
//ϣ������
void QuickSort_sub(int a[], int start, int end);
//����������ӹ���
void QuickSort(int a[], int length);
//�������򣬷�װ�˿����������ʵ�ֵ��ӹ��̣�ֻ��Ҫ�ṩ���ȼ���
void MergeSort_sub(int a[], int start, int end, int *p);
//�鲢������ӹ���
void MergeSort(int a[], int length);
//�鲢���򣬷�װ�˹鲢�������ʵ�ֵ��ӹ��̣�Ϊ�����븨���ռ�p�������ӹ��̺��ͷţ�ֻ��Ҫ�ṩ���ȼ���
void HeapSort_sub(int a[], int start, int length);
//��������ӹ��̣�����[start,length)�г�start�������ѵĶ��壬����start��λ��ʹ��Ϊһ����
void HeapSort(int a[], int length);
//�������Ƚ�����ʼ�ѣ���ѭ���������Ѷ�Ԫ���Ƶ�ĩβ��������Ԫ�ص�����Ϊ�¶�

#endif
