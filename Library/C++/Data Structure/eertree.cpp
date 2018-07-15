const int MAXN = 100005;

struct NODE {
	int nxt[26];    //26 = # of alphabet
	int L, link;
} tree[MAXN];

int L;
char s[MAXN];
int num;        	// node 1 - root with L -1, node 2 - root with L 0
int suff; 	        // max suffix palindrome

bool addLetter(int pos) {
	int cur = suff, curL = 0;
	int let = s[pos] - 'a';

	while (true) {
		curL = tree[cur].L;
		if (pos - 1 - curL >= 0 && s[pos - 1 - curL] == s[pos]) break;	
		cur = tree[cur].link;
	}		
	if (tree[cur].nxt[let]) {	
		suff = tree[cur].nxt[let];
		return false;
	}

	num++;
	suff = num;
	tree[num].L = tree[cur].L + 2;
	tree[cur].nxt[let] = num;

	if (tree[num].L == 1) {
		tree[num].link = 2;
		return true;
	}

	while (true) {
		cur = tree[cur].link;
		curL = tree[cur].L;
		if (pos - 1 - curL >= 0 && s[pos - 1 - curL] == s[pos]) {
			tree[num].link = tree[cur].nxt[let];
			break;
		}    	
	}
	return true;
}

void initTree() {
	num = 2; suff = 2;
	tree[1].L = -1; tree[1].link = 1;
	tree[2].L = 0; tree[2].link = 1;
}

int solve() {
	scanf("%s\n", &s[0]);
	L = strL(s);
	initTree();
	for (int i = 0; i < L; i++) {
		addLetter(i);
	}
	return 0;
}