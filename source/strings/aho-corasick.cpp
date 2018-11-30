struct Node {
	int go[MAXN], link, term;
	Node() { memset(go, 0, sizeof(go)), term = link = 0; }
};

vector < Node > bb;

void add_string(string s) {
	int v = 0;
	for (auto cs : s) {
		int c = c_id[cs];
		if (!bb[v].go[c]) {
			bb[v].go[c] = (int)bb.size();
			bb.pb(Node());
		}
		v = bb[v].go[c];
	}
	bb[v].term = 1;
}

void push_links() {
	queue < int > qq;
	qq.push(0);
	while (!qq.empty()) {
		int v = qq.front();
		int u = bb[v].link;
		qq.pop();
		if (!bb[v].term)
			bb[v].term = bb[u].term;
		for (int c = 0; c < N; c++) {
			int &to = bb[v].go[c];
			if (to) {
				bb[to].link = v ? bb[u].go[c] : 0;
				qq.push(to);
			} else
				to = bb[u].go[c];
		}
	}
}

void build_all() {
	bb.resize(1);
	for (auto word : dictionary)
		add_string(word);
	push_links();
}