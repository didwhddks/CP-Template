template <typename T>
struct Fenwick {
	int n;
	vector<T> a;

	Fenwick(int n = 0) {
		init(n);
	}

	void init(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int i, T val) {
		for (++i; i <= n; i += i & -i) {
			a[i] += val;
		}
	}

	T query(int i) {
		T res = T();
		for (++i; i; i -= i & -i) {
			res += a[i];
		}
		return res;
	}

	T rangeSum(int L, int R) {
		return query(R) - query(L - 1);
	}
};