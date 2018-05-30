/*
 * POJ 3264 (Ïß¶ÎÊ÷RMQ) Ä£°åÌâ
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int maxn = int(5e4 + 5);
int mi[maxn][20], ma[maxn][20];
int a[maxn], n, q, t;

inline int Min(int l, int r) {

    for(t = 0; (1 << (t + 1)) <= r - l + 1; t++);
    return min(mi[l][t], mi[(r + 1 - (1 << t))][t]);
}
inline int Max(int l, int r) {

    for(t = 0; (1 << (t + 1)) <= r - l + 1; t++);
    return max(ma[l][t], ma[(r + 1 - (1 << t))][t]);
}
void solve() {

    for(int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        mi[i][0] = ma[i][0] = a[i];
    }
    for(int j = 1; (1 << j) <= n; j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++) {
            mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
            ma[i][j] = max(ma[i][j - 1], ma[i + (1 << (j - 1))][j - 1]);
        }
    int l, r;
    while(q--) {
        scanf("%d%d", &l, &r);
        printf("%d\n", Max(l, r) - Min(l, r));
    }
}
int main() {

    while(cin >> n >> q) solve();

//    system("pause");
    return 0;
}
