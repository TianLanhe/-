#include "../matrix_graph.h"
#include "depthFirstSpanningTree.h"
#include <stdlib.h>
#include <stdio.h>

Status DFSForest(MGraph graph, CSTNode **root) {
	int i;
	int visit[MAXVEX];
	CSTNode *node, *pre;
	Status status;

	for (i = 0; i < graph.vexnum; i++)
		visit[i] = false;

	*root = NULL;
	for (i = 0; i < graph.vexnum; i++) {
		if (visit[i] == false) {
			visit[i] = true;

			node = (CSTNode*)malloc(sizeof(CSTNode));
			if (!node)
				return OVERFLOW;

			node->firstchild = NULL;
			node->nextsibling = NULL;
			node->data = graph.vexs[i];

			if (*root == NULL)
				*root = node;
			else
				pre->nextsibling = node;
			pre = node;

			if ((status = DFSTree(graph, i, node, visit)) != OK)
				return status;
		}
	}
	return OK;
}

Status DFSTree(MGraph graph, int index, CSTNode *root, int visit[]) {
	CSTNode *node, *pre;
	int nextvex;
	int first;
	Status status;

	first = true;			//������ȱ���root��ÿһ���ڽӶ��㣬����������
	for (nextvex = FirstAdjVex(graph, index); nextvex >= 0; nextvex = NextAdjVex(graph, index, nextvex)) {
		if (visit[nextvex] == false) {				//���û���ʹ����򽫴˶������ӵ�root�ϲ��ݹ鹹������
			visit[nextvex] = true;

			node = (CSTNode*)malloc(sizeof(CSTNode));
			if (!node)
				return OVERFLOW;

			node->firstchild = NULL;
			node->nextsibling = NULL;
			node->data = graph.vexs[nextvex];

			if (first) {
				root->firstchild = node;
				first = false;						//�����ֵ�������һ���������Ÿ��ף��ڶ����������ŵ�һ������
			}
			else {
				pre->nextsibling = node;
			}
			pre = node;

			if ((status = DFSTree(graph, nextvex, node, visit)) != OK)
				return status;
		}
	}
	return OK;
}

int main() {
	MGraph graph;
	CSTNode *root;
	int i, j;
	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("��");
			else printf("%2d", graph.arcs[i][j]);
		}
		printf("\n");
	}

	if (DFSForest(graph, &root) != OK)return 1;
	PreOrderTraverseCSForest(root, PrintCSTree);
	InOrderTraverseCSForest(root, PrintCSTree);

	DestroyCSForest(&root);
	return 0;
}
