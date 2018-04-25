/*
 * POJ 2429 (素数测试+合数分解+二进制枚举)
 * 题目大意：给定两个数的gcd和lcm，求两数之和最小的满足条件的两数
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long LL;

const int S = 8;
vector<LL> fact;    //记录因子
map<LL,int> a;      //记录每个因子的个数
LL x,y;

LL mod_mult(LL x,LL y,const LL &mod){  //return x*y%mod

    LL res = 0;
    while(y){
        if(y & 1) res = (res + x) % mod;
        x = (x << 1) % mod;
        y >>= 1;
    }
    return res;
}
LL mod_pow(LL x,LL n,const LL &mod){   //return x^n%mod

    LL res = 1;
    while(n){
        if(n & 1) res = mod_mult(res,x,mod);
        x = mod_mult(x,x,mod);
        n >>= 1;
    }
    return res;
}
LL poww(LL x,LL n){

    LL res = 1;
    while(n){
        if(n & 1) res *= x;
        n >>= 1;
        x *= x;
    }
    return res;
}
bool check(LL a,LL n,LL x,LL t){    //概率测试n是否为合数

    LL now = mod_pow(a,x,n), pre = now;
    for(int i = 0; i < t; i++){
        now = mod_mult(now,now,n);
        if(now == 1 and pre != 1 and pre != n-1) return true;   //二次探测
        pre=now;
    }
    return now != 1;
}
bool Miller_Rabin(LL n){    //判断n是否为素数

    if(n == 2) return true;
    if(n < 2 || (n & 1) == 0) return false;
    LL x = n-1, t = 0;   //n-1 = x*2^t
    while((x & 1) == 0){
        x >>= 1;
        t ++;
    }
    for(int i = 0;i < S; i++){
        LL a = rand() % (n - 1) + 1;
        if(check(a,n,x,t)) return false;
    }
    return true;
}
LL gcd(LL a,LL b){  //求最小公因数

    LL res = b ? gcd(b,a % b) : a;
    return res < 0 ? -res : res;  //注意处理负数情况
}
LL pollard_rho(LL x,LL c){  //求出x的一个因子

    LL i = 1, k = 2;
    LL x1 = rand() % (x-1) + 1, x2 = x1;
    while(1){
        i ++;
        x2=(mod_mult(x2,x2,x) + c) % x;
        LL d = gcd(x1-x2,x);
        if(d != 1 and d != x) return d;    //若gcd不为1则返回因子
        if(x1 == x2) return x;
        if(i == k){
            x1 = x2;
            k += k;
        }
    }
}
void find_fac(LL n,int k){    //找出并记录因子

    if(n == 1) return;
    if(Miller_Rabin(n)){
        fact.push_back(n);
        a[n]++;
        return;
    }
    LL p = n;
    while(p >= n) p = pollard_rho(p,k--);
    find_fac(p,k);   //深搜寻找因子
    find_fac(n / p, k);
}
void solve(){

    if(x == y){
        cout<<x<<' '<<y<<endl;
        return;
    }
    fact.clear();
    a.clear();
    LL z = y/x, base = x;   //两数必须是最大公因数base的倍数，分解lcm/gcd即可
    find_fac(z,107);        //c一般设为107次即可
    pair<LL,LL> res = make_pair(LL(2.3e18),LL(2.3e18)); //数取尽量大，但两数之和不能爆LL
    sort(fact.begin(),fact.end());
    int ct = unique(fact.begin(),fact.end()) - fact.begin();    //对因子进行去重
    for(int i = 0; i < (1 << ct); i++){     //二进制暴力枚举所有情况
        x = 1;
        for(int j = 0; j < ct; j++)
            if(i & (1<<j)) x *= poww(fact[j],a[fact[j]]);   //每次将相同的所有因子都乘起来
        if(x + z/x < res.first + res.second) res = make_pair(x,z/x);
    }
    if(res.first > res.second) swap(res.first,res.second);
    printf("%lld %lld\n",res.first * base, res.second * base);
}
int main(){

    while(scanf("%lld%lld",&x,&y) != -1) solve();

//    system("pause");
    return 0;
}