const int mxn=5e5+5, mxk=1e5+5;
bool match[mxk];

struct AC {
	int tr[mxn][26], fail[mxn], tot, cnt[mxn];
	bool end[mxn], vis[mxn], chk[mxn];
	vt<int> idx[mxn], rev_fail[mxn];
	AC() {
		memset(tr, 0, sizeof(tr));
		memset(fail, 0, sizeof(fail));
		memset(cnt, 0, sizeof(cnt));
		memset(chk, 0, sizeof(chk));
		memset(end, 0, sizeof(end));
		memset(vis, 0, sizeof(vis));
		tot=0;
	}
	// insert word and build trie structure
	void insert(int id, string s) {
		int u=0;
		EACH(ch, s) {
			if(!tr[u][ch-'a'])
				tr[u][ch-'a']=++tot;
			u=tr[u][ch-'a'];
		}
		idx[u].pb(id);
		//end[u]=1;
	}
	// build fail pointer for each node and build dictionary graph
	void build() {
		queue<int> qu;
		FOR(26)
			if(tr[0][i])
				qu.push(tr[0][i]);
		while(sz(qu)) {
			int u=qu.front();
			qu.pop();
			FOR(26) {
				if(tr[u][i]) {
					fail[tr[u][i]]=tr[fail[u]][i], qu.push(tr[u][i]);
					//rev_fail[tr[fail[u]][i]].pb(tr[u][i]);
				}
				else
					tr[u][i]=tr[fail[u]][i];
			}
		}
	}
	void solve(string s) {
		int u=0;
		FOR(sz(s)) {
			u=tr[u][s[i]-'a'];
			//++cnt[u];
			for(int j=u; j&&!chk[j]; j=fail[j]) {
				EACH(k, idx[j])
					match[k]=true;
				chk[j]=1;
			}
		}
		/* FOR(tot+1)
			if(!vis[i])
				dfs(i); */
	}
	/* void dfs(int u) {
		vis[u]=1;
		EACH(v, rev_fail[u]) {
			if(!vis[v])
				dfs(v);
			cnt[u]+=cnt[v];
		}
		EACH(v, idx[u])
			ans[v]=cnt[u];
	} */
} ac;
