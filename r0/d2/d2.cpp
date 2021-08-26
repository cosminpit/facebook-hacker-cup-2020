#include <queue>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;
const int64_t INF = 1e16;

struct SegTree {
    vector<int64_t> t;

    SegTree(int n) : t(2*n, INF) {
    }

    void update(int i, int64_t x) {
        for (i += t.size()/2; i; i /= 2) t[i] = min(t[i], x);
    }

    int64_t query(int l, int r) {
        int n = t.size()/2;
        int64_t res = INF;
        for (l += n, r += n; l <= r; l /= 2, r /= 2) {
            if ((l & 1) == 1) res = min(res, t[l++]);
            if ((r & 1) == 0) res = min(res, t[r--]);
        }
        return res;
    }
};

void bfs(int u, Graph &g, vector<int> &p, vector<int> &h) {
    vector<bool> visited(g.size());
    queue<int> q;
    q.push(u), p[u] = -1, h[u] = 0, visited[u] = true;
    while (!q.empty()) {
        u = q.front(), q.pop();
        for (int v: g[u]) if (!visited[v]) {
            q.push(v), p[v] = u, h[v] = 1 + h[u], visited[v] = true;
        }
    }
}

int64_t expand(int u, int m, Graph &g, vector<int> &h, vector<int> &c, vector<bool> &visited, SegTree &segTree) {
    int lo = h[u];
    queue<int> q; q.push(u), visited[u] = true;
    int64_t res = -1;
    while (!q.empty()) {
        u = q.front(), q.pop();
        if (h[u] - lo > m) continue;

        int hi = min<int>(lo + (m - (h[u] - lo)), g.size() - 1);
        int64_t cost = segTree.query(lo, hi);
        
        if (cost == INF) continue;
        if (lo == h[u]) res = cost;
        if (c[u]) segTree.update(h[u], cost + c[u]);

        for (int v: g[u]) if (!visited[v]) {
            q.push(v), visited[v] = true;
        }
    }
    return res;
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n, m, a, b; fin >> n >> m >> a >> b; a--; b--;
        vector<int> c(n), p(n), h(n);
        Graph g(n);

        for (int u = 0; u < n; u++) {
            int v; fin >> v >> c[u]; v--;
            if (v == -1) continue;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        bfs(b, g, p, h);

        SegTree segTree(n); segTree.update(h[a], 0);    
        vector<bool> visited(n);
        int64_t ans = -1;
        for (int u = a; u != -1; u = p[u]) {
            if (p[u] != -1) visited[p[u]] = true;
            int64_t cost = expand(u, m, g, h, c, visited, segTree);
            if (u == b) ans = cost;
            if (p[u] != -1) visited[p[u]] = false;
        }
        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}
