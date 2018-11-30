int n;
int p[MAXN], d[MAXN], pos[MAXN], color[MAXN], t[2 * MAXN];

vi g[MAXN];
vvi path;

int dfs(int v, int par = -1) {
    int sz = 1;
    int max_sz = 0;
    int max_son = -1;
    for (int to : g[v]) {
        if (to == par) continue;
        d[to] = d[v] + 1;
        p[to] = v;
        int cur_sz = dfs(to, v);
        sz += cur_sz;
        if (max_sz < cur_sz) {
            max_sz = cur_sz;
            max_son = to;
        }
    }
    if (sz == 1) {
        color[v] = sz(path);
        path.pb(vi(1, v));
    } else {
        color[v] = color[max_son];
        path[color[v]].pb(v);
    }
    return sz;
}

void add(int pos, int val) {
    pos += n;
    t[pos] += val;
    while (pos >>= 1) t[pos] = max(t[pos << 1], t[pos << 1 | 1]);
}

int get_max(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, t[l++]);
        if (r & 1) res = max(res, t[--r]);
    }
    return res;
}

int get(int a, int b) {
    int res = 0;
    while (color[a] != color[b]) {
        if (d[path[color[a]].back()] < d[path[color[b]].back()])
            swap(a, b);
        res = max(res, get_max(pos[a], pos[path[color[a]].back()] + 1));
        a = p[path[color[a]].back()];
    }
    if (pos[a] > pos[b])
        swap(a, b);
    res = max(res, get_max(pos[a], pos[b] + 1));
    return res;
}