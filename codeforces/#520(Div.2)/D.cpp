#include <bits/stdc++.h>
using namespace std;

int main() {
	int N; scanf("%d",&N);
	long long ans = 0;
	for (int i = 2; i < N; i++) {
		ans += i*(N/i-1);
	}
	ans *= 4LL;
	printf("%lld\n", ans);
}