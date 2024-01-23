template <typename Info, typename Tag>
struct LazySegTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
 
    LazySegTree(int n = 0) {
        init(n);
    }
 
    void init(int n) {
        this->n = n;
        info.assign(4 * n, Info());
        tag.assign(4 * n, Tag());
    }

    void apply(int i, int L, int R, const Tag& _tag) {
        info[i].apply(L, R, _tag);
        tag[i].apply(_tag);
    }

    void push(int i, int L, int mid, int R) {
        if (tag[i] == Tag()) {
            return;
        }
        apply(2 * i, L, mid, tag[i]);
        apply(2 * i + 1, mid + 1, R, tag[i]);
        tag[i] = Tag();
    }
 
    void pull(int i) {
        info[i] = info[2 * i] + info[2 * i + 1];
    }
 
    void set(int idx, Info _info, int i, int L, int R) {
        if (L == R) {
            info[i] = _info;
            return;
        }
        int mid = (L + R) / 2;
        push(i, L, mid, R);
        if (idx <= mid) {
            set(idx, _info, 2 * i, L, mid);
        } else {
            set(idx, _info, 2 * i + 1, mid + 1, R);
        }
        pull(i);
    }

    void set(int idx, Info _info) {
        set(idx, _info, 1, 0, n - 1);
    }
 
    Info rangeQuery(int qL, int qR, int i, int L, int R) {
        if (R < qL || qR < L) {
            return Info();
        }
        if (qL <= L && R <= qR) {
            return info[i];
        }
        int mid = (L + R) / 2;
        push(i, L, mid, R);
        Info a = rangeQuery(qL, qR, 2 * i, L, mid);
        Info b = rangeQuery(qL, qR, 2 * i + 1, mid + 1, R);
        return a + b;
    }

    Info rangeQuery(int qL, int qR) {
        if (qL > qR) {
            return Info();
        }
        return rangeQuery(qL, qR, 1, 0, n - 1);
    }

    void rangeUpdate(int uL, int uR, Tag _tag, int i, int L, int R) {
        if (R < uL || uR < L) {
            return;
        }
        if (uL <= L && R <= uR) {
            apply(i, L, R, _tag);
            return;
        }
        int mid = (L + R) / 2;
        push(i, L, mid, R);
        rangeUpdate(uL, uR, _tag, 2 * i, L, mid);
        rangeUpdate(uL, uR, _tag, 2 * i + 1, mid + 1, R);
        pull(i);
    }

    void rangeUpdate(int uL, int uR, Tag _tag) {
        if (uL > uR) {
            return;
        }
        rangeUpdate(uL, uR, _tag, 1, 0, n - 1);
    }
};

struct Tag {
    // To-do
    Tag(int x = 0) {
        ;
    }
    void apply(const Tag& _tag) {
        ;
    }
    bool operator==(const Tag& _tag) {
        ;
    }
};

struct Info {
    // To-do
    Info(int x = 0) {
        ;
    }
    void apply(int L, int R, const Tag& _tag) {
        ;
    }
    Info operator+(const Info& b) {
        ;
    }
};