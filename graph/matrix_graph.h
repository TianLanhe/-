#ifndef MATRIX_GRAPG_H
#define MATRIX_GRAPG_H

#define Graph MGraph
#define GraphVertex VertexType
#define VertexType int

typedef struct _mgraph MGraph;

#include "graph_base.h"

typedef struct _mgraph {
	VertexType vexs[MAXVEX];			//��������
	int vexnum;							//ͼ�ĵ�ǰ������
	int arcnum;							//ͼ�ĵ�ǰ����
	int arcs[MAXVEX][MAXVEX];			//ͼ�Ķ����ڽӾ���
	GraphKind kind;						//ͼ������
}MGraph;

#endif