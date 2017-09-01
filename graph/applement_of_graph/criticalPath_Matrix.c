#include "../matrix_graph.h"
#include "criticalPath.h"

Status TopologicalOrder(MGraph graph, int toposequ[MAXVEX], int etv[MAXVEX]) {
	int queue[MAXVEX];
	int top, bottom;
	int inarc[MAXVEX];
	int i, j;
	int topvex;
	int count;

	if (graph.kind == UDG || graph.kind == UDN)
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;
	if (!toposequ || !etv)
		return ERROR;

	top = bottom = 0;						//��ʼ������
	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;
		etv[i] = 0;							//�¼�(����)���緢��ʱ��
	}

	for (i = 0; i < graph.vexnum; i++)
		for (j = 0; j < graph.vexnum; j++)
			if (graph.arcs[i][j] != MAXINT)
				inarc[j]++;					//ͳ�Ƹ�����������

	for (i = 0; i < graph.vexnum; i++)		//ѭ��һ�飬�����Ϊ0�Ķ�����ջ
		if (inarc[i] == 0)
			queue[bottom++] = i;

	count = 0;								//ͳ�ƶ�����������������������ж����������
	while (top != bottom) {					//ͼ�Ķ�����������ʾ���ڻ�·��Ӧ����ERROR
		topvex = queue[top++];
		toposequ[count++] = topvex;			//Ѱ����topvexΪβ�ıߣ�Ȼ��ɾ���յ�����

		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			inarc[i]--;
			if (inarc[i] == 0)
				queue[bottom++] = i;

			if (etv[i] < etv[topvex] + graph.arcs[topvex][i])
				etv[i] = etv[topvex] + graph.arcs[topvex][i];
		}
	}

	if (count != graph.vexnum)	//���ڻ�·
		return ERROR;
	return OK;
}

Status CriticalPath(MGraph graph, int criticalVex[MAXVEX + 1], Edge criticalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1]) {
	int etv[MAXVEX];			//�������緢��ʱ��
	int ltv[MAXVEX];			//����������ʱ��
	int ete, lte;				//�����緢��ʱ�䣬��������ʱ��
	int toposequ[MAXVEX];		//��������
	int top, topvex;			//topģ��ջ����topvex��ʾȡ����ջ��Ԫ��
	int i, j;

	if (TopologicalOrder(graph, toposequ, etv) == ERROR)	//�����������򲢼��㶥�����緢��ʱ��
		return ERROR;

	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)
		ltv[i] = etv[top];

	while (top != -1) {			//���������д�β��ʼ������㶥��������ʱ��
		topvex = toposequ[top--];

		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			if (ltv[topvex] > ltv[i] - graph.arcs[topvex][i])	//���¶���������ʱ��
				ltv[topvex] = ltv[i] - graph.arcs[topvex][i];
		}
	}

	criticalVex[0] = 0;
	criticalEdge[0].start = criticalEdge[0].end = 0;
	for (i = 0; i < graph.vexnum; i++) {	//���������ݶ����ʱ�����ÿ���ߵ����緢��ʱ����������ʱ��
		for (j = FirstAdjVex(graph, i); j >= 0; j = NextAdjVex(graph, i, j)) {	//����ȣ���֤�����ǹؼ���
			ete = etv[i];
			lte = ltv[j] - graph.arcs[i][j];
			if (ete == lte) {
				++criticalEdge[0].start;
				++criticalEdge[0].end;
				criticalEdge[criticalEdge[0].start].start = graph.vexs[i];
				criticalEdge[criticalEdge[0].end].end = graph.vexs[j];
			}
		}

		if (etv[i] == ltv[i]) {	//���ݶ�������ʱ�������ʱ���ж��Ƿ��ǹؼ�����
			++criticalVex[0];
			criticalVex[criticalVex[0]] = graph.vexs[i];
		}
	}
	return OK;
}

int main() {
	MGraph graph;
	int criticalVex[MAXVEX + 1];
	Edge critivalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1];
	int i, j;

	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("��");
			else printf("%2d", graph.arcs[i][j]);
		}
		printf("\n");
	}

	if (CriticalPath(graph, criticalVex, critivalEdge) != OK)return 1;

	for (i = 1; i <= criticalVex[0]; ++i)
		printf("%d ", criticalVex[i]);
	printf("\n");

	for (i = 1; i <= critivalEdge[0].start; ++i)
		printf("<%d,%d> ", critivalEdge[i].start, critivalEdge[i].end);
	printf("\n");
	return 0;
}
