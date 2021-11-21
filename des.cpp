#include<bits/stdc++.h>
using namespace std;

int ip[8]={2,6,3,1,4,8,5,7};
int ipInv[8]={4,1,3,5,7,2,8,6};
int k1[8],k2[8],ptCpy[8],key[10],pt[8],ct[8],dct[8];
int ep[8]={4,1,2,3,2,3,4,1};
int p4[4]={2,4,3,1};
int s0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int s1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
int p10[10]={3,5,2,7,4,10,1,9,8,6};
int p8[8]={6,3,7,4,8,5,10,9};
int mat[2][2]={{0,1},{2,3}};
char bin[4][3]={"00","01","10","11"};

void permute(int* res,int* data,int* perm,int n){
	for(int i=0;i<n;i++){
		res[i]=data[perm[i]-1];
	}
}

void swp(){
	int tmp;
	for(int i=0;i<4;i++){
		swap(ptCpy[4+i],ptCpy[i]);
	}
}

void lShift(int* l,int *r,int *arr,int s,int n=10){
	n/=2;
	for(int i=0;i<n;i++){
		l[i]=arr[(i+s)%n];
		r[i]=arr[n+(i+s)%n];
	}
}

void cpy(int *arr,int *toCpy,int index){
	for(int i=0;i<5;i++){
		arr[index+i]=toCpy[i];
	}
}

void keygen(int *key){
	int l[5],r[5],tmp[10];
	permute(tmp,key,p10,10);
	lShift(l,r,tmp,1);
	cpy(tmp,l,0);
	cpy(tmp,r,5);
	permute(k1,tmp,p8,8);
	lShift(l,r,tmp,2);
	cpy(tmp,l,0);
	cpy(tmp,r,5);
	permute(k2,tmp,p8,8);

}

void fk(int *key){
	int l[2],r[2],temp[10],xorOut[10],row,col;
	for(int i=0;i<8;i++){
		temp[i]=ptCpy[4+ep[i]-1];
	}
	for(int i=0;i<8;i++){
		temp[i]=(temp[i]^key[i]);
	}
	row=mat[temp[0]][temp[3]];
	col=mat[temp[1]][temp[2]];
	l[0]=bin[s0[row][col]][0]-'0';
	l[1]=bin[s0[row][col]][1]-'0';
	row=mat[temp[4+0]][temp[4+3]];
	col=mat[temp[4+1]][temp[4+2]];
	r[0]=bin[s1[row][col]][0]-'0';
	r[1]=bin[s1[row][col]][1]-'0';
	for(int i=0;i<2;i++){
		temp[i]=l[i];
		temp[2+i]=r[i];
	}
	permute(xorOut,temp,p4,4);
	for(int i=0;i<4;i++){
		ptCpy[i]=ptCpy[i]^xorOut[i];
	}
}

void encrypt(){
	permute(ptCpy,pt,ip,8);
	fk(k1);
	swp();
	fk(k2);
	permute(ct,ptCpy,ipInv,8);
}

void decrypt(){
	permute(ptCpy,ct,ip,8);
	fk(k2);
	swp();
	fk(k1);
	permute(dct,ptCpy,ipInv,8);
}

int main(){
	cout<<"Enter 10 bit key :"<<endl;
	for(int i=0;i<10;i++)cin>>key[i];
	cout<<"Enter 8 bit plain text :"<<endl;
	for(int i=0;i<8;i++)cin>>pt[i];
	keygen(key);
	encrypt();
	decrypt();
	cout<<"plain text: ";
	for(int i=0;i<8;i++)cout<<pt[i]<<" ";
	cout<<"\nkey1: ";
	for(int i=0;i<8;i++)cout<<k1[i]<<" ";
	cout<<"\nkey2: ";
	for(int i=0;i<8;i++)cout<<k2[i]<<" ";
	cout<<"\ncipher text: ";
	for(int i=0;i<8;i++)cout<<ct[i]<<" ";
	cout<<"\ndecipher text: ";
	for(int i=0;i<8;i++)cout<<dct[i]<<" ";
	cout<<endl;
	// for(int i=0;i<8;i++)cout<<k1[i]<<' ';
	// cout<<endl;
	// for(int i=0;i<8;i++)cout<<k2[i]<<' ';
	// cout<<endl;	
}
/*
0 0 1 0 0 1 0 1 1 1
1 0 1 0 0 1 0 1
*/