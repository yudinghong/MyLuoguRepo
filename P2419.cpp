#ifdef TOPOLOGICAL_SORT_METHOD
#include <cstdio>
#include <iostream>
const int maxn = 4e3 + 10;
int n, m, G[maxn][maxn], fa[maxn];
int path[maxn][maxn];
int find(int x) {
    while (x != fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}
int q[maxn], ind[maxn];
int l, r, ret;
int topo() {
    for (int i = 1; i <= n; i++) {
        if (!ind[i])
            q[++r] = i;
    }
    while (l < r) {
        int u = q[++l];
        if (l == r) {
            int i;
            for (i = 1; i <= r; i++)
                if (path[u][q[i]] == 0)
                    break;
            if (i == r + 1)
                ret++;
        }
        for (int i = 1; i <= n; i++) {
            if (G[u][i] /*&& ind[i]*/) {
                ind[i]--;
                if (!ind[i])
                    q[++r] = i;
                for (int j = 1; j <= r; j++)
                    path[i][q[j]] |= path[u][q[j]];
                // if (path[u][q[j]])
                //     path[i][q[j]] = 1;
            }
        }
    }
    return ret;
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        fa[find(x)] = find(y);
        G[x][y] = 1;
        ind[y]++;
    }
    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i)
            k++;
        path[i][i] = 1;
    }
    if (k > 1) {
        printf("0\n");
        return 0;
    }
    printf("%d\n", topo());
    return 0;
}
#endif

#include <cstdio>
using namespace std;
const int maxn = 120;
int ans;
int n, m, f[maxn][maxn];
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        f[x][y] = 1;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = f[i][j] | (f[i][k] & f[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        int ok = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            ok = ok & (f[i][j] | f[j][i]);
        }
        ans += ok;
    }
    printf("%d\n", ans);
    return 0;
}
