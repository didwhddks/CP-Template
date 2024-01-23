struct BlockCutTree {
    // 1-indexed
    int n, cnt;
    vector<int> dep, low, stk, idx;
    vector<bool> vis, act, cut;
    vector<vector<int>> adj, bcc;
    vector<vector<int>> nadj;
    vector<pair<int, int>> edges;

    BlockCutTree(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        cnt = 0;
        dep.assign(n + 1, 0);
        low.resize(n + 1);
        idx.resize(n + 1);
        vis.assign(n + 1, false);
        act.assign(n + 1, false);
        adj.assign(n + 1, vector<int>());
        bcc.assign(n + 1, vector<int>());
        cut.assign(2 * n + 1, false);
        nadj.assign(2 * n + 1, vector<int>());
        edges.clear();
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void dfs(int u = 1, int p = 0) {
        vis[u] = act[u] = true;
        low[u] = dep[u];
        stk.push_back(u);

        for (int v : adj[u]) {
            if (!vis[v]) {
                dep[v] = dep[u] + 1;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dep[u]) {
                    int t;
                    ++cnt;
                    do {
                        t = stk.back();
                        stk.pop_back();
                        bcc[t].push_back(cnt);
                    } while (t != v);
                    bcc[u].push_back(cnt);
                }
            } else if (act[v] && v != p) {
                low[u] = min(low[u], dep[v]);
            }
        }
        act[u] = false;
    }

    void build() {
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) {
                continue;
            }
            dfs(i);
        }
        edges.clear();
        for (int i = 1; i <= n; ++i) {
            if (bcc[i].size() > 1) {
                idx[i] = ++cnt;
                cut[idx[i]] = true;
                for (int v : bcc[i]) {
                    nadj[idx[i]].push_back(v);
                    nadj[v].push_back(idx[i]);
                    edges.emplace_back(v, idx[i]);
                }
            } else {
                idx[i] = bcc[i].back();
            }
        }
    }

    int getIdx(int u) {
        assert(u < int(idx.size()));
        return idx[u];
    }

    bool isCut(int u) {
        assert(u < int(cut.size()));
        return cut[u];
    }
};