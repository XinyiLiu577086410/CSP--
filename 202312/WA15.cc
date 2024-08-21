/*WA, 15*/
#include <cstdio>
#include <deque>
#include <stack>
#include <math.h>
#include <algorithm>

#pragma GCC optimize(2,3,"Ofast", "inline")
#define int long long 
int mod  = 998244353;
struct mat
{
	int data[2][2];
	mat operator * ( const mat & b ) const {
		mat ret;
		ret.data[0][0] = (data[0][0] * b.data[0][0] + data[0][1] * b.data[1][0])%mod;
		ret.data[0][1] = (data[0][0] * b.data[0][1] + data[0][1] * b.data[1][1])%mod;
		ret.data[1][0] = (data[1][0] * b.data[0][0] + data[1][1] * b.data[1][0])%mod;
		ret.data[1][1] = (data[1][0] * b.data[0][1] + data[1][1] * b.data[1][1])%mod;
		return ret;
	}
	void print() {
		printf("%lld %lld %lld %lld\n", data[0][0], data[0][1], data[1][0], data[1][1]);
	}
	void read() {
		scanf("%lld%lld%lld%lld", &data[0][0], &data[0][1], &data[1][0], &data[1][1]);
	}
};

struct instrction
{
	int type;
	mat data;
	void read() {
		scanf("%lld", &type);
		if ( type == 1 || type == 2 )
			data.read();
	} 
} ins[100010];


struct block
{
	// mat lsum, rsum;
	std::vector<mat> lpresum, rpresum;
	std::vector<int> lcnt, rcnt;
	int n3=0;
	int n12=0;
	void make(int l, int r);
};

void cal(int l, int r, block & ret, int N3) {
	std::vector<mat> lmats, rmats;
	std::vector<char> op;
	int n3 = 0;
	for(int i=l; i<=r; ++i) {
		instrction & inst = ins[i];
		if(inst.type == 1) {
			op.push_back('l');
			lmats.push_back(inst.data);
		}
		else if(inst.type == 2) {
			op.push_back('r');
			rmats.push_back(inst.data);
		}
		else if(inst.type == 3) {
			if(!op.empty()) {
				char c = op.back();
				op.pop_back();
				if(c == 'l') {
					lmats.pop_back();
				}
				else if(c == 'r') {
					rmats.pop_back();
				}
			}
			else n3++;
		}
	}
	ret.lcnt.push_back(0);
	ret.rcnt.push_back(0);
	for(auto p : op) {
		switch (p)
		{
		case 'l':
			ret.lcnt.push_back(ret.lcnt.back() + 1);
			ret.rcnt.push_back(ret.rcnt.back() + 0);
			break;
		case 'r':
			ret.lcnt.push_back(ret.lcnt.back() + 0);
			ret.rcnt.push_back(ret.rcnt.back() + 1);
			break;		
		default:
			break;
		}	
	}

	for(int i=0; i<N3; ++i) {
		if(!op.empty()) {
			char c = op.back();
			op.pop_back();
			if(c == 'l') {
				lmats.pop_back();
			}
			else if(c == 'r') {
				rmats.pop_back();
			}
		}
		else n3++;
	}

	int n12 = lmats.size() + rmats.size();
	mat lsum {1,0,0,1};
	ret.lpresum.push_back(lsum);
	for(auto const & p : lmats){
		lsum = p * lsum;
		ret.lpresum.push_back(lsum);
	}

	mat rsum {1,0,0,1};
	ret.rpresum.push_back(rsum);
	for(auto const & p : rmats) {
		rsum = rsum * p;
		ret.rpresum.push_back(rsum);
	}

	// ret.lsum = lsum;
	// ret.rsum = rsum;
	// ret.lmat = (std::vector<mat> &&) lmats;
	// ret.rmat = (std::vector<mat> &&) rmats;
	ret.n12 = n12;
	ret.n3 = n3;
}

void block::make(int l, int r) {
	cal(l, r, *this, 0);
}

block blks[1000]; 

signed main() {
	int n, m, type;
	scanf("%lld%lld", &n, &m);
	for( int i=1; i<=n; ++i ) {
		ins[i].read();
	}
	int rtn = std::max((int)sqrt(n), 20ll);
	for( int i=0; i*rtn<n; ++i ) {
		blks[i].make(i*rtn, std::min(i*rtn+rtn-1, n));
	}
	for( int i=0; i<m; ++i ) {
		scanf("%lld", &type);
		if(type == 2) {
			int l, r;
			scanf("%lld%lld", &l, &r);
			if(l/rtn == r/rtn) {
				block b;
				cal(l, r, b, 0);
				(b.lpresum.back() * b.rpresum.back()).print();
			}
			else {
				block b1, b3;
				cal(r/rtn*rtn, r, b3, 0);
				int N3 = b3.n3;
				std::vector<mat> rmats, lmats;
				for( int i=r/rtn-1; i>l/rtn; --i ) {
					if(N3 == 0) {
						lmats.push_back(blks[i].lpresum.back());
						rmats.push_back(blks[i].rpresum.back());
					}
					else if(N3 >= blks[i].n12) {
						;
					}
					else {
						block b;
						// cal(i*rtn, (i+1)*rtn-1, b, N3);
						lmats.push_back(b.lpresum[b.lcnt[blks[i].n12 - N3]]);
						rmats.push_back(b.rpresum[b.rcnt[blks[i].n12 - N3]]);
					}
					N3 = std::max(0LL, N3 - blks[i].n12) + blks[i].n3;
				}
				cal(l, std::min(l/rtn*rtn+rtn-1, n), b1, N3);
				mat lsum {1,0,0,1}, rsum {1,0,0,1};
				for(auto & p : lmats) {
					lsum = lsum * p;
				}
				for(auto & p : rmats) {
					rsum = p * rsum;
				}
				(b3.lpresum.back() * lsum * b1.lpresum.back() * b1.rpresum.back() * rsum * b3.rpresum.back()).print();

			}
		}
		else {
			int i;
			scanf("%lld", &i);
			ins[i].read();
			blks[i/rtn].make(i/rtn*rtn, std::min((i/rtn+1)*rtn-1, n));
		}
	}
}
/**
 * 也是一个点都不过，挂零。改成long long后35分。
 * 今天先把题解实现一下。
 * 构思的时候想不通怎么加速没关系， 先把算法整出来
 * 20240211: 原来错在几个边界的地方，分块的逻辑修好了
 * 带3型指令的点TLE
 * 
*/