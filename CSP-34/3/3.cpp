#pragma GCC optimize("Ofast", "inline")
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

void get_candi( const vector<pair<int, vector<int> > >  &text  ,
                const vector<string>                    &tokens,
                vector < pair< vector<int>,  pair<int, int> > >   &candi
                ) {
    for(auto const & encoded_word : text) {
        // #ifdef DBG
        //     cout << "[";
        //     for(auto s : word.second) cout << s << ",";
        //     cout << "]" << endl;
        // #endif
        for(auto it = encoded_word.second.begin(); ; it++) {
            auto it_ = it;
            it_++;
            if(it_ >= encoded_word.second.end()) break;
            auto new_token = make_pair(*it, *it_);
            bool noval = true;
            for(auto & t : candi) {
                if(t.second == new_token) {
                    t.first[0] -= encoded_word.first;
                    noval = false;
                }
            }
            //{-1 * freqency, new token size, first origin token size}
            if(noval) {
                vector<int> foo;
                foo.push_back(-1 * encoded_word.first);
                foo.push_back((int)(tokens[new_token.first] + tokens[new_token.second]).size());
                foo.push_back((int) tokens[new_token.first].size());
                candi.emplace_back(make_pair(foo, new_token));
            }
        }
    }
}

                
void tokenize(  vector<pair<int, vector<int> > > &text,
                const pair<int, int>   &new_token_pair,
                const int             new_token_encode
            ) {
    for(auto & encoded_word : text) {
        vector<int> new_word;
        for(auto it = encoded_word.second.begin(); it < encoded_word.second.end(); it++) {
            auto it_ = it; it_++;
            if(it_ < encoded_word.second.end())  {
                auto const token_pair = make_pair(*it, *it_);
                if(token_pair == new_token_pair) {
                    new_word.emplace_back(new_token_encode);
                    it++;
                } else {
                    new_word.emplace_back(*it);
                }
            }
            else {
                new_word.emplace_back(*it);
            }
        }
        encoded_word.second = new_word;
    }
}


signed main (void) {
    int n, m;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    cin >> n >> m;
    vector<pair<int, string> > orig;
    for (long i = 0; i < n; ++i) {
        int feq;
        string str;
        cin >> str >> feq;
        orig.emplace_back(make_pair(feq, str));
    }

    vector<bool> vis(26, false);
    for(auto & p : orig) {
        for(auto const & c : p.second) {
            vis.at(c - 'a') = true;
        }
    }

    vector<string> tokens;
    map<char, int> get_char_code;
    for(long i = 0; i < 26; ++i) {
        if(vis.at(i)) {
            get_char_code[i + 'a'] = tokens.size();
            tokens.emplace_back(string(1, i + 'a'));
        }
    }
    
    vector<pair<int, vector<int> > > text(n);
    for(long i = 0; i < orig.size(); ++i) {
        auto & str = orig.at(i).second;
        text[i].first = orig[i].first;
        for(auto const & c : str) {
            text[i].second.emplace_back(get_char_code[c]);
        }
    }

    while (tokens.size() < m) {
        auto get_str = [&] (pair<vector<int>,  pair<int, int> > p) {
            return tokens[p.second.first] + tokens[p.second.second];
        };
        vector<pair<vector<int>,  pair<int, int> > > candi;
        get_candi(text, tokens, candi);
        if(candi.size()){
            auto final = candi[0];
            for(auto & p : candi) {
                if(p.first < final.first) {
                    final = p;
                } else if (p.first == final.first) {
                    auto str_p = get_str(p);
                    auto str_final = get_str(final);
                    if(str_p < str_final) {
                        final = p;
                    }
                }
            }
            tokenize(text, final.second, tokens.size());
            auto new_token_str = get_str(final);
            tokens.emplace_back(new_token_str);
            #ifdef DBG
                cout << tokens.size() << endl;
            #endif
        } else {
            break;
        }
    }
    
    int i = 0;
    for (auto const & p : tokens) {
        cout << p << endl;
        i++;
        if(i >= m) break;
    }
}