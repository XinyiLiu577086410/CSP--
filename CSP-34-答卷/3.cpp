#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;

int n,m;
int x1,x2,y1,y2,v;


int relu(int x) {return x > 0 ? x : 0;}

signed main(void) {
    scanf("%d%d", &n,&m);
    map<std::pair<int,int>,int> grid;
    while(n--) {
        scanf("%d%d%d%d%d", &x1,&x2,&y1,&y2,&v);
        for(int x = x1; x <= x2; ++x) {
            for(int y = y1; y<= y2; ++y) {
                auto cood = make_pair(x,y);
                grid[cood] = v + relu(grid[cood] - v);
            }
        }
    }

    while(m--) {
        int maxv = 0;
        scanf("%d%d%d%d", &x1,&x2,&y1,&y2);
        for (auto p : grid) {
            int x = p.first.first;
            int y = p.first.second;
            if ( x >= x1 && x <= x2 && y >= y1 && y<= y2)
                maxv = std::max(maxv, p.second);
        }
        printf("%d\n", maxv);
    }

}