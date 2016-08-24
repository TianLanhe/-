#include "sort.h"
#define OK 0
#define ERROR -1
#define Status int

Status Sequ_Search(int a[],int length,int target);
//˳����ң������ڱ������һ��Ԫ��֮��
Status Binary_Search(int a[],int length,int target);
//�۰����(������)
Status BinarySearch_sub(int a[],int start,int end,int target);
//�۰����(�ݹ鷨)���ӹ���
Status BinarySearch(int a[],int length,int target);
//�۰����(�ݹ鷨)����װ�˾���ʵ�ֵ��ӹ��̣�ֻ��Ҫ�ṩ���ȼ���
Status Fibonacci_Search(int a[],int length,int target);
//쳲���������(������)
void getFibonacci(int f[],int length);
//��쳲��������е�ǰlength������f��
Status FibonacciSearch_sub(int a[],int start,int end,int target,int f[],int n);
//쳲���������(�ݹ鷨)���ӹ���
Status FibonacciSearch(int a[],int length,int target);
//쳲���������(�ݹ鷨)����쳲��������к�����׼��������Ȼ������ӹ��̲���

Status Sequ_Search(int a[],int length,int target){
    int i;
    a[length]=target;
    for(i=0;a[i] != target;i++);    //�����ж�i�Ƿ�С��length�����Ч��
    return i==length?ERROR:i;
}
Status Binary_Search(int a[],int length,int target){
    int but=length-1,top=0;
    int mid;
    while(top<=but){
        mid=(top+but)/2;
        if(target==a[mid])return mid;
        else if(target>a[mid])top=mid+1;
        else but=mid-1;
    }
    return ERROR;
}
int BinarySearch_sub(int a[],int start,int end,int target){    //�ݹ鷨�۰����
    int mid=(start+end)/2;
    if(target==a[mid])return mid;
    else if(start>end)return ERROR;        //ע������Ҫ���ڣ����ֻ�ǵ��ڣ����������start=53,end=53,����mid=53,��end=mid-1���������
    else if(target<a[mid])return BinarySearch_sub(a,start,mid-1,target);
    else if(target>a[mid])return BinarySearch_sub(a,mid+1,end,target);
}
int BinarySearch(int a[],int length,int target){
    return BinarySearch_sub(a,0,length-1,target);
}
void getFibonacci(int f[],int length){
    int i;
    f[0]=f[1]=1;
    for(i=2;i<length;i++){
        f[i]=f[i-1]+f[i-2];
    }
}
Status Fibonacci_Search(int a[],int length,int target){
    int f[45];			//쳲���������40��ͳ���long int�ܱ�ʾ��������� 
    int index,i;
    int low,high,mid;
    getFibonacci(f,45);
    index=0;
    low=0;
    high=length-1;
    while(f[index]-1 < length)index++;
    for(i=length;i<f[index]-1;i++)a[i]=a[length-1]; //�����������
    while(low<=high){
        mid=f[index-1]-1+low;
        if(target == a[mid]){
            if(mid < length)return mid;
            else return length-1;
        }else if(target < a[mid]){
            high=mid-1;
            index--;
        }else{
            low=mid+1;
            index-=2;
        }
    }
    return ERROR;
}
Status FibonacciSearch_sub(int a[],int start,int end,int target,int f[],int n){
    int mid;
    mid=f[n-1]-1+start;
    if(start > end)return ERROR;
    else if(a[mid] == target)return mid;
    else if(target < a[mid])return FibonacciSearch_sub(a,start,mid-1,target,f,n-1);
    else return FibonacciSearch_sub(a,mid+1,end,target,f,n-2);
}
Status FibonacciSearch(int a[],int length,int target){
    int f[45];
    int index,i;
    getFibonacci(f,45);
    index=0;
    while(f[index]-1 < length)index++;
    for(i=length;i<f[index]-1;i++)a[i]=a[length-1];
    index=FibonacciSearch_sub(a,0,length-1,target,f,index);
    return index>=length?length-1:index;
}
int main(){
	int *a;
    int i;
    int num;
    int find1,find2;
    creatarr(&a,100,100);
    BinInsertSort(a,100);
    display(a,100);
    printf("\n");
    for(i=0;i<100;i++){
	    num=rand()%100;
	    find1=Fibonacci_Search(a,100,num);
	    find2=FibonacciSearch(a,100,num);
	    printf("%d:%d  %d:%d",num,find1,num,find2);
	    if(find1 != find2)printf(" false\n");
	    else printf("\n");
	}
    return 0;
}
