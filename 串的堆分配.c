#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define OK 0
#define Status int
typedef struct {
	char *ch;		//�����ַ�����ʹ�ö�̬����
	int len;		//�洢�ַ�������
}HString;
Status InitStr(HString *str);
//��ʼ��str�������ֵΪ0
Status StrAssign(HString *str1,char *str2);
//����һ����ֵ����str2�Ĵ�str1
int StrCompare(HString str1,HString str2);
//���ֵ���Ƚ�������str1��str2������ȷ���0����str1<str2�����ش��ڴ���0����������str1>str2������С��0������
int StrLength(HString str);
//����S��Ԫ�ظ����������ĳ���
Status ClearString(HString *str);
//����str��Ϊ�մ������ͷ�str��ռ�ռ�
Status Concat(HString *str3,HString str1,HString str2);
//��str3����str1��str2���Ӷ��ɵ��´�
Status SubString(HString *sub,HString str,int position,int length);
//0<=position<str.len,len>=0,���ش��ĵ�position���ַ��𳤶�Ϊlength���Ӵ�
Status PrintStr(HString str);
//��ӡ��str������
Status InitStr(HString *str){
	str->ch=NULL;
	str->len=0;
	return OK;
}
Status StrAssign(HString *str1,char *str2){
	int i;
	char *p;
	if(str1->ch){
		free(str1->ch);
		str1->ch=NULL;
		str1->len=0;
	}
	if(*str2){
		for(i=0;str2[i];i++);
		str1->len=i;
		str1->ch=(char*)malloc(sizeof(char)*i);
		if(!str1->ch)return ERROR;
		for(p=str1->ch;*p++=*str2++;);
		return OK;
	}else return ERROR;
}
int StrCompare(HString str1,HString str2){
	char *p1,*p2;
	for(p1=str1.ch,p2=str2.ch;p1&&p2;p1++,p2++){
		if(*p1!=*p2)return *p1-*p2;
	}
	return *p1-*p2;
}
int StrLength(HString str){
	int i;
	if(!str.ch)return 0;
	else{
		for(i=0;str.ch[i];i++);
		return i;
	}
}
Status ClearString(HString *str){
	if(str->ch){
		free(str->ch);
		str->ch=NULL;
	}
	str->len=0;
	return OK;
}
Status Concat(HString *str3,HString str1,HString str2){
	int i,j;
	char *p,*p1,*p2;
	if(str3->ch){
		free(str3->ch);
		str3->ch=NULL;
		str3->len=0;
	}
	for(i=0;str1.ch[i];i++);
	for(j=0;str2.ch[j];j++);
	if(i+j){
		str3->len=i+j;
		str3->ch=(char*)malloc(sizeof(char)*(i+j+1));
		if(!str3->ch)return ERROR;
		for(p=str3->ch,p1=str1.ch;*p++=*p1++;);
		for(p--,p2=str2.ch;*p++=*p2++;);
		return OK;
	}else return ERROR;
}
Status SubString(HString *sub,HString str,int position,int length){
	int i;
	char *p;
	if(position<0||position>=str.len||length<0)return ERROR;
	if(sub->ch){
		free(sub->ch);
		sub->ch=NULL;
	}
	sub->ch=(char*)malloc(sizeof(char)*(length+1));
	for(i=0,p=str.ch+position;i<length&&*p;i++,p++){
		sub->ch[i]=*p;
	}
	sub->ch[i]='\0';
	if(i!=length)sub->ch=(char*)realloc(sub->ch,sizeof(char)*(i+1));
	sub->len=i; 
	return OK;
}
Status PrintStr(HString str){
	if(!str.ch)return ERROR;
	printf("%s\n",str.ch);
}
int main(){
	HString str1,str2;
	InitStr(&str1);
	InitStr(&str2);
	StrAssign(&str1,"hello ");
	StrAssign(&str2,"world!");
	PrintStr(str2);
	SubString(&str1,str2,1,3);
	PrintStr(str1);
	printf("%d\n",str1.len);
	return 0;
}
