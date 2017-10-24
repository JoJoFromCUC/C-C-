/*
author: JoeZhu
time: Oct 2nd,2017
institution: UCAS
license��GPL 3.0
*/
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include "func.h"
#define DIM 60

int main(){
    cout.precision(8);
    cout.setf(ios::fixed);
    SparseMatrix A;
    A.rows = DIM;
    A.cols = DIM;
    int rank = DIM;
	int len = 2*DIM-1;
	
    //�����������
	FILE *fp;
	fp = fopen("./ctest/data.txt","r");
    for(int i=0;i<A.rows;i++){
		int tmp;
        for(int j=0;j<A.cols;j++){
			if(fscanf(fp,"%d",&tmp) == EOF) break; 
            A.cells.push_back(Cell(i,j,tmp));
        }
		if(feof(fp)) break;
    }
	fclose(fp);  
	
	/* cout<<"A = "<<endl;//���A
    A.moveFirst();
    for(int i=0;i<A.rows;i++){
        for(int j=0;j<A.cols;j++){
            cout<<A.next().value<<" ";
        }
        cout<<endl;
    }
	cout<<endl;  */
	
	/* vector<vector<double> > Q;
    vector<double> D; */
	vector<double> alpha(DIM);
	vector<double> beta(DIM-1);
	
	alpha.clear();
	beta.clear();
	vector<Cell> temp = A.cells;
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			if(j == i) alpha.push_back(temp[i*DIM+j].value);
			else if(j == i+1) beta.push_back(temp[i*DIM+j].value); 
		}
	} 
	
	/* ifstream in("./ctest/data1.txt");//��ȡ���Խǡ����Խ�Ԫ��
	if(!in){
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		return -1;
	}
	D.clear();
	int temp;
	while(in >> temp){
		D.push_back(temp);
	}
	in.close();
	alpha.clear();
	beta.clear();
	for(int i=0;i<DIM-1;i++){
		alpha.push_back(D[i]);
		beta.push_back(D[i+DIM]);
	}
	alpha.push_back(D[DIM-1]); 
	D.clear();
	D.resize(DIM);
	*/
	cout<<"alpha:"<<endl;
	for(int i=0;i<DIM;i++){
		cout<<alpha[i]<<" ";
	}
	cout<<endl<<"beta:"<<endl;
	for(int i=0;i<DIM-1;i++){
		cout<<beta[i]<<" ";
	} 
	cout<<endl<<"���ݶ�ȡ���..."<<endl<<"alpha.size: "<<alpha.size()<<endl
		<<"beta.size: "<<beta.size()<<endl;
	clock_t start,finish;//��ʱ
	start = clock();
	
	cout<<"rank = "<<rank<<endl;
    cout<<endl;
	cout<<"��ʼ�ֽ�..."<<endl;

	//DCTridiagonal(alpha,beta,Q,D);
	
	vector<vector<double> > U,V;
    vector<double> s;
	svd(A,rank,U,s,V);//��ʼsvd�ֽ� 
	
	cout<<endl;
	cout<<"����ֵ:"<<endl;//�������ֵ
    for(int i=0;i<s.size();i++){
        for(int j=0;j<s.size();j++){
            if(i == j) cout<<s[i]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
	
	fp = fopen("./ctest/result.txt","w");//д��������������
	int rows = U.size(),cols = U[0].size();
	fprintf(fp,"%s","������������Ϊ:\n");
	for(int i=0;i<rows;++i){
		for(int j=0;j<cols;++j){
			fprintf(fp,"%f ",U[i][j]);
		}
		fprintf(fp,"%s","\n");
	}
	fclose(fp);
    cout<<"��������������д��result.txt�ļ�!\n"<<endl; 
    //print(U);

	/* fp = fopen("./ctest/result.txt","a");//д�����V
	rows = V.size(),cols = V[0].size();
	fprintf(fp,"%s","V����Ϊ:\n");
	for(int i=0;i<rows;++i){
		for(int j=0;j<cols;++j){
			fprintf(fp,"%f ",V[i][j]);
		}
		fprintf(fp,"%c",'\n');
	}
	fclose(fp);
    cout<<"V ������д��result.txt�ļ�!"<<endl; */
    //print(V);
	
	finish = clock();
	cout<<"���������ʱ��"<<(double)(finish-start)/CLOCKS_PER_SEC<<"��"<<endl;
	system("pause");
    return 0;
}