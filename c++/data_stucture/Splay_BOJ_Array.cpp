#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct NODE {
	NODE *l, *r, *p;
	ll cnt, rev, g;
	ll min, max, sum, v;
	NODE(NODE *l, NODE *r, NODE *p, ll cnt, ll rev, ll min, ll max, ll sum, ll v) : 
	l(l), r(r), p(p), cnt(cnt), rev(rev), g(g), min(min), max(max), sum(sum), v(v) {}
} *root, *W[300005];
ll min(ll a, ll b) {
	if (a == 0) return b;
	if (b == 0) return a;
	if (a < b) return a;
	return b;
}
void upd(NODE *x) {
	x->sum = x->v + (x->l ? x->l->sum : 0) + (x->r ? x->r->sum : 0);
	x->min = min(x->v, min(x->l ? x->l->min : 0, x->r ? x->r->min : 0));
	x->max = max(x->v, max(x->r ? x->r->max : 0, x->l ? x->l->max : 0));
	x->cnt = 1 + (x->l ? x->l->cnt : 0) + (x->r ? x->r->cnt : 0);
}
void Lazy(NODE *x) {
	if (!x->rev) return;
	NODE *l = x->l;
	x->l = x->r;
	x->r = l;
	if (x->l)x->l->rev ^= 1;
	if (x->r)x->r->rev ^= 1;
	x->rev = 0;
}
void Rotate(NODE *x) {
	NODE *p, *b;
	p = x->p;
	if (p->l == x) {
		p->l = b = x->r;
		x->r = p;
	}
	else{
		p->r = b = x->l;
		x->l = p;
	}
	if (b)b->p = p;
	x->p = p->p;
	p->p = x;
	(x->p ? (x->p->l == p ? x->p->l : x->p->r) : root) = x;
	upd(p);
	upd(x);
}
void do_Lazy(NODE *x) {
	if (x->p)do_Lazy(x->p);
	Lazy(x);
}
void Splay(NODE *x) {
	do_Lazy(x);
	NODE *p, *g;
	while (x->p) {
		p = x->p;
		g = p->p;
		if (g)Rotate((p->l == x) == (g->l == p) ? p : x);
		Rotate(x);
	}
}
void find_Kth(ll k) {
	NODE *x = root;
	Lazy(x);
	while (1) {
		while (x->l&&x->l->cnt > k) {
			x = x->l;
			Lazy(x);
		}
		if (x->l)k -= x->l->cnt;
		if (k == 0)break;
		k--;
		x = x->r;
		Lazy(x);
	}
	Splay(x);
}
void init(ll n) {
	ll i;
	NODE *now = root = new NODE(NULL, NULL, NULL, n + 2, 0,0,0,0,0);
	for (i = 0; i < n+1; i++) {
		now->r = new NODE(NULL, NULL, now, n + 1 - i, 0,0,0,0,(i==n?0:i+1));
		now = now->r;
		W[i + 1] = now;
	}
	while (now) {
		upd(now);
		now = now->p;
	}
}
void interval(ll l, ll r) {
	find_Kth(l - 1);
	NODE *x = root;
	root = root->r;
	root->p = NULL;
	find_Kth(r - l + 1);
	root->p = x;
	x->r = root;
	root = x;
}
void rev(ll l, ll r) {
	interval(l, r);
	NODE *x = root->r->l;
	x->rev ^= 1;
	Lazy(x);
}
ll get_kth(NODE *x) {
	do_Lazy(x);
	Splay(x);
	Lazy(x);
	return x->l->cnt;
}
void do_interval(ll l, ll r) {
	interval(l, r);
	NODE *x = root->r->l;
	upd(x);
	printf("%lld %lld %lld\n", x->min, x->max, x->sum);
}
void go(NODE *x) {
	Lazy(x);
	if (x->l) go(x->l);
	if (x->v != 0) printf("%lld ", x->v);
	if (x->r) go(x->r);
}
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	init(n);
	for (int i = 0; i < q; i++) {
		int type;
		ll l, r, x, k, g;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%lld%lld", &l, &r);
			do_interval(l, r);
			rev(l, r);
			break;
		case 2:
			scanf("%lld%lld%lld", &l, &r, &x);
			do_interval(l, r);
			g = (r - l + 1);
			x %= g;
			if (x < 0) x += g;
			if (x != 0) {
				rev(l, r);
				rev(l, l + x - 1);
				rev(l + x, r);
			}
			break;
		case 3:
			scanf("%lld", &k);
			find_Kth(k);
			printf("%lld\n", root->v);
			break;
		case 4:
			scanf("%lld", &x);
			printf("%lld\n", get_kth(W[x]));
			break;
		}
	}
	go(root);
}