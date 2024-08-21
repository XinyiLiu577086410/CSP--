/*WA, 35, 30*/
#pragma GCC optimize(2,3,"Ofast", "inline")
#include <cstdio>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>
#define ARROPT
#define int long long 
int mod  = 998244353;
constexpr int M = 320;
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
	#ifndef ARROPT
	std::vector<mat> lpresum, rpresum;
	std::vector<int> lcnt, rcnt;
	#else
	mat lpresum[M], rpresum[M];
	int lcnt[M], rcnt[M];
	int cur_lcnt = 0, cur_rcnt = 0, cur_lpresum = 0, cur_rpresum = 0;
	#endif

	int n3=0;
	int n12=0;

	void make(int l, int r);
	void clean() {
		#ifndef ARROPT
		lpresum.clear();
		rpresum.clear();
		lcnt.clear();
		rcnt.clear();
		#else
		cur_lcnt = 0;
		cur_rcnt = 0;
		cur_lpresum = 0;
		cur_rpresum = 0;
		#endif
	}
// private:
};

#ifdef ARROPT
int lmatref[M], rmatref[M];
char op[M];
int cur_lmatref = 0, cur_rmatref = 0, cur_op = 0;
#endif

inline void cal(int l, int r, block & ret) {
	#ifndef ARROPT
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
	#else
	cur_lmatref = 0;
	cur_rmatref = 0;
	cur_op = 0;
	int n3 = 0;
	for(int i=l; i<=r; ++i) {
		instrction & inst = ins[i];
		if(inst.type == 1) {
			op[cur_op++] = 'l';
			lmatref[cur_lmatref++] = i;
		}
		else if(inst.type == 2) {
			op[cur_op++] = 'r';
			rmatref[cur_rmatref++] = i;
		}
		else if(inst.type == 3) {
			if(cur_op > 0) {
				char c = op[cur_op-1];
				cur_op--;
				if(c == 'l') {
					cur_lmatref--;
				}
				else if(c == 'r') {
					cur_rmatref--;
				}
			}
			else n3++;
		}
	}
	#endif

	ret.clean();

	/**
	 * After adding this,
	 * WA, 35 -> TLE, 75
	 * Remember to clean!
	*/

	#ifndef ARROPT
	ret.lcnt.push_back(0);
	ret.rcnt.push_back(0);
	#else
	ret.lcnt[ret.cur_lcnt++] = 0;
	ret.rcnt[ret.cur_rcnt++] = 0;
	#endif
	#ifndef ARROPT
	for(auto p : op) {
		switch (p)
		{
		case 'l':
			#ifndef ARROPT
			ret.lcnt.push_back(ret.lcnt.back() + 1);
			ret.rcnt.push_back(ret.rcnt.back() + 0);
			#else
			ret.lcnt[ret.cur_lcnt] = (ret.lcnt[ret.cur_lcnt-1] + 1);
			ret.rcnt[ret.cur_rcnt] = (ret.rcnt[ret.cur_rcnt-1] + 0);
			ret.cur_lcnt++;
			ret.cur_rcnt++;
			#endif

			break;
		case 'r':
			#ifndef ARROPT
			ret.lcnt.push_back(ret.lcnt.back() + 0);
			ret.rcnt.push_back(ret.rcnt.back() + 1);
			#else
			ret.lcnt[ret.cur_lcnt] = (ret.lcnt[ret.cur_lcnt-1] + 0);
			ret.rcnt[ret.cur_rcnt] = (ret.rcnt[ret.cur_rcnt-1] + 1);
			ret.cur_lcnt++;
			ret.cur_rcnt++;
			#endif

			break;		
		default:
			break;
		}	
	}
	#else
	for(int i=0; i<cur_op; ++i) {
		switch (op[i])
		{
		case 'l':
			ret.lcnt[ret.cur_lcnt] = (ret.lcnt[ret.cur_lcnt-1] + 1);
			ret.rcnt[ret.cur_rcnt] = (ret.rcnt[ret.cur_rcnt-1] + 0);
			ret.cur_lcnt++;
			ret.cur_rcnt++;
			break;
		case 'r':
			ret.lcnt[ret.cur_lcnt] = (ret.lcnt[ret.cur_lcnt-1] + 0);
			ret.rcnt[ret.cur_rcnt] = (ret.rcnt[ret.cur_rcnt-1] + 1);
			ret.cur_lcnt++;
			ret.cur_rcnt++;
			break;		
		default:
			break;
		}	
	}
	#endif

	mat lsum {1,0,0,1};

	#ifndef ARROPT
	ret.lpresum.emplace_back(lsum);
	#else
	ret.lpresum[ret.cur_lpresum++] = mat {1, 0, 0, 1};
	#endif
	
	#ifndef ARROPT
	for(auto const & p : lmatsref){
		// lsum = ins[p].data * lsum;

		#ifndef ARROPT
		ret.lpresum.emplace_back(ins[p].data * ret.lpresum.back());
		#else
		ret.lpresum[ret.cur_lpresum] = (ins[p].data * ret.lpresum[ret.cur_lpresum-1]);
		ret.cur_lpresum++;
		#endif
	}
	#else
	for(int i=0; i<cur_lmatref; ++i) {
		ret.lpresum[ret.cur_lpresum] = (ins[lmatref[i]].data * ret.lpresum[ret.cur_lpresum-1]);
		ret.cur_lpresum++;
	}
	#endif

	mat rsum {1,0,0,1};

	#ifndef ARROPT
	ret.rpresum.emplace_back(rsum);
	#else
	ret.rpresum[ret.cur_rpresum++]= rsum;
	#endif

	#ifndef ARROPT
	for(auto const & p : rmatsref) {

		// rsum = rsum * ins[p].data;
		#ifndef ARROPT
		ret.rpresum.emplace_back(ret.rpresum.back() * ins[p].data);
		#else
		ret.rpresum[ret.cur_rpresum] = ret.rpresum[ret.cur_rpresum-1] * ins[p].data; // wrong here
		ret.cur_rpresum++;
		#endif
	}
	#else
	for(int i=0; i<cur_rmatref; ++i) {
		ret.rpresum[ret.cur_rpresum] = ret.rpresum[ret.cur_rpresum-1] * ins[rmatref[i]].data;
		ret.cur_rpresum++;
	}
	#endif
	#ifndef ARROPT	
	ret.n12 = op.size();
	#else
	ret.n12 = cur_op;
	#endif

	ret.n3 = n3;
	// if(ret.n12 != op.size())
		// throw 1;
}

void block::make(int l, int r) {
	cal(l, r, *this);
}

block blks[1000]; 
block b1, b3;
block b;
mat rmats[M], lmats[M];
int cur_lmat = 0, cur_rmat = 0;
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
				cal(l, r, b);
				#ifndef ARROPT
				(b.lpresum.back() * b.rpresum.back()).print();
				#else
				(b.lpresum[b.cur_lpresum-1] * b.rpresum[b.cur_rpresum-1]).print();
				#endif
			}
			else {
				cal((r-1)/blksz*blksz+1, r, b3);
				int N3 = b3.n3;
				#ifndef ARROPT
				std::vector<mat> rmats, lmats;
				#else
				cur_lmat = 0;
				cur_rmat = 0;
				#endif
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
						#ifndef ARROPT
						lmats.emplace_back(b.lpresum[b.lcnt[how_many]]);
						rmats.emplace_back(b.rpresum[b.rcnt[how_many]]);
						#else
						lmats[cur_lmat++] = b.lpresum[b.lcnt[how_many]];
						rmats[cur_rmat++] = b.rpresum[b.rcnt[how_many]];
						#endif
					}
					N3 = std::max(0LL, N3 - b.n12) + b.n3;
				}
				cal(l, std::min((l-1)/blksz*blksz+blksz, n), b1);
				mat lsum {1,0,0,1}, rsum {1,0,0,1};
				#ifndef ARROPT
				for(auto p : lmats) {
					lsum = lsum * p;
				}
				for(auto p : rmats) {
					rsum = p * rsum;
				}
				#else
				for(int i=0; i<cur_lmat; ++i) {
					lsum = lsum * lmats[i];
				}
				for(int i=0; i<cur_rmat; ++i) {
					rsum = rmats[i] * rsum;
				}

				#endif
				#ifdef ARROPT
				(b3.lpresum[b3.cur_lpresum-1] * lsum * b1.lpresum[ b1.lcnt[std::max(0LL, b1.n12-N3)] ] \
				* b1.rpresum[ b1.rcnt[std::max(0LL, b1.n12-N3)] ] * rsum * b3.rpresum[b3.cur_rpresum-1])\
				.print();
				#else
				(b3.lpresum.back() * lsum * b1.lpresum[ b1.lcnt[std::max(0LL, b1.n12-N3)] ] \
				* b1.rpresum[ b1.rcnt[std::max(0LL, b1.n12-N3)] ] * rsum * b3.rpresum.back())\
				.print();
				#endif
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