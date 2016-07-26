#include <stdio.h>
#include <stdlib.h>
#define Status int
#define MAXINT 0x7fffffff
#define OK 0
#define ERROR -1
#define true 1
#define false 0
#define DG 1    		//����ͼ
#define DN 2			//������
#define UDG 3 			//����ͼ
#define UDN 4 			//������
#define MAXVEX 20		//��󶥵���

typedef int GraphKind;
typedef int TElemType;
typedef struct _cstree{					//�����ֵ�������
	TElemType data;
	struct _cstree *firstchild;			//����
	struct _cstree *nextsibling;		//�Һ���
}CSTNode;
typedef struct _mgraph {
	int vexnum;							//ͼ�ĵ�ǰ������
	int arcnum;							//ͼ�ĵ�ǰ�������
	int arcs[MAXVEX][MAXVEX];			//ͼ�Ķ����ڽӾ���
	GraphKind kind;						//ͼ������
}MGraph;
Status CreateDG(MGraph *graph);
//��������ͼ����ʾ�û����벢������Ϣ��������ͼ�ڽӾ���
Status CreateDN(MGraph *graph);
//��������������ʾ�û����벢������Ϣ�����������ڽӾ���
Status CreateUDG(MGraph *graph);
//��������ͼ����ʾ�û����벢������Ϣ��������ͼ�ڽӾ���
Status CreateUDN(MGraph *graph);
//��������������ʾ�û����벢������Ϣ�����������ڽӾ���
Status CreateGraph(MGraph *graph);
//����ͼ����ʾ�û����벢������Ӧ���͵�ͼ
Status DestriyGraph(MGraph *graph);
//����ͼgraph���������Ա��0
int FirstAdjVex(MGraph graph,int v);
//���ض���v�ĵ�һ���ڽӶ��㣬��graph�����ڻ�v����graph�Ķ����vû���ڽӶ��㣬�򷵻�-1
int NextAdjVex(MGraph graph,int v,int w);
//���ض���v�����w�ĵ�һ���ڽӶ��㣬��graph�����ڻ�v����graph�Ķ����w����graph�Ķ������v�����w֮��û���ڽӶ��㣬�򷵻�-1
Status InsertVex(MGraph *graph,int v);
//��ͼgraph�������¶���v����graph�����ڻ��Ѿ��ﵽMAXVEX����vС��0���ڵ���MAXVEX���򷵻�ERROR
//���������̫�ã����״�����ǰ�������ţ��д��Ľ�
Status DeleteVex(MGraph *graph,int v);
//��ͼgraph��ɾ������v��������صĻ�����ͼgraph�����ڻ򶥵�v�����ڣ�����ERROR
Status DeleteArc(MGraph *graph,int v,int w);
//��ͼgraph��ɾ����<v,w>����graph������ģ�����ɾ���Գƻ�<w,v>����ͼgraph�����ڻ򶥵�v��w�����ţ��򷵻�ERROR
Status InsertArc(MGraph *graph,int v,int w,int adj);
//��ͼ��û�л�<v,w>������ͼgraph�����Ӹû�����graph������ģ��������ӶԳƻ�<w,v>����ͼgraph�����ڻ򶥵�v��w�����ڻ��<v,w>�Ѵ��ڣ��򷵻�ERROR
Status DFSTraverse(MGraph *graph,Status (*traverse)(int));
//��ͼ����������ȱ�������ÿ���������һ��traverse����(�����Ӧ�ú���)����ͼ�����ڻ�����һ������traverseʧ�ܣ�����ERROR
Status DFSTraverse_sub(MGraph *graph,int start,Status (*traverse)(int),int *visit);
//������ȱ������Ӻ������ݹ�ʵ��������ȱ�����
Status Print(int i);
//�����Ӧ�ú�������ӡ��������
Status BFSTraverse(MGraph *graph,Status (*traverse)(int));
//��ͼ���й�����ȱ�������ÿ���������һ��traverse����(�����Ӧ�ú���)����ͼ�����ڻ�����һ������traverseʧ�ܣ�����ERROR
Status DFSForest(MGraph graph,CSTNode **root);
//��������ͼgraph�������������ɭ��root
Status DFSTree(MGraph graph,int index,CSTNode *root,int visit[]);
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
Status MiniSpanTree_PRIM(MGraph graph,int start);
//����ķ����ӵ�start���������������graph����С����������������ߡ���start���ڵ���graph������������ERROR
//˵����������ӡ
Status TopologicalSort(MGraph oldgraph,int toposequ[]);
//������ͼ(��)oldgraph���޻�·����oldgraph��һ���������б�����toposequ�в�����OK����oldgraph������ͼ(��)���л�������ERROR
Status CopyGraph(MGraph *newgraph,MGraph oldgraph);
//����(��¡)oldgraph��newgraph��
Status hasLoop_un_sub(MGraph graph,int start,int visit[]);
//�ݹ���������ͼ(��)graph,��ͼ�д��ڻ�·������ERROR�����򷵻�OK
Status hasLoop_un(MGraph graph);
//������ͼ(��)graph���޻�·���򷵻�false���л�·����true����������ͼ(��)������ERROR��
Status hasLoop(MGraph graph);
//�ж�ͼ���Ƿ���ڣ��з���true�����򷵻�false
Status DijShortPath(MGraph graph,int v,int path[][MAXVEX+2],int *dist);
//����Dijkstra�㷨��ͼgraph��v���㵽��������ľ���(���������Ϊ0���޷��������ΪMAXINT)
//path[w][...]�洢��v��w�����·��������path[w][0]��ʾ���·���Ķ������(����������յ�)��������n��Ԫ��Ϊ���㡣dist[w]��ʾ����v��w�ľ���
Status FloShortPath(MGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]);
//����Floyd�㷨��ͼgraph��ÿ�����㵽���ඥ��ľ���(���������Ϊ0���޷��������ΪMAXINT)
//path[v][w][...]�洢��v��w�����·��������path[v][w][0]��ʾ���·���Ķ������(����������յ�)��������n��Ԫ��Ϊ���㡣dist[v][w]��ʾ����v��w�ľ���

Status FloShortPath(MGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]){
	int i,j,k;
	if(path == NULL || dist == NULL)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	for(i=0;i<graph.vexnum;i++){		//�����ǳ�ʼ������
		for(j=0;j<graph.vexnum;j++){
			dist[i][j]=graph.arcs[i][j];
			path[i][j][0]=0;
			path[i][j][1]=MAXINT;
			if(dist[i][j] != MAXINT){
				path[i][j][0]+=2;
				path[i][j][1]=i;
				path[i][j][2]=j;
			}
		}
		path[i][i][0]++;
		path[i][i][1]=i;
		dist[i][i]=0;
	}
	for(i=0;i<graph.vexnum;i++){		//�����Ǵ�����
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
Status DijShortPath(MGraph graph,int v,int path[][MAXVEX+2],int *dist){
	int i,j,k;
	int mindist;
	int vexter;
	if(graph.vexnum == 0)return ERROR;
	if(path == NULL  || dist == NULL)return ERROR;
	if(v >= graph.vexnum)return ERROR;		//�жϲ����Ϸ���
	for(i=0;i<graph.vexnum;i++){		//�����ǳ�ʼ������
		dist[i]=graph.arcs[v][i];		//dist[i]��ʾ����vֱ�ӻ򾭹��м�ڵ��ӵ�i�ľ���
		path[i][0]=0;
		path[i][1]=MAXINT;
		if(dist[i] != MAXINT){
			path[i][0]++;
			path[i][1]=v;
		}
	}
	path[v][0]=1;						//path�Ĵ洢�ṹΪpath[0]=length��ʾ��ĸ���
	path[v][1]=v;						//������length��Ԫ��Ϊ���㣬��length+1��Ԫ��
	path[v][2]=0;						//�ݴ����dist������dist��-1��ʾ�Ѳ���S�У������������ٸ�ֵ��dist
	dist[v]=-1;								//-1��ʾ�õ��Ѳ���S��
	for(i=1;i<graph.vexnum;i++){		//�����Ǵ�����
		mindist=MAXINT;
		for(j=0;j<graph.vexnum;j++){	//ѡһ��dist��Ϊ-1����С�Ķ���
			if(dist[j] != -1 && dist[j] < mindist){
				mindist=dist[j];
				vexter=j;
			}
		}
		if(mindist != MAXINT){			//���ûѡ����˵��ʣ�µĵ�Ҫô����-1Ҫô����MAXINT�������޷���������������
			path[vexter][0]++;
			path[vexter][path[vexter][0]]=vexter;
			path[vexter][path[vexter][0]+1]=dist[vexter];
			for(j=0;j<graph.vexnum;j++){
				if(dist[j] != -1 && graph.arcs[vexter][j] != MAXINT){
					if(dist[vexter]+graph.arcs[vexter][j] < dist[j]){
						dist[j]=dist[vexter]+graph.arcs[vexter][j];
						for(k=0;k<path[vexter][0]+1;k++){
							path[j][k]=path[vexter][k];
						}
					}
				}
			}
			dist[vexter]=-1;
		}else break;
	}
	for(i=0;i<graph.vexnum;i++){
		dist[i]=path[i][path[i][0]+1];
	}
	return OK;
}
Status hasLoop_un(MGraph graph){
	int visit[MAXVEX];
	int i;
	if(graph.kind == DG || graph.kind == DN)return ERROR;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++)
		if(visit[i] == false)
			if(hasLoop_un_sub(graph,i,visit) == ERROR)
				return true;
	return false;
}
Status hasLoop_un_sub(MGraph graph,int start,int visit[]){
	int nextvex;
	if(visit[start] == true)return ERROR;
	visit[start]=true;
	for(nextvex=FirstAdjVex(graph,start);nextvex>=0;nextvex=NextAdjVex(graph,start,nextvex)){
		if(DeleteArc(&graph,start,nextvex) == ERROR)return ERROR;
		if(hasLoop_un_sub(graph,nextvex,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status hasLoop(MGraph graph){
	int toposequ[MAXVEX];
	if(graph.kind == DG || graph.kind == DN)			//����ͼ(��)�����������ж��Ƿ��л�·
		return TopologicalSort(graph,toposequ)==ERROR?true:false;
	else												//����ͼ(��)������ȱ����ж��Ƿ��л�·
		return hasLoop_un(graph);
}
Status CopyGraph(MGraph *newgraph,MGraph oldgraph){
	int i,j;
	if(newgraph == NULL)return ERROR;
	newgraph->kind=oldgraph.kind;
	newgraph->vexnum=oldgraph.vexnum;
	newgraph->arcnum=oldgraph.arcnum;
	for(i=0;i<oldgraph.vexnum;i++){
		for(j=0;j<oldgraph.vexnum;j++){
			newgraph->arcs[i][j]=oldgraph.arcs[i][j];
		}
	}
	return OK;
}
Status TopologicalSort(MGraph oldgraph,int toposequ[]){
	int count;
	int column,row;
	int flag;
	int visit[MAXVEX];					//��������ֻ�������ͼ
	MGraph graph;						//���������ͼ������ERROR
	if(oldgraph.kind == UDG || oldgraph.kind == UDN)return ERROR;
	if(toposequ == NULL)return ERROR;
	CopyGraph(&graph,oldgraph);			//����ѡ��һ�������Ҫɾ��������㼰������ıߣ�������ƻ��Ե�
	count=0;							//��copy��һ���µ���ʱͼ���������ɲο��ڽӱ�洢�ṹ��ͼ����һ���ָ��õķ���
	for(row=0;row<graph.vexnum;row++)visit[row]=false;
	while(count < graph.vexnum){
		for(column=0;column<graph.vexnum;column++){	//��ͷ��ʼ������������һ��û���ʹ��������Ϊ0�Ķ���
			flag=true;
			for(row=0;row<graph.vexnum;row++){
				if(visit[column] == true || graph.arcs[row][column] != MAXINT)
					flag=false;
			}
			if(flag == true){						//���ҵ��ˣ�������visit�ѷ��ʣ�������������
				visit[column]=true;
				toposequ[count]=column;
				count++;
				for(row=0;row<graph.vexnum;row++){
					graph.arcs[column][row]=MAXINT;	//����ö�������ı�ȫ��ȥ��
				}
				break;								//����ѭ�����¿�ʼ��ͷ����
			}
		}											//�������һȦ��û���ҵ����Ϊ0�Ķ���
		if(flag == false && count<graph.vexnum){
			DestriyGraph(&graph);
			return ERROR;							//Ҫô���ж��㶼���ʹ��ˣ�Ҫô�޷��ҵ���������
		}
	}
	DestriyGraph(&graph);							//�ǵ�ʹ��������ٿ�¡��ͼ������ʵ��û���漰����̬����
	return OK;										//���ᷢ���ڴ�й©���������ٶ�����ν��
}
Status MiniSpanTree_PRIM(MGraph graph,int start){
	int i,j;
	int index;
	struct {
		int vexno;
		int lowcost;
	}closedge[MAXVEX];
	if(start >= graph.vexnum)return ERROR;		//�жϲ����Ϸ���
	for(i=0;i<graph.vexnum;i++){
		closedge[i].vexno=start;
		if(i != start){
			closedge[i].lowcost=graph.arcs[start][i];
		}else{
			closedge[i].lowcost=-1;
		}
	}											//��ʼ��closedge���飬lowcost=-1��ʾ������ѡ������
	for(i=1;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++)
			if(closedge[j].lowcost != -1)
				break;						//��ֱ����index=0��ԭ�����п���closedge[0].lowcostΪ-1
		index=j;
		for(j=j+1;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && closedge[j].lowcost < closedge[index].lowcost)
				index=j;
		}												//��������forѡ��closedge�������һ��lowcost��Ϊ-1����С���±�
		printf("<%d,%d>  ",closedge[index].vexno,index);
		closedge[index].lowcost=-1;
		for(j=0;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && graph.arcs[index][j] < closedge[j].lowcost){
				closedge[j].vexno=index;
				closedge[j].lowcost=graph.arcs[index][j];
			}
		}
	}
	printf("\n");
	return OK;
}
Status DFSForest(MGraph graph,CSTNode **root){
	int i;
	int visit[MAXVEX];
	CSTNode *node,*pre;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	*root=NULL;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=i;
			if(*root == NULL)*root=node;
			else pre->nextsibling=node;
			pre=node;
			if(DFSTree(graph,i,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTree(MGraph graph,int index,CSTNode *root,int visit[]){
	CSTNode *node,*pre;
	int nextvex;
	int first;
	visit[index]=true;
	first=true;										//������ȱ���root��ÿһ���ڽӶ��㣬����������
	for(nextvex=FirstAdjVex(graph,index);nextvex>=0;nextvex=NextAdjVex(graph,index,nextvex)){
		if(visit[nextvex] == false){				//���û���ʹ����򽫴˶������ӵ�root�ϲ��ݹ鹹������
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=nextvex;						//����5�г�ʼ��һ�����ڵ�
			if(first){
				root->firstchild=node;
				first=false;						//�����ֵ�������һ���������Ÿ��ף��ڶ����������ŵ�һ������
			}else{
				pre->nextsibling=node;
			}
			pre=node;
			if(DFSTree(graph,nextvex,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
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
	for(tress=root;tress;tress=tress->nextsibling){		//��ɭ��root��ÿ����������һ��ǰ�����
		if(PreOrderTraverseCSTress(tress,visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}
Status PrintCSTree(CSTNode *node){
	printf("%3d",node->data);
	return OK;
}
Status DFSTraverse_sub(MGraph *graph,int start,Status (*traverse)(int),int *visit){
	int nextvex;
	if(traverse(start) == ERROR)return ERROR;
	visit[start]=true;
	for(nextvex=FirstAdjVex(*graph,start);nextvex>=0;nextvex=NextAdjVex(*graph,start,nextvex)){
		if(visit[nextvex] == false){
			if(DFSTraverse_sub(graph,nextvex,traverse,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse(MGraph *graph,Status (*traverse)(int)){
	int visit[MAXVEX];
	int i;
	if(graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	if(DFSTraverse_sub(graph,0,traverse,visit) == ERROR)return ERROR;
	return OK;
}
Status Print(int i){
	printf("%2d",i);
	return OK;
}
Status BFSTraverse(MGraph *graph,Status (*traverse)(int)){
	int queue[MAXVEX];			//������������queue�ͷ��ʱ�־����visit
	int top,buttom;				//top��ʾ���ж��ף�buttom��ʾ���ж�β
	int vexter;
	int nextvex;
	int visit[MAXVEX];
	int i;
	if(graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	top=buttom=0;				//��ʼ�����У����׵��ڶ�β��ʾ����Ϊ��
	queue[buttom]=0;
	buttom++;					//������ģ������У��������������У�Ȼ���β���һ��	
	visit[0]=true;
	while(top != buttom){		//�����в���ʱ
		vexter=queue[top];
		top++;					//������ģ������У���������ŴӶ����е�������ʹ�������һ��
		if(traverse(vexter) == ERROR)return ERROR;	//���ʶ���
		for(nextvex=FirstAdjVex(*graph,vexter);nextvex>=0;nextvex=NextAdjVex(*graph,vexter,nextvex)){
			if(visit[nextvex] == false){	//������㻹δ���ʹ�
				visit[nextvex]=true;
				queue[buttom]=nextvex;		//�������
				buttom++;
			}
		}
	}
	return OK;
}
Status DeleteArc(MGraph *graph,int v,int w){
	if(graph->vexnum == 0)return ERROR;
	if(v<0 || v>=graph->vexnum)return ERROR;
	if(w<0 || w>=graph->vexnum)return ERROR;
	if(graph->arcs[v][w] != MAXINT){
		graph->arcnum--;
		graph->arcs[v][w]=MAXINT;
		if(graph->kind == UDG || graph->kind == UDN)
			graph->arcs[w][v]=MAXINT;
	}
	return OK;
}
Status InsertArc(MGraph *graph,int v,int w,int adj){
	if(graph->vexnum == 0)return ERROR;
	if(v<0 || v>=graph->vexnum)return ERROR;
	if(w<0 || w>=graph->vexnum)return ERROR;
	if(adj <= 0)return ERROR;						//�жϲ����ĺϷ���
	if(graph->arcs[v][w] != MAXINT)return ERROR;	//�����бߣ�����error
	if(graph->kind == DG || graph->kind == UDG){	//��ӱߣ���������ͼ(��)��������ӶԳƱ�
		graph->arcs[v][w]=1;
		if(graph->kind == UDG)graph->arcs[w][v]=1;
	}else{
		graph->arcs[v][w]=adj;
		if(graph->kind == UDN)graph->arcs[w][v]=adj;
	}												
	graph->arcnum++;
	return OK;
}
Status InsertVex(MGraph *graph,int v){
	int i,j;
	if(graph->vexnum == 0 || graph->vexnum == MAXVEX)return ERROR;
	if(v < 0 || v > graph->vexnum)return ERROR;			//�ж�ͼ�Ͷ���ĺϷ���
	for(i=graph->vexnum-1;i>=v;i--){
		for(j=0;j<graph->vexnum;j++){				//�������Ժ�Ķ����������һ��
			graph->arcs[i+1][j]=graph->arcs[i][j];
		}
	}
	for(j=0;j<graph->vexnum;j++)graph->arcs[v][j]=MAXINT;	//�������б�����
	for(i=0;i<graph->vexnum+1;i++){					//�������Ժ�Ķ����������һ��
		for(j=graph->vexnum-1;j>=v;j--){
			graph->arcs[i][j+1]=graph->arcs[i][j];
		}
	}
	for(i=0;i<graph->vexnum+1;i++)graph->arcs[i][v]=MAXINT;	//�������б�����
	graph->vexnum++;
	return OK;
}
Status DeleteVex(MGraph *graph,int v){
	int i,j;
	if(graph->vexnum == 0)return ERROR;
	if(v < 0 || v >= graph->vexnum)return ERROR;	//�ж�ͼ�Ͷ���ĺϷ���
	for(i=0;i<graph->vexnum;i++)
		if(graph->arcs[v][i] != MAXINT)
			graph->arcnum--;						//��ȥ��vΪβ�Ļ�
	if(graph->kind == DG || graph->kind == DN){		//��graph������ͼ
		for(i=0;i<graph->vexnum;i++)				//����Ҫ��ȥ��vΪͷ�Ļ�
			if(graph->arcs[i][v] != MAXINT)
				graph->arcnum--;
	}
	for(i=v;i<graph->vexnum;i++){					//��v���µ��������ƶ�һ��
		for(j=0;j<graph->vexnum;j++){
			graph->arcs[i][j]=graph->arcs[i+1][j];
		}
	}
	for(i=0;i<graph->vexnum-1;i++){					//��v���ҵ��������ƶ�һ��
		for(j=v;j<graph->vexnum;j++){
			graph->arcs[i][j]=graph->arcs[i][j+1];
		}
	}
	graph->vexnum--;
	return OK;
}
int FirstAdjVex(MGraph graph,int v){
	int w;
	if(v<0 || v>=graph.vexnum || graph.vexnum==0)return -1;
	for(w=0;w<graph.vexnum;w++)
		if(graph.arcs[v][w] != MAXINT)return w;
	return -1;
}
int NextAdjVex(MGraph graph,int v,int w){
	int nexvex;
	if(graph.vexnum == 0)return -1;
	if(v<0 || v>=graph.vexnum)return -1;
	if(w<0 || w>=graph.vexnum)return -1;
	for(nexvex=w+1;nexvex<graph.vexnum;nexvex++)
		if(graph.arcs[v][nexvex] != MAXINT)return nexvex;
	return -1;
}
Status DestriyGraph(MGraph *graph){
	int i,j;
	if(graph == NULL)return ERROR;
	graph->arcnum=0;
	graph->vexnum=0;
	for(i=0;i<MAXVEX;i++)
		for(j=0;j<MAXVEX;j++)
			graph->arcs[i][j]=0;
	graph->kind=0;
	return OK;
}
Status CreateDG(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
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
	for(i=0;i<vexnum;i++){
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("������ߵ�ʼ����յ㣬����-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("�߲��Ϸ���\n");
			return ERROR;
		}
		if(start == end){
			printf("��������ֻ���\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=1;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDG(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
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
	for(i=0;i<vexnum;i++){				//��ʼ�����б�ΪMAXINT
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("������ߵ�ʼ����յ㣬����-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("�߲��Ϸ���\n");
			return ERROR;
		}
		if(start == end){
			printf("��������ֻ���\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=graph->arcs[end][start]=1;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateDN(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
	int start;
	int end;
	int adj;
	graph->kind=DN;
	printf("�����붥������");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){			//�ж϶��������Ƿ�Ϸ�
		printf("���������Ϸ���\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	for(i=0;i<vexnum;i++){					//��ʼ�����б�ΪMAXINT
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("������ߵ�ʼ�㡢�յ�ͱߵ�Ȩ������-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);					//�ж������յ�ĺϷ���
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("�߲��Ϸ���\n");
			return ERROR;
		}
		if(start == end){					//�涨����ͼ�����ܴ��ڻ�
			printf("��������ֻ���\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){							//�ж�Ȩ�ĺϷ���
			printf("��Ȩ���Ϸ���\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=adj;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDN(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
	int start;
	int end;
	int adj;
	graph->kind=UDN;
	printf("�����붥������");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){			//�ж϶������Ŀ�Ƿ�Ϸ�
		printf("���������Ϸ���\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	for(i=0;i<vexnum;i++){					//��ʼ�����б�ΪMAXINT
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("������ߵ�ʼ�㡢�յ�ͱߵ�Ȩ������-1����:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);					//�ж������յ�ĺϷ���
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("�߲��Ϸ���\n");
			return ERROR;
		}
		if(start == end){					//�涨����ͼ�����ܴ��ڻ�
			printf("��������ֻ���\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){							//�ж�Ȩ�ĺϷ���
			printf("��Ȩ���Ϸ���\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=graph->arcs[end][start]=adj;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateGraph(MGraph *graph){
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
int main(){
	MGraph graph;
	int dist[MAXVEX][MAXVEX];
	int path[MAXVEX][MAXVEX][MAXVEX+2];
	int i,j;
	CreateGraph(&graph);
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			if(graph.arcs[i][j] == MAXINT)printf("��");
			else printf("%2d",graph.arcs[i][j]);
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
