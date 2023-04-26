vt<int> buildPi(string s) {
	int n=sz(s);
	vt<int> Pi(n, -1);
	FOR(i, 1, n) {
		int j=Pi[i-1];
		while(~j&&s[i]!=s[j+1])
			j=Pi[j];
		Pi[i]=s[i]==s[j+1]?j+1:j;
	}
	return Pi;
}

/*以字串b匹配字串a，傳回匹配成功的數量(用b的pi array)*/
int kmp_match(string a, string b) {
	int j=-1, ans=0, n1=sz(a), n2=sz(b);
	vt<int> Pi=buildPi(b);
	FOR(n1) {
		while(~j&&a[i]!=b[j+1])
			j=Pi[j];
		if(a[i]==b[j+1])
			++j;
		if(j==n2-1)
			++ans, j=Pi[j];
	}
	return ans;
}
