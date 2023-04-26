vt<int> buildZ(string s) {
	int n=sz(s), l=0, r=0;
	vt<int> Z(n, 0);
	FOR(i, 1, n) {
		if(i<=r)
			Z[i]=min(r-i+1, Z[i-l]);
		while(s[Z[i]]==s[i+Z[i]])
			++Z[i];
		if(i+Z[i]-1>r)
			l=i, r=i+Z[i]-1;
	}
	return Z;
}
