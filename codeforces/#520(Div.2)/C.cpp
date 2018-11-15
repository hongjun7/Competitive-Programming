#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;
const int MAXN = 1e5+5;

int N, Q;
char S[MAXN];
int one[MAXN];

typedef long long ll;

ll pw(ll a, ll p) {
	if (p == 0) return 1;
	if (p == 1) return a;
	ll t = pw(a, p/2);
	t = (t*t) % mod;
	if (p&1) t = (t*a) % mod;
	return t;
}

int main() {
	scanf("%d%d",&N,&Q);
	scanf("%s", S+1);
	for (int i = 1; i <= N; i++) {
		one[i] = one[i-1] + (S[i]=='1');
	}
	for (int i = 1; i <= Q; i++) {
		int l, r; scanf("%d%d",&l,&r);
		int o = one[r] - one[l-1];
		int z = (r-l+1) - o;
		ll ans = pw(2LL, z);
		ans = (ans * (pw(2LL, o)-1)) % mod;
		printf("%lld\n", ans);
	}
}