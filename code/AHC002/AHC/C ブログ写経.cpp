#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
constexpr char ln =  '\n';
constexpr long long INF = 1LL<<61;
constexpr double EPS = 1e-9;
#define all(v) v.begin(), v.end()
#define rep(i, n) for(int i=0;i<(n);i++)
#define rept(i, j, n) for(int i=(j); i<(n); i++)
#define rrep(i, n) for(int i=(n)-1; i>=0; i--)
#define fore(i, a) for(auto &i:a)
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return true; } return false; }
template <class T> inline void drop(T x) { cout << x << "\n"; exit(0); }

#ifdef _DEBUG
template <class T1, class T2> ostream& operator<<(ostream& os, pair<T1, T2> p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <size_t N, class TUPLE> void debug_tuple(ostream& os, TUPLE _) { (void)os; (void)_; }
template <size_t N, class TUPLE, class T, class ...Args> void debug_tuple(ostream &os, TUPLE t) { os << (N == 0 ? "" : ", ") << get<N>(t); debug_tuple<N + 1, TUPLE, Args...>(os, t); }
template <class ...Args> ostream& operator<<(ostream& os, tuple<Args...> t) { os << "("; debug_tuple<0, tuple<Args...>, Args...>(os, t); return os << ")"; }
string debug_delim(int& i) { return i++ == 0 ? "" : ", "; }
#define debug_embrace(x) { int i = 0; os << "{";  { x } return os << "}"; }
template <class T> ostream& operator<<(ostream& os, vector<T> v) { debug_embrace( for (T e : v) { os << debug_delim(i) << e; } ) }
template <class T, size_t N> ostream& operator<<(ostream& os, array<T, N> a) { debug_embrace( for (T e : a) { os << debug_delim(i) << e; } ) }
template <class T, size_t N> enable_if_t<!is_same_v<char, remove_cv_t<T>>, ostream>& operator<<(ostream& os, T(&a)[N]) { debug_embrace( for (T e : a) { os << debug_delim(i) << e; } ) }
template <class Key> ostream& operator<<(ostream& os, set<Key> s) { debug_embrace( for (Key e : s) { os << debug_delim(i) << e; }) }
template <class Key, class T> ostream& operator<<(ostream& os, map<Key, T> mp) { debug_embrace( for (auto e : mp) { os << debug_delim(i) << e; }) }
template <class Key> ostream& operator<<(ostream& os, multiset<Key> s) { debug_embrace( for (Key e : s) { os << debug_delim(i) << e; }) }
template <class T> ostream& operator<<(ostream& os, queue<T> q) { debug_embrace( for (; !q.empty(); q.pop()) { os << debug_delim(i) << q.front(); } ) }
template <class T> ostream& operator<<(ostream& os, deque<T> q) { debug_embrace( for (T e : q) { os << debug_delim(i) << e; } ) }
template <class T> ostream& operator<<(ostream& os, priority_queue<T> q) { debug_embrace( for (; !q.empty(); q.pop()) { os << debug_delim(i) << q.top(); } ) }
template <class T> ostream& operator<<(ostream& os, priority_queue<T, vector<T>, greater<T>> q) { debug_embrace( for (; !q.empty(); q.pop()) { os << debug_delim(i) << q.top(); } ) }
void debug_out() { cerr << endl; }
template <class T, class... Args> void debug_out(const T& x, const Args& ... args) { cerr << " " << x; debug_out(args...); }
#define debug(...) cerr << __LINE__ << " : [" << #__VA_ARGS__ << "] =", debug_out(__VA_ARGS__)
#else
#define debug(...)(void(0))
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////

const int inf= 1<<30;

unordered_map<char, int> genom;
ll calc_score(vector<string> &S, int m){
    ll score = 0;
    rep(j, S[0].size()){
        vector<int> cnt(5);
        rep(i, m){
            int idx = genom[S[i][j]];
            cnt[idx]++;
        }
        int add = accumulate(all(cnt), 0) - *max_element(all(cnt));
        score += add;
    }
    return score;
}
void init(){
    genom['A'] = 0; genom['G'] = 1; genom['C'] = 2; genom['T'] = 3; genom['-'] = 4;
}

void solve(){
    int m; cin >> m;
    vector<string> S(m);
    const int id = 0;
    rep(i, m) cin >> S[i];

    for(int kkt = 88; kkt <= 89; kkt++){
        vector<vector<int>> dp, kkt89_cute;
        for(int jupi=0; jupi<m; jupi++){
            if(jupi == id) continue;
            const auto &s = S[jupi];
            const auto &t = S[id];
            //dp[i][j]:=指定した2行を前からi/j文字使った最小スコア
            dp.clear(); dp.resize(s.size() + 1, vector<int>(t.size() + 1, inf));
            kkt89_cute.clear(); kkt89_cute.resize(s.size() + 1, vector<int>(t.size() + 1, inf));
            dp[0][0] = 0;
            rep(i, s.size()+1){
                rep(j, t.size()+1){
                    if(i + 1 <= (int)s.size() and j + 1 <= (int)t.size()){
                        if(s[i] == t[j] and chmin(dp[i+1][j+1], dp[i][j]));{
                            kkt89_cute[i+1][j+1] = 0;
                        }
                        if(chmin(dp[i+1][j+1], dp[i][j] + 1)){
                            kkt89_cute[i+1][j+1] = 0;
                        }
                    }
                    if(kkt != 89){
                        if(i+1<=(int)s.size()){
                            if(chmin(dp[i+1][j], dp[i][j] + 1)){
                                kkt89_cute[i+1][j] = 1;
                            }
                        }
                    }
                    if(j+1<=(int)t.size()){
                        if(chmin(dp[i][j+1], dp[i][j]+1)){
                            kkt89_cute[i][j+1] = 2;
                        }
                        if(t[j] == '-' and chmin(dp[i][j+1], dp[i][j])){
                            kkt89_cute[i][j+1] = 2;
                        }
                    }
                }
            }
            string rest, ress;
            int sid = (int)s.size(), tid = (int)t.size();
            while(sid > 0 or tid > 0){
                if(kkt89_cute[sid][tid] == 0){
                    rest += t[tid-1];
                    ress += s[sid-1];
                    sid--; tid--;
                }
                else if(kkt89_cute[sid][tid] == 1){
                    rest += "-";
                    ress += s[sid-1];
                    sid--;
                }
                else{
                    rest += t[tid-1];
                    ress += "-";
                    tid--;
                }
            }
            reverse(all(ress));
            reverse(all(rest));
            swap(S[id], rest);
            swap(S[jupi], ress);
            debug(S);
        }
    }

    int score = calc_score(S, m);
    debug(score);

    rep(i, m) cout << S[i] << ln;
}



int main() {
    init();
    solve();
}
