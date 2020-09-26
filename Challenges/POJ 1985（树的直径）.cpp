#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

const int maxn = int(5e5 + 5);
struct data {
    int to, cost, next;
    data(int to, int cost, int next):to(to), cost(cost), next(next){}
};
vector<data> a;
int head[maxn], father[maxn], dis[maxn];
int n, m;

void add(int x, int y, int z) {

    a.push_back(data(y, z, head[x]));
    head[x] = a.size() - 1;
}
void dfs(int pre) {

    for (int i = head[pre]; i != -1; i = a[i].next) {
        int now = a[i].to;
        if (father[pre] == now) continue;
        father[now] = pre;
        dis[now] = dis[pre] + a[i].cost;
        dfs(now);
    }
}
int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();
    cin >> n >> m;

    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        dis[i] = 0;
    }

    int x, y, z;
    char cc;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z >> cc;
        add(x, y, z);
        add(y, x, z);
    }
    dfs(1);
    int res = INT_MIN, id = 1;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > res) {
            res = dis[i];
            id = i;
        }
        father[i] = i;
        dis[i] = 0;
    }

    dfs(id);
    for (int i = 1; i <= n; i++) {
        res = max(res, dis[i]);
    }
    cout << res << endl;


    return 0;
}