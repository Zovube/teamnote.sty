// structure for maintaining Fenwick Tree
struct BIT {
	vll dataMul, dataAdd;
	int size, mxlog;
	
	// initialize BIT and calculate mxlog for binsearch
	void init(int nn) {
		mxlog = 0;
		while(two(mxlong) < nn) mxlog++;
		size = two(mxlog) + 1;
		dataMul.resize(size);
		dataAdd.resize(size);
	}
	
	// add linear function (mul * x + add) to [pos]
	void add(int pos, ll mul, ll add) {
		for(; pos < size; pos |= (pos + 1)) {
	 		dataMul[pos] += mul;
	 		dataAdd[pos] += add;
	 	}
	}
	
	// calculate sum on [0..pos]
	ll query(int pos) {
	 	ll mul = 0, add = 0, start = pos;
	 	for(; pos >= 0; pos = (pos & (pos + 1)) - 1) {
	 		mul += dataMul[pos];
	 		add += dataAdd[pos];
	 	}
	 	return mul * start + add;
	 }
	 
	 // add val to all elements on [l..r]
	 void add_range(int l, int r, ll val) {
	 	add(l, val, (l - 1) * -val);
	 	add(r, -val, r * val);
	 }
	 
	 // calculate sum on [l..r]
	 ll sum(int l, int r) {
	 	return query(r) - query(l - 1);
	 }
	 
	 // find k-th order statictic, almost binsearch
	 int kth(ll k) {
	 	int res = 0;
		for(int i = mxlog; i >= 0; i--) {
			if(dataAdd[res + two(i) - 1] < k) {
				k -= dataAdd[res + two(i) - 1];
				res += two(i);
			}
		}
		return res;	
	 }
	 	 
} bit;