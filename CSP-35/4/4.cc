#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using std::cin;
using std::cout;
#define endl '\n'
using std::vector;
using std::string;
int n,m;
int nx[5000], ny[5000];
int x[5000], y[5000], r[5000], t[5000];
int dis[5000][5000];
signed main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        cin >> nx[i] >> ny[i];
    }
    for(int i = 0; i < m; ++i)
    {
        auto f = [&](int node, int station) -> bool {
            return nx[node] >= x[station] - r[station] &&
                   nx[node] <= x[station] + r[station] &&
                   ny[node] >= y[station] - r[station] &&
                   ny[node] <= y[station] + r[station];
        };
        cin >> x[i] >> y[i] >> r[i] >> t[i];
        for(int j = 0; j < n; ++j)
        if( f(j, i) )
            for(int k = 0; k < n; ++k)
            if( f(k, i) ) 
            {
                dis[j][k] = dis[k][j] = std::min(dis[j][k], t[i]);
            }
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
                dis[j][i] = dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
    cout <<  dis[0][n-1] << endl;

}
