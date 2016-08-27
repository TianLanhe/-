#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR 0
#define OK 1
#define Status int
typedef struct _Element{
	int x;							//����Ԫ�ص���
	int y;							//����Ԫ�ص���
	double value;					//����Ԫ�ص�ֵ
}Element;
typedef struct _RLSMatrix{
	Element *data;					//�������Ԫ�ص�һά����
	int *rowpos;					//����ÿһ�е�һ������Ԫ����һλ�����λ��
	int row;						//���������
	int column;						//���������
	int num;						//�������Ԫ�صĸ���
}RLSMatrix;
Status SetData(Element *data,int x,int y,double value);
//����matrix.data[i]��ֵ��������������ֵ
Status CreatMatrix_Num(RLSMatrix *matrix);
//���ݷ���Ԫ�ظ�������ϡ�����
Status CreatMatrix_All(RLSMatrix *matrix);
//ֱ�������������Ԫ�ش���ϡ�����
Status SortMatrix(RLSMatrix *matrix);
//��ϡ�����matrix�ĳ�Աdata�еķ���Ԫ�ص����а���С�����˳������
Status InitMatrix(RLSMatrix *matrix);
//��ʼ��ϡ�����
Status DestroyMatrix(RLSMatrix *matrix);
//����ϡ�����
Status PrintMatrix(RLSMatrix matrix);
//��ӡϡ�����
Status CopyMatrix(RLSMatrix *result,RLSMatrix matrix);
//��ϡ�����matrix���Ƶõ�result
Status AddMatrix(RLSMatrix *result,RLSMatrix matrix1,RLSMatrix matrix2);
//��ϡ�����ĺ�result=matrix1+matrix2
Status SubMatrix(RLSMatrix *result,RLSMatrix matrix1,RLSMatrix matrix2);
//��ϡ�����Ĳ�result=matrix1-matrix2
Status ScalarMatrix(RLSMatrix *result,RLSMatrix matrix1,double num);
//��ϡ����������result=matrix1*num
Status MultMatrix(RLSMatrix *result,RLSMatrix matrix1,RLSMatrix matrix2);
//��ϡ�����ĳ˻�result=matrix1*matrix2
Status TransMatrix(RLSMatrix *result,RLSMatrix matrix);
//��ϡ������ת��
Status PowMatrix(RLSMatrix *result,RLSMatrix matrix,int n);
//��ϡ�����matrix��n����result=matrix^n
Status inverse(double *value);
//���������Ĺ��ܺ�������ϡ������ÿ������Ԫ��ȡ��
Status MatrixTraverse(RLSMatrix *matrix,Status (*visit)(double*));
//���ζ�ϡ������ÿ������Ԫ�ص���visit()��һ������ʧ�ܣ������ʧ��
Status SetData(Element *data,int x,int y,double value){
	if(!data)return ERROR;
	data->x=x;
	data->y=y;
	data->value=value;
	return OK;
}
Status CreatMatrix_Num(RLSMatrix *matrix){
	int row,column,num;
	int i;
	int x,y;
	double value;
	int *rownum;
	if(!matrix)return ERROR;
	printf("������ϡ������������");
	scanf("%d",&row);
	if(row<=0){
		printf("�����������Ϸ���\n");
		return ERROR;
	}
	printf("������ϡ������������");
	scanf("%d",&column);
	if(column<=0){
		printf("�����������Ϸ���\n");
		return ERROR;
	}
	printf("������ϡ��������Ԫ�صĸ�����");
	scanf("%d",&num);
	if(num>row*column||num<0){
		printf("Ԫ�ظ������Ϸ���\n");
		return ERROR;
	}
	matrix->num=num;
	matrix->row=row;
	matrix->column=column;
	if(!num){
		matrix->data=NULL;
		matrix->rowpos=NULL;
	}else{
		matrix->data=(Element *)malloc(sizeof(Element)*num);
		if(!matrix->data)return ERROR;
		rownum=(int *)calloc(row,sizeof(int));
		if(!rownum)return ERROR;
		matrix->rowpos=(int *)malloc(row*sizeof(int));
		if(!matrix->rowpos)return ERROR;
		for(i=0;i<num;i++){
			do{
				printf("�������%d������Ԫ�ص�������������ֵ��",i+1);
				scanf("%d%d%lf",&x,&y,&value);
				if(x>row||y>column||x<=0||y<=0)printf("Ԫ�ص��������������Ϸ�������������\n");
				if(!value)printf("Ԫ�ص�ֵ����Ϊ0������������\n");
			}while(x>row||y>column||x<=0||y<=0||!value);
			if(!SetData(&matrix->data[i],x,y,value))return ERROR;
			rownum[x-1]++;
		}
		if(!SortMatrix(matrix))return ERROR;
		for(i=0;i<row;i++){
			if(!i)matrix->rowpos[i]=0;
			else matrix->rowpos[i]=matrix->rowpos[i-1]+rownum[i-1];
		}
		free(rownum);
	}
	return OK;
}
Status CreatMatrix_All(RLSMatrix *matrix){
	int row,column,num=0;
	double value;
	int i,j;
	Element *data;
	int *rownum;
	if(!matrix)return ERROR;
	printf("����������������");
	scanf("%d",&row);
	if(row<=0){
		printf("�����������Ϸ���\n");
		return ERROR;
	}
	printf("����������������");
	scanf("%d",&column);
	if(column<=0){
		printf("�����������Ϸ���\n");
		return ERROR;
	}
	rownum=(int *)calloc(row,sizeof(int));
	if(!rownum)return ERROR;
	data=(Element *)malloc(sizeof(Element)*10000);
	if(!data)return ERROR;
	printf("���������\n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			scanf("%lf",&value);
			if(abs(value)>10e-6){
				num++;
				if(!SetData(data+num-1,i+1,j+1,value))return ERROR;
				rownum[i]++;
			}
		}
	}
	matrix->row=row;
	matrix->column=column;
	matrix->num=num;
	if(!num){
		matrix->data=NULL;
		matrix->rowpos=NULL;
	}else{
		data=(Element *)realloc(data,sizeof(Element)*num);
		if(!data)return ERROR;
		matrix->data=data;
		matrix->rowpos=(int *)malloc(sizeof(int)*row);
		if(!matrix->rowpos)return ERROR;
		for(i=0;i<row;i++){
			if(!i)matrix->rowpos[i]=0;
			else matrix->rowpos[i]=matrix->rowpos[i-1]+rownum[i-1];
		}
	}
	free(rownum);
	return OK;
}
Status InitMatrix(RLSMatrix *matrix){
	if(!matrix)return ERROR;
	matrix->row=matrix->column=matrix->num=0;
	matrix->data=NULL;
	matrix->rowpos=NULL;
	return OK;
}
Status DestroyMatrix(RLSMatrix *matrix){
	if(!matrix||(!matrix->row&&!matrix->column))return ERROR;
	matrix->row=matrix->column=matrix->num=0;
	if(!matrix->data)free(matrix->data);
	if(!matrix->rowpos)free(matrix->rowpos);
	matrix->data=NULL;
	matrix->rowpos=NULL;
	return OK;
}
Status PrintMatrix(RLSMatrix matrix){
	int i,j;
	int num=0;
	if(!matrix.row&&!matrix.column)return ERROR;
	for(i=0;i<matrix.row;i++){
		for(j=0;j<matrix.column;j++){
			if(matrix.num&&i==matrix.data[num].x-1&&j==matrix.data[num].y-1)printf("%3.0f",matrix.data[num++].value);
			else printf("  0");
		}
		printf("\n");
	}
	return OK;
}
Status SortMatrix(RLSMatrix *matrix){
	if(!matrix->num)return ERROR;
	int i,j,index;
	Element temp;
	for(i=0;i<matrix->num;i++){
		index=i;
		for(j=i+1;j<matrix->num;j++){
			if(matrix->data[j].x<matrix->data[index].x||(matrix->data[j].x==matrix->data[index].x&&matrix->data[j].y<matrix->data[index].y)){
				index=j;
			}
		}
		if(index!=i){
			temp=matrix->data[i];
			matrix->data[i]=matrix->data[index];
			matrix->data[index]=temp;
		}
	}
	return OK;
}
Status CopyMatrix(RLSMatrix *result,RLSMatrix matrix){
	int i;
	if((!matrix.row&&!matrix.column)||!result)return ERROR;
	DestroyMatrix(result);
	result->num=matrix.num;
	result->column=matrix.column;
	result->row=matrix.row;
	if(matrix.num){
		result->rowpos=(int *)malloc(sizeof(int)*matrix.row);
		if(!result->rowpos)return ERROR;
		for(i=0;i<matrix.row;i++)result->rowpos[i]=matrix.rowpos[i];
		result->data=(Element *)malloc(sizeof(Element)*matrix.num);
		if(!result->data)return ERROR;
		for(i=0;i<matrix.num;i++){
			result->data[i].x=matrix.data[i].x;
			result->data[i].y=matrix.data[i].y;
			result->data[i].value=matrix.data[i].value;
		}
	}else{
		result->data=NULL;
		result->rowpos=NULL;
	}
	return OK;
}
Status AddMatrix(RLSMatrix *result,RLSMatrix matrix1,RLSMatrix matrix2){
	Element *data;
	int i,num=0;
	int num1,num2;
	int *rownum;
	if((!matrix1.row&&!matrix1.column)||(!matrix2.row&&!matrix2.column))return ERROR;
	if(!result)return ERROR;
	if(matrix1.row!=matrix2.row||matrix1.column!=matrix2.column)return ERROR;
	DestroyMatrix(result);
	if(matrix1.num+matrix2.num){
		data=(Element *)malloc(sizeof(Element)*(matrix1.num+matrix2.num));
		if(!data)return ERROR;
		rownum=(int *)calloc(matrix1.row,sizeof(int));
		for(num1=0,num2=0;num1<matrix1.num&&num2<matrix2.num;){
			if(matrix1.data[num1].x<matrix2.data[num2].x||(matrix1.data[num1].x==matrix2.data[num2].x&&matrix1.data[num1].y<matrix2.data[num2].y)){
				if(!SetData(data+num++,matrix1.data[num1].x,matrix1.data[num1].y,matrix1.data[num1].value))return ERROR;
				rownum[matrix1.data[num1].x-1]++;
				num1++;
			}else if(matrix1.data[num1].x>matrix2.data[num2].x||(matrix1.data[num1].x==matrix2.data[num2].x&&matrix1.data[num1].y>matrix2.data[num2].y)){
				if(!SetData(data+num++,matrix2.data[num2].x,matrix2.data[num2].y,matrix2.data[num2].value))return ERROR;
				rownum[matrix2.data[num2].x-1]++;
				num2++;
			}else{
				if(!(abs(matrix1.data[num1].value+matrix2.data[num2].value)<10e-6)){
					if(!SetData(data+num++,matrix1.data[num1].x,matrix1.data[num1].y,matrix1.data[num1].value+matrix2.data[num2].value))return ERROR;
					rownum[matrix1.data[num1].x-1]++;
				}
				num1++;
				num2++;
			}
		}
		while(num1<matrix1.num){
			if(!SetData(data+num++,matrix1.data[num1].x,matrix1.data[num1].y,matrix1.data[num1].value))return ERROR;
			rownum[matrix1.data[num1].x-1]++;
			num1++;
		}
		while(num2<matrix2.num){
			if(!SetData(data+num++,matrix2.data[num2].x,matrix2.data[num2].y,matrix2.data[num2].value))return ERROR;
			rownum[matrix2.data[num2].x-1]++;
			num2++;
		}
		if(num!=num1+num2)data=(Element *)realloc(data,sizeof(Element)*num);
		result->num=num;
		result->row=matrix1.row;
		result->column=matrix1.column;
		result->data=data;
		result->rowpos=(int *)malloc(sizeof(int)*result->row);
		for(i=0;i<result->row;i++){
			if(!i)result->rowpos[i]=0;
			else result->rowpos[i]=result->rowpos[i-1]+rownum[i-1];
		}
	}else{
		result->row=matrix1.row;
		result->column=matrix1.column;
	}
	return OK;
}
Status SubMatrix(RLSMatrix *result,RLSMatrix matrix1,RLSMatrix matrix2){
	RLSMatrix temp;
	InitMatrix(&temp);
	if(!CopyMatrix(&temp,matrix2))return ERROR;
	if(!MatrixTraverse(&temp,inverse))return ERROR;
	if(!AddMatrix(result,matrix1,temp))return ERROR;
	if(!DestroyMatrix(&temp))return ERROR;
	return OK;
}
Status inverse(double *value){
	*value*=-1;
	return OK;
}
Status MatrixTraverse(RLSMatrix *matrix,Status (*visit)(double*)){
	int i; 
	if(!matrix->row&&!matrix->column)return ERROR;
	for(i=0;i<matrix->num;i++){
		if(!visit(&matrix->data[i].value))return ERROR;
	}
	return OK;
}
Status ScalarMatrix(RLSMatrix *result,RLSMatrix matrix,double num){
	int i;
	if(!matrix.row&&!matrix.column)return ERROR;
	DestroyMatrix(result);
	if(matrix.num&&num){
		if(!CopyMatrix(result,matrix))return ERROR;
		for(i=0;i<result->num;i++)result->data[i].value*=num;
	}else{
		result->row=matrix.row;
		result->column=matrix.column;
	}
	return OK;
}
Status TransMatrix(RLSMatrix *result,RLSMatrix matrix){
	int i;
	int *temp;
	int *rownum;
	int index;
	if(!matrix.row&&!matrix.column)return ERROR;
	DestroyMatrix(result);
	result->column=matrix.row;
	result->row=matrix.column;
	result->num=matrix.num;
	if(result->num){
		result->data=(Element *)malloc(sizeof(Element)*matrix.num);
		if(!result->data)return ERROR;
		result->rowpos=(int *)malloc(sizeof(int)*result->row);
		if(!result->rowpos)return ERROR;
		rownum=(int *)calloc(result->row,sizeof(int));
		if(!rownum)return ERROR;
		for(i=0;i<matrix.num;i++)rownum[matrix.data[i].y-1]++;
		for(i=0;i<result->row;i++){
			if(!i)result->rowpos[i]=0;
			else result->rowpos[i]=result->rowpos[i-1]+rownum[i-1];
		}
		temp=(int *)malloc(sizeof(int)*result->row);
		if(!temp)return ERROR;
		for(i=0;i<result->row;i++)temp[i]=result->rowpos[i];
		for(i=0;i<matrix.num;i++){
			index=temp[matrix.data[i].y-1];
			result->data[index].x=matrix.data[i].y;
			result->data[index].y=matrix.data[i].x;
			result->data[index].value=matrix.data[i].value;
			temp[matrix.data[i].y-1]++;
		}
		free(temp);
		free(rownum);
	}
	return OK;
}
Status MultMatrix(RLSMatrix *result,RLSMatrix matrix1,RLSMatrix matrix2){
	int i,k,j,q;
	int num=0;
	int start1,end1,start2,end2;
	double *temp;
	Element *data;
	if((!matrix1.row&&!matrix1.column)||(!matrix2.row&&!matrix2.column))return ERROR;
	if(!result)return ERROR;
	if(matrix1.column!=matrix2.row)return ERROR;
	DestroyMatrix(result);
	result->row=matrix1.row;
	result->column=matrix2.column;
	if(matrix1.num&&matrix1.num){
		result->rowpos=(int *)malloc(sizeof(int)*result->row);
		if(!result->rowpos)return ERROR;
		temp=(double *)malloc(sizeof(double)*result->column);
		if(!temp)return ERROR;
		data=(Element *)malloc(sizeof(Element)*10000);
		if(!data)return ERROR;
		for(i=0;i<matrix1.row;i++){
			for(k=0;k<result->column;k++)temp[k]=0;
			result->rowpos[i]=num;
			start1=matrix1.rowpos[i];
			if(i==matrix1.row-1)end1=matrix1.num;
			else end1=matrix1.rowpos[i+1];
			for(j=start1;j<end1;j++){
				start2=matrix2.rowpos[matrix1.data[j].y-1];
				if(matrix1.data[j].y==matrix2.row)end2=matrix2.num;
				else end2=matrix2.rowpos[matrix1.data[j].y];
				for(q=start2;q<end2;q++){
					temp[matrix2.data[q].y-1]+=matrix1.data[j].value*matrix2.data[q].value;
				}
			}
			for(k=0;k<result->column;k++){
				if(abs(temp[k])>10e-6){
					data[num].x=i+1;
					data[num].y=k+1;
					data[num].value=temp[k];
					num++;
				}
			}
		}
		data=(Element *)realloc(data,sizeof(Element)*num);
		if(!data)return ERROR;
		result->data=data;
		result->num=num;
		if(!num){
			free(result->rowpos);
			result->rowpos=NULL;
		}
		free(temp);
	}else result->num=0;
	return OK;
}
Status PowMatrix(RLSMatrix *result,RLSMatrix matrix,int n){
	int i;
	RLSMatrix temp;
	if(!matrix.row&&!matrix.column||!result||n<0||matrix.row!=matrix.column)return ERROR;
	DestroyMatrix(result);
	if(n){
		if(!CopyMatrix(result,matrix))return ERROR;
		InitMatrix(&temp);
		for(i=0;i<n-1;i++){
			if(!CopyMatrix(&temp,*result))return ERROR;
			if(!MultMatrix(result,temp,matrix))return ERROR;
		}
		DestroyMatrix(&temp);
	}else{
		result->num=result->row=result->column=matrix.row;
		result->rowpos=(int *)malloc(sizeof(int)*result->row);
		result->data=(Element *)malloc(sizeof(Element)*result->row);
		for(i=0;i<result->row;i++){
			result->rowpos[i]=i;
			result->data[i].x=i+1;
			result->data[i].y=i+1;
			result->data[i].value=1.0;
		}
	}
	return OK;
}
int main(){
	RLSMatrix matrix1;
	RLSMatrix matrix2;
	RLSMatrix result;
	int i;
	InitMatrix(&matrix1);
	InitMatrix(&matrix2);
	InitMatrix(&result);
	CreatMatrix_All(&matrix1);
	//CreatMatrix_All(&matrix2);
	PowMatrix(&result,matrix1,4);
	PrintMatrix(result);
	printf("%d  %d  %d\n",result.row,result.column,result.num);
	for(i=0;i<result.row;i++)printf("%d",result.rowpos[i]);
	return 0;
}
