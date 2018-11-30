const int ALF = 27;

struct Node {
  int len, suff_link, to[ALF];
  vi to_suff;
  ll cnt;
  Node() {
    len = 0, suff_link = 0;
    memset(to, 0, sizeof(to));
    cnt = 0;
  }
};

struct Tree {
  int len, suff, w;
  vector < Node > t;
  string s;

  void init(string _s) {
    t.resize(3);
    w = 2, suff = 2;
    t[1].len = -1;
    t[1].suff_link = 1;
    t[2].len = 0;
    t[2].suff_link = 1;
    s = _s;
    for (int i = 0; i < (int)s.size(); i++)
      add_letter(i);
  }

  bool add_letter(int pos) {
    int cur = suff, cur_len = 0;
    int c = s[pos] - 'A';
    while (true) {
      cur_len = t[cur].len;
      if (pos - 1 - cur_len >= 0 && s[pos - 1 - cur_len] == s[pos])
        break;
      cur = t[cur].suff_link;
    }
    if (t[cur].to[c]) {
      suff = t[cur].to[c];
      t[suff].cnt++;
      return false;
    }
    t.pb(Node());
    w++;
    suff = w;
    t[w].len = t[cur].len + 2;
    t[cur].to[c] = w;
    t[w].cnt = 1;
    if (t[w].len == 1) {
      t[w].suff_link = 2;
      t[2].to_suff.pb(w);
      return true;
    }
    while (true) {
      cur = t[cur].suff_link;
      cur_len = t[cur].len;
      if (pos - 1 - cur_len >= 0 && s[pos - 1 - cur_len] == s[pos]) {
        t[w].suff_link = t[cur].to[c];
        t[t[cur].to[c]].to_suff.pb(w);
        break;
      }
    }
    return true;
  }
};