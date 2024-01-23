vector<int> buildZ(string s) {
	const int n = s.size();
	int L = 0, R = 0;
	vector<int> Z(n);
	for (int i = 1; i < n; ++i) {
		if (i <= R) {
			Z[i] = min(Z[i - L], R - i + 1);
		}
		while (s[Z[i]] == s[i + Z[i]]) {
			++Z[i];
		}
		if (i + Z[i] - 1 > R) {
			L = i;
			R = i + Z[i] - 1;
		}
	}
	return Z;
}
