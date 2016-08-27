#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AtomType int
#define OK 1
#define ERROR 0
#define Status int
#define TRUE 1
#define FALSE 0
typedef enum _tag{
	ATOM,
	LIST
}ElemTag;
typedef struct _genenode{
	ElemTag tag;
	union {
		AtomType atom;
		struct _genenode *hp;
	};
	struct _genenode *next;
}GLNode;
Status RemBracket(char **substr,char *str);
//ɾ�����������д��ʽ���ַ������������
Status SplitStr(char ***arrstr,char *str,int *len);
//���ַ���str�Զ���Ϊ�ָ�����Ϊ���ɸ��Ӵ�������arrstr�ַ�������������Ӵ��ĸ���������len��
Status InitGList(GLNode **glist);
//��ʼ�������glist���趨��ΪLIST����ͷָ��ͺ��ָ���Ϊ��
Status DestroyGList(GLNode **glist);
//���ٹ����glist
Status CreateGList(GLNode **glist,char *str);
//str�ǹ�������д��ʽ������str���������
Status CopyGList(GLNode **newglist,GLNode *glist);
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
Status InsetFirst_GL(GLNode **glist,GLNode *node);
//����Ԫ��node��Ϊ�����glist�ĵ�һԪ��
Status DeleteFirst_GL(GLNode **glist,GLNode **node);
//ɾ�������glist�ĵ�һԪ�أ�����node������ֵ
Status PrintGList(GLNode *glist);
//��ӡ��������д��ʽ�ַ���
Status Add(GLNode *node);
//���������Ĺ��ܺ�������ÿ��ԭ�ӵ�atomֵ��һ
Status TraverseGList(GLNode *glist,Status (*visit)(GLNode *));
//���������glist���ú���visit����ÿ��Ԫ��
Status InitGList(GLNode **glist){
	*glist=(GLNode *)malloc(sizeof(GLNode));
	if(!(*glist))return ERROR;
	(*glist)->tag=LIST;
	(*glist)->hp=NULL;
	(*glist)->next=NULL;
	return OK;
}
Status DestroyGList(GLNode **glist){
	if((*glist)->tag==LIST&&!(*glist)->hp||(*glist)->tag==ATOM){
		free(*glist);
		*glist=NULL;
	}else{
		int length;
		GLNode *node;
		GLNode *temp;
		length=GListLength(*glist);
		node=(*glist)->hp;
		while(node){
			temp=node->next;
			DestroyGList(&node);
			node=temp;
		}
		free(*glist);
		*glist=NULL;
	}
	return OK;
}
Status RemBracket(char **substr,char *str){
	int len;
	int i,num;
	len=strlen(str);
	if(str[0]!='('||str[len-1]!=')')return ERROR;
	(*substr)=(char *)malloc(sizeof(char)*len-1);
	if(!(*substr))return ERROR;
	for(i=1,num=0;i<len-1;i++)(*substr)[num++]=str[i];
	(*substr)[num]='\0';
	return OK;
}
Status SplitStr(char ***arrstr,char *str,int *len){
	int i,k,num;
	int *pos;
	int start,end;
	int count;
	pos=(int *)malloc(sizeof(int)*1000);
	if(!pos)return ERROR;
	for(i=0,k=0,num=0;str[i];i++){
		if(str[i]=='(')k++;
		else if(str[i]==')')k--;
		else if(str[i]==','&&!k)pos[num++]=i;
	}
	*len=num+1;
	(*arrstr)=(char **)malloc(sizeof(char*)*(1+num));
	if(!(*arrstr))return ERROR;
	for(i=0;i<num+1;i++){
		if(!i)start=0;
		else start=pos[i-1]+1;
		if(i!=num)end=pos[i];
		else end=strlen(str);
		(*arrstr)[i]=(char *)malloc(sizeof(char)*(end-start+1));
		if(!(*arrstr)[i])return ERROR;
		count=0;
		for(k=start;k<end;k++){
			(*(*arrstr+i))[count++]=str[k];
		}
		(*(*arrstr+i))[count]='\0';
	}
	free(pos);
	return OK;
}
Status CreateGList(GLNode **glist,char *str){
	InitGList(glist);
	if(strlen(str)==1){
		(*glist)->tag=ATOM;
		(*glist)->atom=*str;
		(*glist)->next=NULL;
	}else if(strcmp(str,"()")){
		char *substr;
		char **splitstr;
		int n,i;
		GLNode *temp;
		GLNode *p;
		if(!RemBracket(&substr,str))return ERROR;
		if(!SplitStr(&splitstr,substr,&n))return ERROR;
		for(i=0,p=*glist;i<n;i++){
			CreateGList(&temp,splitstr[i]);
			if(!i){
				p->hp=temp;
				p=p->hp;
			}else{
				p->next=temp;
				p=p->next;
			}
		}
		for(i=0;i<n;i++)free(splitstr[i]);
		free(splitstr);
	}
	return OK;
}
Status PrintGList(GLNode *glist){
	if(glist->tag==ATOM)printf("%c",glist->atom);
	else if(!glist->hp)printf("()");
	else if(glist->tag==LIST){
		GLNode *node;
		printf("(");
		for(node=glist->hp;node;node=node->next){
			PrintGList(node);
			if(node->next)printf(",");
		}
		printf(")");
	}
	return OK;
}
Status CopyGList(GLNode **newglist,GLNode *glist){
	InitGList(newglist);
	if(glist->tag==ATOM){
		(*newglist)->tag=ATOM;
		(*newglist)->atom=glist->atom;
		(*newglist)->next=NULL;
	}else if(glist->tag==LIST&&glist->hp){
		GLNode *node;
		GLNode *newnode;
		GLNode *p;
		for(node=glist->hp,p=*newglist;node;node=node->next){
			CopyGList(&newnode,node);
			if(node==glist->hp){
				p->hp=newnode;
				p=p->hp;
			}else{
				p->next=newnode;
				p=p->next;
			}
		}
	}
	return OK;
}
int GListLength(GLNode *glist){
	int i;
	if(!glist||!glist->hp)return 0;
	for(glist=glist->hp,i=0;glist;glist=glist->next,i++);
	return i;
}
Status GListEmpty(GLNode *glist){
	if(!glist||!glist->hp)return TRUE;
	else return FALSE;
}
GLNode *GetGLHead(GLNode *glist){
	if(!glist||!glist->hp)return ERROR;
	return glist->hp;
}
GLNode *GetGLTail(GLNode *glist){
	if(!glist||!glist->hp)return ERROR;
	return glist->hp->next;
}
int GListDepth(GLNode *glist){
	if(glist->tag==LIST&&!glist->hp)return 1;
	else if(glist->tag==ATOM)return 0;
	else{
		int length;
		int max;
		GLNode *node;
		length=GListLength(glist);
		for(node=GetGLHead(glist),max=0;node;node=node->next){
			if(max<GListDepth(node))max=GListDepth(node);
		}
		return max+1; 
	}
	return OK;
}
Status InsetFirst_GL(GLNode **glist,GLNode *node){
	GLNode *head;
	if(!*glist||!node)return ERROR;
	CopyGList(&head,node);
	head->next=(*glist)->hp;
	(*glist)->hp=head;
	return OK;
}
Status DeleteFirst_GL(GLNode **glist,GLNode **node){
	if(!*glist||!(*glist)->hp)return ERROR;
	*node=(*glist)->hp;
	(*glist)->hp=(*glist)->hp->next;
	(*node)->next=NULL;
	return OK;
}
Status Add(GLNode *node){
	if(!node||!node->tag==ATOM)return ERROR;
	node->atom++;
	return OK;
}
Status TraverseGList(GLNode *glist,Status (*visit)(GLNode*)){
	if(!glist||!glist->hp)return ERROR;
	if(glist->tag==ATOM){
		if(!visit(glist))return ERROR;
	}else if(glist->tag==LIST&&glist->hp){
		GLNode *node;
		for(node=glist->hp;node;node=node->next)TraverseGList(node,visit);
	}
	return OK;
}
int main(){
	char *str="(((b,c,d),a),(),(e))";
	GLNode *glist=NULL;
	GLNode *head=NULL;
	GLNode *node;
	CreateGList(&glist,str);
	PrintGList(glist);
	printf("\n");
	TraverseGList(glist,Add);
	PrintGList(glist);
	printf("\n");
	printf("depth=%d  length=%d\n",GListDepth(glist),GListLength(glist));
	return 0;
}
