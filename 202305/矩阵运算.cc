#include <cstdio>
#include <cstring>
#include <cstdint>
#define int int64_t
#pragma GCC optimize(2, 3, "Ofast", "inline")
// #define DBG
struct mat
{
	int *data;
	int n,d;
	mat(int n, int d) : data(new int[n*d]), n(n), d(d) { 
		memset(data, 0, n*d*sizeof(int));
	}
	
	void del() {
		if(data) delete [] data; data = nullptr; 
	};

	~mat() { 
		del(); 
	}

	mat(const mat & tmp) {
		data = new int [tmp.n*tmp.d];
		n = tmp.n;
		d = tmp.d;
		memcpy(data, tmp.data, n*d*sizeof(int));
	}

	mat operator=(mat && tmp) {
		del();
		data = new int [tmp.n*tmp.d];
		n = tmp.n;
		d = tmp.d;
		memcpy(data,tmp.data,n*d*sizeof(int));
		return *this;
	}

	void read() {
		for( int i=0; i<n; ++i )
			for( int j=0; j<d; ++j )
				scanf("%lld", &data[j + i*d]);
	}

	void Tread() {
		for( int j=0; j<d; ++j )
			for( int i=0; i<n; ++i )
				scanf("%lld", &data[i * d + j]);
	}

	mat T() {
		mat bT(d, n);
		for( int i=0; i<n; ++i )
			for( int j=0; j<d; ++j )
				bT.data[i + n * j] = data[j + i * d];
		return bT;
	}

	mat operator* (mat & b) {
		auto bT = b.T();
		mat res(n, b.d);
		for ( int i=0; i<n; ++i )
			for ( int j=0; j<b.d; ++j )
				for ( int k=0; k<d; ++k )
					res.data[j + i * b.d] += data[k + i * d] * bT.data[k + j * d];
		return res;
	}

	mat operator* (mat && b) {
		auto bT = b.T();
		mat res(n, b.d);
		for ( int i=0; i<n; ++i )
			for ( int j=0; j<b.d; ++j )
				for ( int k=0; k<d; ++k )
					res.data[j + i * b.d] += data[k + i * d] * bT.data[k + j*d];
		return res;
	}

	void print() 
	{
		for(int i=0; i<n; ++i) 
			for(int j=0; j<d; ++j) 
				printf("%lld%c", data[j + i*d], j==d-1?'\n':' ');
	}

	friend mat dot(mat W, mat A) {
		for(int i=0; i<W.d; ++i) 
			for(int j=0; j<A.d; ++j)
				A.data[j+i*A.d] *= W.data[i];
		
		return A;
	}
};



signed n, d;
signed main() {
	scanf("%d%d", &n, &d);
	mat Q(n, d), K(d, n), V(n, d), W(1, n);
	Q.read();
	K.Tread();
	V.read();
	W.read();	
	#ifdef DBG
	Q.print();
	K.print();
	V.print();
	W.print();
	#endif
	(dot(W, (Q * (K * V)))).print(); // 
}

/**
 * 奇怪，样例可以过，测评一个点都没过。
 * 原来是new出来的内存。。。。不为全零。
 * 转置+点乘在最外面：70
 * 这个评测机在WA后就停机了。。
 * 转置+点乘在最外面：MLE
 * 点乘在最外面：70
 * 改变结合顺序：AC!
*/
// dot(W, Q x K.T x V)
// signed main() {
// 	int n, d;
// 	scanf("%lld%lld", &n, &d);
// 	int Q[n][d];
// 	int K[d][n];
// 	int V[n][d];
// 	int W[n];
// 	for(int i=0; i<n; ++i) 
// 		for(int j=0; j<d; ++j) 
// 			scanf("%lld", &Q[i][j]);
// 	for(int j=0; j<n; ++j) 
// 		for(int i=0; i<d; ++i) 
// 			scanf("%lld", &K[i][j]);
// 	for(int i=0; i<n; ++i) 
// 		for(int j=0; j<d; ++j) 
// 			scanf("%lld", &V[i][j]);
// 	for(int i=0; i<n; ++i)
// 		for(int j=0; j<n; ++j) {
// 			int x = 0;
// 			for(int k=0; k<d; ++k) 
// 				x += Q K
// 		}

// }