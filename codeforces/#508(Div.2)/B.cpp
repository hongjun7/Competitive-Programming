#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
	scanf("%d",&N);
	if (N <= 2) puts("No");
	else {
		int total = N*(N+1)/2;
		int subtract = 0;
		if (N%2 == 0) subtract = N/2;
		else subtract = N/2+1;
		puts("Yes");
		printf("1 %d\n", subtract);
		printf("%d", N-1);
		for (int i = 1; i <= N; i++) {
			if (i == subtract) continue;
			printf(" %d", i);
		}
		puts("");
	}
}