vt<int> arr, in, out;

void dfs(int u, int p=-1) {
	arr.pb(u);
	// arr.pb(cost[u]);
	in[u]=sz(arr)-1;
	EACH(v, adj[u])
		if(v^p)
			dfs(v, u);
	// arr.pb(u);
	// arr.pb(-cost[u]);
	out[u]=sz(arr)-1;
}

Treap *root=NULL;
vt<Treap*> arr, in, out;

void dfs(int u, int p=-1) {
	in[u]=new Treap(cost[u]);
	root=merge(root, in[u]);
	EACH(v, adj[u])
		if(v^p)
			dfs(v, u);
	out[u]=new Treap(0);
	root=merge(root, out[u]);
}
