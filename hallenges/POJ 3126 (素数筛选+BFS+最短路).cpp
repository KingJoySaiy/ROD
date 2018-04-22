/*
 * POJ 3126 (素数筛选+BFS+最短路)
 * 题目大意：给定两个四位的素数，每次改变某一位成为另一个素数，求最小操作次数。
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <cstring>

using namespace std;

const int maxn = int(1e4);
vector<int> prime;
int x, y, len;

struct node{        //s->当前素数, step->操作次数

    int s, step;
    node(int s,int step):s(s),step(step){}
    node(){}
    node operator = (const node &t){
        s = t.s;
        step = t.step;
        return *this;
    }
};

void ini(){     //埃氏筛法打出四位数的素数表

    bool book[maxn] = {};
    for(int i = 2; i < maxn; i++){
        if(!book[i]){
            if(i > 999) prime.push_back(i);
            for(int j = i + i; j < maxn; j += i) book[j] = true;
        }
    }
    len = prime.size();
}
inline int f(const int &x, const int &i){      //返回x第i位的数

    switch(i){
        case 0: return x / 1000;
        case 1: return (x/100) % 10;
        case 2: return (x/10) % 10;
        default : return x % 10;
    }
}
inline int work(const int &x, const int &i, const int &tt){ //改变x第i位的数为tt

    switch(i){
        case 0: return x % 1000 + tt * 1000;
        case 1: return x / 1000 * 1000 + x % 100 + tt * 100;
        case 2: return x / 100 * 100 + x % 10 + tt * 10;
        default: return x / 10 * 10 + tt;
    }
}
void solve(){

    cin >> x >> y;
    map<int,bool> book;     //标记素数是否已经出现过
    int num[10], id, tt;
    queue<node> que;
    que.push(node(x, 0));

    node t;
    while(!que.empty()){     //BFS

        t = que.front(); que.pop();
        if(t.s == y){
            cout<<t.step<<endl;
            return ;
        }
        for(int i = 0; i < 4; i++){
            memset(num, 0, sizeof(num));    //标记0 - 9中哪些数字可用
            if(!i) num[0] = 1;              //注意不能出现前导0
            num[f(t.s,i)] = 1;
            for(int j = 0; j < 10; j++)
                if(!num[j]){
                    tt = work(t.s,i,j);
                    id = lower_bound(prime.begin(), prime.end(),tt) - prime.begin();
                    
                    //tt必须是素数，且未标记过
                    if(id == len or prime[id] != tt or book.count(tt)) continue;
                    que.push(node(tt,t.step+1));
                    book[tt] = true;
                }
        }
    }
}
int main(){

    ini();
    int ct;
    cin >> ct;
    while(ct--) solve();

//    system("pause");
    return 0;
}