#define mod 1073676287
#define ll long long
const int M=1e9+7, mxn=1e5+5, prime=31;
/*mod 必須要是質數*/
ll p[mxn], h[mxn];
string s;

void p_init(int n) { // 0-indexed
	p[0]=1;
	FOR(i, 1, n)
		p[i]=p[i-1]*prime%M;
}

void hash_init(int n) { // 1-indexed
	FOR(i, 1, n+1)
		h[i]=(h[i-1]*prime%M+s[i-1])%M;
}

ll get_hash(int l, int r) { // get hash value of substring
	return (h[r+1]-h[l]*p[r-l+1]%M+M)%M;
}
