struct SCC {
    // 1-indexed
    int n, cnt, time;
    vector<int> dfn, low, stk, idx;
    vector<bool> inStk;
    vector<vector<int>> adj, scc;
    vector<vector<int>> nadj;
    vector<pair<int, int>> edges;

    SCC(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        cnt = time = 0;
        low.resize(n + 1);
        idx.resize(n + 1);
        dfn.assign(n + 1, -1);
        inStk.assign(n + 1, false);
        adj.assign(n + 1, vector<int>());
        scc.assign(n + 1, vector<int>());
        nadj.assign(n + 1, vector<int>());
        edges.clear();
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
    }

    void dfs(int u = 1, int p = 0) {
        stk.push_back(u);
        inStk[u] = true;
        low[u] = dfn[u] = time++;

        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            } else if (inStk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            ++cnt;
            int t;
            do {
                t = stk.back();
                stk.pop_back();
                inStk[t] = false;
                scc[cnt].push_back(t);
                idx[t] = cnt;
            } while (t != u);
        }
    }

    void build() {
        for (int i = 1; i <= n; ++i) {
            if (~dfn[i]) {
                continue;
            }
            dfs(i);
        }
        edges.clear();
        set<pair<int, int>> t;
        for (int i = 1; i <= n; ++i) {
            for (int j : adj[i]) {
                int u = idx[i], v = idx[j];
                if (u == v) {
                    continue;
                }
                t.insert({u, v});
            }
        }
        for (auto [u, v] : t) {
            edges.emplace_back(u, v);
            nadj[u].push_back(v);
        }
    }

    int getIdx(int u) {
        assert(u < int(idx.size()));
        return idx[u];
    }
};