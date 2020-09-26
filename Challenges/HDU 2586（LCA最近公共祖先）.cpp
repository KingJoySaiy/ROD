#include <bits/stdc++.h>

using namespace std;

const int maxn = 40005;
struct data {
    int to, cost;
    data(int to, int cost):to(to), cost(cost){}
};
vector<data> all[maxn];

int dp[maxn][20];
int depth[maxn], father[maxn], cost[maxn];
int n, m;

void dfs(int now, int pre, int deep) {

    depth[now] = deep;
    father[now] = pre;
    for (auto &p : all[now]) {
        if (p.to != pre) {
            cost[p.to] = cost[now] + p.cost;
            dfs(p.to, now, deep + 1);
        }
    }
}

int LCA(int x, int y) {

    if (depth[x] < depth[y]) {
        swap(x, y);
    }
    int t = 0;
    while ((1 << t) <= depth[x]) t++;

    for (int i = t - 1; i >= 0; i--) {
        if (depth[x] - (1 << i) >= depth[y]) {
            x = dp[x][i];
        }
    }
    if (x == y) return x;
    for (int i = t - 1; i >= 0; i--) {
        if (dp[x][i] != -1 and dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    return father[x];
}
void solve() {

    for (int i = 0; i < maxn; i++) {
        all[i].clear();
    }
    cin >> n >> m;
    int a, b, c;
    for (int i = 1; i < n; i++) {
        cin >> a >> b >> c;
        all[a].emplace_back(b, c);
        all[b].emplace_back(a, c);
    }
    cost[1] = 0;
    dfs(1, -1, 0);

    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = father[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (dp[i][j - 1] != -1) {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
    }

    while (m--) {
        cin >> a >> b;
        cout << cost[a] + cost[b] - 2 * cost[LCA(a, b)] << endl;
    }
}
int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();
    int ct;
    cin >> ct;
    while (ct--) solve();


    return 0;
}