#include <iostream>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

int n;
int times[128];

signed main(void) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    while(n--) {
        memset(times, 0, sizeof(times));
        std::string s;
        cin >> s;
        bool alpha=false, number=false, spec=false;
        for (auto p : s) {
            if (p == '#' || p == '*') 
                spec = true;
            if (p >= '0' && p <= '9')
                number = true;
            if ((p >= 'a' && p <= 'z') || (p >= 'A' && p <= 'Z'))
                alpha = true;
            times[p]++;
        }
        if(alpha && number && spec) 
        {
            auto high = true; 
            for(int i = 0 ; i < 128; ++i) 
                if(times[i] > 2) {
                    high = false;
                }
            if(high)
            {
                cout << 2 << endl;
            } else {
                cout << 1 << endl;
            }
        } else {
            cout << 0 << endl;
        }
    } 

}