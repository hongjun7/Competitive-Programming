#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2e5+5;

int N, Q, bn;
int A[MAXN];
LL S[4*MAXN]; int M[4*MAXN];

void upd(int p, int x) {
	p += bn;
	S[p] = M[p] = x;
	p /= 2;
	while (p >= 1) {
		S[p] = S[p*2] + S[p*2+1];
		M[p] = max(M[p*2], M[p*2+1]);
		p /= 2;
	}
}

LL sum(int s, int e) {
	LL ret = 0;
	s += bn; e += bn;
	while (s <= e) {
		if (s == e) {
			ret += S[s];
			break;
		}
		if (s&1) ret += S[s], s++;
		if (!(e&1)) ret += S[e], e--;
		s /= 2; e /= 2;
	}
	return ret;
}

int f(int x, int s, int e, int l, int r, int w) {
	if (e < l || r < s) return 0;
	if (s == e) return s;
	int m = (s+e)/2;
	int ret = 0;
	if (M[x*2] >= w) {
		ret = f(x*2, s, m, l, r, w);
		if (ret) return ret;
	}
	if (M[x*2+1] >= w) {
		ret = f(x*2+1, m+1, e, l, r, w);
		if (ret) return ret;
	}
	return ret;
}

int main() {
	scanf("%d%d",&N,&Q);
	bn = 1; while (bn < N) bn *= 2; bn--;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		S[bn+i] = M[bn+i] = A[i];
	}
	for (int i = bn; i >= 1; i--) {
		S[i] = S[i*2] + S[i*2+1];
		M[i] = max(M[i*2], M[i*2+1]);
	}
	for (int k = 1; k <= Q; k++) {
		int p, x; scanf("%d%d",&p,&x);
		upd(p, x);
		LL w = 0;
		bool ok = false;
		for (int i = 0; w <= M[1]; w = sum(1, i)) {
			int j = f(1, 1, bn+1, i+1, N, w);
			if (!j) break;
			i = j;
			if (sum(1, i-1) == S[bn+i]) {
				ok = true;
				printf("%d\n", i);
				break;
			}
		}
		if (!ok) puts("-1");
	}
}