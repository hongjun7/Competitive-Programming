#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 5e5+5;

int N;
int A[MAXN];
LL pos, neg;

int main() {
	scanf("%d",&N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		if (A[i] > 0) pos += A[i];
		if (A[i] < 0) neg += A[i];
	}
	LL ans = -1e18;
	if (N == 1) {
		ans = A[0];
	} else {
		for (int i = 0; i < N; i++) {
			LL curMax;
			if (A[i] > 0) curMax = (pos - A[i]) - neg;
			else curMax = pos - (neg - A[i]);
			if (pos != 0) ans = max({ans, -A[i] + curMax});
			else ans = max({ans, A[i] + curMax});
		}
	}
	printf("%lld\n", ans);
}