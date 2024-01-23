vt<int> size, heavyChild, arr, top, idx;
vt<int> parent, depth;

void findHeavyChild(int u, int p=-1) {
	sz[u]=1;
	heavyChild[u]=-1;
	EACH(v, adj[u])
		if(v^p) {
			parent[v]=u;
			depth[v]=depth[u]+1;
			findHeavyChild(v, u);
			if(heavyChild[u]==-1||size[heavyChild[u]]<size[v])
				heavyChild[u]=v;
			size[u]+=size[v];
		}
}

void build_link(int u, int p, int link_top) {
	arr.pb(u);
	idx[u]=sz(arr)-1;
	top[u]=link_top;
	if(heavyChild[u]==-1) // Leaf node
		return;
	build_link(heavyChild[u], u, link_top);
	EACH(v, adj[u])
		if(v^p&&v^heavyChild[u])
			build_link(v, u, v);
}

int lca(int a, int b) {
	int ta=top[a], tb=top[b];
	while(ta^tb) {
		if(depth[a]<depth[b]) {
			b=parent[tb];
			tb=top[b];
		} else {
			a=parent[ta];
			ta=top[a];
		}
	}
	// at the same chain
	if(depth[a]>depth[b])
		swap(a, b);
	return a;
}
