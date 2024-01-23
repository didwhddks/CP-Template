struct DSU {
	int n;
	vector<int> p;
	vector<int> sz;

	DSU(int n = 0) {
		init(n);
	}

	void init(int n) {
		this->n = n;
		sz.assign(n + 1, 1);
		p.assign(n + 1, 0);
		iota(p.begin(), p.end(), 0);
	}

	int find(int x) {
		return x == p[x] ? x : p[x] = find(p[x]);
	}

	bool joint(int a, int b) {
		return find(a) == find(b);
	}

	void merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) {
			return;
		}
		if (sz[a] > sz[b]) {
			swap(a, b);
		}
		p[a] = b;
		sz[b] += sz[a];
	}
};