/*WA, 35, 30*/
#pragma GCC optimize(2,3,"Ofast", "inline")
#include <cstdio>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>

#define int long long 
int mod  = 998244353;
constexpr int M = 1e5 + 10;
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
	bool operator== (mat & b) {
		return data[0][0] == b.data[0][0] && data[0][1] == b.data[0][1] \
				&& data[1][0] == b.data[1][0] && data[1][1] == b.data[1][1];
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
	mat lsum, rsum;
	std::vector<mat> lpresum, rpresum;
	std::vector<int> lcnt, rcnt;
	// mat lpresum[M], rpresum[M];
	// int lcnt[M], rcnt[M];

	int n3=0;
	int n12=0;
	void make(int l, int r);
	void clean() {
		lpresum.clear();
		rpresum.clear();
		lcnt.clear();
		rcnt.clear();
	}
};

inline void cal(int l, int r, block & ret) {
	std::vector<int> lmatsref, rmatsref;
	std::vector<char> op;
	int n3 = 0;
	for(int i=l; i<=r; ++i) {
		instrction & inst = ins[i];
		if(inst.type == 1) {
			op.push_back('l');
			lmatsref.push_back(i);
		}
		else if(inst.type == 2) {
			op.push_back('r');
			rmatsref.push_back(i);
		}
		else if(inst.type == 3) {
			if(!op.empty()) {
				char c = op.back();
				op.pop_back();
				if(c == 'l') {
					lmatsref.pop_back();
				}
				else if(c == 'r') {
					rmatsref.pop_back();
				}
			}
			else n3++;
		}
	}
	ret.clean();
	/**
	 * After adding this,
	 * WA, 35 -> TLE, 75
	 * Remember to clean!
	*/
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

	mat lsum {1,0,0,1};
	ret.lpresum.emplace_back(lsum);
	for(auto const & p : lmatsref){
		// lsum = ins[p].data * lsum;
		ret.lpresum.emplace_back(ins[p].data * ret.lpresum.back());
	}

	mat rsum {1,0,0,1};
	ret.rpresum.emplace_back(rsum);
	for(auto const & p : rmatsref) {
		// rsum = rsum * ins[p].data;
		ret.rpresum.emplace_back(ret.rpresum.back() * ins[p].data);
	}

	ret.n12 = op.size();
	ret.n3 = n3;
	// if(ret.n12 != op.size())
		// throw 1;
}

void block::make(int l, int r) {
	cal(l, r, *this);
}

block blks[1000]; 

signed main() {
	int n, m, type;
	scanf("%lld%lld", &n, &m);
	for( int i=1; i<=n; ++i ) {
		ins[i].read();
	}
	int blksz = std::max((int)sqrt(n), 0LL);
	for( int i=0; i*blksz+1<=n; ++i ) {
		blks[i].make(i*blksz+1, std::min(i*blksz+1+blksz-1, n));
	}
	for( int i=0; i<m; ++i ) {
		scanf("%lld", &type);
		if(type == 2) {
			int l, r;
			scanf("%lld%lld", &l, &r);
			if((l-1)/blksz == (r-1)/blksz) {
				block b;
				cal(l, r, b);
				(b.lpresum.back() * b.rpresum.back()).print();
			}
			else {
				block b1, b3;
				cal((r-1)/blksz*blksz+1, r, b3);
				int N3 = b3.n3;
				std::vector<mat> rmats, lmats;
				for( int i=(r-1)/blksz-1; i>(l-1)/blksz; --i ) {
					block & b = blks[i];
					// if(N3 == 0) {
					// 	lmats.push_back(b.lpresum[b.lcnt[b.n12]]);
					// 	rmats.push_back(b.rpresum[b.rcnt[b.n12]]);
					// 	// lmats.push_back(b.lpresum.back());
					// 	// rmats.push_back(b.rpresum.back());
					// 	#ifdef DBG
					// 	if (!(b.lpresum.back() == b.lpresum[b.lcnt[b.n12]])) {
					// 		throw "wrong";
					// 	}
					// 	#endif
					// }
					// else
					if(N3 >= b.n12) {
						;
					}
					else {
						// cal(i*blksz, (i+1)*blksz-1, b, N3);
						auto how_many = b.n12 - N3;
						lmats.emplace_back(b.lpresum[b.lcnt[how_many]]);
						rmats.emplace_back(b.rpresum[b.rcnt[how_many]]);
					}
					N3 = std::max(0LL, N3 - b.n12) + b.n3;
				}
				cal(l, std::min((l-1)/blksz*blksz+blksz, n), b1);
				mat lsum {1,0,0,1}, rsum {1,0,0,1};
				for(auto p : lmats) {
					lsum = lsum * p;
				}
				for(auto p : rmats) {
					rsum = p * rsum;
				}
				(b3.lpresum.back() * lsum * b1.lpresum[ b1.lcnt[std::max(0LL, b1.n12-N3)] ] \
				* b1.rpresum[ b1.rcnt[std::max(0LL, b1.n12-N3)] ] * rsum * b3.rpresum.back())\
				.print();

			}
		}
		else {
			int i;
			scanf("%lld", &i);
			ins[i].read();
			blks[(i-1)/blksz].make(((i-1)/blksz)*blksz+1, std::min(((i-1)/blksz)*blksz+1+blksz-1, n));
		}
	}
}
/**
 * 也是一个点都不过，挂零。改成long long后35分。
 * 今天先把题解实现一下。
 * 构思的时候想不通怎么加速没关系， 先把算法整出来
 * 20240211: 原来错在几个边界的地方，分块的逻辑修好了
 * 
*/