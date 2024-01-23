struct Treap {
	int key, val, priority, sz, sum, tag;
	Treap *left, *right, *par;

	Treap(int k, int v) {
		init(k, v);
	}

	void init(int k, int v) {
		key = k;
		val = sum = v;
		tag = -1;
		priority = rand();
		sz = 1;
		left = right = par = NULL;
	}

	void app() {
		// To-do
		return;
	}

	void push() {
		if (tag == -1) {
			return;
		}
		if (left != NULL) {
			left->app();
		}
		if (right != NULL) {
			right->app();
		}
		tag = -1;
	}

	void pull() {
		sz = 1 + (left ? left->sz : 0) + (right ? right->sz : 0);
		sum = sum + (left ? left->sum : 0) + (right ? right->sum : 0);
		if (left != NULL) {
			left->par = this;
		}
		if (right != NULL) {
			right->par = this;
		}
	}
};

Treap* merge(Treap* a, Treap* b) {
	if (a == NULL || b == NULL) {
		return a == NULL ? b : a;
	}
	if (a->priority < b->priority) {
		a->push();
		a->right = merge(a->right, b);
		a->pull();
		return a;
	}
	b->push();
	b->left = merge(a, b->left);
	b->pull();
	return b;
}

pair<Treap*, Treap*> splitK(Treap* root, int k) {
	Treap *a = NULL, *b = NULL;
	if (root == NULL) {
		return make_pair(a, b);
	}
	root->push();
	int sz = (root->left ? root->left->sz : 0) + 1;

	if (sz <= k) {
		a = root;
		tie(a->right, b) = splitK(a->right, k - sz);
		a->pull();
	} else {
		b = root;
		tie(a, b->left) = splitK(b->left, k);
		b->pull();
	}
	return make_pair(a, b);
}

int find(Treap* target) {
	vector<Treap*> path;
	Treap* tmp = target;
	while (tmp) {
		path.push_back(tmp);
		tmp = tmp->par;
	}
	reverse(path.begin(), path.end());

	for (auto &p : path) {
		p->push();
		p->pull();
	}

	int idx = (target->left ? target->left->sz : 0) + 1;
	while (target) {
		Treap* p = target->par;
		if (p != NULL && p->right == target) {
			idx += (p->left ? p->left->sz : 0) + 1;
		}
		target = target->par;
	}
	return idx;
}

Treap* build(const vector<int>& v) {
	Treap* root = NULL;
	for (int i = 0; i < int(v.size()); ++i) {
		root = merge(root, new Treap(i, v[i]));
	}
	return root;
}

void print(Treap* root) {
	while (root) {
		Treap* tmp = NULL;
		tie(tmp, root) = splitK(root, 1);
		cout << tmp->val << " ";
		delete tmp;
	}
}