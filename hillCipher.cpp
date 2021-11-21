#include<bits/stdc++.h>
using namespace std;

int multiplicativeInv(int x,int m){
    for(int i=1;i<m;i++){
        if((x*i)%m==1)return i;
    }
    cout<<"inv doesn't exist"<<endl;
    exit(0);

}

int main(){
    int matrix[2][2];
    cout<<"enter matrix"<<endl;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cin>>matrix[i][j];
        }
    }
    int x=(matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
    string s;
    cout<<"enter message"<<endl;
    cin>>s;
    int length;
    if(s.size()%2!=0)length=s.size()-2;
    else length=s.size()-1;
    string ans="";

    for(int i=0;i<length;i+=2){
        int m[2]={(int)s[i]-65,(int)s[i+1]-65};
        int p[2]={(m[0]*matrix[0][0]+m[1]*matrix[1][0])%26,
                            (m[0]*matrix[0][1]+m[1]*matrix[1][1])%26};
        ans+=(char)(p[0]+65);
        ans+=(char)(p[1]+65);
    }
    cout<<ans<<endl;

    //inverse of matrix
    swap(matrix[0][0],matrix[1][1]);
    matrix[0][1]*=-1;
    matrix[1][0]*=-1;
    string message="";
    
    //decryption
    for(int i=0;i<length;i+=2){
        int m[2]={(int)ans[i]-65,(int)ans[i+1]-65};
        int inv=multiplicativeInv(x,26);
        int p[2]={(inv*(m[0]*matrix[0][0]+m[1]*matrix[1][0]))%26,
                            (inv*(m[0]*matrix[0][1]+m[1]*matrix[1][1]))%26};
        if(p[0]<0)p[0]+=26;
        if(p[1]<0)p[1]+=26;
        message+=(char)(p[0]+65);
        message+=(char)(p[1]+65);
    }
    cout<<message<<endl;
}