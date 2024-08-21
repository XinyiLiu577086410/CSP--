#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
#define M 5000010
int n,m;
int x1[M],x2[M],y1[M],y2[M],v[M];
int xl,xr,yl,yr;
bool lap(int a1,int a2, int b1, int b2) {
    return (a1 - b2) * (a2 - b1) <= 0;
}
signed main(void) {
    scanf("%d%d", &n,&m);
    map<std::pair<int,int>,int> grid;
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d%d", &x1[i],&x2[i],&y1[i],&y2[i],&v[i]);
    }

    while(m--) {
        int maxv = 0;
        scanf("%d%d%d%d", &xl,&xr,&yl,&yr);
        for(int i = 1; i <= n; ++i) {
            if( 
                lap(xl, xr, x1[i], x2[i]) &&  lap(yl, yr, y1[i], y2[i])
            )
            maxv = std::max(maxv, v[i]);
        }
        printf("%d\n", maxv);
    }

}