const int mxn=1e5+5;
vt<int> adj[mxn];
vt<vt<int>> bcc;
int d[mxn], anc[mxn][19];
bool vis[2*mxn], act[mxn], cut[mxn];
 
void dfs(int u=0, int p=-1) {
	anc[u][0]=p;
	FOR(i, 1, 19)
		anc[u][i]=~anc[u][i-1]?anc[anc[u][i-1]][i-1]:-1;
	EACH(v, adj[u])
		if(v^p) {
			d[v]=d[u]+1;
			dfs(v, u);
		}
}

int jump(int u, int d) {
	FOR(19)
		if(d&1<<i)
			u=anc[u][i];
	return u;
}
 
int lca(int u, int v) {
	if(d[u]>d[v])
		swap(u, v);
	v=jump(v, d[v]-d[u]);
	if(u==v)
		return u;
	FOR(i, 18, -1, -1)
		if(anc[u][i]^anc[v][i])
			u=anc[u][i], v=anc[v][i];
	return anc[u][0];
}
