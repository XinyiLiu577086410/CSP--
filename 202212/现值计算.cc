#include <cmath>
#include <cstdio>
double i, sum=0.0;
double ii = 1.0;
int n;
signed main() {
	scanf("%d%lf", &n, &i);
	for(int j=0; j<=n; ++j) {
		double io;
		scanf("%lf", &io);
		sum += io / ii;
		ii *= 1 + i;
	}
	
	printf("%lf", sum);
}