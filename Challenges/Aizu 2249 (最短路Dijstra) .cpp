/*
 * Aizu 2249 (Dijstra)
 */
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cstdio>
#include <cmath>
#include <utility>
#include <bitset>
#include <vector>
#include <queue>
#include <map>
//#define int LL

using namespace std;
typedef long long LL;
typedef pair<int, int> pp;

const int maxn = int(1e4 + 5);
const int inf = (INT_MAX >> 1) - 5;

struct data{

    int to, dis, cost;
    data(int x = 0, int y = 0, int z = 0): to(x), dis(y), cost(z){}
};
vector<data> a[maxn];
pp res[maxn];   //first->dist, second->cost
int u, v, d, c;
int n, m;

void dijstra(int x) {

    priority_queue<pp, vector<pp>, greater<pp> > que;   //first->dist, second->to
    fill(res, res + maxn, make_pair(inf, inf));
    res[x] = make_pair(0, 0);
    que.push(make_pair(0, x));

    int from;
    pp t;
    data s;
    while(!que.empty()) {
        t = que.top(); que.pop();
        from = t.second;
        if(res[from].first < t.first) continue;
        for(int i = 0; i < a[from].size(); i++) {
            s = a[from][i];
            if(res[s.to].first > res[from].first + s.dis) {
                //满足松弛条件时入队，更新cost
                res[s.to] = make_pair(res[from].first + s.dis, s.cost);
                que.push(make_pair(res[s.to].first, s.to));
            }
            else if(res[s.to].first == res[from].first + s.dis) {
                //相等时只需更新cost
                res[s.to].second = min(res[s.to].second, s.cost);
            }
        }
    }
}
void solve() {

    for(int i = 0; i < maxn; i++) a[i].clear();
    while(m--) {
        scanf("%d%d%d%d", &u, &v, &d, &c);
        a[u].push_back(data(v, d, c));
        a[v].push_back(data(u, d, c));
    }
    dijstra(1);
    int ans = 0;
    for(int i = 2; i <= n; i++) ans += res[i].second;
    cout << ans << endl;
}
int32_t main() {

    while(cin >> n >> m, n or m) solve();


//    system("pause");
    return 0;
}
