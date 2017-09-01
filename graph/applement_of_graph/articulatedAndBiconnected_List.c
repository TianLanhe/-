#include "../list_graph.h"
#include "articulatedAndBiconnected.h"
#include <stdio.h>

Status FindArticul(ALGraph graph, int articulated[MAXVEX + 1]) {
	int visited_sequ[MAXVEX];		//�����ʵ����к�
	int vex_can_arrived[MAXVEX];	//�ܵ�������类���ʵ����к�
	int index, i;
	int count;

	if (graph.vexnum < 2)
		return ERROR;
	if (!articulated)
		return ERROR;

	articulated[0] = 0;
	count = 0;
	for (i = 0; i < graph.vexnum; ++i)		//�������г�ʼ��
		visited_sequ[i] = -1;

	for (i = 0; i < graph.vexnum; ++i) {
		if (visited_sequ[i] == -1) {
			visited_sequ[i] = count;
			++count;

			if ((index = FirstAdjVex(graph, i)) == -1)	//���ܴ��ڶ�Ϊ0�ĵ�(��������һ����ͨ����)
				return ERROR;

			// �Ը���һ���������б������ҳ��ؽڵ�
			DFSArticul(graph, index, &count, articulated, visited_sequ, vex_can_arrived);

			// �жϸ��Ƿ��ǹؽڵ�
			for (index = FirstAdjVex(graph, i); index != -1; index = NextAdjVex(graph, i, index)) {
				if (visited_sequ[index] == -1) {
					++articulated[0];
					articulated[articulated[0]] = graph.vertices[index].vexno;
					break;
				}
			}
		}
	}
	return OK;
}

Status DFSArticul(ALGraph graph, int vex_index, int *count, int articulated[MAXVEX + 1], int visited_sequ[MAXVEX], int vex_can_arrived[MAXVEX]) {
	int nextvex;

	visited_sequ[vex_index] = *count;
	++*count;
	vex_can_arrived[vex_index] = visited_sequ[vex_index];	//min(�Լ�����ţ������ܵ����������ţ��Լ������ȱ������ȵ����)

	for (nextvex = FirstAdjVex(graph, vex_index); nextvex != -1; nextvex = NextAdjVex(graph, vex_index, nextvex)) {
		if (visited_sequ[nextvex] == -1) {
			DFSArticul(graph, nextvex, count, articulated, visited_sequ, vex_can_arrived);
			if (vex_can_arrived[nextvex] < vex_can_arrived[vex_index]) {
				vex_can_arrived[vex_index] = vex_can_arrived[nextvex];
			}
			if (vex_can_arrived[nextvex] >= visited_sequ[vex_index]) {
				int i;
				for (i = 1; i <= articulated[0]; ++i)	//����õ��Ѿ���ӹ��ˣ��򲻱������
					if (articulated[i] == graph.vertices[vex_index].vexno)
						break;
				if (i == articulated[0] + 1) {
					++articulated[0];
					articulated[articulated[0]] = graph.vertices[vex_index].vexno;
				}
			}
		}
		else if (visited_sequ[nextvex] < vex_can_arrived[vex_index]) {
			vex_can_arrived[vex_index] = visited_sequ[nextvex];
		}
	}
	return OK;
}

int isBiconnectedGraph(ALGraph graph) {
	int articulated[MAXVEX + 1];
	if (FindArticul(graph, articulated) != OK)
		return false;

	return articulated[0] == 0;
}

int main() {
	ALGraph graph;
	ArcNode *temp;
	int articulated[MAXVEX + 1];
	int i;
	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}

	printf("%d\n", isBiconnectedGraph(graph));
	if (FindArticul(graph, articulated) != OK)return 1;
	for (i = 1; i <= articulated[0]; ++i)
		printf("%d ", articulated[i]);
	printf("\n");
	return 0;
}
