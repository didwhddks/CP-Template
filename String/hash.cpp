struct StringHash {
	const int mod = 1073676287;
	const int p = 31;
	vector<int> prime;

	StringHash() {
		prime.assign(1E6 + 1, 1);
		for (int i = 1; i <= 1E6; ++i) {
			prime[i] = 1LL * prime[i - 1] * p % mod;
		}
	}

	vector<int> hash_init(string s) {
		const int n = s.size();
		vector<int> hash(n + 1);
		for (int i = 1; i <= n; ++i) {
			hash[i] = (1LL * hash[i - 1] * p % mod + s[i - 1]) % mod;
		}
		return hash;
	}

	int get_hash(int L, int R, vector<int>& hash) {
		int h = (hash[R + 1] - 1LL * hash[L] * prime[R - L + 1] % mod + mod) % mod;
		return h;
	}
};
