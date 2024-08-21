#include<cstdio>
typedef long long llong;
llong x[100], y[100], dx[100], dy[100], op, coord;
int main(void) {
	scanf("%lld%lld", &op, &coord);
	for (int i=0; i<op; ++i) {
		scanf("%lld%lld", &dx[i], &dy[i]);
	}
	for (int i=0; i<coord; ++i) {
		scanf("%lld%lld", &x[i], &y[i]);
	}
	for (int i=0; i<coord; ++i) {
		for (int j=0; j<op; ++j) {
			x[i] += dx[j];
			y[i] += dy[j];
		}
	}
	for (int i=0; i<coord; ++i) {
		printf("%lld %lld\n", x[i], y[i]);
	}
	return 0;
}