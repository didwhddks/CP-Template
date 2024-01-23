struct LCA {
    // 1-indexed
    int n, time, logN;
    vector<int> tin, tout, dep;
    vector<vector<int>> adj, anc;

    LCA(int n = 1) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        time = 0;
        logN = __lg(n);
        tin.assign(n + 1, 0);
        tout.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        adj.assign(n + 1, vector<int>());
        anc.assign(n + 1, vector<int>(logN + 1, 0));
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void dfs(int u, int p) {
        tin[u] = ++time;
        anc[u][0] = p;
        for (int i = 1; i <= logN; ++i) {
            anc[u][i] = anc[anc[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
        tout[u] = ++time;
    }

    void build(int root = 1, int p = 0) {
        dfs(root, p);
        tout[0] = ++time;
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int getLCA(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = logN; ~i; --i) {
            if (isAncestor(anc[u][i], v) == false) {
                u = anc[u][i];
            }
        }
        return anc[u][0];
    }

    int getDist(int u, int v) {
        int lca = getLCA(u, v);
        return dep[u] + dep[v] - 2 * dep[lca];
    }

    bool onPath(int u, int x, int v) {
        int a = getLCA(u, v);
        int b = getLCA(u, x);
        int c = getLCA(v, x);
        return (a == c && b == x) || (a == b && c == x);
    }
};