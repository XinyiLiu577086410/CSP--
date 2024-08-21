// #define DBG

#include <cstdio>
#include <iostream>
#include <stack>
#define int long long
#define OPERATOR 0LL
#define VARIABLE 1LL
#define CONSTANT 2LL
using namespace std;
constexpr int mod = 1e9 + 7;
int x[200] {};

struct node 
{	int type;
	int data;
	int l=0;
	int r=0;
	int f=0;
	int d=0;
	void backforward(int var);
} tree [200];

void node::backforward(int var) {
	if(type == CONSTANT) {
		f = data;
		d = 0;
	}
	else if(type == VARIABLE) {
		f = x[data];
		if( data == var ) {
			d = 1;
		}
		else {
			d = 0;
		}
	}
	else if(type == OPERATOR) {
		tree[l].backforward(var);
		tree[r].backforward(var);
		if(data == '+') {
			f = tree[l].f + tree[r].f;
			d = tree[l].d + tree[r].d;
		}
		else if(data == '-') {
			f = tree[l].f - tree[r].f;
			d = tree[l].d - tree[r].d;
		}
		else if(data == '*') {
			f = tree[l].f * tree[r].f;
			d = tree[l].d * tree[r].f + tree[l].f * tree[r].d;
		}
	}
}
int n, m;
int cur = 1;
char c;

#ifdef DBG
	void mtr(int k) {
		if(tree[k].l) mtr(tree[k].l);
		if(tree[k].type == OPERATOR) 
			printf("%c ", (char)tree[k].data);
		else if(tree[k].type == VARIABLE) 
			printf("x%lld ", tree[k].data);
		else if(tree[k].type == CONSTANT) 
			printf("%lld ", tree[k].data);
		if(tree[k].r) mtr(tree[k].r);
	}
#endif

signed main() {
	scanf( "%lld%lld", &n, &m ); 
	getchar();

	stack<int> mystk;
	while((c=getchar()) != '\n') {
		if(c == ' ') 
			continue;
		else if(c == 'x') { 
			/**
			 * 错在只读了一位数。
			 * 改正后由60提升至80
			 * 
			*/
			int sum = getchar() - '0';
			while ((c = getchar()) != ' ' && c != '\n') {
				sum *= 10;
				sum += c - '0';
			}
			tree[cur].type = VARIABLE;
			tree[cur].data = sum;
			mystk.push(cur);
			++cur;
			if(c == '\n')
				break;
		}
		else if(c == '+' || c == '*') {
			tree[cur].type = OPERATOR;
			tree[cur].data = c;
			tree[cur].r = mystk.top();
			mystk.pop();
			tree[cur].l = mystk.top();
			mystk.pop();
			mystk.push(cur);
			++cur;
		}
		else if(c == '-') {
			c = getchar();
			if(c == ' ') {
				tree[cur].type = OPERATOR;
				tree[cur].data = '-';
				tree[cur].r = mystk.top();
				mystk.pop();
				tree[cur].l = mystk.top();
				mystk.pop();
				mystk.push(cur);
				++cur;
			}
			else if(c == '\n') {
				tree[cur].type = OPERATOR;
				tree[cur].data = '-';
				tree[cur].r = mystk.top();
				mystk.pop();
				tree[cur].l = mystk.top();
				mystk.pop();
				mystk.push(cur);
				++cur;
				break;
			}
			else {
				int sum = c - '0';
				while ((c=getchar()) != ' ' && c != '\n') {
					sum *= 10;
					sum += c - '0';
				}
				
				tree[cur].type = CONSTANT;
				tree[cur].data = -1LL * sum;
				mystk.push(cur);
				++cur;
				if(c == '\n') 
					break;
			}
		}

		else {
			int sum = c - '0';
			while ((c=getchar()) != ' ' && c != '\n') {
				sum *= 10;
				sum += c - '0';
			}
			tree[cur].type = CONSTANT;
			tree[cur].data = sum;
			mystk.push(cur);
			++cur;
			if(c == '\n') 
				break;
		}
	}

	#ifdef DBG
		mtr(mystk.top());
	#endif

	int root = mystk.top();
	for( int i=0; i<m; ++i ) {
		int tar; 
		scanf("%lld", &tar);
		for( int j=0; j<n; ++j ) {
			scanf("%lld", &x[j+1]);
		}
		tree[root].backforward(tar);
		printf("%lld\n", (tree[root].d % mod + mod) % mod);
	}
}

/**
 * WA, 卡在第7个点上了。
 * 可恶。
 * 雷一会儿。 
 */