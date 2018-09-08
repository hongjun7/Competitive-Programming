#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 1005;

double eps = 1e-12;

struct PT {
	double x, y;
	PT() {}
	PT(double x, double y) : x(x), y(y) {}
	PT(const PT &p) : x(p.x), y(p.y) {}
	PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y); }
	PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y); }
	PT operator * (double c)     const { return PT(x*c, y*c); }
	PT operator / (double c)     const { return PT(x / c, y / c); }
};
double dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }
// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
	return fabs(cross(b - a, c - d)) < eps;
}
bool LinesCollinear(PT a, PT b, PT c, PT d) {
	return LinesParallel(a, b, c, d)
		&& fabs(cross(a - b, a - c)) < eps
		&& fabs(cross(c - d, c - a)) < eps;
}
// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
	if (LinesCollinear(a, b, c, d)) {
		if (dist2(a, c) < eps || dist2(a, d) < eps ||
			dist2(b, c) < eps || dist2(b, d) < eps) return true;
		if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
			return false;
		return true;
	}
	if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
	if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
	return true;
}
// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
	b = b - a; d = c - d; c = c - a;
	assert(dot(b, b) > eps && dot(d, d) > eps);
	return a + b*cross(c, d) / cross(b, d);
}
int N;
struct SEG {
	PT s, e;
} L[MAXN];

LL gcd(LL x, LL y) {
	return y == 0 ? x : gcd(y, x%y);
}

LL ans;

int main() {
	scanf("%d",&N);
	for (int i = 0; i < N; i++) {
		int sx, sy, ex, ey;
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		L[i] = {{sx, sy}, {ex, ey}};
		LL dx = abs(ex-sx);
		LL dy = abs(ey-sy);
		LL g = gcd(dx, dy);
		ans += g+1;
	}
	set <pair<int,int>> total, v[1005];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (SegmentsIntersect(L[i].s, L[i].e, L[j].s, L[j].e)) {
				auto cur = ComputeLineIntersection(L[i].s, L[i].e, L[j].s, L[j].e);
				int cx = cur.x;
				int cy = cur.y;
				if (fabs(cur.x-cx) < eps && fabs(cur.y-cy) < eps) {
					total.insert({cx, cy});
					v[i].insert({cx, cy});
				}
			}
		}
		ans -= (int)v[i].size();
	}
	ans += (int)total.size();
	printf("%lld\n", ans);
}