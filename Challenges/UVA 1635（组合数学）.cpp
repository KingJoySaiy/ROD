/*
 * UVA 1635（组合数学）
 * 题目大意：略
 */
#include<bits/stdc++.h>
using namespace std;

const int maxn=int(1e5+5);
bool bad[maxn];

void fact(int m,vector<int> &primes){  //m分解因子

    int x=int(sqrt(m)+0.5);
    for(int i=2;i<=x;i++){
        if(m%i==0){
            primes.push_back(i);
            while(m%i==0) m/=i;
        }
    }
    if(m>1) primes.push_back(m);
}
int main(){

    int n,m;
    while(cin>>n>>m){

        memset(bad,false,sizeof(bad));
        vector<int> primes;
        fact(m, primes);
        n--;

        // 求c(n,0)~c(n,n)有哪些数是m的倍数
        for(int i=0;i<primes.size();i++){
            int p=primes[i],e=0;    //C(n,0)=p^e
            int min_e=0,x=m;
            while(x%p==0){
                x/=p;
                min_e++;
            }
            // c(n,k)=c(n,k-1)*(n-k+1)/k
            // 第k个组合数prime[i]的系数都大于min_e才能被整除
            for(int k=1;k<n;k++){
                x=n-k+1;
                while(x%p==0){
                    x/=p;
                    e++;
                }
                x=k;
                while(x%p==0){
                    x/=p;
                    e--;
                }
                if(e<min_e) bad[k]=true;    //第k项不能被整除
            }
        }
        vector<int> res;
        for(int k=1;k<n;k++) if(!bad[k]) res.push_back(k+1);
        cout<<res.size()<<endl;
        if(!res.empty()){
            cout<<res[0];
            for(int i=1;i<res.size();i++) cout<<' '<<res[i];
        }
        puts("");
    }
    return 0;
}

