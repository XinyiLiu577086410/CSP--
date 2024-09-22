#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using std::cin;
using std::cout;
// using std::endl;
#define endl '\n'
using std::vector;
using std::string;
#define BAD_PATCH() do{cout<<"Patch is damaged."<<endl; return 0;}while(0)

int n;
signed main() 
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<string> patch, orig, newfile;
    string tmp;
    cin >> n;
    std::getline(cin, tmp);
    //origin file
    for(int i = 0; i < n; ++i) {
        std::getline(cin, tmp);
        orig.emplace_back(tmp);
    }
    //patch
    while(std::getline(cin, tmp)) 
    {
        if(tmp.empty() || tmp.at(0) != '#')
            patch.emplace_back(tmp);
    }
    vector<int> at;
    do
    {
        int i = 0;
        for(auto p : patch) 
        {
            if(!p.empty() && p.at(0) == '@')
                at.emplace_back(i);
            i++;
        }
    }while(0);
    if(at.size()==0)
        BAD_PATCH();
    vector<vector<string>> oldsegs(at.size()), newsegs(at.size());
    vector<int> NN_arr(at.size()), MM_arr(at.size());
    for(int i = 0; i < at.size(); ++i) {
        auto start = at[i];
        auto end = (i + 1 == at.size()) ? patch.size(): at[i + 1]; 
        auto & start_line = patch.at(start); 
        if(start_line.substr(0, 3) != "@@ " || start_line.substr(start_line.size() - 3) != " @@")
            BAD_PATCH();
        auto head = start_line.substr(3, start_line.size() - 6);
        // cout << head << endl;
        int NN,MM,nn,mm,last_end = 0;
        for(auto & p : head) {
            if(p == '-' || p == '+' || p == ',') {
                p = ' ';
            }
        }
        for(auto & p : head) {
            if ( (p < '0' || p > '9') && p != ' ') {
                BAD_PATCH();
            }
        }
        sscanf(&head[0], "%d%d%d%d", &NN, &MM, &nn, &mm);
        if(last_end > NN) 
            BAD_PATCH();
        else
            last_end = NN + MM;
        vector<string> & oldseg = oldsegs[i];
        vector<string> & newseg = newsegs[i];
        for(int j = start + 1; j < end; ++j) 
        {
            auto line = patch.at(j).substr(1);
            auto c = patch.at(j).at(0);
            if(c != ' ' && c != '+'&& c != '-') 
                BAD_PATCH();
            if(c == ' ')
            {
                oldseg.push_back(line);
                newseg.push_back(line);
            }
            if(c == '-')
            {
                oldseg.push_back(line);
            }
            if(c == '+')
            {
                newseg.push_back(line);
            }
        }
        // cout << "old" << endl;
        // for(auto p : oldseg) cout << p << endl;
        // cout << "new" << endl;
        // for(auto p : newseg) cout << p << endl;
        // cout << NN << MM << nn << mm << endl;
        if(oldseg.size() != MM || newseg.size() != mm)
            BAD_PATCH();
        NN_arr[i] = NN;
        MM_arr[i] = MM;
    }
    for(int i = 0; i < at.size(); ++i) 
    {
        auto start = at[i];
        auto end = (i + 1 == at.size()) ? patch.size(): at[i + 1];
        bool find = false; 
        int delta = 0;
        vector<string> & oldseg = oldsegs[i];
        vector<string> & newseg = newsegs[i];
        for(; ; delta++) 
        {
            auto where = NN_arr[i] - delta;
            if(NN_arr[i] - delta < 0 && NN_arr[i] + delta >= orig.size()) 
            {
                break;
            }
            bool match = true;
            if(where >= 0) 
            {
                for(int j = where, jj = 0; j < where + MM_arr[i]; ++j, ++jj)
                {
                    if(oldseg[jj] != orig[j])
                    { 
                        match = false;
                        break;
                    }
                }
                if(match) 
                {
                    find = true;
                    delta = -delta;
                    break;
                }
            }

            where = NN_arr[i] + delta;
            match = true;
            if(where < orig.size()) 
            {
                for(int j = where, jj = 0; j < where + MM_arr[i]; ++j, ++jj)
                {
                    if(patch[jj] != orig[j])
                    { 
                        match = false;
                        break;
                    }
                }
                if(match) 
                {
                    find = true;
                    delta = delta;
                    break;
                }
            }
        }
        if(find) 
        {
            vector<string> tmp;
            if(i)
                if(NN_arr[i] + delta < NN_arr[i-1] + MM_arr[i-1])
                    BAD_PATCH();
            // cout << "DBG : " << NN_arr[i] << endl;
            for(int ii = i; ii < at.size(); ++ii) {
                NN_arr[i] += delta;
            }
            // cout << "DBG : " << NN_arr[i] << endl;
            auto same_seg_start = i ? NN_arr[i-1] + MM_arr[i-1] : 0;
            auto realstart = NN_arr[i]; 
            // cout << "DBG : " << same_seg_start << " " << realstart << endl;
            for(int j = same_seg_start; j < realstart; ++j) 
            {
                newfile.emplace_back(orig.at(j));
            }
            for(const auto & s : newsegs[i]) 
            {
                newfile.emplace_back(s);
            }
            if(at.size() - 1 == i) {
                for(int j = NN_arr[i] + MM_arr[i]; j < orig.size(); ++j)
                {
                    newfile.emplace_back(orig.at(j));
                }
            }
        }
        else
            BAD_PATCH();
    }

    for(const auto & line : newfile) 
        cout << line << endl;
}