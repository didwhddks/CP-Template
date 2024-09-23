template <typename Info>
struct SegmentTree {
    int n;
    vector<Info> info;
 
    SegmentTree(int n = 0) {
        init(n);
    }
 
    void init(int n) {
        this->n = n;
        info.assign(4 * n, Info());
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
        Info a = rangeQuery(qL, qR, 2 * i, L, mid);
        Info b = rangeQuery(qL, qR, 2 * i + 1, mid + 1, R);
        return a + b;
    }

    Info rangeQuery(int qL, int qR) {
        return rangeQuery(qL, qR, 1, 0, n - 1);
    }
};

struct Info {
    // To-do
    Info(int x = 0) {
        ;
    }
    Info operator+(const Info& b) {
        ;
    }
};