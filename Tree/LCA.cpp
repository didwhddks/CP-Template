struct LCA {
  int time = 0, logN;
  vector<int> tin, tout;
  vector<vector<int>> adj, anc;
  void init(int n) {
    logN = __lg(n);
    anc.assign(n + 1, vector<int>(logN + 1, 0));
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    adj.assign(n + 1, vector<int>());
  }
  void add_edge(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  void dfs(int u = 1, int p = 0) {
    tin[u] = ++time;
    anc[u][0] = p;
    for (int i = 1; i <= logN; ++i) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int v : adj[u])
      if (v != p) dfs(v, u);
    tout[u] = ++time;
  }
  void build() {
    dfs();
    tout[0] = ++time;
  }
  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }
  int query(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = logN; ~i; --i)
      if (!is_ancestor(anc[u][i], v)) u = anc[u][i];
    return anc[u][0];
  }
};