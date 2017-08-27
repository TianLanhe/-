#ifndef MINIMUM_SPANNING_TREE_H
#define MINIMUM_SPANNING_TREE_H

#include "../graph_base.h"

Status MiniSpanTree_PRIM(Graph graph, int start);
//����ķ����ӵ�start���������������graph����С����������������ߡ���graph�в����ڱ��Ϊstart�Ķ��㣬����ERROR
//˵����������ӡ
int findparent(int *arr, int vertex);
//��³˹���������Ӻ�����������vertex�ĸ��ڵ㣬���������ĸ��ڵ㶼��ͬ�����ʾ�ṹ�ɻ�
Status MiniSpanTree_Kruskal(Graph graph);
//��³˹������������graph����С����������������ߡ�
//˵����������ӡ

#endif