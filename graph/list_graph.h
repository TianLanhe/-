#ifndef LIST_GRAPG_H
#define LIST_GRAPG_H

#define Graph ALGraph
#define GraphVertex VNode

typedef struct _algraph ALGraph;
typedef struct _vnode VNode;

#include "graph_base.h"

typedef struct _arcnode {
	int adjvex;					//�û�ָ��Ķ����λ��
	int weight;					//Ȩ(�涨ֻ����Ȩ)
	struct _arcnode *nextarc;	//ָ����һ����
}ArcNode;

typedef struct _vnode {
	int vexno;					//�������(���)
	ArcNode *firstarc;			//ָ���һ����
}VNode;

typedef struct _algraph {
	int vexnum;					//ͼ�ĵ�ǰ������
	int arcnum;					//ͼ�ĵ�ǰ�������
	VNode vertices[MAXVEX];		//ͼ�Ķ����ڽӱ�(˳��洢)
	GraphKind kind;				//ͼ������
}ALGraph;

#endif