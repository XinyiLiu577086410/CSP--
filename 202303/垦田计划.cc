#include <cstdio>
#include <algorithm>
constexpr int M = 1e5 + 10;
#define int long long 
/**
 * 算法是没错的，是int爆了
 * m不会爆， 不代表total不会爆！
*/
int n, m, k;
int t[M], c[M];
int maxt = 0;

int cost (int tar, int which) {
	if(tar >= t[which])
		return 0;
	else 
		return (t[which] - tar) * c[which];
}

int total(int tar) {
	int sum = 0; /*WA: 没有初始化*/
	for(int which=0; which<n; ++which) {
		sum += cost(tar, which);
	}
	return sum;
}

int work() {
	int up = maxt;
	int down = k;
	int mid;
	if(total(k) <= m)
		return k;

	while(up - down > 1) {
		/**
		 * const: 
		 * 		f() is strictly mono, 
		 * 		f(up) >= m,
		 * 		f(down) < m,
		 * 		up > mid + 1,
		 * 		down < mid implies f(down) > f(mid) > m,
		 *		up >= mid implies f(up) >= f(mid) >= m.
		 * output:
		 * 		up as return value;
		 * 
		 * analysis:
		 * down in [, root)
		 * up in [root, ]
		*/
		mid = (up + down) / 2;
		int t = total(mid);
		if ( t > m ) 
			down = mid;
		else		  
			up = mid;
	}
	return up;
}


signed main () {
	scanf("%lld%lld%lld", &n, &m, &k);
	for ( int i=0; i<n; ++i ) {
		scanf("%lld%lld", &t[i], &c[i]);
		maxt = std::max(maxt, t[i]);
	}
	printf("%lld", work());
}