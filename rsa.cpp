#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;

int multiplicativeInv(int x,int m){
    for(int i=2;i<m;i++){
        if((x*i)%m==1)return i;
    }
    cout<<"inv doesn't exist"<<endl;
    exit(0);
}
int powCustom(int a,int b,int n){
    int ans=1;
    while(b--){
        ans=(ans*a)%n;
    }
    return ans;
}
int main(){
    int p,q;
    cout<<"enter p,q: ";
    cin>>p>>q;
    int n=p*q,o=(p-1)*(q-1),e=o;
    while(__gcd(e,o)!=1){
        cout<<"enter e: ";
        cin>>e;
    }
    int d=multiplicativeInv(e,o);
    cout<<"d: "<<d<<endl;
    vector<int>ku={e,n};
    vector<int>kr={d,p,q};
    int m;
    cout<<"enter message: ";
    cin>>m;
    ll c=powCustom(m,e,n);
    cout<<"cipher text: "<<c<<endl;
    cout<<"decipher text: "<<powCustom(c,d,n)<<endl;
}