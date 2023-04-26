struct Treap {
	int k, v, pr, size, lz, sum;
	Treap *l, *r, *p;
	Treap(int k, int v):pr(rand()), k(k), v(v), size(1), l(NULL), r(NULL), p(NULL), lz(0), sum(v) {}
	void pull() {
		size=1+(l?l->size:0)+(r?r->size:0);
		sum=0ll+v+(l?l->sum:0)+(r?r->sum:0);
		if(l) l->p=this;
		if(r) r->p=this;
	}
	void app(int cnt) {
		swap(l, r);
		lz+=cnt;
	}
	void push() {
		if(lz&1) {
			if(l) l->app(lz);
			if(r) r->app(lz);
		}
		lz=0;
	}
};

Treap* merge(Treap *a, Treap *b) {
	if(!a||!b)	return a?a:b;
	if(a->pr<b->pr) {
		a->push();
		a->r=merge(a->r, b);
		a->pull();
		return a;
	}
	b->push();
	b->l=merge(a, b->l);
	b->pull();
	return b;
}

pair<Treap*, Treap*> splitK(Treap* rt, int k) {
	Treap *a=NULL, *b=NULL;
	if(!rt) return {a, b};
	rt->push();
	int left_size=(rt->l?rt->l->size:0)+1;
	if(k>=left_size) {
		a=rt;
		tie(a->r, b)=splitK(a->r, k-left_size);
	} else {
		b=rt;
		tie(a, b->l)=splitK(b->l, k);
	}
	if(a) a->pull();
	if(b) b->pull();
	return {a, b};
}

int find(int n, vt<Treap*>& handle) {
	Treap* h=handle[n];
	vt<Treap*> path;
	while(h) {
		path.pb(h);
		h=h->p;
	}
	reverse(all(path));
	EACH(t, path) {
		t->push();
		t->pull();
	}
	h=handle[n];
	int idx=(h->l?h->l->size:0)+1;
	while(h) {
		if(h->p&&h==h->p->r)
			idx+=(h->p->l?h->p->l->size:0)+1;
		h=h->p;
	}
	return idx;
}
