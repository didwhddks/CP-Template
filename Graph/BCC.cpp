const int mxn=1e5+5;
vt<int> adj[mxn], adj1[2*mxn];
vt<vt<int>> bcc;
int low[mxn], d[mxn], cnt;
bool vis[2*mxn], act[mxn], cut[mxn];
stack<int> st;
 
void dfs(int u=0, int p=-1) {
	vis[u]=act[u]=1;
	low[u]=d[u];
	st.push(u);
	int flag=0;
	EACH(v, adj[u]) {
		if(!vis[v]) {
			d[v]=d[u]+1;
			dfs(v, u);
			++flag;
			if(low[v]>=d[u]) {
				if(~p||flag>1)
					cut[u]=1;
				adj1[u].pb(++cnt);
				do {
					adj1[cnt].pb(st.top());
					st.pop();
				} while(adj1[cnt].back()^v);
			}
			umin(low[u], low[v]);
		} else if(act[v]&&v^p)
			umin(low[u], d[v]);
	}
	act[u]=0;
}
