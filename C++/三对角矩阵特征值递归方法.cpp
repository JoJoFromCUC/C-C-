/*
author: Joe Zhu
date  : Sep,2017
from  : UCAS
*/
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<time.h>
using namespace std;

//size          ����ά��
//delta         �洢���Խ�Ԫ��
//alfa          �洢�ζԽ�Ԫ��
//a,b			��������˵�
//lamda			��������ֵ
#define N 10
#define TOL 0.000001 //��ֹ����

//ͳ�ƴ���x������ֵ����
int s(float x,float delta[N],float alfa[N-1],int size){
	float p[N];
	p[0]=1;p[1]=delta[0]-x;
	for(int i=2;i<size+1;++i){//ѭ������������ʽ����
		p[i] = (delta[i-1]-x)*p[i-1]-alfa[i-2]*alfa[i-2]*p[i-2];
	}
	int count = 0;
	for(int i=1;i<size+1;i++){
		if(p[i]==0) p[i] = -p[i-1];
		else if(p[i]>0 && p[i-1]>0) count++;
		else if(p[i]<0 && p[i-1]<0) count++;
	}
	return count;
}
//���ַ��ݹ����
void half_eigen(float a,float b,float delta[N],float alfa[N-1],float lamda[N],int size){
	if( b-a < TOL ){
		lamda[s(a,delta,alfa,size)-1] = (a+b)/2;//��������ֵ
	}
	else{//�ݹ�
		if( s((a+b)/2,delta,alfa,size) < s(a,delta,alfa,size)){
			 half_eigen(a,(a+b)/2,delta,alfa,lamda,size);
		}//��ݹ�
		else if( s((a+b)/2,delta,alfa,size) > s(a,delta,alfa,size)){
			half_eigen((a+b)/2,b,delta,alfa,lamda,size);//�ҵݹ�
		} 
	}
}
int main(){
	/*
	��ʼ�����������������
	*/
	clock_t start,finish;
	double total_time;
	int size = N;
	float delta[N]={1,1,1,1,1,1,1,1,1,1},
			alfa[N-1]={1,1,1,1,1,1,1,1,1};
	float lamda[N];
	//float delta[N],alfa[N-1];
	float Tinf;//�װ뾶
	start = clock();
	Tinf = fabs(delta[size-1])+fabs(alfa[size-2]);
	if(Tinf < (fabs(delta[0])+fabs(alfa[0]))){
		Tinf = fabs(delta[0])+fabs(alfa[0]);
	}
	for(int i=1;i<size-1;++i){
		if(Tinf < (fabs(alfa[i])+fabs(delta[i])+fabs(alfa[i-1]))){
			Tinf = fabs(alfa[i])+fabs(delta[i])+fabs(alfa[i-1]);
		}
	}
	half_eigen(-Tinf, Tinf, delta, alfa, lamda, size); //���õݹ麯��
	for(int i=0;i<size;++i){
		cout<<lamda[i]<<endl;
	}
	finish = clock();
	total_time = double(finish - start)/CLOCKS_PER_SEC*1000;
	cout<<endl<<"time:"<<total_time;
	system("pause");
	return 0;
}