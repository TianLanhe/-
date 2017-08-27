#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "../graph_base.h"

Status DijShortPath(Graph graph, int v, int path[][MAXVEX + 1], int *dist);
//����Dijkstra�㷨��ͼgraph��v���㵽��������ľ���(���������Ϊ0���޷��������ΪMAXINT)
//path[w][...]�洢��v��w�����·��������path[w][0]��ʾ���·���Ķ������(����������յ�)��������n��Ԫ��Ϊ���㡣dist[w]��ʾ����v��w�ľ���
Status FloShortPath(Graph graph, int path[MAXVEX][MAXVEX][MAXVEX + 1], int dist[MAXVEX][MAXVEX]);
//����Floyd�㷨��ͼgraph��ÿ�����㵽���ඥ��ľ���(���������Ϊ0���޷��������ΪMAXINT)
//path[v][w][...]�洢��v��w�����·��������path[v][w][0]��ʾ���·���Ķ������(����������յ�)��������n��Ԫ��Ϊ���㡣dist[v][w]��ʾ����v��w�ľ���

#endif
