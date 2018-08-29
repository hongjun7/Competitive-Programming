#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int N, M, Q;

struct PT {
	int i, j;
};

struct CELL {
	int v;
	PT R, D;
} A[MAXN][MAXN];


int main() {
	scanf("%d%d%d",&N,&M,&Q);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d",&A[i][j].v);
		}
	}
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			A[i][j].R = {i, j+1};
			A[i][j].D = {i+1, j};
		}
	}
	for (int q = 1; q <= Q; q++) {
		int a, b, c, d, h, w; scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&h,&w);
		vector <PT> u1, u2, l1, l2, r1, r2, d1, d2;
		{
			for (int i = A[a-1][0].R.i, j = A[a-1][0].R.j, cur = 1; cur <= b+w-1; tie(i, j) = make_tuple(A[i][j].R.i, A[i][j].R.j), cur++) {
				if (b <= cur && cur <= b+w-1) u1.push_back({i, j});
			}
		} {
			for (int i = A[c-1][0].R.i, j = A[c-1][0].R.j, cur = 1; cur <= d+w-1; tie(i, j) = make_tuple(A[i][j].R.i, A[i][j].R.j), cur++) {
				if (d <= cur && cur <= d+w-1) u2.push_back({i, j});
			}
		}
		{
			for (int i = A[a+h-1][0].R.i, j = A[a+h-1][0].R.j, cur = 1; cur <= b+w-1; tie(i, j) = make_tuple(A[i][j].R.i, A[i][j].R.j), cur++) {
				if (b <= cur && cur <= b+w-1) d1.push_back({i, j});
			}
		} {
			for (int i = A[c+h-1][0].R.i, j = A[c+h-1][0].R.j, cur = 1; cur <= d+w-1; tie(i, j) = make_tuple(A[i][j].R.i, A[i][j].R.j), cur++) {
				if (d <= cur && cur <= d+w-1) d2.push_back({i, j});
			}
		}
		{
			for (int i = A[0][b-1].D.i, j = A[0][b-1].D.j, cur = 1; cur <= a+h-1; tie(i, j) = make_tuple(A[i][j].D.i, A[i][j].D.j), cur++) {
				if (a <= cur && cur <= a+h-1) l1.push_back({i, j});
			}
		} {
			for (int i = A[0][d-1].D.i, j = A[0][d-1].D.j, cur = 1; cur <= c+h-1; tie(i, j) = make_tuple(A[i][j].D.i, A[i][j].D.j), cur++) {
				if (c <= cur && cur <= c+h-1) l2.push_back({i, j});
			}
		}
		{
			for (int i = A[0][b+w-1].D.i, j = A[0][b+w-1].D.j, cur = 1; cur <= a+h-1; tie(i, j) = make_tuple(A[i][j].D.i, A[i][j].D.j), cur++) {
				if (a <= cur && cur <= a+h-1) r1.push_back({i, j});
			}
		} {
			for (int i = A[0][d+w-1].D.i, j = A[0][d+w-1].D.j, cur = 1; cur <= c+h-1; tie(i, j) = make_tuple(A[i][j].D.i, A[i][j].D.j), cur++) {
				if (c <= cur && cur <= c+h-1) r2.push_back({i, j});
			}
		}
		for (int i = 0; i < w; i++) {
			{
				auto t1 = u1[i], t2 = u2[i];
				swap(A[t1.i][t1.j].D, A[t2.i][t2.j].D);
			} {
				auto t1 = d1[i], t2 = d2[i];
				swap(A[t1.i][t1.j].D, A[t2.i][t2.j].D);
			}
		}
		for (int i = 0; i < h; i++) {
			{
				auto t1 = l1[i], t2 = l2[i];
				swap(A[t1.i][t1.j].R, A[t2.i][t2.j].R);
			} {
				auto t1 = r1[i], t2 = r2[i];
				swap(A[t1.i][t1.j].R, A[t2.i][t2.j].R);
			}
		}
	}
	for (int r = 1; r <= N; r++) {
		for (int i = A[r][0].R.i, j = A[r][0].R.j, k = 1; k <= M; tie(i, j) = make_tuple(A[i][j].R.i, A[i][j].R.j), k++) {
			printf("%d ", A[i][j].v);
		}
		puts("");
	}
}