/*
    Created by Pujx on 2024/7/18.
*/
#pragma GCC optimize(2, 3, "Ofast", "inline")
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
#define endl '\n'
//#define int long long
//#define double long double
using i64 = long long;
using ui64 = unsigned long long;
//using i128 = __int128;
#define inf (int)0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define yn(x) cout << (x ? "yes" : "no") << endl
#define Yn(x) cout << (x ? "Yes" : "No") << endl
#define YN(x) cout << (x ? "YES" : "NO") << endl
#define mem(x, i) memset(x, i, sizeof(x))
#define cinarr(a, n) for (int _ = 1; _ <= n; _++) cin >> a[_]
#define cinstl(a) for (auto& _ : a) cin >> _
#define coutarr(a, n) for (int _ = 1; _ <= n; _++) cout << a[_] << " \n"[_ == n]
#define coutstl(a) for (const auto& _ : a) cout << _ << ' '; cout << endl
#define all(x) (x).begin(), (x).end()
#define ls (s << 1)
#define rs (s << 1 | 1)
#define ft first
#define se second
#define pii pair<int, int>
#ifdef DEBUG
    #include "debug.h"
#else
    #define dbg(...) void(0)
#endif

const int N = 2e5 + 5;
//const int M = 1e5 + 5;
const int mod = 998244353;
//const int mod = 1e9 + 7;
//template <typename T> T ksm(T a, i64 b) { T ans = 1; for (; b; a = 1ll * a * a, b >>= 1) if (b & 1) ans = 1ll * ans * a; return ans; }
//template <typename T> T ksm(T a, i64 b, T m = mod) { T ans = 1; for (; b; a = 1ll * a * a % m, b >>= 1) if (b & 1) ans = 1ll * ans * a % m; return ans; }

int a[N];
int n, m, t, k, q;

vector<vector<int> > v;
vector<int> cnt;
vector<string> ans;

struct node {
    int id1, id2, cnt, vis;
    bool operator < (const node& t) const {
        if (cnt != t.cnt) 
            return cnt < t.cnt;
        if (ans[id1].length() + ans[id2].length() != ans[t.id1].length() + ans[t.id2].length())
            return ans[id1].length() + ans[id2].length() > ans[t.id1].length() + ans[t.id2].length();
        if (ans[id1].length() != ans[t.id1].length())
            return ans[id1].length() > ans[t.id1].length();
        return ans[id1] + ans[id2] > ans[t.id1] + ans[t.id2];
    }
};

priority_queue<node> pq;

struct Info {
    multiset<int> posi;
    int cnt, vis;
};

map<pair<int, int>, Info> mpInfo;

Info& getInfo(int id1, int id2) {
    if (mpInfo.count({id1, id2})) return mpInfo[{id1, id2}];
    else return mpInfo[{id1, id2}] = {multiset<int>(), 0, 0};
}

void work() {
    cin >> n >> m;
    vector<string> str(n);
    vector<int> vis(26, 0);
    v.resize(n), cnt.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> str[i] >> cnt[i];
        for (auto& ch : str[i]) vis[ch - 'a'] = 1;
    }
    for (int i = 0; i < 26; i++) {
        if (vis[i])
            ans.emplace_back(string(1, 'a' + i));
        if (i) vis[i] += vis[i - 1];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < str[i].length(); j++) {
            v[i].emplace_back(vis[str[i][j] - 'a'] - 1);
            if (j) {
                Info& info = getInfo(v[i][j - 1], v[i][j]);
                info.posi.emplace(i), info.cnt += cnt[i], ++info.vis;
                pq.emplace((node){v[i][j - 1], v[i][j], info.cnt, info.vis});
            }
        }
    }

    while (ans.size() < m) {
        while (pq.size() && pq.top().vis != mpInfo[{pq.top().id1, pq.top().id2}].vis) pq.pop();
        if (pq.empty()) break;
        if (pq.top().cnt == 0) break;

        int id1 = pq.top().id1, id2 = pq.top().id2;
        dbg(id1, id2);
        Info& info = getInfo(id1, id2);
        pq.pop();
        ans.emplace_back(ans[id1] + ans[id2]);

        for (auto i : info.posi) {
            int p = -1;
            for (int j = 0; j < v[i].size() - 1; j++)
                if (v[i][j] == id1 && v[i][j + 1] == id2) {
                    p = j;
                    break;
                }
            if (p == -1) continue;

            auto remove = [&] (int id1, int id2, int idx) {
                Info& tem = getInfo(id1, id2);
                if (&tem.posi == &info.posi) return;
                tem.posi.erase(tem.posi.find(idx));
                tem.cnt -= cnt[idx], ++tem.vis;
                pq.emplace((node){id1, id2, tem.cnt, tem.vis});
            };
            auto add = [&] (int id1, int id2, int idx) {
                Info& tem = getInfo(id1, id2);
                if (&tem.posi == &info.posi) return;
                tem.posi.emplace(idx);
                tem.cnt += cnt[idx], ++tem.vis;
                pq.emplace((node){id1, id2, tem.cnt, tem.vis});
            };

            if (p) remove(v[i][p - 1], v[i][p], i);
            if (p + 2 < v[i].size()) remove(v[i][p + 1], v[i][p + 2], i);

            v[i].erase(v[i].begin() + p + 1);
            v[i][p] = ans.size() - 1;

            if (p) add(v[i][p - 1], v[i][p], i);
            if (p + 1 < v[i].size()) add(v[i][p], v[i][p + 1], i);
        }

        info.posi.clear();
        info.cnt = 0, ++info.vis;
        pq.emplace((node){id1, id2, info.cnt, info.vis});
    }

    for (auto& str : ans) cout << str << endl;
}

signed main() {
#ifdef LOCAL
    freopen("C:\\Users\\admin\\CLionProjects\\Practice\\data.in", "r", stdin);
    freopen("C:\\Users\\admin\\CLionProjects\\Practice\\data.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int Case = 1;
    //cin >> Case;
    while (Case--) work();
    return 0;
}
/*
     _____   _   _       _  __    __
    |  _  \ | | | |     | | \ \  / /
    | |_| | | | | |     | |  \ \/ /
    |  ___/ | | | |  _  | |   }  {
    | |     | |_| | | |_| |  / /\ \
    |_|     \_____/ \_____/ /_/  \_\
*/
