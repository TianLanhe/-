#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define STACK_INIT_SIZE 100
#define INCREMENT 10
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
#define Status int
typedef int SElemType;
typedef struct _stack{
	SElemType *bottom;
	SElemType *top;
	int stacksize;
}SqStack;
Status InitStack(SqStack *stack);			    			//����һ����ջS
Status DestroyStack(SqStack *stack);						//ջS������
Status ClearStack(SqStack *stack);							//��ջ��Ϊ��ջ
Status StackEmpty(SqStack stack);							//��ջΪ��ջ���򷵻�TRUE�����򷵻�FALSE
int StackLength(SqStack stack);								//����S��Ԫ�ظ�������ջ�ĳ���
Status GetTop(SqStack stack,SElemType *e);					//��e����S��ջ��Ԫ��
Status Pop(SqStack *stack,SElemType *e);					//ɾ��S��ջ��Ԫ�أ�����e������ֵ
Status Push(SqStack *stack,SElemType e);					//����Ԫ��eΪ�µ�ջ��Ԫ��
Status StackTraverse(SqStack stack,void (*visit)(SElemType));//��ջ�͵�ջ�����ζ�S��ÿ������Ԫ�ص��ú���visit(),һ��visit()����ʧ�ܣ������ʧ��
void Conversion(int num,int base);							//��ʮ������numת��Ϊbase���Ƶ�����
Status BracketMatch(char *str);								//����ƥ��
void PrintStr(SElemType e);
void PrintNum(SElemType e);
void LineEdit(char back,char clear);
Status isNum(char ch);
SElemType Calculator(char *str);
int Precede(char ch1,char ch2);
SElemType Operator(char _num1,char operator,char _num2);
Status InitStack(SqStack *stack){
	stack->bottom=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!stack->bottom)return ERROR;
	stack->top=stack->bottom;
	stack->stacksize=STACK_INIT_SIZE;
	return OK;
}
Status DestroyStack(SqStack *stack){
	if(!stack->bottom)return ERROR;
	free(stack->bottom);
	stack->bottom=stack->top=NULL;
	stack->stacksize=0;
	return OK;
}
Status ClearStack(SqStack *stack){
	if(!stack->bottom)return ERROR;
	stack->top=stack->bottom;
	stack->stacksize=0;
	return OK;
}
Status StackEmpty(SqStack stack){
	if(StackLength(stack))return FALSE;
	else return TRUE;
}
void PrintStr(SElemType e){
	printf("%c",e);
}
void PrintNum(SElemType e){
	printf("%d ",e);
}
Status StackTraverse(SqStack stack,void (*visit)(SElemType)){
	if(stack.top<=stack.bottom)return ERROR;
	SElemType *e;
	for(e=stack.bottom;e<stack.top;e++)visit(*e);
	printf("\n");
	return OK;
}
int StackLength(SqStack stack){
	if(!stack.bottom)return 0;
	int i;
	SElemType *p;
	p=stack.bottom;
	for(i=0;p<stack.top;p++,i++);
	return i;
}
Status GetTop(SqStack stack,SElemType *e){
	if(stack.top<=stack.bottom){
		*e=0;
		return ERROR;
	}
	*e=*(stack.top-1);
	return OK;
}
Status Pop(SqStack *stack,SElemType *e){
	if(stack->top<=stack->bottom)return ERROR;
	stack->top--;
	*e=*stack->top;
	return OK;
}
Status Push(SqStack *stack,SElemType e){
	if(stack->top<stack->bottom)return ERROR;
	if(stack->top-stack->bottom>=stack->stacksize){
		stack->bottom=(SElemType *)realloc(stack->bottom,sizeof(SElemType)*(stack->stacksize+INCREMENT));
		if(!stack->bottom)return ERROR;
		stack->top=stack->bottom+stack->stacksize;
		stack->stacksize+=INCREMENT;
	}
	*stack->top=e;
	stack->top++;
	return OK;
}
void Conversion(int num,int base){
	SqStack stack;
	InitStack(&stack);
	if(!num)printf("0\n");
	while(num){
		Push(&stack,num%base);
		num/=base;
	}
	while(!StackEmpty(stack)){
		Pop(&stack,&num);
		printf("%d",num);
	}
	printf("\n");
	DestroyStack(&stack);
}
Status BracketMatch(char *str){
	SqStack stack;
	int t;
	InitStack(&stack);
	while(*str){
		switch(*str){
			case '[':Push(&stack,1);break;
			case ']':
				if(StackEmpty(stack))return ERROR;
				GetTop(stack,&t);
				if(t==1)Pop(&stack,&t);
				break;
			case '(':Push(&stack,2);break;
			case ')':
				if(StackEmpty(stack))return ERROR;
				GetTop(stack,&t);
				if(t==2)Pop(&stack,&t);
				break;
		}
		str++;
	}
	if(StackEmpty(stack)){
		DestroyStack(&stack);
		return OK;
	}else{
		DestroyStack(&stack);
		return ERROR;
	}
}
void LineEdit(char back,char clear){
	SqStack stack;
	char ch;
	SElemType e;
	InitStack(&stack);
	ch=getchar();
	while(ch!=EOF&&ch!='\n'){
		if(ch==back)Pop(&stack,&e);
		else if(ch==clear)ClearStack(&stack);
		else Push(&stack,ch);
		ch=getchar();
	}
	StackTraverse(stack,PrintStr);
	DestroyStack(&stack);
}
int main(){
	SElemType result;
	result=Operator('2','*','4');
	printf("%c\n",result);
	return 0;
}