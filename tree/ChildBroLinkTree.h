#ifndef CHILD_BRO_LINK_TREE_H
#define CHILD_BRO_LINK_TREE_H

#include "../DataStructureBase.h"

#ifndef TElemType
#define TElemType ElemType
#endif

typedef struct _cstree {				//�����ֵ�������
	TElemType data;
	struct _cstree *firstchild;			//����
	struct _cstree *nextsibling;		//�Һ���
}CSTNode;

Status DestroyCSTree(CSTNode **root);
//������root��ʹ��Ϊ����
Status DestroyCSForest(CSTNode **root);
//����ɭ��root��ѭ��ɾ��root���������nextsibling.ʹ���Ϊ��ɭ��
Status PreOrderTraverseCSTrees(CSTNode *root, Status(*visit)(CSTNode *));
//�������(�ݹ鷨)��root����ÿ�������ú���visitһ���ҽ�һ�Σ�һ������ʧ�ܣ�����ʧ��
Status PreOrderTraverseCSForest(CSTNode *root, Status(*visit)(CSTNode *));
//�������(�ݹ鷨)ɭ��root����ÿ�������ú���visitһ���ҽ�һ�Σ�һ������ʧ�ܣ�����ʧ��
Status InOrderTraverseCSTrees(CSTNode *root, Status(*visit)(CSTNode *));
//�������(�ݹ鷨)��root����ÿ�������ú���visitһ���ҽ�һ�Σ�һ������ʧ�ܣ�����ʧ��
Status InOrderTraverseCSForest(CSTNode *root, Status(*visit)(CSTNode *));
//�������(�ݹ鷨)ɭ��root����ÿ�������ú���visitһ���ҽ�һ�Σ�һ������ʧ�ܣ�����ʧ��
Status PrintCSTree(CSTNode *node);
//���������Ĺ��ܺ�������ӡ�ڵ������ֵ

#endif