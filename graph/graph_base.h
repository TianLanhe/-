#ifndef GRAPH_BASE_H
#define GRAPH_BASE_H

#include "../DataStructureBase.h"

#define MAXINT 0x7fffffff

#ifndef MAXVEX
#define MAXVEX 20		//��󶥵���
#endif

#ifndef Graph
#define Graph void
#endif

#ifndef GraphVertex
#define GraphVertex int
#endif

typedef enum _graphkind {
	DG = 1, DN, UDG, UDN   	//����ͼ��������������ͼ��������
} GraphKind;				//ͼ������

Status sub_CreateGraph(Graph *graph, GraphKind kind);
//�����û���������ʹ���ͼ����������������Ҫ��ʾ����Ȩֵ����������ģ���Ҫ����˫���
Status CreateGraph(Graph *graph);
//����ͼ����ʾ�û����벢������Ӧ���͵�ͼ
int LocateVex(Graph graph, int vexnum);
//���ݶ���ı��ȷ�����±꣬���޴˶����򷵻�-1
Status DestroyGraph(Graph *graph);
//����ͼgraph���������Ա��0
int FirstAdjVex(Graph graph, int index);
//���ض���v�ĵ�һ���ڽӶ��㣬��graph�����ڻ�v����graph�Ķ����vû���ڽӶ��㣬�򷵻�-1
int NextAdjVex(Graph graph, int index1, int index2);
//���ض���v�����w�ĵ�һ���ڽӶ��㣬��graph�����ڻ�v����graph�Ķ����w����graph�Ķ������v�����w֮��û���ڽӶ��㣬�򷵻�-1
int Distance(Graph graph, int index1, int index2);
//������������ľ��룬���޷�ֱ�ӵ������MAXINT�����±겻�Ϸ�������MAXINT
Status InsertVex(Graph *graph, int vexnum);
//��ͼgraph��������Ϊvexnum���¶��㣬��graph�����ڻ��Ѿ��ﵽMAXVEX����vexnumС��0���Ѿ��������ŵĶ��㣬�򷵻�ERROR
Status DeleteVex(Graph *graph, int vexnum);
//��ͼgraph��ɾ�����Ϊvexnum�Ķ��㣬������صĻ�����ͼgraph�����ڻ򶥵�v�����ڣ�����ERROR
Status InsertArc(Graph *graph, int v, int w, int adj);
//��ͼ��û�л�<v,w>������ͼgraph�����Ӹû�����graph������ģ��������ӶԳƻ�<w,v>����ͼgraph�����ڻ򶥵�v��w�����ڻ��<v,w>�Ѵ��ڣ��򷵻�ERROR
Status DeleteArc(Graph *graph, int v, int w);
//��ͼgraph��ɾ����<v,w>����graph������ģ�����ɾ���Գƻ�<w,v>����ͼgraph�����ڻ򶥵�v��w�����ţ��򷵻�ERROR
Status DFSTraverse(Graph *graph, Status(*traverse)(GraphVertex));
//��ͼ����������ȱ�������ÿ���������һ��traverse����(�����Ӧ�ú���)����ͼ�����ڻ�����һ������traverseʧ�ܣ�����ERROR
Status DFSTraverse_sub(Graph *graph, int idx_start, Status(*traverse)(GraphVertex), int *visit);
//������ȱ������Ӻ������ݹ�ʵ��������ȱ�����
Status BFSTraverse(Graph *graph, Status(*traverse)(GraphVertex));
//��ͼ���й�����ȱ�������ÿ���������һ��traverse����(�����Ӧ�ú���)����ͼ�����ڻ�����һ������traverseʧ�ܣ�����ERROR
Status Print(GraphVertex i);
//�����Ӧ�ú�������ӡ��������

#endif