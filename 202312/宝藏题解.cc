/*
    Created by Pujx on 2024/2/2.
*/
#pragma GCC optimize(2, 3, "Ofast", "inline")
#include <iostream>
#include <deque>
using namespace std;
#define endl '\n'
//#define int long long
//#define double long double
using i64 = long long;
using ui64 = unsigned long long;
using i128 = __int128;
#define inf (int)0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define yn(x) cout << (x ? "yes" : "no") << endl
#define Yn(x) cout << (x ? "Yes" : "No") << endl
#define YN(x) cout << (x ? "YES" : "NO") << endl
#define mem(x, i) memset(x, i, sizeof(x))
#define cinarr(a, n) for (int i = 1; i <= n; i++) cin >> a[i]
#define cinstl(a) for (auto& x : a) cin >> x;
#define coutarr(a, n) for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n]
#define coutstl(a) for (const auto& x : a) cout << x << ' '; cout << endl
#define all(x) (x).begin(), (x).end()
#define md(x) (((x) % mod + mod) % mod)
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

const int N = 1e5 + 5;
const int M = 350 + 5;
const int mod = 998244353;
//const int mod = 1e9 + 7;
//template <typename T> T ksm(T a, i64 b) { T ans = 1; for (; b; a = 1ll * a * a, b >>= 1) if (b & 1) ans = 1ll * ans * a; return ans; }
//template <typename T> T ksm(T a, i64 b, T m = mod) { T ans = 1; for (; b; a = 1ll * a * a % m, b >>= 1) if (b & 1) ans = 1ll * ans * a % m; return ans; }

//int a[N];
int n, m, t, k, q;

struct mat {
    int v[2][2];
    mat(bool isE = false) {
        v[0][0] = v[1][1] = isE;
        v[1][0] = v[0][1] = 0;
    }
    friend mat operator * (const mat& a, const mat& b) {
        mat ans;
        ans.v[0][0] = (1ll * a.v[0][0] * b.v[0][0] + 1ll * a.v[0][1] * b.v[1][0]) % mod;
        ans.v[0][1] = (1ll * a.v[0][0] * b.v[0][1] + 1ll * a.v[0][1] * b.v[1][1]) % mod;
        ans.v[1][0] = (1ll * a.v[1][0] * b.v[0][0] + 1ll * a.v[1][1] * b.v[1][0]) % mod;
        ans.v[1][1] = (1ll * a.v[1][0] * b.v[0][1] + 1ll * a.v[1][1] * b.v[1][1]) % mod;
        return ans;
    }
    friend istream& operator >> (istream& in, mat& x) {
        return in >> x.v[0][0] >> x.v[0][1] >> x.v[1][0] >> x.v[1][1];
    }
    friend ostream& operator << (ostream& out, const mat& x) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                out << x.v[i][j] << " ";
        return out;
    }
};

struct node {
    int op;
    mat l, r;
    friend istream& operator >> (istream& in, node& nd) {
        in >> nd.op;
        if (nd.op == 1) in >> nd.l, nd.r = mat(true);
        else if (nd.op == 2) in >> nd.r, nd.l = mat(true);
        else nd.l = nd.r = mat(true);
        return in;
    }
} op[N];

int oringlen;
struct block {
    int l, r, neg, sz;
    mat suml[M], sumr[M];

    void build(int idx) {
        l = idx * oringlen, r = min(l + oringlen - 1, n - 1), neg = 0, sz = 0;
        deque<int> st;
        for (int i = l; i <= r; i++) {
            if (op[i].op != 3) st.push_back(i);
            else if (st.empty()) neg++;
            else st.pop_back();
        }
        sz = st.size();
        suml[0] = sumr[0] = mat(true);
        for (int i = 0; i < st.size(); i++) {
            suml[i + 1] = op[st[i]].l * suml[i];
            sumr[i + 1] = sumr[i] * op[st[i]].r;
        }
    }
} blk[M];

mat query(int l, int r) {
    int blkl = l / oringlen, blkr = r / oringlen;
    if (blkl == blkr) { // 直接模拟
        deque<int> st;
        for (int i = l; i <= r; i++)
            if (op[i].op != 3) st.push_back(i);
            else if (!st.empty()) st.pop_back();
        mat L = mat(true), R = mat(true);
        for (int i = 0; i < st.size(); i++) {
            L = op[st[i]].l * L;
            R = R * op[st[i]].r;
        }
        return L * R;
    }
    else {
        int neg = 0;
        deque<int> st;
        for (int i = blk[blkr].l; i <= r; i++) {
            if (op[i].op != 3) st.push_back(i);
            else if (st.empty()) neg++;
            else st.pop_back();
        }
        mat L = mat(true), R = mat(true);
        for (int i = 0; i < st.size(); i++) {
            L = op[st[i]].l * L;
            R = R * op[st[i]].r;
        }

        for (int i = blkr - 1; i >= blkl + 1; i--) {
            if (blk[i].sz <= neg) neg = neg - blk[i].sz + blk[i].neg;
            else {
                L = L * blk[i].suml[blk[i].sz - neg];
                R = blk[i].sumr[blk[i].sz - neg] * R;
                neg = blk[i].neg;
            }
        }

        while (!st.empty()) st.pop_back();
        for (int i = l; i <= blk[blkl].r; i++) {
            if (op[i].op != 3) st.push_back(i);
            else if (!st.empty()) st.pop_back();
        }
        while (neg && !st.empty()) neg--, st.pop_back();
        for (int i = st.size() - 1; i >= 0; i--) {
            L = L * op[st[i]].l;
            R = op[st[i]].r * R;
        }
        return L * R;
    }
}

void work() {
    cin >> n >> m;
    oringlen = max(1, (int)sqrt(n));

    for (int i = 0; i < n; i++) cin >> op[i];
    for (int i = 0; i < n; i += oringlen) blk[i / oringlen].build(i / oringlen);

    while (m--) {
        int v, idx, l, r;
        cin >> v;
        if (v == 1) {
            cin >> idx;
            cin >> op[--idx];
            blk[idx / oringlen].build(idx / oringlen);
        }
        else {
            cin >> l >> r;
            cout << query(--l, --r) << endl;
        }
    }
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
