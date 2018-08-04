#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

const int MAXS = 1e6 + 5;

int n, P[MAXS];
char S[MAXS];
vector <int> v[MAXS], g[MAXS];
map <string, int> mp;
vector <string> st;
int chk[MAXS];
set <pair<int, int>> past;
int type[MAXS];
int decided[MAXS];
set <pair<int, int>> eq;

string ans;

int main() {
	st.push_back("");
	scanf("%s", S + 1);
	for (int i = 1; S[i]; i++) {
		if (S[i] == '!' || S[i] == '=') {
			string a = "", b = "";
			int at = 0, bt = 0;
			for (int j = i - 1; j >= 1; j--) {
				if (!('a' <= S[j] && S[j] <= 'z') &&
					!('0' <= S[j] && S[j] <= '9') && 
					!('A' <= S[j] && S[j] <= 'Z') &&
					S[j] != '-') break;
				if (('a' <= S[j] && S[j] <= 'z') || ('A' <= S[j] && S[j] <= 'Z'))
					at = 1;
				a += S[j];
			}
			reverse(a.begin(), a.end());
			for (int j = i + 2; S[j]; j++) {
				if (!('a' <= S[j] && S[j] <= 'z') &&
					!('0' <= S[j] && S[j] <= '9') &&
					!('A' <= S[j] && S[j] <= 'Z') &&
					S[j] != '-') break;
				if (('a' <= S[j] && S[j] <= 'z') || ('A' <= S[j] && S[j] <= 'Z'))
					bt = 1;
				b += S[j];
			}
			if (at || bt) {
				if (mp.find(a) == mp.end()) {
					mp[a] = ++n;
					st.push_back(a);
					P[n] = n;
					type[n] = at;
				}
				if (mp.find(b) == mp.end()) {
					mp[b] = ++n;
					st.push_back(b);
					P[n] = n;
					type[n] = bt;
				}
				int ax = mp[a], bx = mp[b];
				if (S[i] == '!') g[ax].push_back(bx), g[bx].push_back(ax);
				else v[ax].push_back(bx), v[bx].push_back(ax);
			}
			else {
				if (a != b && S[i] == '=') {
					puts("0==1");
					return 0;
				}
				if (a == b && S[i] == '!') {
					puts("0==1");
					return 0;
				}
			}
			i++;
		}
	}

	bool isfirst = 1;

	for (int i = 1; i <= n; i++) {
		if (!(chk[i] & 1)) {
			chk[i] |= 1;
			queue <int> qu; qu.push(i);
			vector <int> cur;
			int minlength = 1e9, minx = 0;
			while (!qu.empty()) {
				int x = qu.front(); qu.pop();
				cur.push_back(x);
				if (minlength > st[x].size()) {
					minlength = st[x].size();
					minx = x;
				}
				for (auto &y : v[x]) {
					if (!(chk[y] & 1)) {
						chk[y] |= 1;
						qu.push(y);
					}
				}
			}
			bool hasnumber = 0;
			for (auto &t : cur) {
				if (type[t] == 0) hasnumber = 1;
				if (t == minx) continue;
				if (!isfirst) ans += "&&";
				ans += st[minx];
				ans += "==";
				ans += st[t];
				P[t] = minx;
				isfirst = 0;
			}
			if (hasnumber) {
				for (auto &t : cur) {
					decided[t] = 1;
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (auto &t : g[i]) {
			t = P[t];
		}
		sort(g[i].begin(), g[i].end());
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
		for (auto &j : g[i]) {
			if (P[i] == j) {
				puts("0==1");
				return 0;
			}
			if (P[i] > j) continue;
			if (decided[P[i]] && decided[j]) continue;
			if (past.count({ P[i], j }) || past.count({ j, P[i] })) continue;
			past.insert({ P[i], j });
			if (!isfirst) ans += "&&";
			ans += st[P[i]];
			ans += "!=";
			ans += st[j];
			isfirst = 0;
		}
	}
	if (ans.size() == 0) ans = "0==0";
	puts(ans.c_str());
}