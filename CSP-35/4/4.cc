#pragma GCC optimize("Ofast")
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <map>
#include <queue>
#include <algorithm>
using std::priority_queue;
using std::cin;
using std::cout;
using std::map;
using std::vector;
using std::string;
#define endl '\n'
#define INF 0x3f3f3f3f
#define MIN(a,b) ((a) < (b) ? (a) : (b))

int n,m;
int x[5000], y[5000], r[5000], t[5000];
typedef std::pair<std::pair<int,int>, int> point_t;
std::vector<point_t> graph;
int dis[5000];
map<int, map<int, int> > edge;

bool find_eg(int i, int j) {
    return edge.find(i) != edge.end() && edge[i].find(j) != edge[i].end();
}

struct node{
    unsigned short id;
    bool operator<(const node &a) const {
        return dis[id] < dis[a.id];
    }
};

signed main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        graph.push_back({{x, y}, i});
    }
    std::sort(graph.begin(), graph.end());

    for(int i = 0; i < m; ++i)
    {
        cin >> x[i] >> y[i] >> r[i] >> t[i];
        auto start = std::lower_bound(graph.begin(), graph.end(), point_t{{x[i] - r[i], y[i] - r[i]},   0});
        auto end   = std::upper_bound(graph.begin(), graph.end(), point_t{{x[i] + r[i], y[i] + r[i]}, n-1});
        for(auto j = start; j != end; ++j) {
            for (auto k = start; k != end; ++k) {
                if(std::abs(j->first.first - x[i]) < r[i] && std::abs(j->first.second - y[i]) < r[i] &&
                   std::abs(k->first.first - x[i]) < r[i] && std::abs(k->first.second - y[i]) < r[i]) {
                    if(j->second != k->second) {
                        if(!find_eg(j->second, k->second)) {
                            edge[j->second][k->second] = t[i];
                            edge[k->second][j->second] = t[i];
                        }
                        else {
                            edge[j->second][k->second] = MIN(edge[j->second][k->second], t[i]);
                            edge[k->second][j->second] = MIN(edge[k->second][j->second], t[i]);
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; ++i)
        dis[i] = INF;
    dis[0] = 0;

    priority_queue<node> q;
    for (int i = 0; i < n; ++i)
        q.push({(unsigned short)i});
    while(!q.empty()) {
        int m = q.top().id;
        q.pop();
        for(auto &i : edge[m]) {
            int j = i.first;
            int w = i.second;
            if(dis[j] > dis[m] + w) {
                dis[j] = dis[m] + w;
                q.push({(unsigned short)j});
            }
        }
    }

    if(dis[n-1] != INF)
        cout << dis[n-1] << endl;
    else
        cout << "Nan" << endl;
}
