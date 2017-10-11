/*
 * HDU 1639（对数+期望）
 */
#include<bits/stdc++.h>
using namespace std;
typedef long double LD;

const int maxn=int(2e5+5);
LD a[2*maxn];
double p;
int n;

LD C(int n,int m){

    return a[n]-a[m]-a[n-m];
}
void ini(){

    a[0]=0;
    for(int i=1;i<maxn;i++)
        a[i]=a[i-1]+log(i);
}
void solve(){

    static int kase=0;
    double res=0;
    for(int i=0;i<=n;i++){
        LD cc=C(n*2-i,n);
        LD xx=cc+(n+1)*log(p)+(n-i)*log(1-p);
        LD yy=cc+(n+1)*log(1-p)+(n-i)*log(p);
        res+=i*(exp(xx)+exp(yy));
    }
    printf("Case %d: %.6lf\n",++kase,res);
}
int main(){

    ini();
    while(cin>>n>>p) solve();
//    system("pause");

    return 0;
}
/*
10 0.400000
100 0.500000
124 0.432650
325 0.325100
532 0.487520
2276 0.720000
 */