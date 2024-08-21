#include <__config>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
using namespace std;

int calc_feq(   const vector<pair<int, vector<string> > > &text,
                const string & p,
                const string & q
            ) {
    int feq = 0;
    for(auto const & word : text) {
        int feq_in_word = 0;
        for(auto it = word.second.begin(); ; it++) {
            auto it_ = it;
            it_++;
            if(it_ >= word.second.end())
                break;
            if(*it == p && *it_ == q) {
                feq_in_word++;
                it++;
            }
        }
        feq += feq_in_word * word.first;
    }
    return feq;
}


void tokenize(  vector<pair<int, vector<string> > > &text,
                const string & new_token
            ) {
    vector<string> new_word;
    for(auto & word : text) {
        for(auto it = word.second.begin(); it < word.second.end(); it++) {
            auto it_ = it; it_++;
            if(it_ < word.second.end() && *it + *it_ == new_token) {
                new_word.emplace_back(*it + *it_);
                it++;
            } else {
                new_word.emplace_back(*it);
            }
        }
        word.second = new_word;
    }
}

struct cmp {
    typedef const pair<pair<int, int>, string> type_pair;
    bool operator() (type_pair a, type_pair b) const {
        return a.first.first < b.first.first;
    }
};

signed main (void) {
    int n, m;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> n >> m;
    vector< pair <int, vector <string> > > text;
    while (n--) {
        int feq;
        string orig;
        cin >> orig >> feq;
        vector<string> v;
        v.emplace_back(orig);
        text.emplace_back(make_pair(feq, v));
    }

    set<string> tokens;
    for(auto & p : text) {
        for(auto const & s : p.second) {
            vector <string>  new_text;
            for(auto const & c : s) {
                string tk(1, c);
                new_text.push_back(tk);
                if(tokens.find(tk) == tokens.end()) { 
                    tokens.insert(tk);
                }
            }
            p.second = new_text;
        }
    }

    vector<string> tokens_v;

    for(auto & p : tokens) 
        tokens_v.push_back(p);
    
    while (tokens.size() < m) {
        vector<pair<pair<int, int>, string> > candi;
        for(auto & p : tokens) {
            for(auto & q : tokens) {
                if(q == p) continue;
                if(tokens.find(p + q) == tokens.end())  {
                    int feq = calc_feq(text, p, q);
                    if(feq != 0)
                        candi.emplace_back(make_pair(make_pair(-feq, p.size()), p + q));
                }
            }
        }

        #ifdef DBG
        cout << "candi.size() = " << candi.size() << endl;
        #endif

        sort(candi.begin(), candi.end(), cmp());

        if(candi.size()){
            #ifdef DBG
            cout << "candi = [";
            for (auto p : candi) cout << p.second << ":" << p.first.first << ",";
            cout << "]" << endl;
            #endif
            string final_str;
            if(candi.size() >= 2) {
                if(candi[0].first != candi[1].first) {
                    if(candi[0].first < candi[1].first) 
                        final_str = candi[0].second;
                    else
                        final_str = candi[1].second;
                } else {
                    if(candi[0].second < candi[1].second) 
                        final_str = candi[0].second;
                    else
                        final_str = candi[1].second;
                }
            } else if(candi.size() == 1) 
                final_str = candi[0].second;
            tokenize(text, final_str);
            tokens.insert(final_str);
            tokens_v.emplace_back(final_str);
            #ifdef DBG
            cout << "tokens.size() = " << tokens.size() << endl;
            cout << "final_str = " << final_str << endl;
            #endif
        } else {
            break;
        }
    }
    
    for (auto const & p : tokens_v) {
        cout << p << endl;
    }
}