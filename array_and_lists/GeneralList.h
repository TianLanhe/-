#ifndef GENELIST_H
#define GENELIST_H

#include "../DataStructureBase.h"

#ifndef AtomType
#define AtomType ElemType
#endif

typedef enum _tag {
	ATOM,
	LIST
}ElemTag;

typedef struct _genenode {
	ElemTag tag;
	union {
		AtomType atom;
		struct _genenode *hp;
	};
	struct _genenode *next;
}GLNode;

Status RemBracket(char **substr, char *str);
//ɾ�����������д��ʽ���ַ������������
Status SplitStr(char ***arrstr, char *str, int *len);
//���ַ���str�Զ���Ϊ�ָ�����Ϊ���ɸ��Ӵ�������arrstr�ַ�������������Ӵ��ĸ���������len��
Status InitGList(GLNode **glist);
//��ʼ�������glist���趨��ΪLIST����ͷָ��ͺ��ָ���Ϊ��
Status DestroyGList(GLNode **glist);
//���ٹ����glist
Status CreateGList(GLNode **glist, char *str);
//str�ǹ�������д��ʽ������str���������
Status CopyGList(GLNode **newglist, GLNode *glist);
//�ɹ����glist���Ƶõ�newglist
int GListLength(GLNode *glist);
//������glist�ĳ��ȣ���Ԫ�ظ���
int GListDepth(GLNode *glist);
//������glist����ȣ������������������
Status GListEmpty(GLNode *glist);
//�жϹ�����Ƿ�Ϊ�ձ����򷵻�TRUE,���򷵻�FALSE
GLNode *GetGLHead(GLNode *glist);
//ȡ�����glist�ı�ͷ
GLNode *GetGLTail(GLNode *glist);
//ȡ�����glist�ı�β
Status InsetFirst_GL(GLNode **glist, GLNode *node);
//����Ԫ��node��Ϊ�����glist�ĵ�һԪ��
Status DeleteFirst_GL(GLNode **glist, GLNode **node);
//ɾ�������glist�ĵ�һԪ�أ�����node������ֵ
Status PrintGList(GLNode *glist);
//��ӡ��������д��ʽ�ַ���
Status Add(GLNode *node);
//���������Ĺ��ܺ�������ÿ��ԭ�ӵ�atomֵ��һ
Status TraverseGList(GLNode *glist, Status(*visit)(GLNode *));
//���������glist���ú���visit����ÿ��Ԫ��

#endif
