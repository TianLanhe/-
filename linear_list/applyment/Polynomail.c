#include "Polynomail.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Status SetPolyn(ElemType *e, double coef, int expn) {
	if (!e)return ERROR;
	*e = (ElemType)malloc(sizeof(term)); //ע������ElemType�������һ��ָ������
	if (!*e)return OVERFLOW; 				//����ElemType*�Ǹ�����ָ��
	(*e)->coef = coef; 					//��Ҳ��֪������Ϊʲô�Լ�Ҫ��ô����
	(*e)->expn = expn;
	return OK;
}
void SortPolyn(polynomail *p) {
	Link *p1, *p2;						//����ֱ�Ӳ�������
	for (p1 = p->head->next; p1; p1 = p1->next) {
		for (p2 = p->head->next; p2 != p1; p2 = p2->next) {
			if (p2->data->expn == p1->data->expn) {	//����ߴ�����Ľڵ��ָ����ǰ��������
				Link *pri;						//�ڵ��ָ����ͬ����Ӧ�úϲ������ɾ�����ߣ�����ǰ��
				p2->data->coef += p1->data->coef;
				pri = PriorPos(*p, p1);
				DelFirst(pri, &p1);
				FreeNode(p1);
				--p->len;
				if (fabs(p2->data->coef) < 1e-6) {	//����ϲ���ϵ��Ϊ0����ҲҪ������ڵ�ɾ��
					pri = PriorPos(*p, p2);
					DelFirst(pri, &p2);
					FreeNode(p2);
					--p->len;
				}
				p1 = pri;
				break;
			}
			else if (p1->data->expn < p2->data->expn) {
				Link *pri1, *pri2;
				pri1 = PriorPos(*p, p1);
				DelFirst(pri1, &p1);
				pri2 = PriorPos(*p, p2);
				InsFirst(pri2, p1);
				p1 = pri1;
				break;
			}
		}
	}
	p->tail = GetLast(*p);
}
Status CreatPolyn(polynomail *p, int m) {
	int i, expn;
	double coef;
	ElemType e;
	Link *s;
	if (InitList(p) == ERROR)return ERROR;
	for (i = 0; i < m; i++) {
		printf("�������%d���ϵ����ָ����", i + 1);
		scanf("%lf%d", &coef, &expn);
		if (SetPolyn(&e, coef, expn) == ERROR)return ERROR;	//�������ݣ��γ�������
		if (MakeNode(&s, e) == ERROR)return ERROR;			//��װ��һ�����
		if (Append(p, s) == ERROR)return ERROR;				//������������β
	}
	SortPolyn(p);											//����������
	return OK;
}
Status DestroyPolyn(polynomail *p) {
	if (DestroyList(p) == ERROR)return ERROR;
	else return OK;
}
void PrintPolyn(polynomail p) {
	Link *pt;
	if (ListEmpty(p)){
		printf("y=0\n");
		return;
	}
	printf("y=");
	for (pt = (p.head)->next; pt; pt = pt->next) {
		if (pt != GetHead(p))
			printf("%c", pt->data->coef > 0 ? '+' : '-');
		if (fabs(pt->data->coef) > 1 || pt->data->expn == 0)
			printf("%.2f", pt->data->coef);

		if(pt->data->expn != 0){
			printf("x");
			if (pt->data->expn != 1)printf("^%d", pt->data->expn);
		}
	}
	printf("\n");
}
int PolynLength(polynomail p) {
	return ListLength(p);
}
void AddPolyn(polynomail *pa, polynomail *pb) {
	Link *ha, *hb, *hc;					//���ù鲢�ķ���������������ʽ�ϲ���һ��
	ha = pa->head->next;
	hb = pb->head->next;
	hc = pa->head;
	while (ha&&hb) {
		if (ha->data->expn < hb->data->expn) {
			hc->next = ha;
			hc = hc->next;
			ha = ha->next;
		}
		else if (ha->data->expn == hb->data->expn) {
			Link *t;
			ha->data->coef += hb->data->coef;
			t = hb;
			hb = hb->next;
			FreeNode(t);
			if (fabs(ha->data->coef) < 1e-6) {
				t = ha;
				ha = ha->next;
				FreeNode(t);
			}
			else {
				hc->next = ha;
				ha = ha->next;
				hc = hc->next;
			}
		}
		else {
			hc->next = hb;
			hc = hc->next;
			hb = hb->next;
		}
	}
	if (ha)hc->next = ha;
	else if (hb)hc->next = hb;
	else hc->next = NULL;
	pb->head->next = NULL;
	DestroyPolyn(pb);
	pa->tail = GetLast(*pa);
	pa->len = ListLength(*pa);
}
Status inverse(Link *p) {
	if (!p)
		return ERROR;
	p->data->coef *= -1;
	return OK;
}
void SubtractPolyn(polynomail *pa, polynomail *pb) {
	ListTraverse(*pb, inverse);
	AddPolyn(pa, pb);
}
Link *sub_MultiplyPolyn(Link *p, polynomail *pb) {
	Link *pt, *head = NULL, *newnode = NULL;
	Link *t;
	ElemType e = NULL;
	double coef, coef_ori = p->data->coef;
	int expn, expn_ori = p->data->expn;
	for (pt = pb->head->next; pt; pt = pt->next) {		//����pb��ÿ����㣬�ֱ���p���
		coef = coef_ori;							//�õ��������ݰ�װ�ɽ�㲢����������
		expn = expn_ori;							//Ȼ�󷵻���һ�������׽ڵ��ַ
		coef *= pt->data->coef;
		expn += pt->data->expn;
		if (SetPolyn(&e, coef, expn) == ERROR)return NULL;	//���������
		if (MakeNode(&newnode, e) == ERROR)return NULL;	//��װ����ָ����Ľڵ�
		if (pt == GetHead(*pb))head = t = newnode;			//������������
		else {
			if (InsFirst(t, newnode) == ERROR)return NULL;
			t = t->next;
		}
	}
	return head;
}
Status MultiplyPolyn(polynomail *pa, polynomail *pb) {
	Link *ha;
	Link *t;
	if (!pa || !pb)
		return ERROR;
	if (ListEmpty(*pa) || ListEmpty(*pb))
		return ERROR;
	ha = pa->head->next;
	pa->tail = pa->head;
	pa->head->next = NULL;
	pa->len = 0;
	while (ha) {								//��pa��ÿ�����ֱ���pb���������һ��
		t = sub_MultiplyPolyn(ha, pb);			//����һ����㣬����һ���ڵ����pa��
		if (t == NULL)return ERROR;
		if (Append(pa, t) == ERROR)return ERROR;
		t = ha;
		ha = ha->next;
		FreeNode(t);
	}
	SortPolyn(pa);
	DestroyPolyn(pb);
	return OK;
}
