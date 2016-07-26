#include <stdio.h>
#include <stdlib.h>
#define Status int
#define MAXINT 0x7fffffff
#define OK 0
#define ERROR -1
#define true 1
#define false 0
#define DG 1    //����ͼ
#define DN 2	//������
#define UDG 3 	//����ͼ
#define UDN 4 	//������
#define MAXVEX 20		//��󶥵���

typedef int GraphKind;
typedef int TElemType;
typedef struct _cstree{					//�����ֵ�����
	TElemType data;
	struct _cstree *firstchild;			//����
	struct _cstree *nextsibling;		//�Һ���
}CSTNode;
typedef struct _arcnode{
	int adjvex;					//�û�ָ��Ķ����λ��
	int weight;					//Ȩ(�涨ֻ����Ȩ)
	struct _arcnode *nextarc;	//ָ����һ����
}ArcNode;
typedef struct _vnode{
	int vexno;					//�������(���)
	ArcNode *firstarc;			//ָ���һ����
}VNode;
typedef struct _algraph{
	int vexnum;					//ͼ�ĵ�ǰ������
	int arcnum;					//ͼ�ĵ�ǰ�������
	VNode vertices[MAXVEX];		//ͼ�Ķ����ڽӱ�(˳��洢)
	GraphKind kind;				//ͼ������
}ALGraph;
Status CreateDG(ALGraph *graph);
//��������ͼ����ʾ�û����벢������Ϣ��������ͼ�ڽӾ���
Status CreateDN(ALGraph *graph);
//��������������ʾ�û����벢������Ϣ�����������ڽӾ���
Status CreateUDG(ALGraph *graph);
//��������ͼ����ʾ�û����벢������Ϣ��������ͼ�ڽӾ���
Status CreateUDN(ALGraph *graph);
//��������������ʾ�û����벢������Ϣ�����������ڽӾ���
Status CreateGraph(ALGraph *graph);
//����ͼ����ʾ�û����벢������Ӧ���͵�ͼ
Status DestroyGraph(ALGraph *graph);
//����ͼgraph���������Ա��0
int FirstAdjVex(ALGraph graph,int v);
//���ض���v�ĵ�һ���ڽӶ��㣬��graph�����ڻ�v����graph�Ķ����vû���ڽӶ��㣬�򷵻�-1
int NextAdjVex(ALGraph graph,int v,int w);
//���ض���v�����w����һ���ڽӶ��㣬��graph�����ڻ�v����graph�Ķ����w����graph�Ķ������v�����w֮��û���ڽӶ��㣬�򷵻�-1
Status InsertVex(ALGraph *graph,int v);
//��ͼgraph�������¶���v����graph�����ڻ����ж����Ѿ��ﵽMAXVEX��vС��0��v�Ѵ���graph�У��򷵻�ERROR
Status DeleteVex(ALGraph *graph,int v);
//��ͼgraph��ɾ������v��������صĻ�����ͼgraph�����ڻ򶥵�v�����ڣ�����ERROR
Status DeleteArc(ALGraph *graph,int v,int w);
//��ͼgraph��ɾ����<v,w>����graph������ģ�����ɾ���Գƻ�<w,v>����ͼgraph�����ڻ򶥵�v��w�����ţ��򷵻�ERROR
Status InsertArc(ALGraph *graph,int v,int w,int adj);
//��ͼ��û�л�<v,w>������ͼgraph�����Ӹû�����graph������ģ��������ӶԳƻ�<w,v>����ͼgraph�����ڻ򶥵�v��w�����ڻ��<v,w>�Ѵ��ڣ��򷵻�ERROR
Status DFSTraverse(ALGraph *graph,Status (*traverse)(VNode));
//��ͼ����������ȱ�������ÿ���������һ��traverse����(�����Ӧ�ú���)����ͼ�����ڻ�����һ������traverseʧ�ܣ�����ERROR
Status DFSTraverse_sub(ALGraph *graph,int start,Status (*traverse)(VNode),int *visit);
//������ȱ������Ӻ������ݹ�ʵ��������ȱ�����
Status Print(VNode vnode);
//�����Ӧ�ú�������ӡ��������
Status BFSTraverse(ALGraph *graph,Status (*traverse)(VNode));
//��ͼ���й�����ȱ�������ÿ���������һ��traverse����(�����Ӧ�ú���)����ͼ�����ڻ�����һ������traverseʧ�ܣ�����ERROR
int VexNo(ALGraph graph,int vexnum);
//�жϵ�vexnum�Ƿ���ͼgraph�Ķ��㣬�����򷵻��±꣬���򷵻�-1
Status DFSForest(ALGraph graph,CSTNode **root);
//��������ͼgraph�������������ɭ��root
Status DFSTree(ALGraph graph,int index,CSTNode *root,int visit[]);
//�ӵ�index���������������ȱ���ͼgraph��������rootΪ����������
Status DestroyCSTree(CSTNode **root);
//������root��ʹ��Ϊ����
Status DestroyCSForest(CSTNode **root);
//����ɭ��root��ѭ��ɾ��root���������nextsibling.ʹ���Ϊ��ɭ��
Status PreOrderTraverseCSTress(CSTNode *root,Status (*visit)(CSTNode *));
//�������(�ݹ鷨)��root����ÿ�������ú���visitһ���ҽ�һ�Σ�һ������ʧ�ܣ�����ʧ��
Status PreOrderTraverseCSForest(CSTNode *root,Status (*visit)(CSTNode *));
//�������(�ݹ鷨)ɭ��root����ÿ�������ú���visitһ���ҽ�һ�Σ�һ������ʧ�ܣ�����ʧ��
Status PrintCSTree(CSTNode *node);
//���������Ĺ��ܺ�������ӡ�ڵ������ֵ
int Distance(ALGraph graph,int v,int w);
//������������ľ��룬���޷�ֱ�ӵ������MAXINT����v��w����graph�еĶ��㣬����error
Status MiniSpanTree_PRIM(ALGraph graph,int v);
//����ķ����ӵ�start���������������graph����С�����������������
Status TopologicalSort(ALGraph oldgraph,int toposequ[]);
//������ͼ(��)oldgraph���޻�·����oldgraph��һ���������б�����toposequ�в�����OK����oldgraph������ͼ(��)���л�������ERROR
Status CopyGraph(ALGraph *graph,ALGraph oldgraph);
//����(��¡)oldgraph��graph��
Status hasLoop_un_sub(ALGraph *graph,int start,int visit[]);
//�ݹ���������ͼ(��)graph,��ͼ�д��ڻ�·������ERROR�����򷵻�OK
//Ҫ���ƺ�ɾ�����бߣ����ұߵı������ҡ�Ч�ʲ��ߣ��д��Ľ�
Status hasLoop_un(ALGraph oldgraph);
//������ͼ(��)graph���޻�·���򷵻�false���л�·����true����������ͼ(��)������ERROR��
Status hasLoop(ALGraph graph);
//�ж�ͼ���Ƿ���ڣ��з���true�����򷵻�false
Status DijShortPath(ALGraph graph,int v,int path[][MAXVEX+2],int *dist);
//����Dijkstra�㷨��ͼgraph��v���㵽��������ľ���(���������Ϊ0���޷��������ΪMAXINT)
//path[w][...]�洢·��������path[w][0]��ʾ���������������n��Ԫ��Ϊ���㡣dist[w]��ʾ����v��w�ľ���
Status FloShortPath(ALGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]);
//����Floyd�㷨��ͼgraph��ÿ�����㵽���ඥ��ľ���(���������Ϊ0���޷��������ΪMAXINT)
//path[v][w][...]�洢��v��w�����·��������path[v][w][0]��ʾ���·���Ķ������(����������յ�)��������n��Ԫ��Ϊ���㡣dist[v][w]��ʾ����v��w�ľ���

Status FloShortPath(ALGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]){
	int i,j,k;
	if(path == NULL || dist == NULL)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			dist[i][j]=Distance(graph,graph.vertices[i].vexno,graph.vertices[j].vexno);
			path[i][j][0]=0;
			path[i][j][1]=MAXINT;
			if(dist[i][j] != MAXINT){
				path[i][j][0]+=2;
				path[i][j][1]=graph.vertices[i].vexno;
				path[i][j][2]=graph.vertices[j].vexno;
			}
		}
		path[i][i][0]++;
		path[i][i][1]=graph.vertices[i].vexno;
		dist[i][i]=0;
	}
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			for(k=0;k<graph.vexnum;k++){
				if(dist[j][i]<MAXINT && dist[i][k]<MAXINT){
					if(dist[j][i]+dist[i][k] < dist[j][k]){
						int w,count;
						dist[j][k]=dist[j][i]+dist[i][k];
						count=0;
						for(w=0;w<path[j][i][0]+1;w++)
							path[j][k][count++]=path[j][i][w];
						for(w=2;w<path[i][k][0]+1;w++)
							path[j][k][count++]=path[i][k][w];
						path[j][k][0]+=path[i][k][0]-1;
					}
				}
			}
		}
	}
	return OK;
}
Status DijShortPath(ALGraph graph,int v,int path[][MAXVEX+2],int *dist){
	int index;
	int index2;
	int i,j,k;
	int mindist;
	int distance;
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	if(path == NULL  || dist == NULL)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		dist[i]=Distance(graph,v,graph.vertices[i].vexno);
		path[i][0]=0;
		path[i][1]=MAXINT;
		if(dist[i] != MAXINT){
			path[i][0]++;
			path[i][1]=v;
		}
	}
	path[index][0]=1;						//path�Ĵ洢�ṹΪpath[0]=length��ʾ��ĸ���
	path[index][1]=v;						//������length��Ԫ��Ϊ���㣬��length+1��Ԫ��
	path[index][2]=0;						//�ݴ����dist������dist��-1��ʾ�Ѳ���S�У������������ٸ�ֵ��dist
	dist[index]=-1;								//-1��ʾ�õ��Ѳ���S��
	for(i=1;i<graph.vexnum;i++){
		mindist=MAXINT;
		for(j=0;j<graph.vexnum;j++){
			if(dist[j] != -1 && dist[j] < mindist){
				mindist=dist[j];
				index2=j;
			}
		}
		if(mindist != MAXINT){
			path[index2][0]++;
			path[index2][path[index2][0]]=graph.vertices[index2].vexno;
			path[index2][path[index2][0]+1]=dist[index2];
			for(j=0;j<graph.vexnum;j++){
				if(dist[j] != -1 && (distance=Distance(graph,graph.vertices[index2].vexno,graph.vertices[j].vexno)) != MAXINT){
					if(dist[index2]+distance < dist[j]){
						dist[j]=dist[index2]+distance;
						for(k=0;k<path[index2][0]+1;k++){
							path[j][k]=path[index2][k];
						}
					}
				}
			}
			dist[index2]=-1;
		}else break;
	}
	for(i=0;i<graph.vexnum;i++){
		dist[i]=path[i][path[i][0]+1];
	}
	return OK;
}
Status hasLoop_un_sub(ALGraph *graph,int start,int visit[]){
	int nextvex;
	int index;
	if(visit[start] == true)return ERROR;
	visit[start]=true;
	while((nextvex=FirstAdjVex(*graph,graph->vertices[start].vexno)) >= 0){
		if(DeleteArc(graph,graph->vertices[start].vexno,nextvex) == ERROR)return ERROR;
		if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
		if(hasLoop_un_sub(graph,index,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status CopyGraph(ALGraph *graph,ALGraph oldgraph){
	int i;
	int nextvex;
	ArcNode *node;
	if(graph == NULL || oldgraph.vexnum == 0)return ERROR;
	graph->vexnum=oldgraph.vexnum;
	graph->arcnum=oldgraph.arcnum;
	graph->kind=oldgraph.kind;
	for(i=0;i<oldgraph.vexnum;i++){
		graph->vertices[i].vexno=oldgraph.vertices[i].vexno;
		graph->vertices[i].firstarc=NULL;
	}
	for(i=0;i<oldgraph.vexnum;i++){
		for(node=oldgraph.vertices[i].firstarc;node;node=node->nextarc){
			if(InsertArc(graph,graph->vertices[i].vexno,node->adjvex,node->weight) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status hasLoop_un(ALGraph oldgraph){
	int visit[MAXVEX];
	int i;
	ALGraph graph;
	if(oldgraph.kind == DG || oldgraph.kind == DN)return ERROR;
	if(CopyGraph(&graph,oldgraph) == ERROR)return ERROR;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			if(hasLoop_un_sub(&graph,i,visit) == ERROR){
				DestroyGraph(&graph);
				return true;
			}
		}
	}
	DestroyGraph(&graph);
	return false;
}
Status hasLoop(ALGraph graph){
	int toposequ[MAXVEX];
	if(graph.kind == DG || graph.kind == DN)
		return TopologicalSort(graph,toposequ)==ERROR?true:false;
	else
		return hasLoop_un(graph);
}
Status TopologicalSort(ALGraph graph,int toposequ[]){
	int inarc[MAXVEX];
	int i;
	int vertex;
	int index;
	int count;
	if(graph.kind == UDG || graph.kind == UDN)return ERROR;
	for(i=0;i<graph.vexnum;i++)inarc[i]=0;
	for(i=0;i<graph.vexnum;i++){
		for(vertex=FirstAdjVex(graph,graph.vertices[i].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[i].vexno,vertex)){
			if((index=VexNo(graph,vertex)) == ERROR)return ERROR;
			inarc[index]++;
		}
	}
	count=0;
	while(count < graph.vexnum){
		for(i=0;i<graph.vexnum;i++){
			if(inarc[i] == 0){
				toposequ[count]=graph.vertices[i].vexno;
				inarc[i]=-1;
				count++;
				for(vertex=FirstAdjVex(graph,graph.vertices[i].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[i].vexno,vertex)){
					if((index=VexNo(graph,vertex)) == ERROR)return ERROR;
					inarc[index]--;
				}
				break;
			}
		}
		if(count < graph.vexnum && i == graph.vexnum)return ERROR;
	}
	for(i=0;i<graph.vexnum;i++)printf("%3d",toposequ[i]);
	return OK;
}
Status MiniSpanTree_PRIM(ALGraph graph,int v){
	int i,j;
	int index;
	int distance;
	struct {
		int vexno;
		int lowcost;
	}closedge[MAXVEX];
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		closedge[i].vexno=v;
		if(i != index){
			closedge[i].lowcost=Distance(graph,v,graph.vertices[i].vexno);
			if(closedge[i].lowcost == ERROR)return ERROR;
		}else{
			closedge[i].lowcost=-1;
		}
	}
	for(i=1;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++)
			if(closedge[j].lowcost != -1)
				break;
		index=j;
		for(j=j+1;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && closedge[j].lowcost < closedge[index].lowcost)
				index=j;
		}
		printf("<%d,%d>  ",closedge[index].vexno,graph.vertices[index].vexno);
		closedge[index].lowcost=-1;
		for(j=0;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && (distance=Distance(graph,graph.vertices[index].vexno,graph.vertices[j].vexno)) < closedge[j].lowcost){
				closedge[j].vexno=graph.vertices[index].vexno;
				if(closedge[j].vexno == ERROR)return ERROR;
				closedge[j].lowcost=distance;
			}
		}
	}
	printf("\n");
	return OK;
}
int Distance(ALGraph graph,int v,int w){
	int index;
	int index2;
	ArcNode *node;
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	if((index2=VexNo(graph,w)) == ERROR)return ERROR;
	for(node=graph.vertices[index].firstarc;node;node=node->nextarc){
		if(node->adjvex == w)
			return node->weight;
	}
	return MAXINT;
}
Status DestroyCSTree(CSTNode **root){
	CSTNode *node;
	CSTNode *temp;
	node=(*root)->firstchild;
	free(*root);
	*root=NULL;
	while(node){
		temp=node->nextsibling;
		if(DestroyCSTree(&node) == ERROR)return ERROR;
		node=temp;
	}
	return OK;
}
Status DestroyCSForest(CSTNode **root){
	CSTNode *tree,*temp;
	tree=*root;
	while(tree){
		temp=tree->nextsibling;
		if(DestroyCSTree(&tree) == ERROR)return ERROR;
		tree=temp;
	}
	(*root)=NULL;
	return OK;
}
Status PreOrderTraverseCSTress(CSTNode *root,Status (*visit)(CSTNode *)){
	CSTNode *node;
	if(visit(root) == ERROR)return ERROR;
	for(node=root->firstchild;node;node=node->nextsibling){
		if(PreOrderTraverseCSTress(node,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status PreOrderTraverseCSForest(CSTNode *root,Status (*visit)(CSTNode *)){
	CSTNode *tress;
	for(tress=root;tress;tress=tress->nextsibling){
		if(PreOrderTraverseCSTress(tress,visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}
Status PrintCSTree(CSTNode *node){
	printf("%3d",node->data);
	return OK;
}
Status DFSForest(ALGraph graph,CSTNode **root){
	int visit[MAXVEX];
	int i;
	CSTNode *pre,*node;
	*root=NULL;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=graph.vertices[i].vexno;
			if(*root == NULL)*root=node;
			else pre->nextsibling=node;
			pre=node;
			if(DFSTree(graph,i,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTree(ALGraph graph,int start,CSTNode *root,int *visit){
	int vertex;
	int first;
	int index;
	CSTNode *node,*pre;
	if(start < 0)return ERROR;
	if(root == NULL)return ERROR;
	if(visit == NULL)return ERROR;
	visit[start]=true;
	first=true;
	for(vertex=FirstAdjVex(graph,graph.vertices[start].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[start].vexno,vertex)){
		if((index=VexNo(graph,vertex)) == -1)return ERROR;
		if(visit[index] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->data=vertex;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			if(first){
				root->firstchild=node;
				first=false;
			}else{
				pre->nextsibling=node;
			}
			pre=node;
			if(DFSTree(graph,index,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse_sub(ALGraph *graph,int start,Status (*traverse)(VNode),int *visit){
	int index;
	int nextvex;
	if((index=VexNo(*graph,start)) == ERROR)return ERROR;
	if(traverse(graph->vertices[index]) == ERROR)return ERROR;
	visit[index]=true;
	for(nextvex=FirstAdjVex(*graph,start);nextvex>=0;nextvex=NextAdjVex(*graph,start,nextvex)){
		if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
		if(visit[index] == false){
			if(DFSTraverse_sub(graph,nextvex,traverse,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse(ALGraph *graph,Status (*traverse)(VNode)){
	int visit[MAXVEX];
	int i;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	return DFSTraverse_sub(graph,graph->vertices[0].vexno,traverse,visit);
}
Status BFSTraverse(ALGraph *graph,Status (*traverse)(VNode)){
	int queue[MAXVEX];
	int top,buttom;
	int visit[MAXVEX];
	int vertex;
	int index;
	int i;
	int nextvex;
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	top=buttom=0;				//��ʼ�����У����׵��ڶ�β��ʾ����Ϊ��
	if(traverse(graph->vertices[0]) == ERROR)return ERROR;	//���ʶ���
	visit[0]=true;
	queue[buttom]=graph->vertices[0].vexno;	
	buttom++;					//������ģ������У��������������У�Ȼ���β���һ��	
	while(top != buttom){		//�����в���ʱ
		vertex=queue[top];
		top++;					//������ģ������У���������ŴӶ����е�������ʹ�������һ��
		for(nextvex=FirstAdjVex(*graph,vertex);nextvex>=0;nextvex=NextAdjVex(*graph,vertex,nextvex)){
			if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
			if(visit[index] == false){		//������㻹δ���ʹ�
				if(traverse(graph->vertices[index]) == ERROR)return ERROR;
				visit[index]=true;
				queue[buttom]=nextvex;		//����ʲ������
				buttom++;
			}
		}
	}
	return OK;
}
Status Print(VNode vnode){
	printf("%2d",vnode.vexno);
	return OK;
}
Status InsertVex(ALGraph *graph,int v){
	if(graph == NULL || graph->vexnum >= MAXVEX)return ERROR;
	if(VexNo(*graph,v) != -1)return ERROR;			//�жϲ����Ϸ���
	graph->vertices[graph->vexnum].firstarc=NULL;
	graph->vertices[graph->vexnum].vexno=v;
	graph->vexnum++;
	return OK;
}
Status DeleteVex(ALGraph *graph,int v){
	int index;
	ArcNode *node,*temp;
	int i;
	if(graph == NULL || graph->vexnum <= 0)return ERROR;
	if((index=VexNo(*graph,v)) == -1)return ERROR;			//�жϲ����Ϸ���
	for(i=0;i<graph->vexnum;i++){					//��ɾ���������㵽v�ı�
		if(DeleteArc(graph,graph->vertices[i].vexno,v) == ERROR)return ERROR;
	}
	node=graph->vertices[index].firstarc;			//��ɾ��v����������ı�
	while(node){									//���������ͼ����һ���Ѿ���v����������ı�ɾ����
		temp=node;
		node=node->nextarc;
		free(temp);
	}
	for(;index<graph->vexnum-1;index++){			//�������ж���v���±�index���µĶ���������һ��
		graph->vertices[index].vexno=graph->vertices[index+1].vexno;
		graph->vertices[index].firstarc=graph->vertices[index+1].firstarc;
	}
	graph->vexnum--;
	return OK;
}
Status DeleteArc(ALGraph *graph,int v,int w){
	int index;
	int index2;												//���ַ�������
	ArcNode *node,*pre;										//0:�ɹ�,-1:ʧ��,-2:�ɺ���
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	if((index=VexNo(*graph,v)) == -1)return ERROR;
	if((index2=VexNo(*graph,w)) == -1)return ERROR;			//�жϲ����Ϸ���
	node=graph->vertices[index].firstarc;
	pre=graph->vertices[index].firstarc;					//��ɾ������ͷ�������������ͬ
	while(node){
		if(node->adjvex == w){
			if(node == graph->vertices[index].firstarc){
				graph->vertices[index].firstarc=node->nextarc;
				free(node);
			}else{
				pre->nextarc=node->nextarc;
				free(node);
			}
			if(graph->kind == UDG || graph->kind == UDN){	//��������ͼ(��)����Ҫɾ���ԳƱ�
				node=graph->vertices[index2].firstarc;
				pre=graph->vertices[index2].firstarc;
				while(node){
					if(node->adjvex == v){
						if(node == graph->vertices[index2].firstarc){
							graph->vertices[index2].firstarc=node->nextarc;
							free(node);
						}else{
							pre->nextarc=node->nextarc;
							free(node);
						}
						return OK;
					}else{
						pre=node;
						node=node->nextarc;
					}
				}
			}
			graph->arcnum--;
			return OK;
		}else{
			pre=node;
			node=node->nextarc;
		}
	}
	return -2;
}
int FirstAdjVex(ALGraph graph,int v){
	int index;
	ArcNode *firnode;
	if(graph.vexnum == 0)return ERROR;
	index=VexNo(graph,v);
	if(index == -1)return ERROR;
	firnode=graph.vertices[index].firstarc;
	return firnode==NULL?ERROR:firnode->adjvex;
}
int NextAdjVex(ALGraph graph,int v,int w){
	int index;
	int index2;
	ArcNode *nextnode;
	if(graph.vexnum == 0)return ERROR;
	index=VexNo(graph,v);
	if(index == -1)return ERROR;
	index2=VexNo(graph,w);
	if(index2 == -1)return ERROR;
	for(nextnode=graph.vertices[index].firstarc;nextnode && nextnode->adjvex != w;nextnode=nextnode->nextarc);
	if(nextnode == NULL)return ERROR;
	else nextnode=nextnode->nextarc;
	return nextnode==NULL?ERROR:nextnode->adjvex;
}
Status DestroyGraph(ALGraph *graph){
	int i;
	ArcNode *temp,*arcnode;
	if(graph->vexnum == 0 && graph->arcnum == 0)return ERROR;
	graph->vexnum=0;
	graph->arcnum=0;
	graph->kind=0;
	for(i=0;i<graph->vexnum;i++){
		arcnode=graph->vertices[i].firstarc;
	    while(arcnode){
	    	temp=arcnode;
	    	arcnode=arcnode->nextarc;
	    	free(temp);
	    }
	    graph->vertices[i].firstarc=NULL;
	    graph->vertices[i].vexno=-1;
	}
	return OK;
}
Status CreateGraph(ALGraph *graph){
	int kind;
	printf("1.����ͼ\n2.������\n3.����ͼ\n4.������\n");
	printf("������ͼ�����ͣ�");
	scanf("%d",&kind);
	switch(kind){
		case 1:if(CreateDG(graph) == ERROR)return ERROR;break;
		case 2:if(CreateDN(graph) == ERROR)return ERROR;break;
		case 3:if(CreateUDG(graph) == ERROR)return ERROR;break;
		case 4:if(CreateUDN(graph) == ERROR)return ERROR;break;
		default:printf("��������ȷ��ͼ���ͱ�ţ�\n");
				return ERROR;
	}
	return OK;
}
int VexNo(ALGraph graph,int vexnum){
	int i;
	for(i=0;i<graph.vexnum;i++)
		if(graph.vertices[i].vexno == vexnum)
			break;
	return i<graph.vexnum?i:-1;
}
Status InsertArc(ALGraph *graph,int v,int w,int adj){
	int start,end;
	ArcNode *arcnode,*temp;
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	start=VexNo(*graph,v);
	end=VexNo(*graph,w);
	if(end == -1 || start == -1 || start == end)return ERROR;	//�жϲ����ĺϷ���
	for(temp=graph->vertices[start].firstarc;temp;temp=temp->nextarc)	//����Ѿ���<v,w>���ˣ�����ӣ�����-2
		if(temp->adjvex == w)return -2;							//���ַ�������
	arcnode=(ArcNode*)malloc(sizeof(ArcNode));					//0:�ɹ�,-1:ʧ��,-2:�ɺ���
	if(!arcnode)return ERROR;
	arcnode->adjvex=w;
	if(graph->kind == DG || graph->kind == UDG)
		arcnode->weight=1;
	else arcnode->weight=adj;
	arcnode->nextarc=graph->vertices[start].firstarc;			//�����λ���������ײ�����������Ϊv�ĵ�һ���ڱߣ����������һ��
	graph->vertices[start].firstarc=arcnode;
	if(graph->kind == UDG || graph->kind == UDN){				//���������ͼ(��)����Ҫ����ԳƱ�
		temp=(ArcNode*)malloc(sizeof(ArcNode));
		if(!temp)return ERROR;
		temp->adjvex=v;
		temp->weight=arcnode->weight;
		temp->nextarc=graph->vertices[end].firstarc;
		graph->vertices[end].firstarc=temp;
	}
	return OK;
}
Status CreateDG(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	graph->kind=DG;
	printf("�����붥������");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("���������Ϸ���\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	printf("���������붥��ı��(��Ĭ�ϱ������-1)��");
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("���������-1��������\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("��������ڵ���-1��������\n");
		return ERROR;
	}
	printf("������ߵ�ʼ����յ㣬����-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",end);
			return ERROR;
		}
		if(start == end){
			printf("��������ֻ���\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,1) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateDN(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	int adj;
	graph->kind=DN;
	printf("�����붥������");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("���������Ϸ���\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	printf("���������붥��ı��(��Ĭ�ϱ������-1)��");
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("���������-1��������\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("��������ڵ���-1��������\n");
		return ERROR;
	}
	printf("������ߵ�ʼ�㡢�յ�ͱߵ�Ȩ������-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",end);
			return ERROR;
		}
		if(start == end){
			printf("��������ֻ���\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){
			printf("��Ȩ���Ϸ���\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,adj) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDG(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	graph->kind=UDG;
	printf("�����붥������");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("���������Ϸ���\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	printf("���������붥��ı��(��Ĭ�ϱ������-1)��");
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("���������-1��������\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("��������ڵ���-1��������\n");
		return ERROR;
	}
	printf("������ߵ�ʼ����յ㣬����-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",end);
			return ERROR;
		}
		if(start == end){
			printf("��������ֻ���\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,1) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDN(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	int adj;
	graph->kind=UDN;
	printf("�����붥������");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){				//�ж϶������Ƿ�Ϸ�
		printf("���������Ϸ���\n");
		return ERROR;
	}
	graph->vexnum=vexnum;							   //�ڽӾ������±���Ƕ���ı��
	printf("���������붥��ı��(��Ĭ�ϱ������-1)��");//�����±����ŷֿ��������ſ������⣬���Ӻ���
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("���������-1��������\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("��������ڵ���-1��������\n");
		return ERROR;
	}
	printf("������ߵ�ʼ�㡢�յ�ͱߵ�Ȩ������-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("�����ڱ��Ϊ%d�Ķ��㣡\n",end);
			return ERROR;
		}
		if(start == end){
			printf("��������ֻ���\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){
			printf("��Ȩ���Ϸ���\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,adj) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
int main(){
	ALGraph graph;
	int i,j;
	int dist[MAXVEX][MAXVEX];
	int path[MAXVEX][MAXVEX][MAXVEX+2];
	ArcNode *temp;
	if(CreateGraph(&graph) == ERROR)printf("error!\n");
	for(i=0;i<graph.vexnum;i++){
		printf("%-5d",graph.vertices[i].vexno);
		for(temp=graph.vertices[i].firstarc;temp;temp=temp->nextarc){
			printf("adjvex=%d  weight=%d     ",temp->adjvex,temp->weight);
		}
		printf("\n");
	}
	if(FloShortPath(graph,path,dist) == ERROR)printf("error\n");
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			if(dist[i][j] == MAXINT)printf(" ��");
			else printf("%3d",dist[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<graph.vexnum;i++){
		for(j=1;j<path[0][i][0]+1;j++){
			printf("%3d",path[0][i][j]);
		}
		printf("\n");
	}
	return 0;
}
