#include <stdio.h>
#include <stdlib.h>
#include "../DataStructureBase.h"

Status TopologicalSort(ALGraph oldgraph, int toposequ[]);
//������ͼ(��)oldgraph���޻�·����oldgraph��һ���������б�����toposequ�в�����OK����oldgraph������ͼ(��)���л�������ERROR
Status TopologicalOrder(ALGraph graph, int toposequ[], int etv[]);
//������ͼ(��)���������кͶ������翪ʼʱ�䣬��ͼ��������ģ����ߴ��ڻ����򷵻�ERROR
Status CriticalPath(ALGraph graph);
//��ͼ(��)�Ĺؼ�·�����������ͼ��������ģ����ߴ��ڻ��򷵻�ERROR
Status CopyGraph(ALGraph *graph, ALGraph oldgraph);
//����(��¡)oldgraph��graph��
Status hasLoop_un_sub(ALGraph *graph, int start, int visit[]);
//�ݹ���������ͼ(��)graph,��ͼ�д��ڻ�·������ERROR�����򷵻�OK
//Ҫ���ƺ�ɾ�����бߣ����ұߵı������ҡ�Ч�ʲ��ߣ��д��Ľ�
Status hasLoop_un(ALGraph oldgraph);
//������ͼ(��)graph���޻�·���򷵻�false���л�·����true����������ͼ(��)������ERROR��
Status hasLoop(ALGraph graph);
//�ж�ͼ���Ƿ���ڣ��з���true�����򷵻�false

Status hasLoop_un_sub(ALGraph *graph, int start, int visit[]) {
	int nextvex;
	int index;
	if (visit[start] == true)return ERROR;
	visit[start] = true;
	while ((nextvex = FirstAdjVex(*graph, graph->vertices[start].vexno)) >= 0) {
		if (DeleteArc(graph, graph->vertices[start].vexno, nextvex) == ERROR)return ERROR;
		if ((index = LocateVex(*graph, nextvex)) == ERROR)return ERROR;
		if (hasLoop_un_sub(graph, index, visit) == ERROR)return ERROR;
	}
	return OK;
}
Status CopyGraph(ALGraph *graph, ALGraph oldgraph) {
	int i;
	int nextvex;
	ArcNode *node;
	if (graph == NULL || oldgraph.vexnum == 0)return ERROR;
	graph->vexnum = oldgraph.vexnum;
	graph->arcnum = oldgraph.arcnum;
	graph->kind = oldgraph.kind;
	for (i = 0; i < oldgraph.vexnum; i++) {
		graph->vertices[i].vexno = oldgraph.vertices[i].vexno;
		graph->vertices[i].firstarc = NULL;
	}
	for (i = 0; i < oldgraph.vexnum; i++) {
		for (node = oldgraph.vertices[i].firstarc; node; node = node->nextarc) {
			if (InsertArc(graph, graph->vertices[i].vexno, node->adjvex, node->weight) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status hasLoop_un(ALGraph oldgraph) {
	int visit[MAXVEX];
	int i;
	ALGraph graph;
	if (oldgraph.kind == DG || oldgraph.kind == DN)return ERROR;
	if (CopyGraph(&graph, oldgraph) == ERROR)return ERROR;	//�ڽӱ��в���ֱ���޸����ݣ���Ӱ��ԭͼ
	for (i = 0; i < graph.vexnum; i++)visit[i] = false;				//�ʸ�����һ��
	for (i = 0; i < graph.vexnum; i++) {
		if (visit[i] == false) {
			if (hasLoop_un_sub(&graph, i, visit) == ERROR) {
				DestroyGraph(&graph);
				return true;
			}
		}
	}
	DestroyGraph(&graph);
	return false;
}
Status hasLoop(ALGraph graph) {
	int toposequ[MAXVEX];
	if (graph.kind == DG || graph.kind == DN)
		return TopologicalSort(graph, toposequ) == ERROR ? true : false;
	else
		return hasLoop_un(graph);
}
Status TopologicalSort(ALGraph graph, int toposequ[]) {
	int inarc[MAXVEX];
	int i;
	int vertex;
	int index;
	int count;
	if (graph.kind == UDG || graph.kind == UDN)return ERROR;
	for (i = 0; i < graph.vexnum; i++)inarc[i] = 0;
	for (i = 0; i < graph.vexnum; i++) {
		for (vertex = FirstAdjVex(graph, graph.vertices[i].vexno); vertex >= 0; vertex = NextAdjVex(graph, graph.vertices[i].vexno, vertex)) {
			if ((index = LocateVex(graph, vertex)) == ERROR)return ERROR;
			inarc[index]++;
		}
	}
	count = 0;
	while (count < graph.vexnum) {
		for (i = 0; i < graph.vexnum; i++) {
			if (inarc[i] == 0) {
				toposequ[count] = graph.vertices[i].vexno;
				inarc[i] = -1;
				count++;
				for (vertex = FirstAdjVex(graph, graph.vertices[i].vexno); vertex >= 0; vertex = NextAdjVex(graph, graph.vertices[i].vexno, vertex)) {
					if ((index = LocateVex(graph, vertex)) == ERROR)return ERROR;
					inarc[index]--;
				}
				break;
			}
		}
		if (count < graph.vexnum && i == graph.vexnum)return ERROR;
	}
	for (i = 0; i < graph.vexnum; i++)printf("%3d", toposequ[i]);
	return OK;
}
Status TopologicalOrder(ALGraph graph, int toposequ[], int etv[]) {
	int count;
	int stack[MAXVEX];
	int top;
	int top_toposequ;
	int inarc[MAXVEX];
	int i, j, topvex;
	if (graph.vexnum == 0 || toposequ == NULL || etv == NULL)return ERROR;	//�жϲ����Ϸ���
	if (graph.kind == UDG || graph.kind == UDN)return ERROR;		//ֻ������Ĳ��ܽ�����������
	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;				//��ʼ���������
		etv[i] = 0;				//�Ͷ������翪ʼʱ��
	}
	for (i = 0; i < graph.vexnum; i++) {
		for (j = FirstAdjVex(graph, graph.vertices[i].vexno); j >= 0; j = NextAdjVex(graph, graph.vertices[i].vexno, j)) {
			if ((topvex = LocateVex(graph, j)) == ERROR)return ERROR;
			inarc[topvex]++;	//ͳ�Ƹ��������
		}
	}
	top = -1;
	for (i = 0; i < graph.vexnum; i++) {
		if (inarc[i] == 0) {
			top++;
			stack[top] = i;		//�����Ϊ0�Ķ����±���ջ��ע�����±���ջ
		}
	}
	top_toposequ = -1;
	count = 0;
	while (top != -1) {
		topvex = stack[top];
		top--;
		top_toposequ++;
		toposequ[top_toposequ] = topvex;	//�������±�������������
		count++;
		for (i = FirstAdjVex(graph, graph.vertices[topvex].vexno); i >= 0; i = NextAdjVex(graph, graph.vertices[topvex].vexno, i)) {
			if ((j = LocateVex(graph, i)) == ERROR)return ERROR;
			inarc[j]--;
			if (inarc[j] == 0) {
				top++;
				stack[top] = j;
			}
			if (etv[j] < etv[topvex] + Distance(graph, graph.vertices[topvex].vexno, i))
				etv[j] = etv[topvex] + Distance(graph, graph.vertices[topvex].vexno, i);
		}
	}
	if (count < graph.vexnum)return ERROR;	//���ڻ�·
	else return OK;
}
Status CriticalPath(ALGraph graph) {
	int etv[MAXVEX];
	int ltv[MAXVEX];
	int toposequ[MAXVEX];
	int ete, lte;
	int i, j, topvex;
	int top;
	if (TopologicalOrder(graph, toposequ, etv) == ERROR)return ERROR;
	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)ltv[i] = etv[top];
	while (top != -1) {
		topvex = toposequ[top];
		top--;
		for (i = FirstAdjVex(graph, graph.vertices[topvex].vexno); i >= 0; i = NextAdjVex(graph, graph.vertices[topvex].vexno, i)) {
			if ((j = LocateVex(graph, i)) == ERROR)return ERROR;
			if (ltv[topvex] > ltv[j] - Distance(graph, graph.vertices[topvex].vexno, i))
				ltv[topvex] = ltv[j] - Distance(graph, graph.vertices[topvex].vexno, i);
		}
	}
	for (i = 0; i < graph.vexnum; i++) {
		for (j = FirstAdjVex(graph, graph.vertices[i].vexno); j >= 0; j = NextAdjVex(graph, graph.vertices[i].vexno, j)) {
			if ((topvex = LocateVex(graph, j)) == ERROR)return ERROR;
			ete = etv[i];
			lte = ltv[topvex] - Distance(graph, graph.vertices[i].vexno, j);
			if (ete == lte) {
				printf("<%d,%d>  ", graph.vertices[i].vexno, j);
			}
		}
	}
	printf("\n");
	return OK;
}

int main() {
	ALGraph graph;
	int i, j;
	ArcNode *temp;
	if (CreateGraph(&graph) == ERROR)printf("error!\n");
	/*for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}
	if (CriticalPath(graph) == ERROR)return ERROR;*/
	return 0;
}
