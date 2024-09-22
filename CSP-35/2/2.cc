#include <iostream>
#include <string>
#include <vector>


using std::cin;
using std::cout;
using std::endl;
using std::vector;

char cp[128]; // char project
bool solved[128];
bool in_loop[128];
int group[128];
int pos[128];
int k;
signed main(void) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    std::string tmp, s;
    std::getline(cin, tmp);
    s = tmp.substr(1, tmp.size()-2);
    
    int n;
    cin >> n;
    std::getline(cin, tmp);
    while(n--) {
        std::string raw, proj;
        std::getline(cin, raw);
        proj = raw.substr(1, 2);
        cp[proj[0]] = proj[1];
    }

    vector<vector<char>> loop;
    vector<vector<char>> chain;
    for(int i = 0; i < 128; ++i) {
        if(!solved[i] && cp[i]) {
            auto head = true;
            for(int ii = 0; ii < 128; ++ii)
            {
                if(cp[ii] == i || ii == i)
                {
                    head = false;
                }
            }
            if(head)
            {
                vector<char> tmp;
                int cur = i;
                while(cp[cur]) {
                    tmp.emplace_back((char)cur);
                    solved[cur] = true;
                    cur = cp[cur];
                }
                int cpos = 0;
                for (auto p : tmp)
                {   
                    group[p] = chain.size();
                    pos[p] = cpos;
                    cpos++;
                    in_loop[p] = false;
                }
                chain.emplace_back(tmp);
            }
        }
    }

     for(int i = 0; i < 128; ++i) {
        if(!solved[i] && cp[i]) {
            vector<char> tmp;
            int cur = i;
            while(1) {
                tmp.emplace_back((char)cur);
                solved[cur] = true;
                cur = cp[cur];
                if(cur == i)
                    break;
            }
            int cpos = 0;
            for (auto p : tmp)
            {   
                group[p] = loop.size();
                pos[p] = cpos;
                cpos++;
                in_loop[p] = true;
            }
            loop.emplace_back(tmp);
        }
    }
    
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        int k;
        cin >> k;
        cout << "#";

        for(auto p : s) 
        {
            if(solved[p]) 
            {
                if(in_loop[p]) 
                {
                    cout << loop[group[p]][(k + pos[p]) % loop[group[p]].size()];    
                }
                else
                {
                    cout << ( k + pos[p] >= chain[group[p]].size() ) ?
                            chain[group[p]].back() : chain[group[p]][(k + pos[p])];    
                }
            } 
            else 
            {
                cout << p;
            }
        }

        cout << "#" << endl;    
    }
  
}