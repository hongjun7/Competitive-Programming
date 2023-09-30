typedef long long ll;

const int MAXN = 1e5+5;

class RangeSumBIT {
public:
	ll BIT[2][MAXN];
	//add value v to index p
	void Upd(int r, int p, ll v) { for (; p <= N; p+=p&(-p)) BIT[r][p]+=v; }
	//add value v to range [L, R]
	void RangeUpd(int L, int R, ll v) {
		Upd(0, L, v); Upd(0, R+1, -v);
		Upd(1, L, v*(ll)(L-1)); Upd(1, R+1, -v*(ll)(R));
	}
	ll SumQuery(int r, int p) {
		ll sum = 0;
		for (; p > 0; p-=p&(-p)) sum += BIT[r][p];
		return sum;
	}
	//return the sum of range [1, p]
	ll SumAll(int p) { return SumQuery(0, p)*(ll)p - SumQuery(1, p); }
	//return the sum of range [L, R]
	ll RangeSum(int L, int R) { return SumAll(R)-SumAll(L-1); }
};