#include <cstdio>
#include <vector>
#define vec std::vector<int>
vec hw[1001];
int n, m;
bool l(vec l, vec r) {
	auto len = l.size();
	for(int i=0; i<len; ++i) {
		if(l[i] <= r[i])
			return false;
	}
	return true;
}

signed main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<m; ++j) {
			int a;
			scanf("%d", &a);
			hw[i].push_back(a);
		}
	}
	for(int i=1; i<=n; ++i) {
		auto flag = false;
		for(int j=1; j<=n; ++j) {
			if(l(hw[j], hw[i])) {
				printf("%d\n", j);
				flag = true;
				break;
			}
		}
		if(!flag) {
			printf("%d\n", 0);
		}
	}
}