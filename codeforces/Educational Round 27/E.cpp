#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int N, M, K;
struct PT { int x, y; } P[MAXN];

int D[MAXN*4][MAXN*4];

bool ok(int L) {
	vector <int> X, Y;
	for (int i = 1; i <= K; i++) {
		int sx = max(1, P[i].x - L), ex = min(N, P[i].x + L);
		int sy = max(1, P[i].y - L), ey = min(M, P[i].y + L);
		X.push_back(sx); X.push_back(ex); X.push_back(sx-1); X.push_back(ex+1);
		Y.push_back(sy); Y.push_back(ey); Y.push_back(sy-1); Y.push_back(ey+1);
	}
	X.push_back(0); X.push_back(1); X.push_back(N); X.push_back(N+1);
	Y.push_back(0); Y.push_back(1); Y.push_back(M); Y.push_back(M+1);
	sort(X.begin(), X.end()); X.erase(unique(X.begin(), X.end()), X.end());
	sort(Y.begin(), Y.end()); Y.erase(unique(Y.begin(), Y.end()), Y.end());
	for (int i = 1; i <= K; i++) {
		int sx = max(1, P[i].x - L), ex = min(N, P[i].x + L);
		int sy = max(1, P[i].y - L), ey = min(M, P[i].y + L);
		sx = (lower_bound(X.begin(), X.end(), sx) - X.begin());
		ex = (lower_bound(X.begin(), X.end(), ex) - X.begin());
		sy = (lower_bound(Y.begin(), Y.end(), sy) - Y.begin());
		ey = (lower_bound(Y.begin(), Y.end(), ey) - Y.begin());
		D[sx][sy]++;
		D[ex+1][sy]--; D[sx][ey+1]--;
		D[ex+1][ey+1]++;
	}
	int XN = X.size()-2, YN = Y.size()-2;
	int sx = 0, sy = 0, ex = 0, ey = 0;
	for (int i = 1; i <= XN; i++) {
		for (int j = 1; j <= YN; j++) {
			D[i][j] += D[i-1][j] + D[i][j-1] - D[i-1][j-1];
			if (D[i][j] == 0) {
				if (sx == 0 || sx > i) sx = i;
				if (ex == 0 || ex < i) ex = i;
				if (sy == 0 || sy > j) sy = j;
				if (ey == 0 || ey < j) ey = j;
			}
		}
	}
	for (int i = 0; i <= XN+2; i++) for (int j = 0; j <= YN+2; j++) D[i][j] = 0;
	return max(X[ex] - X[sx], Y[ey] - Y[sy]) <= 2*L;
}

int main() {
	scanf("%d%d%d",&N,&M,&K);
	for (int i = 1; i <= K; i++) {
		scanf("%d%d",&P[i].x,&P[i].y);
	}
	int s = 0, e = max(N, M), ans = 1e9;
	while (s <= e) {
		int m = (s+e)/2;
		if (ok(m)) e = m-1, ans = m;
		else s = m+1;
	}
	printf("%d\n", ans);
	return 0;
}