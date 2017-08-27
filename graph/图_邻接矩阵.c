#include "matrix_graph.h"
#include "../tree/ChildBroLinkTree.h"
#include <stdlib.h>
#include <stdio.h>

Status TopologicalSort(MGraph oldgraph, int toposequ[]);
//������ͼ(��)oldgraph���޻�·����oldgraph��һ���������б�����toposequ�в�����OK����oldgraph������ͼ(��)���л�������ERROR
Status TopologicalOrder(MGraph graph, int toposequ[], int etv[]);
//������ͼ(��)���������кͶ������翪ʼʱ�䣬��ͼ��������ģ����ߴ��ڻ����򷵻�ERROR
Status CriticalPath(MGraph graph);
//��ͼ(��)�Ĺؼ�·�����������ͼ��������ģ����ߴ��ڻ��򷵻�ERROR
Status CopyGraph(MGraph *newgraph, MGraph oldgraph);
//����(��¡)oldgraph��newgraph��
Status hasLoop_un_sub(MGraph graph, int start, int visit[]);
//�ݹ���������ͼ(��)graph,��ͼ�д��ڻ�·������ERROR�����򷵻�OK
Status hasLoop_un(MGraph graph);
//������ͼ(��)graph���޻�·���򷵻�false���л�·����true����������ͼ(��)������ERROR��
Status hasLoop(MGraph graph);
//�ж�ͼ���Ƿ���ڣ��з���true�����򷵻�false

Status TopologicalOrder(MGraph graph, int toposequ[], int etv[]) {
	int stack[MAXVEX];
	int top;
	int inarc[MAXVEX];
	int top_toposequ;
	int i, j;
	int topvex;
	int count;
	if (graph.kind == UDN || graph.kind == UDG)return ERROR;	//���������ͼ���޷���������
	if (toposequ == NULL || etv == NULL || graph.vexnum == 0)return ERROR;	//�жϲ����Ϸ���
	top = -1;						//��ʼ��ջ��
	top_toposequ = -1;			//��ʼ��ջ��
	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;
		etv[i] = 0;				//�¼�(����)���緢��ʱ��
	}
	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] != MAXINT) {
				inarc[j]++;					//ͳ�Ƹ�����������
			}
		}
	}
	for (i = 0; i < graph.vexnum; i++) {			//ѭ��һ�飬�����Ϊ0�Ķ�����ջ
		if (inarc[i] == 0) {
			top++;
			stack[top] = i;
		}
	}
	count = 0;								//ͳ�ƶ�����������������������ж����������
	while (top != -1) {						//ͼ�Ķ�����������ʾ���ڻ�·��Ӧ����ERROR
		topvex = stack[top];
		count++;					//ջ��Ԫ�س�ջ������toposequ�У�
		top--;
		top_toposequ++;
		toposequ[top_toposequ] = topvex;	//Ѱ����topvexΪβ�ıߣ�Ȼ��ɾ���յ�����
		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			inarc[i]--;
			if (inarc[i] == 0) {
				top++;
				stack[top] = i;
			}
			if (etv[i] < etv[topvex] + graph.arcs[topvex][i])
				etv[i] = etv[topvex] + graph.arcs[topvex][i];
		}
	}
	if (count != graph.vexnum)return ERROR;	//���ڻ�·
	else return OK;
}
Status CriticalPath(MGraph graph) {
	int etv[MAXVEX];			//�������緢��ʱ��
	int ltv[MAXVEX];			//����������ʱ��
	int ete, lte;				//�����緢��ʱ�䣬��������ʱ��
	int toposequ[MAXVEX];		//��������
	int top, topvex;
	int i, j;							//�����������򲢼��㶥�����緢��ʱ��
	if (TopologicalOrder(graph, toposequ, etv) == ERROR)return ERROR;
	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)ltv[i] = etv[top];
	while (top != -1) {			//���������д�β��ʼ������㶥��������ʱ��
		topvex = toposequ[top];
		top--;
		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			if (ltv[topvex] > ltv[i] - graph.arcs[topvex][i])	//���¶���������ʱ��
				ltv[topvex] = ltv[i] - graph.arcs[topvex][i];
		}
	}
	for (i = 0; i < graph.vexnum; i++) {			//���������ݶ����ʱ�����ÿ���ߵ����緢��ʱ����������ʱ��
		for (j = FirstAdjVex(graph, i); j >= 0; j = NextAdjVex(graph, i, j)) {//����ȣ���֤�����ǹؼ���
			ete = etv[i];
			lte = ltv[j] - graph.arcs[i][j];
			if (ete == lte) {
				printf("<%d,%d>  ", i, j);
			}
		}
	}
	printf("\n");
	return OK;
}
Status hasLoop_un(MGraph graph) {
	int visit[MAXVEX];
	int i;
	if (graph.kind == DG || graph.kind == DN)return ERROR;
	for (i = 0; i < graph.vexnum; i++)visit[i] = false;
	for (i = 0; i < graph.vexnum; i++)
		if (visit[i] == false)
			if (hasLoop_un_sub(graph, i, visit) == ERROR)
				return true;
	return false;
}
Status hasLoop_un_sub(MGraph graph, int start, int visit[]) {
	int nextvex;
	if (visit[start] == true)return ERROR;
	visit[start] = true;
	for (nextvex = FirstAdjVex(graph, start); nextvex >= 0; nextvex = NextAdjVex(graph, start, nextvex)) {
		if (DeleteArc(&graph, start, nextvex) == ERROR)return ERROR;	//��������Ǹ�����ɾ�������赣��Ӱ�쵽ʵ��
		if (hasLoop_un_sub(graph, nextvex, visit) == ERROR)return ERROR;
	}
	return OK;
}
Status hasLoop(MGraph graph) {
	int toposequ[MAXVEX];
	if (graph.kind == DG || graph.kind == DN)			//����ͼ(��)�����������ж��Ƿ��л�·
		return TopologicalSort(graph, toposequ) == ERROR ? true : false;
	else												//����ͼ(��)������ȱ����ж��Ƿ��л�·
		return hasLoop_un(graph);
}
Status CopyGraph(MGraph *newgraph, MGraph oldgraph) {
	int i, j;
	if (newgraph == NULL)return ERROR;
	newgraph->kind = oldgraph.kind;
	newgraph->vexnum = oldgraph.vexnum;
	newgraph->arcnum = oldgraph.arcnum;
	for (i = 0; i < oldgraph.vexnum; i++) {
		for (j = 0; j < oldgraph.vexnum; j++) {
			newgraph->arcs[i][j] = oldgraph.arcs[i][j];
		}
	}
	return OK;
}
Status TopologicalSort(MGraph oldgraph, int toposequ[]) {
	int count;
	int column, row;
	int flag;
	int visit[MAXVEX];					//��������ֻ�������ͼ
	MGraph graph;						//���������ͼ������ERROR
	if (oldgraph.kind == UDG || oldgraph.kind == UDN)return ERROR;
	if (toposequ == NULL)return ERROR;
	CopyGraph(&graph, oldgraph);			//����ѡ��һ�������Ҫɾ��������㼰������ıߣ�������ƻ��Ե�
	count = 0;							//��copy��һ���µ���ʱͼ���������ɲο��ڽӱ�洢�ṹ��ͼ����һ���ָ��õķ���
	for (row = 0; row < graph.vexnum; row++)visit[row] = false;
	while (count < graph.vexnum) {
		for (column = 0; column < graph.vexnum; column++) {	//��ͷ��ʼ������������һ��û���ʹ��������Ϊ0�Ķ���
			flag = true;
			for (row = 0; row < graph.vexnum; row++) {
				if (visit[column] == true || graph.arcs[row][column] != MAXINT)
					flag = false;
			}
			if (flag == true) {						//���ҵ��ˣ�������visit�ѷ��ʣ�������������
				visit[column] = true;
				toposequ[count] = column;
				count++;
				for (row = 0; row < graph.vexnum; row++) {
					graph.arcs[column][row] = MAXINT;	//����ö�������ı�ȫ��ȥ��
				}
				break;								//����ѭ�����¿�ʼ��ͷ����
			}
		}											//�������һȦ��û���ҵ����Ϊ0�Ķ���
		if (flag == false && count < graph.vexnum) {
			DestroyGraph(&graph);
			return ERROR;							//Ҫô���ж��㶼���ʹ��ˣ�Ҫô�޷��ҵ���������
		}
	}
	DestroyGraph(&graph);							//�ǵ�ʹ��������ٿ�¡��ͼ������ʵ��û���漰����̬����
	return OK;										//���ᷢ���ڴ�й©���������ٶ�����ν��
}

int main() {
	MGraph graph;
	int etv[MAXVEX];
	int toposequ[MAXVEX];
	int i, j;
	if (CreateGraph(&graph) == ERROR)return ERROR;
	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("��");
			else printf("%2d", graph.arcs[i][j]);
		}
		printf("\n");
	}
	int path[MAXVEX][MAXVEX + 1];
	int dist[MAXVEX];
	if (DijShortPath(graph, 1, path, dist) == ERROR)return 1;
	for (i = 0; i < graph.vexnum; ++i) {
		for (j = 1; j <= path[i][0]; ++j) {
			printf("%d ", path[i][j]);
		}
		printf("dist:%d\n", dist[i]);
	}
	// CriticalPath(graph);
	return 0;
}
