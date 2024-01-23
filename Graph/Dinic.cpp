template <typename T>
struct flowEdge {
    int u, v;
    T flow, cap;
    flowEdge(int u, int v, T cap) {
        this->u = u;
        this->v = v;
        this->flow = 0;
        this->cap = cap;
    }
};

template <typename T>
struct Dinic {
    // 1-indexed
    int n, cnt, start, end;
    T INF = numeric_limits<T>::max();
    vector<int> dep, ptr;
    vector<vector<int>> adj;
    vector<flowEdge<T>> edges;

    Dinic(int n = 0, int start = 0, int end = 0) {
        init(n, start, end);
    }

    void init(int n, int start, int end) {
        this->n = n;
        this->start = start;
        this->end = end;
        cnt = 0;
        dep.assign(n + 1, -1);
        ptr.assign(n + 1, 0);
        adj.assign(n + 1, vector<int>());
        edges.clear();
    }

    void addEdge(int u, int v, T cap) {
        flowEdge<T> forward(u, v, cap);
        flowEdge<T> rev(v, u, 0);
        edges.push_back(forward);
        edges.push_back(rev);
        adj[u].push_back(cnt);
        adj[v].push_back(cnt + 1);
        cnt += 2;
    }

    bool bfs() {
        queue<int> qu;
        qu.push(start);
        dep[start] = 0;

        while (qu.size()) {
            int u = qu.front();
            qu.pop();
            for (int eid : adj[u]) {
                int v = edges[eid].v;
                T res = edges[eid].cap - edges[eid].flow;
                if (res <= T() || ~dep[v]) {
                    continue;
                }
                dep[v] = dep[u] + 1;
                qu.push(v);
            }
        }
        return dep[end] != -1;
    }

    T dfs(int u, T mn) {
        if (mn == T() || u == end) {
            return mn;
        }
        for (int &p = ptr[u]; p < int(adj[u].size()); ++p) {
            int eid = adj[u][p];
            int v = edges[eid].v;
            T res = edges[eid].cap - edges[eid].flow;
            if (res <= T() || dep[v] != dep[u] + 1) {
                continue;
            }
            T f = dfs(v, min(mn, res));
            if (f == T()) {
                continue;
            }
            edges[eid].flow += f;
            edges[eid ^ 1].flow -= f;
            return f;
        }
        return T();
    }

    T flow() {
        T ans = T();
        while (bfs()) {
            T f = T();
            while (f = dfs(start, INF)) {
                ans += f;
            }
            fill(ptr.begin(), ptr.end(), 0);
            fill(dep.begin(), dep.end(), -1);
        }
        return ans;
    }
};