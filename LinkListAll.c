#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
// #define ERROR 0
// #define OVERFLOW -2
// #define true 1
// #define false 0
// #define OK 1
// #define Status int
// #define FreeNode(p) _FreeNode(&(p))	//����һ��ָ�뼴��
// typedef struct {						//�ڵ�����������
// 	double coef;				   	//ϵ��
// 	int expn;						//ָ��
// }*ElemType, term;
// typedef struct LNode {				//�ڵ�����
// 	ElemType data;
// 	struct LNode *next;
// }Link;
// typedef struct _linklist {			//��������
// 	Link *head;
// 	Link *tail;
// 	int len;
// }LinkList;
// typedef LinkList polynomail;		//�ض�����������Ϊ����ʽ����
// typedef LinkList SqStack;			//�ض�����������Ϊջ����
// typedef Link SElemType;				//�ض���ڵ�����Ϊջ�ڵ�����
// typedef ElemType SData;				//�ض���ڵ�����������Ϊջ�ڵ������������
// typedef LinkList LinkQueue;			//�ض�����������Ϊ��������
// typedef Link QNode;					//�ض�������ڵ�����Ϊ���нڵ�����
// typedef ElemType QData;				//�ض���ڵ�����������Ϊ���нڵ������������





// //�������������
// void _FreeNode(Link **p);
// //�ͷ�p��ָ�ڵ�
// Status MakeNode(Link **p, ElemType data);
// //������pָ���ֵΪe�Ľ�㣬������OK��������ʧ�ܣ��򷵻�ERROR
// Status InitList(LinkList *linklist);
// //����һ���յ���������linklist
// Status DestroyList(LinkList *linklist);
// //������������linklist��linklist���ٴ���
// Status ClearList(LinkList *linklist);
// //����������linklist����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
// Status InsFirst(Link *head, Link *p);
// //��֪headָ�����������ͷ��㣬��p��ָ��һ��(��)�������ڵ�һ�����֮ǰ
// Status DelFirst(Link *head, Link **p);
// //��֪headָ�����������ͷ��㣬ɾ�������еĵ�һ����㲢��q����
// Status Append(LinkList *linklist, Link *p);
// //��ָ��p��ָ���˴���ָ����������һ�������������������linklist�����һ���ڵ�
// //֮�󣬲��ı�����linklist��βָ��ָ���µ�β���
// Status Remove(LinkList *linklist, Link **p);
// //ɾ�����������β��㲢��p���أ��ı�����linklist��βָ��ָ���µ�β���
// Status InsBefore(LinkList *linklist, Link **p, Link *h);
// //��֪pָ�����������е�һ����㣬��h��ָ��������p��ָ���֮ǰ��
// //���޸�ָ��pָ���²���Ľڵ�
// Status InsAfter(LinkList *linklist, Link **p, Link *h);
// //��֪pָ�����������е�һ����㣬��s��ָ��������p��ָ���֮��
// //���޸�ָ��pָ���²���Ľڵ�
// Status LinkListInsert(LinkList *linklist, int position, ElemType e);
// //�ڴ�������������linklist�ĵ�i��Ԫ��֮ǰ����Ԫ��e
// Status SetCurElem(Link *p, ElemType e);
// //��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
// ElemType GetCurElem(Link *p);
// //��֪pָ�����������е�һ����㣬����p��ָ���������Ԫ�ص�ֵ
// Status ListEmpty(LinkList linklist);
// //����������Ϊ�ձ��򷵻�TRUE�����򷵻�FALSE
// int ListLength(LinkList linklist);
// //������������linklist��Ԫ�ظ���
// Link *GetHead(LinkList linklist);
// //������������linklistͷ���
// Link *GetLast(LinkList linklist);
// //������������linklistβ���
// Link *PriorPos(LinkList linklist, Link *p);
// //��֪pָ�����������һ����㣬����p��ָ����ֱ��ǰ����λ��
// //����ǰ�����򷵻�NULL
// Link *NextPos(LinkList linklist, Link *p);
// //��֪pָ�����������һ����㣬����p��ָ����ֱ�Ӻ�̵�λ��
// //���޺�̣��򷵻�NULL
// Status LocatePos(LinkList linklist, int i, Link **p);
// //����pָʾ��������linklist�е�i������λ�ò�����OK��iֵ���Ϸ�ʱ����ERROR
// Status inverse(Link *p);
// //���������õĹ��ܺ������书���ǽ����p��������Ԫ�ص�coef(ϵ��)ȡ��
// Status PrintLinkList(Link *p);
// //���������õĹ��ܺ������书���Ǵ�ӡ�ڵ�p�е�����������Ա
// Status ListTraverse(LinkList linklist, Status(*visit)(Link*));
// //���ζ�linklist��ÿ��Ԫ�ص���visit()��һ������ʧ�ܣ������ʧ��





// //����Ӧ�á�������ʽ����������
// Status SetPolyn(ElemType *e, double coef, int expn);
// //������eָ���Ԫ�ص�����ֵ����������coef��expn��Ա��������OK��������ʧ�ܣ��򷵻�ERROR
// Status CreatPolyn(polynomail *p, int m);
// //����m���ϵ����ָ����������ʾһԪ����ʽ����������p
// Status DestroyPolyn(polynomail *p);
// //����һԪ����ʽp
// void PrintPolyn(polynomail p);
// //��ӡ���һԪ����ʽ
// int PolynLength(polynomail p);
// //����һԪ����ʽp�е�����
// void SortPolyn(polynomail *p);
// //��һԪ����ʽ�������򡢺ϲ���ɾ��������һԪ����ʽ��Ϊָ���ӵ͵��ߵ�ϵ����Ϊ0����ʽ
// void AddPolyn(polynomail *pa, polynomail *pb);
// //���һԪ����ʽ��������㣬����pa=pa+pb��������һԪ����ʽpb
// void SubtractPolyn(polynomail *pa, polynomail *pb);
// //���һԪ����ʽ��������㣬����pa=pa-pb��������һԪ����ʽpb
// Link *sub_MultiplyPolyn(Link *p, polynomail *pb);
// //��ɵ���ʽ��������㣬����pc=a*pb����һԪ����ʽ��˵Ļ���
// Status MultiplyPolyn(polynomail *pa, polynomail *pb);
// //���һԪ����ʽ��������㣬����pa=pa*pb��������һԪ����ʽpb





// //��ջ�Ļ���������
// Status InitStack(SqStack *stack);
// //����һ����ջstack
// Status DestroyStack(SqStack *stack);
// //����ջstack��ջstack���ٴ���
// Status ClearStack(SqStack *stack);
// //��ջstack��Ϊ��ջ�����ͷ�ԭ����Ľ��ռ�
// Status StackEmpty(SqStack stack);
// //��ջstackΪ��ջ���򷵻�TRUE�����򷵻�FALSE
// int StackLength(SqStack stack);
// //����ջstack�Ľڵ��������ջ�ĳ���
// Status GetTop(SqStack stack, SElemType **e);
// //��e����ջStack��ջ���ڵ�
// Status Pop(SqStack *stack, SElemType **e);
// //ɾ��ջstack��ջ���ڵ㣬����e������ֵ
// Status Push(SqStack *stack, SElemType *e);
// //����ڵ�ΪeΪ�µ�ջ���ڵ�
Status SetData(SData *e, double dou, int num);
//������eָ���Ԫ�ص�����ֵ����������coef��expn��Ա��������OK��������ʧ�ܣ��򷵻�ERROR
// void PrintStr(SElemType e);
// //���������õĹ��ܺ������书���Ǵ�ӡ���e��������Ԫ�ص�expn(�ַ�)
// void PrintNum(SElemType e);
// //���������õĹ��ܺ������书���Ǵ�ӡ���e��������Ԫ�ص�expn(����)
// void PrintNode(SElemType e);
// //���������õĹ��ܺ������书���Ǵ�ӡ���e��������Ԫ�ص�coef��expn
// Status StackTraverse(SqStack stack, void(*visit)(SElemType));
// //��ջ�͵�ջ�����ζ�S��ÿ������Ԫ�ص��ú���visit(),һ��visit()����ʧ�ܣ������ʧ��





// //��ջӦ�á�������ת��������ƥ�䡢�б༭�����ʽ��ֵ��8�ʺ�����
// void Conversion(int num, int base);
// //����ת������ʮ������numת��Ϊbase���Ƶ�����
// Status BracketMatch(char *str);
// //����ƥ�䣬ʵ������С�����������ŵ�ƥ�䡣�ɹ�ƥ�䷵��OK��ƥ��ʧ�ܷ���ERROR
// void LineEdit(char back, char clear);
// //�б༭�������趨backΪ�˸����clearΪ�������ʵ���˸�ɾ��һ���ַ������ɾ��һ���ַ�
// int Precede(char ch1, char ch2);
// //�Ƚ���������������ȼ�����ch1�����ȼ�С��ch2������ֵС��0���Դ�����
// Status GetNum(char **str, double *dou);
// //���ַ��������������ַ�ת��Ϊ������
// SElemType *Operate(SElemType *num1, SElemType *operator,SElemType *num2);
// //����������������
// SElemType *Calculator(char *str);
//���ʽ��ֵ
// typedef struct {
// 	int x, y;					//ϡ��������Ԫ�ص�����
// 	int value;					//ϡ��������Ԫ�ص�ֵ
// }Triple;
// typedef struct {
// 	Triple data[8];				//����ϡ��������Ԫ�ص���Ϣ
// 	int row, column, num;			//ϡ���������������ͷ���Ԫ�ظ���
// }TSMatrix;
// Status CreateSMatrix(TSMatrix *matrix, SqStack stack);
// //����ջ�����ݴ�����Ӧ��ϡ�����matrix����ʾ�����ϻʺ��λ��
// void PrintSMatrix(TSMatrix matrix);
// //��ӡϡ�����
// void SortMatrix(TSMatrix *matrix);
// //��ϵ������ķ���Ԫ�ص������������У�ʹ�������С��������
// Status sub_isEquel(TSMatrix matrix1, TSMatrix matrix2);
// //�ж����������ʾ�������Ƿ���ͨ����ת�õ������ܼ���ͬһ��������TRUE�����򷵻�FALSE
// Status isEquel(TSMatrix *matrix1, TSMatrix matrix2, int length);
// //�жϾ���matrix2�Ƿ���ͨ��֮ǰ����һ��������ת��ã����ܷ���TRUE�����򷵻�FALSE
// int CompareMatrix(TSMatrix matrix1, TSMatrix matrix2);
// //�Ƚ����������Ƿ����
// Status LRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2);
// //��ϡ�����matrix2��ʱ����ת90�ȵľ���matrix1
// Status RRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2);
// //��ϡ�����matrix2˳ʱ����ת90�ȵľ���matrix1
// Status TurnMatrix(TSMatrix *matrix1, TSMatrix matrix2);
// //��ϡ�����matrix2��ת180�ȵľ���matrix1
// Status isPeace(SqStack stack, SData data);
// //���ջ��Ԫ�ص������Ƿ�������Ԫ�ش���ͬһ�л���ͬһ�л���ͬһб�ߣ��Ƿ���ERROR���񷵻�OK
// //���������������ƣ��涨coefΪ��(double��)��expnΪ��(int��)
// void EightQueen();
// //���˻ʺ����⣬����8*8�Ĺ������������ϰڷŰ˸��ʺ�ʹ�䲻��ͬһ�л���ͬһ�л���ͬһб���ϵ����аڷ�





// //���еĻ���������
// Status InitQueue(LinkQueue *Q);
// //����һ���ն���Q
// Status DestroyQueue(LinkQueue *Q);
// //���ٶ���Q��Q���ٴ���
// Status ClearQueue(LinkQueue *Q);
// //��Q��Ϊ�ն���
// Status QueueEmpty(LinkQueue Q);
// //������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
// int QueueLength(LinkQueue Q);
// //����Q��Ԫ�ظ����������еĳ���
// Status GetQHead(LinkQueue Q, QData *e);
// //�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
// Status EnQueue(LinkQueue *Q, QData e);
// //����Ԫ��eΪQ�Ķ�βԪ��
// Status DeQueue(LinkQueue *Q, QData *e);
// //�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�FALSE
// void PrintQueue(QData data);
// //���б��������Ĺ��ܺ������书���Ǵ�ӡ����Ԫ�ص�����ֵ
// Status QueueTraverse(LinkQueue Q, void(*visit)(QData));
// //�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���visit(),һ��visit����ʧ�ܣ������ʧ��





//���е��ռ�Ӧ�ã�����ҵ��ģ��
//���ܣ�ģ������һ���пͻ������ж�����ƽ��ʱ�䣨���㷽����ƽ������ʱ��=�ܶ���ʱ��/��������
//�������ͣ������루��������
//�����������¼�����ģ�⣬��һ��������Ϊ�¼����¼�ͻ����¼�����(���ﻹ���뿪)�͵���ʱ�䡣
//      ���ĸ����зֱ�����ĸ����ڣ���������Ԫ�ص����ݰ����û������ʱ����¼����ͣ�
//		���е�����Ԫ�����ݰ����ͻ������ʱ��Ϳͻ�����ҵ������ʱ�䡣
//���̣����ȼ���¼����һ�����(���ʼ����һ������Ŀͻ�Ϊ��һ�����)������һ��
//		�����Ϊ��һ���ͻ�����ļ��ʱ�䣬������һ���ͻ������ʱ�䲢����һ�����(�¼�)
//		��ʱ���Ⱥ�˳����뵽���Ա��У�������һ���������ʾ�ͻ�����ҵ������ʱ�䣬
//		���ͻ����ŵ�����(Ԫ��)���ٵĴ���(����)�У�����ÿͻ��Ǹô��ڵ�һ��(Ψһ��)�ͻ���
//		��Ҫ�ڴ�ʱ�����뿪�¼�����ʱ���(�����л��������ͻ������¼���Ŀͻ��뿪ʱ��ȡ����ǰ����˵İ���ʱ�����뿪ʱ�䣬�ʴ�ʱ�������������뿪�¼�)
//		���ǵ�һ���ͻ����򲢸��ݹ˿͵���ʱ����Ⱥ�ʱ������뿪ʱ�䣬���¼�����һ��
//		���ɿͻ��뿪�¼���ʱ��˳����뵽�¼����С����¼�������ϣ����¼�����ɾ�����¼���
//		���ż���¼�����һ����㣬�������¼������ж��¼����ͣ����ǵ����¼�������е���ʱ��Ĵ���
//		���ɼ��ʱ�䣬������һ���ͻ�����ʱ�����ɵ���ڵ�����¼�����(ע�⵽��ʱ�������ڽ���Ӫҵʱ��)
//		������ҵ�����ʱ�䰲�ŵ������У��ж��Ƿ��ǵ�һ���ͻ������ǣ��������뿪�¼������¼���
//		�����ǣ��������뿪�¼������¼����С����¼�������ϣ���ʱ���ɾ����ʱ�䣬���Ŵ�����һ�¼�
//		�������¼����ж��¼����ͣ������뿪ʱ�䣬������뿪�¼��Ĵ������㶺��ʱ�䣬
//		�������������ܶ���ʱ�䣬Ϊ��һ�ͻ������뿪�¼�����ʱ����У�ɾ����ͷԪ�أ����¼�������ϣ�
//		��ʱ�����ɾ�����¼���
//˵�������������������ƣ��涨�¼�����coefΪ�¼�����ʱ��(double��)��expnΪ�¼�����(int��)
//					      ����(����)��coefΪ�ͻ�����ʱ��(double��)��expnΪҵ����ʱ��(int��)
typedef struct _bankinformation {
	LinkQueue *eventlist;					//�¼���
	LinkQueue *service[4];					//�ĸ�������Ϊ����
	int total_time;							//�ܵȺ�ʱ��
	int total_num;							//������
	int opentime;							//Ӫҵʱ��(����)
	int closetime;			  				//����ʱ��(����)
	int intertime_arr;						//���������ʱ��
	int intertime_work;						//ҵ��ȴ��ʱ��
}BankInfor;
//�����е�������Ϣ��װ��һ���ṹ����
int Minimum(BankInfor *infor);
//�ҳ��ĸ�������Ԫ��(����)���ٵĶ��е��±�
Status EventInsert(BankInfor *infor, int evtype, int arrivetime);
//���¼����ͺ��¼�����ʱ���װ�ɽṹ������¼�����
Status OpenForDay(BankInfor *infor, int opentime, int closetime, int intertime_arr, int intertime_work);
//��ʼ����Ϣ�ṹ������¼������к��ĸ�ʱ�䣬������һ�����������ӵ��¼�����
double CloseForDay(BankInfor *infor);
//������Ϣ�ṹ����ĸ��ֽṹ�壬���㲢����ƽ���Ⱥ�ʱ��
void CustomerArrived(BankInfor *infor);
//�������¼������ͻ���ӵ��������ٵĶ����У����¼�����ɾ����ʱ��
void CustomerDeparture(BankInfor *infor);
//�����뿪ʱ�䣬���ͻ��Ⱥ�ʱ�������ʱ�䣬���ͻ��Ӷ�����ɾ���������¼����¼�����ɾ��
void BankSimulation(int opentime, int closetime, int intertime_arr, int intertime_work, int isPrint);
//ģ������ҵ�񣬼���ÿ���˾��Ⱥ�ʱ��





Status EventInsert(BankInfor *infor, int evtype, int arrivetime) {
	QData data;
	QNode *node;
	QNode *p;
	if (!SetData(&data, arrivetime, evtype))return ERROR;
	if (!MakeNode(&node, data))return ERROR;
	p = infor->eventlist->head->next;
	for (; p != NULL&&p->data->coef < arrivetime; p = p->next);
	if (!p)Append(infor->eventlist, node);
	else InsBefore(infor->eventlist, &p, node);
	return OK;
}
Status OpenForDay(BankInfor *infor, int opentime, int closetime, int intertime_arr, int intertime_work) {
	int i;
	int arrtime;
	time_t t;
	time(&t);
	srand(t);
	infor->eventlist = (LinkQueue *)malloc(sizeof(LinkQueue));
	if (!infor->eventlist)return ERROR;
	if (!InitQueue(infor->eventlist))return ERROR;
	for (i = 0; i < 4; i++) {
		infor->service[i] = (LinkQueue *)malloc(sizeof(LinkQueue));
		if (!infor->service[i])return ERROR;
		if (!InitQueue(infor->service[i]))return ERROR;
	}
	infor->total_num = infor->total_time = 0;
	infor->opentime = opentime;
	infor->closetime = closetime;
	infor->intertime_work = intertime_work;
	infor->intertime_arr = intertime_arr;
	arrtime = rand() % infor->intertime_arr + infor->opentime;
	if (!EventInsert(infor, 0, arrtime))return ERROR;
	return OK;
}
double CloseForDay(BankInfor *infor) {
	double aver_time;
	int i;
	DestroyQueue(infor->eventlist);
	free(infor->eventlist);
	infor->eventlist = NULL;
	for (i = 0; i < 4; i++) {
		DestroyQueue(infor->service[i]);
		free(infor->service[i]);
		infor->service[i] = NULL;
	}
	aver_time = infor->total_time*1.0 / infor->total_num;
	infor->total_num = infor->total_time = 0;
	infor->opentime = infor->closetime = 0;
	infor->intertime_arr = infor->intertime_work = 0;
	return aver_time;
}
int Minimum(BankInfor *infor) {
	int len[4];
	int i, min;
	for (i = 0, min = 0; i < 4; i++) {
		len[i] = QueueLength(*infor->service[i]);
		if (len[i] < len[min])min = i;
	}
	return min;
}
void CustomerArrived(BankInfor *infor) {
	int duringtime;
	int arrivetime;
	int min;
	QData data;
	QData t;
	QNode *node;
	time_t T;
	time(&T);
	srand(T);
	DeQueue(infor->eventlist, &data);
	infor->total_num++;
	duringtime = rand() % infor->intertime_work;
	arrivetime = rand() % infor->intertime_arr + (int)data->coef;
	min = Minimum(infor);
	SetData(&t, data->coef, duringtime);
	EnQueue(infor->service[min], t);
	if (arrivetime < infor->closetime)EventInsert(infor, 0, arrivetime);
	if (QueueLength(*infor->service[min]) == 1)EventInsert(infor, min + 1, duringtime + data->coef);
}
void CustomerDeparture(BankInfor *infor) {
	QData data;
	QData customer;
	int i;
	DeQueue(infor->eventlist, &data);
	i = data->expn - 1;
	DeQueue(infor->service[i], &customer);
	infor->total_time += data->coef - customer->coef;
	if (!QueueEmpty(*infor->service[i])) {
		GetQHead(*infor->service[i], &customer);
		EventInsert(infor, i + 1, data->coef + customer->expn);
	}
}
void BankSimulation(int opentime, int closetime, int intertime_arr, int intertime_work, int isPrint) {
	BankInfor infor;
	int i;
	int j;
	OpenForDay(&infor, opentime, closetime, intertime_arr, intertime_work);
	if (isPrint) {
		ListTraverse(*infor.eventlist, PrintLinkList);
		printf("\n");
	}
	while (!QueueEmpty(*infor.eventlist)) {
		i = (infor.eventlist)->head->next->data->expn;
		if (!i) {
			CustomerArrived(&infor);
			if (isPrint) {
				ListTraverse(*infor.eventlist, PrintLinkList);
				printf("%d %d %d %d\n", QueueLength(*infor.service[0]), QueueLength(*infor.service[1]), QueueLength(*infor.service[2]), QueueLength(*infor.service[3]));
				for (j = 0; j < 4; j++) {
					printf("Queue%d:", j);
					QueueTraverse(*infor.service[j], PrintQueue);
					printf("\n");
				}
				printf("\n");
			}
		}
		else {
			CustomerDeparture(&infor);
			if (isPrint) {
				ListTraverse(*infor.eventlist, PrintLinkList);
				printf("%d %d %d %d\n", QueueLength(*infor.service[0]), QueueLength(*infor.service[1]), QueueLength(*infor.service[2]), QueueLength(*infor.service[3]));
				for (j = 0; j < 4; j++) {
					printf("Queue%d:", j);
					QueueTraverse(*infor.service[j], PrintQueue);
					printf("\n");
				}
				printf("\n");
			}
		}
		if (isPrint)getch();
	}
	i = infor.total_num;
	j = infor.total_time;
	printf("��������%d(��)\n��ʱ�䣺%d(����)\nƽ��ʱ�䣺%.2f(����)\n", i, j, CloseForDay(&infor));
}





// Status InitQueue(LinkQueue *Q) {
// 	if (InitList(Q) == ERROR)return ERROR;
// 	else return OK;
// }
// Status DestroyQueue(LinkQueue *Q) {
// 	if (DestroyList(Q) == ERROR)return ERROR;
// 	else return OK;
// }
// Status ClearQueue(LinkQueue *Q) {
// 	if (ClearList(Q) == ERROR)return ERROR;
// 	else return OK;
// }
// Status QueueEmpty(LinkQueue Q) {
// 	return ListEmpty(Q);
// }
// int QueueLength(LinkQueue Q) {
// 	return ListLength(Q);
// }
// Status EnQueue(LinkQueue *Q, QData e) {
// 	QNode *t;
// 	if (MakeNode(&t, e) == ERROR)return ERROR;
// 	if (Append(Q, t) == ERROR)return ERROR;		//������β����ڵ�ģ�������
// 	else return OK;
// }
// Status GetQHead(LinkQueue Q, QData *e) {
// 	QNode *t;
// 	if ((t = GetHead(Q)) == NULL)return ERROR;		//������(����)Ϊ�գ���GetHead����NULL
// 	else {
// 		*e = t->data;
// 		return OK;
// 	}
// }
// Status DeQueue(LinkQueue *Q, QData *e) {
// 	QNode *t;									//ɾ�������һ����㣬ģ�������
// 	t = Q->head->next;
// 	if (!t)return ERROR;					//����Ϊ�գ��޷������У�����ERROR
// 	if (!t->next)Q->tail = Q->head;
// 	Q->head->next = t->next;
// 	*e = t->data;
// 	free(t);
// 	Q->len--;
// 	return OK;
// }
// void PrintQueue(QData data) {
// 	printf("%d %d  ", (int)data->coef, data->expn);
// }
// Status QueueTraverse(LinkQueue Q, void(*visit)(QData)) {
// 	QNode *p;
// 	for (p = (Q.head)->next; p; p = p->next)visit(p->data);
// 	return OK;
// }






// Status StackTraverse(SqStack stack, void(*visit)(SElemType)) {
// 	if (stack.len <= 0)return ERROR;
// 	SElemType *e;							//��������void�ģ�Ӧ����Status�ȽϺ�
// 	for (e = (stack.head)->next; e; e = e->next)visit(*e);
// 	printf("\n");
// 	return OK;
// }
Status SetData(SData *e, double dou, int num) {
	if (SetPolyn(e, dou, num) == ERROR)return ERROR;
	else return OK;
}
// Status InitStack(SqStack *stack) {
// 	if (InitList(stack) == ERROR)return ERROR;
// 	else return OK;
// }
// void PrintStr(SElemType e) {
// 	printf("%c", (e.data)->expn);
// }
// void PrintNum(SElemType e) {
// 	printf("%d ", (e.data)->expn);
// }
// void PrintNode(SElemType e) {
// 	printf("%d   %d\n", (int)(e.data)->coef, (e.data)->expn);
// }
// Status DestroyStack(SqStack *stack) {
// 	if (DestroyList(stack) == ERROR)return ERROR;
// 	else return OK;
// }
// Status ClearStack(SqStack *stack) {
// 	if (ClearList(stack) == ERROR)return ERROR;
// 	else return OK;
// }
// Status StackEmpty(SqStack stack) {
// 	return ListEmpty(stack);
// }
// Status GetTop(SqStack stack, SElemType **e) {
// 	if ((*e = GetLast(stack)) == NULL)return ERROR;	//����ջ����������
// 	return OK;										//��GetLast����NULL
// }
// int StackLength(SqStack stack) {
// 	return ListLength(stack);
// }
// Status Push(SqStack *stack, SElemType *e) {
// 	if (Append(stack, e) == ERROR)return ERROR;		//���������һ����㣬ģ����ջ
// 	else return OK;
// }
// Status Pop(SqStack *stack, SElemType **e) {
// 	if (Remove(stack, e) == ERROR)return ERROR;		//������ɾ��һ����㣬ģ���ջ
// 	else return OK;
// }





// void _FreeNode(Link **p) {
// 	if (p&&*p) {
// 		if ((*p)->data)
// 			free((*p)->data);
// 		(*p)->data = NULL;
// 		free(*p);
// 		*p = NULL;
// 	}
// }
// Status MakeNode(Link **node, ElemType data) {
// 	if (!node)
// 		return ERROR;
// 	*node = (Link*)malloc(sizeof(Link));
// 	if (!*node)
// 		return OVERFLOW;
// 	(*node)->data = data;
// 	(*node)->next = NULL;
// 	return OK;
// }
// Status InitList(LinkList *linklist) {
// 	if (!linklist)
// 		return ERROR;
// 	linklist->tail = linklist->head = (Link *)malloc(sizeof(Link));	//������ͷ�ڵ㣬����ͷ��β��ָ��ͷ����ʾ������
// 	if (!linklist->head)
// 		return OVERFLOW;
// 	linklist->head->data = NULL;
// 	linklist->head->next = NULL;
// 	linklist->len = 0;
// 	return OK;
// }
// Status DestroyList(LinkList *linklist) {
// 	if (!linklist)
// 		return ERROR;
// 	if (ClearList(linklist) == ERROR)
// 		return ERROR;
// 	free(linklist->head);
// 	linklist->len = 0;
// 	linklist->tail = NULL;
// 	linklist->head = NULL;
// 	return OK;
// }
// Status ClearList(LinkList *linklist) {
// 	if (!linklist)
// 		return ERROR;
// 	Link *pf, *pb;
// 	pb = linklist->head->next;			//����㶼�ͷ���
// 	while (pb) {
// 		pf = pb->next;
// 		FreeNode(pb);
// 		pb = pf;
// 	}
// 	linklist->len = 0;					//�޸ĳ���
// 	linklist->head->next = NULL;			//�޸���ͷ���
// 	linklist->tail = linklist->head;		//�޸���βָ��
// 	return OK;
// }
// Status InsFirst(Link *head, Link *p) {
// 	Link *tail;
// 	if (!p || !head)
// 		return ERROR;
// 	for (tail = p; tail->next; tail = tail->next);	//�ҵ�p��β��
// 	tail->next = head->next;					//����
// 	head->next = p;
// 	return OK;
// }
// Status DelFirst(Link *head, Link **p) {
// 	if (!head || !head->next)
// 		return ERROR;					//����ǿ������޷�ɾ��������ERROR
// 	*p = head->next;						//ȡ����һ�����
// 	head->next = (*p)->next;				//�޸�ָ��ڶ������
// 	(*p)->next = NULL;
// 	return OK;
// }
// Status Append(LinkList *linklist, Link *p) {
// 	Link *t;
// 	int i;
// 	if (!p || !linklist)
// 		return ERROR;
// 	for (i = 1, t = p; t->next; t = t->next, ++i);	//�ҵ�p��β�ͣ�ͬʱͳ�ƽ�����
// 	linklist->tail->next = p;				//����
// 	linklist->tail = t;
// 	linklist->len += i;
// 	return OK;
// }
// Status Remove(LinkList *linklist, Link **p) {
// 	Link *t;
// 	if (!linklist || linklist->len == 0)
// 		return ERROR;
// 	*p = linklist->tail;
// 	--linklist->len;
// 	for (t = linklist->head; t->next != linklist->tail; t = t->next);
// 	t->next = NULL;
// 	linklist->tail = t;
// 	return OK;
// }
// Status InsBefore(LinkList *linklist, Link **p, Link *h) {
// 	Link *t;
// 	if (!linklist || linklist->len == 0 || !h)
// 		return ERROR;
// 	for (t = linklist->head; t->next&&t->next != *p; t = t->next);
// 	if (!t->next)			// p���������еĽڵ�
// 		return ERROR;
// 	if (InsFirst(t, h) == ERROR)
// 		return ERROR;
// 	++linklist->len;
// 	*p = h;
// 	return OK;
// }
// Status InsAfter(LinkList *linklist, Link **p, Link *h) {
// 	Link *t;
// 	if (!linklist || linklist->len == 0 || !h)
// 		return ERROR;
// 	for (t = linklist->head; t&&t != *p; t = t->next);
// 	if (!t)						// p���������еĽڵ�
// 		return ERROR;
// 	++linklist->len;			// �޸ĳ���
// 	h->next = t->next;			// �޸�ָ��ָ��
// 	t->next = h;
// 	if (t == linklist->tail)		// ���p��β�ڵ㣬����Ҫ�޸�linklist.tail
// 		linklist->tail = h;
// 	return OK;
// }
// Status LinkListInsert(LinkList *linklist, int position, ElemType e) {
// 	Link *t;									//ֻ�ܲ��뵽[0,len)֮���λ�ã�����ı�β���
// 	Link *newnode;
// 	if (LocatePos(*linklist, position - 1, &t) == ERROR)return ERROR;
// 	if (MakeNode(&newnode, e) == ERROR)return ERROR;
// 	if (InsFirst(t, newnode) == ERROR)return ERROR;
// 	linklist->len++;
// 	return OK;
// }
// Status SetCurElem(Link *p, ElemType e) {
// 	if (p == NULL)
// 		return ERROR;
// 	p->data = e;
// 	return OK;
// }
// ElemType GetCurElem(Link *p) {
// 	return p ? p->data : NULL;
// }
// Status ListEmpty(LinkList linklist) {
// 	return linklist.len ? false : true;
// }
// int ListLength(LinkList linklist) {
// 	Link *t;							//������linklist.lenֱ�ӻ��
// 	int i;								//������������ڵ����
// 	for (t = linklist.head, i = 0; t->next; t = t->next, i++);
// 	return i;
// }
// Link *GetHead(LinkList linklist) {
// 	return (linklist.head)->next;		//����linklist.headֱ�ӷ��ص�һ��
// }
// Link *GetLast(LinkList linklist) {
// 	Link *t; 							//������linklist.tailֱ�ӻ�ã�ͨ����������õ����һ��
// 	if (ListEmpty(linklist) == true)
// 		return NULL;					//����ǿձ���û�����һ��������ERROR
// 	for (t = linklist.head; t->next; t = t->next); //һֱ�ߵ�ͷ�����ظýڵ�
// 	return t;
// }
// Link *PriorPos(LinkList linklist, Link *p) {
// 	Link *t;
// 	if (p == linklist.head || p == NULL)return NULL;		//�ýڵ������׽ڵ㣬����һ����㣬����NULL
// 	for (t = linklist.head; t->next&&t->next != p; t = t->next);	//һֱ�ߵ�p����һ��
// 	if (!t->next)
// 		return NULL;						//��û�ҵ���һ����p����p���������еĽ�㣬����ERROR
// 	else
// 		return t;
// }
// Link *NextPos(LinkList linklist, Link *p) {
// 	Link *t;
// 	if (p == NULL)
// 		return NULL;
// 	for (t = linklist.head; t&&t != p; t = t->next);	//�ҵ����p
// 	if (!t)
// 		return NULL;						//��û�ҵ����p����ERROR
// 	else
// 		return t->next;					//���򷵻�p����һ���ڵ�
// }
// Status LocatePos(LinkList linklist, int i, Link **p) {
// 	int count;
// 	Link *t;
// 	if (i < 0 || i >= linklist.len)
// 		return ERROR;		//λ�÷Ƿ�����ERROR
// 	for (count = 0, t = (linklist.head)->next; count < i&&t; t = t->next, count++);
// 	if (!t)
// 		return ERROR;
// 	*p = t;
// 	return OK;
// }
// Status inverse(Link *p) {
// 	if (!p)
// 		return ERROR;
// 	p->data->coef *= -1;
// 	return OK;
// }
// Status PrintLinkList(Link *p) {
// 	if (!p)
// 		return ERROR;
// 	printf("%d  %f\n", p->data->expn, p->data->coef);
// 	return OK;
// }
// Status ListTraverse(LinkList linklist, Status(*visit)(Link*)) {
// 	Link *p;
// 	for (p = (linklist.head)->next; p; p = p->next)
// 		if (visit(p) == ERROR)
// 			return ERROR;
// 	return OK;
// }




// void Conversion(int num, int base) {
// 	SqStack stack;
// 	SData e;
// 	SElemType *t;
// 	int basenum[100], i;
// 	InitStack(&stack);
// 	if (!num)printf("0\n");
// 	for (i = 0; i < 100; i++) {				//��Ϊ����ʮ���ƾ�Ҫ��ABCD��
// 		if (i < 10)basenum[i] = '0' + i;	//������һ�����鴢��һ�ű��ñ��Ǹý������õķ��ż���
// 		else basenum[i] = 'A' + i - 10;
// 	}
// 	while (num) {
// 		SetData(&e, 0, basenum[num%base]);	//�Ѹý������õķ�����ջ������λ����ջ����λ����ջ
// 		MakeNode(&t, e);
// 		Push(&stack, t);
// 		num /= base;
// 	}
// 	while (!StackEmpty(stack)) {
// 		Pop(&stack, &t);			//��ջ����ӡ
// 		printf("%c", t->data->expn);
// 	}
// 	printf("\n");
// 	DestroyStack(&stack);
// }
// Status BracketMatch(char *str) {
// 	SqStack stack;
// 	InitStack(&stack);
// 	SElemType *t;
// 	SData e;
// 	for (; *str; str++) {
// 		if (*str == '[') {
// 			SetData(&e, 0, 1);	//��1��ʾ'['
// 			MakeNode(&t, e);
// 			Push(&stack, t);
// 		}
// 		else if (*str == ']') {	//��2��ʾ']'
// 			if (StackEmpty(stack))return ERROR;
// 			GetTop(stack, &t);
// 			if (t->data->expn == 1) {
// 				Pop(&stack, &t);
// 				FreeNode(t);
// 			}
// 			else return ERROR;
// 		}
// 		else if (*str == '(') {	//��3��ʾ'('
// 			SetData(&e, 0, 2);
// 			MakeNode(&t, e);
// 			Push(&stack, t);
// 		}
// 		else if (*str == ')') {	//��4��ʾ')'
// 			if (StackEmpty(stack))return ERROR;
// 			GetTop(stack, &t);
// 			if (t->data->expn == 2) {
// 				Pop(&stack, &t);
// 				free(t);
// 			}
// 			else return ERROR;
// 		}
// 	}
// 	if (StackEmpty(stack)) {
// 		DestroyStack(&stack);
// 		return OK;
// 	}
// 	else {
// 		DestroyStack(&stack);
// 		return ERROR;
// 	}
// }
// void LineEdit(char back, char clear) {
// 	SqStack stack;
// 	char ch;
// 	SElemType *e;
// 	SData data;
// 	InitStack(&stack);
// 	ch = getchar();
// 	while (ch != EOF&&ch != '\n') {
// 		if (ch == back) {
// 			Pop(&stack, &e);
// 			free(e);
// 		}
// 		else if (ch == clear)ClearStack(&stack);
// 		else {
// 			SetData(&data, 0, ch);
// 			MakeNode(&e, data);
// 			Push(&stack, e);
// 		}
// 		ch = getchar();
// 	}
// 	StackTraverse(stack, PrintStr);
// 	DestroyStack(&stack);
// }
// int Precede(char ch1, char ch2) {
// 	if (ch1 == '=') {
// 		if (ch2 == '=')return 0;
// 		else return -1;
// 	}
// 	else if (ch1 == ')') {
// 		return 1;
// 	}
// 	else if (ch1 == '(') {
// 		if (ch2 == ')')return 0;
// 		else return -1;
// 	}
// 	else if (ch1 == '*' || ch1 == '/') {
// 		if (ch2 == '(')return -1;
// 		else return 1;
// 	}
// 	else if (ch1 == '+' || ch1 == '-') {
// 		if (ch2 == '(' || ch2 == '*' || ch2 == '/')return -1;
// 		else return 1;
// 	}
// 	return -2;
// }
// Status GetNum(char **str, double *dou) {
// 	char s[11];
// 	int n = 0;
// 	for (; **str && (isdigit(**str) || **str == '.'); (*str)++) {
// 		s[n++] = **str;
// 	}
// 	s[n] = '\0';
// 	if (!**str)return ERROR;
// 	*dou = atof(s);
// 	(*str)--;
// 	return OK;
// }
// SElemType *Operate(SElemType *num1, SElemType *operator,SElemType *num2) {
// 	double result = 0;
// 	SData data;
// 	SElemType *e;
// 	switch (operator->data->expn) {
// 	case '+':result = num1->data->coef + num2->data->coef; break;
// 	case '-':result = num1->data->coef - num2->data->coef; break;
// 	case '*':result = num1->data->coef*num2->data->coef; break;
// 	case '/':result = num1->data->coef / num2->data->coef; break;
// 	}
// 	SetData(&data, result, 0);
// 	MakeNode(&e, data);
// 	return e;
// }
// SElemType *Calculator(char *str) {
// 	SqStack optr;
// 	SqStack opnd;
// 	SElemType *e;
// 	SData data;
// 	double dou = 0;
// 	if (BracketMatch(str) == ERROR)return ERROR;
// 	InitStack(&optr);
// 	InitStack(&opnd);
// 	SetData(&data, 0, '=');
// 	MakeNode(&e, data);
// 	Push(&optr, e);
// 	while (*str) {
// 		if (isdigit(*str)) {
// 			if (GetNum(&str, &dou) == ERROR)break;
// 			SetData(&data, dou, 0);
// 			MakeNode(&e, data);
// 			Push(&opnd, e);
// 			str++;
// 		}
// 		else {
// 			GetTop(optr, &e);
// 			if (Precede(e->data->expn, *str) < 0) {
// 				SetData(&data, 0, *str);
// 				MakeNode(&e, data);
// 				Push(&optr, e);
// 				str++;
// 			}
// 			else if (Precede(e->data->expn, *str) == 0) {
// 				Pop(&optr, &e);
// 				FreeNode(e);
// 				str++;
// 			}
// 			else if (Precede(e->data->expn, *str) > 0) {
// 				SElemType *num1, *num2, *result;
// 				SElemType *operator;
// 				Pop(&optr, &operator);
// 				Pop(&opnd, &num2);
// 				Pop(&opnd, &num1);
// 				result = Operate(num1, operator,num2);
// 				Push(&opnd, result);
// 				FreeNode(num1);
// 				FreeNode(num2);
// 			}
// 		}
// 	}
// 	DestroyStack(&optr);
// 	GetTop(opnd, &e);
// 	return e;
// }
// Status CreateSMatrix(TSMatrix *matrix, SqStack stack) {
// 	SqStack temp;
// 	SData data;
// 	SElemType *node;
// 	int i;
// 	if (StackEmpty(stack))return ERROR;
// 	matrix->column = matrix->row = 8;
// 	matrix->num = StackLength(stack);
// 	if (!InitStack(&temp))return ERROR;
// 	for (i = 0; i < StackLength(stack); i++) {
// 		LocatePos(stack, i, &node);
// 		SetData(&data, node->data->coef, node->data->expn);
// 		MakeNode(&node, data);
// 		Push(&temp, node);
// 	}
// 	for (i = matrix->num - 1; i >= 0; i--) {
// 		Pop(&temp, &node);
// 		matrix->data[i].x = (int)node->data->coef;
// 		matrix->data[i].y = node->data->expn;
// 		matrix->data[i].value = 1;
// 	}
// 	SortMatrix(matrix);
// 	DestroyStack(&temp);
// 	return OK;
// }
// void PrintSMatrix(TSMatrix matrix) {
// 	int i, j, n;
// 	for (i = 0, n = 0; i < matrix.row; i++) {
// 		for (j = 0; j < matrix.column; j++) {
// 			if (i == matrix.data[n].x&&j == matrix.data[n].y)printf("%d", matrix.data[n++].value);
// 			else printf("O");
// 			if (j != matrix.column - 1)printf(" ");
// 		}
// 		printf("\n");
// 	}
// }
// void SortMatrix(TSMatrix *matrix) {
// 	int i, j;
// 	int index;
// 	Triple temp;
// 	for (i = 0; i < matrix->num; i++) {
// 		index = i;
// 		for (j = i + 1; j < matrix->num; j++) {
// 			if (matrix->data[j].x < matrix->data[index].x || (matrix->data[j].x == matrix->data[index].x&&matrix->data[j].y < matrix->data[index].y)) {
// 				index = j;
// 			}
// 		}
// 		if (index != i) {
// 			temp = matrix->data[i];
// 			matrix->data[i] = matrix->data[index];
// 			matrix->data[index] = temp;
// 		}
// 	}
// }
// Status sub_isEquel(TSMatrix matrix1, TSMatrix matrix2) {
// 	TSMatrix temp;
// 	int i = 0;
// 	if (!CompareMatrix(matrix1, matrix2))i = 1;
// 	LRevolveMatrix(&temp, matrix1);
// 	if (!CompareMatrix(temp, matrix2))i = 1;
// 	RRevolveMatrix(&temp, matrix1);
// 	if (!CompareMatrix(temp, matrix2))i = 1;
// 	TurnMatrix(&temp, matrix1);
// 	if (!CompareMatrix(temp, matrix2))i = 1;
// 	return i;
// }
// Status isEquel(TSMatrix *matrix1, TSMatrix matrix2, int length) {
// 	int i;
// 	for (i = 0; i < length; i++) {
// 		if (sub_isEquel(matrix1[i], matrix2))return true;
// 	}
// 	return false;
// }
// int CompareMatrix(TSMatrix matrix1, TSMatrix matrix2) {
// 	int i;
// 	if (matrix1.column != matrix2.column&&matrix1.row != matrix2.row&&matrix1.num != matrix2.num)return -1;
// 	for (i = 0; i < matrix1.num; i++) {
// 		if (matrix1.data[i].x != matrix2.data[i].x || matrix1.data[i].y != matrix2.data[i].y || matrix1.data[i].value != matrix2.data[i].value)return -1;
// 	}
// 	return 0;
// }
// Status LRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2) {
// 	int i;
// 	matrix1->row = matrix2.column;
// 	matrix1->column = matrix2.row;
// 	matrix1->num = matrix2.num;
// 	for (i = 0; i < matrix1->num; i++) {
// 		matrix1->data[i].y = matrix2.data[i].x;
// 		matrix1->data[i].x = matrix2.row - 1 - matrix2.data[i].y;
// 		matrix1->data[i].value = matrix2.data[i].value;
// 	}
// 	SortMatrix(matrix1);
// 	return OK;
// }
// Status RRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2) {
// 	int i;
// 	matrix1->row = matrix2.column;
// 	matrix1->column = matrix2.row;
// 	matrix1->num = matrix2.num;
// 	for (i = 0; i < matrix1->num; i++) {
// 		matrix1->data[i].x = matrix2.data[i].y;
// 		matrix1->data[i].y = matrix2.row - 1 - matrix2.data[i].x;
// 		matrix1->data[i].value = matrix2.data[i].value;
// 	}
// 	SortMatrix(matrix1);
// 	return OK;
// }
// Status TurnMatrix(TSMatrix *matrix1, TSMatrix matrix2) {
// 	TSMatrix temp;
// 	if (RRevolveMatrix(&temp, matrix2) == ERROR)return ERROR;
// 	if (RRevolveMatrix(matrix1, temp) == ERROR)return ERROR;
// 	return OK;
// }
// Status isPeace(SqStack stack, SData data) {
// 	SElemType *t;
// 	if (StackEmpty(stack))return OK;
// 	for (t = (stack.head)->next; t; t = t->next) {
// 		if (t->data->coef == data->coef || t->data->expn == data->expn || abs(t->data->coef - data->coef) == abs(t->data->expn - data->expn))
// 			return ERROR;
// 	}
// 	return OK;
// }
// void EightQueen() {
// 	int x = 0, y = 0, n = 0, num = 0;
// 	SqStack stack;
// 	SElemType *node;
// 	SData data;
// 	TSMatrix matrix[100];
// 	InitStack(&stack);
// 	while (StackLength(stack) < 8) {
// 		SetData(&data, x, y);
// 		//printf("%d   %d   �ѷ�%d��\n",(int)data->coef,data->expn,StackLength(stack));
// 		if (!isPeace(stack, data)) {
// 			//printf("�Ų���\n");
// 			while (data->expn == 7) {
// 				if (!GetTop(stack, &node))return;
// 				if (node->data->coef != data->coef) {
// 					free(data);
// 					Pop(&stack, &node);
// 					data = node->data;
// 					x = data->coef;
// 					y = data->expn;
// 					free(data);
// 				}
// 			}
// 		}
// 		else {
// 			MakeNode(&node, data);
// 			Push(&stack, node);
// 			y = 7;
// 		}
// 		if (StackLength(stack) == 8) {
// 			TSMatrix temp;
// 			CreateSMatrix(&temp, stack);
// 			if (!isEquel(matrix, temp, n)) {
// 				matrix[n++] = temp;
// 				printf("��%d�ְڷ���\n", n);
// 				PrintSMatrix(temp);
// 			}
// 			do {
// 				Pop(&stack, &node);
// 				data = node->data;
// 				x = data->coef;
// 				y = data->expn;
// 				free(data);
// 			} while (y == 7);
// 		}
// 		//getch();
// 		if (y == 7) {
// 			y = 0;
// 			x++;
// 		}
// 		else y++;

// 	}
// 	DestroyStack(&stack);
// }





// Status SetPolyn(ElemType *e, double coef, int expn) {
// 	if(!e)return ERROR;
// 	*e = (ElemType)malloc(sizeof(term)); //ע������ElemType�������һ��ָ������
// 	if (!*e)return OVERFLOW; 				//����ElemType*�Ǹ�����ָ��
// 	(*e)->coef = coef; 					//��Ҳ��֪������Ϊʲô�Լ�Ҫ��ô����
// 	(*e)->expn = expn;
// 	return OK;
// }
// void SortPolyn(polynomail *p) {
// 	Link *p1, *p2;						//����ֱ�Ӳ�������
// 	for (p1 = p->head->next; p1; p1 = p1->next) {
// 		for (p2 = p->head->next; p2 != p1; p2 = p2->next) {
// 			if (p2->data->expn == p1->data->expn) {	//����ߴ�����Ľڵ��ָ����ǰ��������
// 				Link *pri;						//�ڵ��ָ����ͬ����Ӧ�úϲ������ɾ�����ߣ�����ǰ��
// 				p2->data->coef += p1->data->coef;
// 				pri = PriorPos(*p, p1);
// 				DelFirst(pri, &p1);
// 				FreeNode(p1);
// 				p->len--;
// 				if (abs(p2->data->coef) < 1e-6) {	//����ϲ���ϵ��Ϊ0����ҲҪ������ڵ�ɾ��
// 					pri = PriorPos(*p, p2);		//����Լ�����˼ά�������
// 					DelFirst(pri, &p2);
// 					FreeNode(p2);
// 					p->len--;
// 				}
// 				p1 = pri;
// 				break;
// 			}
// 			else if (p1->data->expn < p2->data->expn) {
// 				Link *pri1, *pri2;
// 				pri1 = PriorPos(*p, p1);			//��ѧ������ϵͳ�Լ���ð����Ĳ���������������5�о͸㶨��
// 				DelFirst(pri1, &p1);
// 				pri2 = PriorPos(*p, p2);
// 				InsFirst(pri2, p1);
// 				p1 = pri1;
// 				break;
// 			}
// 		}
// 	}
// 	p->tail = GetLast(*p);					//������һ��β��㣬����������Լ����ܵ�˼ά
// }
// Status CreatPolyn(polynomail *p, int m) {
// 	int i, expn;
// 	double coef;
// 	ElemType e;
// 	Link *s;
// 	if (InitList(p) == ERROR)return ERROR;
// 	for (i = 0; i < m; i++) {
// 		printf("�������%d���ϵ����ָ����", i + 1);
// 		scanf("%lf%d", &coef, &expn);
// 		if (SetPolyn(&e, coef, expn) == ERROR)return ERROR;	//�������ݣ��γ�������
// 		if (MakeNode(&s, e) == ERROR)return ERROR;			//��װ��һ�����
// 		if (Append(p, s) == ERROR)return ERROR;				//������������β
// 	}
// 	SortPolyn(p);											//����������
// 	return OK;
// }
// Status DestroyPolyn(polynomail *p) {
// 	if (DestroyList(p) == ERROR)return ERROR;
// 	else return OK;
// }
// void PrintPolyn(polynomail p) {
// 	Link *pt;
// 	if (ListEmpty(p))return;
// 	printf("y=");
// 	for (pt = (p.head)->next; pt; pt = pt->next) {
// 		if (pt == (p.head)->next&&abs(pt->next->data->coef + 1) < 1e-6)printf("-");
// 		if (!(abs(pt->data->coef) - 1 < 1e-6))printf("%.2f", pt->data->coef);
// 		printf("x^%d", pt->data->expn);
// 		if (pt->next) {
// 			if (pt->next->data->coef > 0)printf("+");
// 			else if (abs(pt->next->data->coef + 1) < 1e-6)printf("-");
// 		}
// 	}
// 	printf("\n");
// }
// int PolynLength(polynomail p) {
// 	return ListLength(p);
// }
// void AddPolyn(polynomail *pa, polynomail *pb) {
// 	Link *ha, *hb, *hc;					//���ù鲢�ķ���������������ʽ�ϲ���һ��
// 	ha = pa->head->next;
// 	hb = pb->head->next;
// 	hc = pa->head;
// 	while (ha&&hb) {
// 		if (ha->data->expn < hb->data->expn) {
// 			hc->next = ha;
// 			hc = hc->next;
// 			ha = ha->next;
// 		}
// 		else if (ha->data->expn == hb->data->expn) {
// 			Link *t;
// 			ha->data->coef += hb->data->coef;
// 			t = hb;
// 			hb = hb->next;
// 			FreeNode(t);
// 			if (abs(ha->data->coef) < 1e-6) {
// 				t = ha;
// 				ha = ha->next;
// 				FreeNode(t);
// 			}
// 			else {
// 				hc->next = ha;
// 				ha = ha->next;
// 				hc = hc->next;
// 			}
// 		}
// 		else {
// 			hc->next = hb;
// 			hc = hc->next;
// 			hb = hb->next;
// 		}
// 	}
// 	if (ha)hc->next = ha;
// 	if (hb)hc->next = hb;
// 	pb->head->next = NULL;
// 	DestroyPolyn(pb);
// 	pa->tail = GetLast(*pa);
// 	pa->len = ListLength(*pa);
// }
// void SubtractPolyn(polynomail *pa, polynomail *pb) {
// 	ListTraverse(*pb, inverse);
// 	AddPolyn(pa, pb);
// }
// Link *sub_MultiplyPolyn(Link *p, polynomail *pb) {
// 	Link *pt, *head = NULL, *newnode = NULL;
// 	Link *t;
// 	ElemType e = NULL;
// 	double coef, coef_ori = p->data->coef;
// 	int expn, expn_ori = p->data->expn;
// 	for (pt = pb->head->next; pt; pt = pt->next) {		//����pb��ÿ����㣬�ֱ���p���
// 		coef = coef_ori;							//�õ��������ݰ�װ�ɽ�㲢����������
// 		expn = expn_ori;							//Ȼ�󷵻���һ�������׽ڵ��ַ
// 		coef *= pt->data->coef;
// 		expn += pt->data->expn;
// 		if (SetPolyn(&e, coef, expn) == ERROR)return NULL;	//���������
// 		if (MakeNode(&newnode, e) == ERROR)return NULL;	//��װ����ָ����Ľڵ�
// 		if (pt == pb->head->next)head = t = newnode;			//������������
// 		else {
// 			if (InsFirst(t, newnode) == ERROR)return NULL;
// 			t = t->next;
// 		}
// 	}
// 	return head;
// }
// Status MultiplyPolyn(polynomail *pa, polynomail *pb) {
// 	Link *ha;
// 	Link *t;
// 	ha = pa->head->next;
// 	pa->tail = pa->head;
// 	pa->head->next = NULL;
// 	pa->len = 0;
// 	while (ha) {								//��pa��ÿ�����ֱ���pb���������һ��
// 		t = sub_MultiplyPolyn(ha, pb);			//����һ����㣬����һ���ڵ����pa��
// 		if (Append(pa, t) == ERROR)return ERROR;
// 		t = ha;
// 		ha = ha->next;
// 		FreeNode(t);
// 	}
// 	SortPolyn(pa);
// 	DestroyPolyn(pb);
// }





int main() {
	// polynomail p1,p2;
	// printf("�������һ������ʽ��\n");
	// CreatPolyn(&p1,2);
	// printf("������ڶ�������ʽ��\n");
	// CreatPolyn(&p2,4);
	// printf("\n����������ʽ�ֱ��ǣ�\n");
	// PrintPolyn(p1);
	// PrintPolyn(p2);
	// MultiplyPolyn(&p1,&p2);
	// printf("\n��˵Ľ���ǣ�\n");
	// PrintPolyn(p1);

	// char str[20];
	// SElemType *e;
	// printf("��������ʽ��");
	// gets(str);
	// e=Calculator(str);
	// printf("���Ϊ��%f\n",e->data->coef);

	// int opentime,closetime,intertime_arr,intertime_work;
	// printf("�����뿪ʼӪҵʱ�䣺");
	// scanf("%d",&opentime);
	// printf("���������Ӫҵʱ�䣺");
	// scanf("%d",&closetime);
	// printf("������ÿ���˵�������ʱ������");
	// scanf("%d",&intertime_arr);
	// printf("������ͻ�ҵ�������ʱ�䣺");
	// scanf("%d",&intertime_work);
	// BankSimulation(0,100,5,30,0);

	// EightQueen();

	// Conversion(100000000,16);

	// printf("%d\n",BracketMatch("([(]])])"));
	return 0;
}
