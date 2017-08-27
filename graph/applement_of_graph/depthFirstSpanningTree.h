#ifndef DEPTH_FIRST_SPANNING_TREE_H
#define DEPTH_FIRST_SPANNING_TREE_H

#include "../graph_base.h"
#include "../../tree/ChildBroLinkTree.h"

Status DFSForest(Graph graph, CSTNode **root);
//��������ͼgraph�������������ɭ��root
Status DFSTree(Graph graph, int index, CSTNode *root, int visit[]);
//�ӵ�index���������������ȱ���ͼgraph��������rootΪ����������

#endif
