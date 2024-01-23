struct Trie {
    int n, cnt;
    vector<int> end;
    vector<vector<int>> tr;

    Trie(int n = 5E5) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        cnt = 0;
        tr.assign(n, vector<int>(26, 0));
        end.assign(n, 0);
    }

    void insert(string word) {
        int u = 0;
        for (char &c : word) {
            int v = c - 'a';
            if (!tr[u][v]) {
                tr[u][v] = ++cnt;
            }
            u = tr[u][v];
        }
        end[u]++;
    }

    bool find(string word) {
        int u = 0;
        for (char &c : word) {
            int v = c - 'a';
            if (!tr[u][v]) {
                return false;
            }
            u = tr[u][v];
        }
        return end[u] > 0;
    }
};