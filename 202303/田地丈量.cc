#include <cstdio>
#include <algorithm>

int a, b, n;
long long sum=0;

long long intersection(int l1, int r1, int l2, int r2) {
	if(l1 >= r2 || l2 >= r1) 
		return 0LL;
	else if( (l1 - l2) * (r1 - r2) <= 0 ) {
		return 1LL * std::min(r1 - l1, r2 - l2);
	}
	else return 1LL * std::min(std::abs(r2-l1), std::abs(r1-l2));
}

long long int f(int x1, int y1, int x2, int y2) {
	return intersection(x1, x2, 0, a) * intersection(y1, y2, 0, b);
}

signed main() {
	scanf("%d%d%d", &n, &a, &b);
	for(int i=0; i<n; ++i) {
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		sum += f(x1, y1, x2, y2);
	}
	printf("%lld", sum);
}
