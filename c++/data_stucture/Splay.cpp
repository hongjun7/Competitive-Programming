#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct NODE {
	NODE *l, *r, *p;
	ll cnt, value, sum, lazy;
	NODE(NODE *l, NODE *r, NODE *p, ll cnt, ll value, ll sum, ll lazy) : 
	l(l), r(r), p(p), cnt(cnt), value(value), sum(sum), lazy(lazy) {}
} *root;
void Update(NODE *x){
	x->cnt = 1;
	x->sum = x->value;
	if (x->l){
		x->cnt += x->l->cnt;
		x->sum += x->l->sum;
	}
	if (x->r){
		x->cnt += x->r->cnt;
		x->sum += x->r->sum;
	}
}
void Lazy(NODE *x){
	x->value += x->lazy;
	if (x->l){
		x->l->lazy += x->lazy;
		x->l->sum += x->l->cnt*x->lazy;
	}
	if (x->r){
		x->r->lazy += x->lazy;
		x->r->sum += x->r->cnt*x->lazy;
	}
	x->lazy = 0;
}
void Rotate(NODE *x){
	NODE *p=x->p, *b;
	if (p->l == x){
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
	(x->p ? ((x->p->l == p) ? x->p->l : x->p->r) : root) = x;
	Update(p);
	Update(x);
}
void Splay(NODE *x){
	NODE *p, *g;
	while (x->p){
		p = x->p;
		g = p->p;
		if (g)Rotate(((p->l == x) == (g->l == p)) ? p : x);
		Rotate(x);
	}
}
void find_kth(int k){
	NODE *now = root;
	Lazy(now);
	while (1) {
		while (now->l&&now->l->cnt > k){
			now = now->l;
			Lazy(now);
		}
		if (now->l)k -= now->l->cnt;
		if (k == 0) break;
		k--;
		now = now->r;
		Lazy(now);
	}
	Splay(now);
}
void init(int n){
	NODE *x;
	x = root = new NODE(NULL, NULL, NULL, n + 2, 0, 0, 0);
	for (int i = 0; i < n + 1; i++){
		x->r = new NODE(NULL, NULL, x, n + 1 - i, 0, 0, 0);
		x = x->r;
	}
}
void Interval(int l, int r){
	NODE *x;
	find_kth(l - 1);
	x = root;
	root = root->r;
	root->p = NULL;
	find_kth(r - l + 1);
	root->p = x;
	x->r = root;
	root = x;
}
void insert_g(int l, int r, ll g){
	Interval(l, r);
	NODE *x = root->r->l;
	x->lazy += g;
	x->sum += x->cnt*g;
}
ll get_sum(ll l, ll r){
	Interval(l, r);
	return root->r->l->sum;
}
ll S[1000005];
int main(){
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++){
		int x; scanf("%d", &x);
		S[i] = S[i - 1] + x;
	}
	init(n);
	for (int i = 0; i < m + k; i++){
		int type, s, e; ll g;
		scanf("%d%d%d", &type, &s, &e);
		if (type == 1) {
			scanf("%lld", &g);
			insert_g(s, e, g);
		}
		else printf("%lld\n", S[e]-S[s-1] + get_sum(s, e));
	}
}