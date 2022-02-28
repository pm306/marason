#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
constexpr char ln =  '\n';
constexpr long long INF = 1LL<<60;
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

string S, T;
ll score(int si, int ti){
    return S[si] == T[ti] ? 1 : -3;
}

int main() {
    cin >> S >> T;
    int ls = S.size(), lt = T.size();

    //dp[i][s][t]:=前からi文字目まで決めて、Sをs文字、Tをt文字使った時の最高スコア
    vector dp(ls+lt+1, vector(ls+1, vector<ll>(lt+1, -INF)));
    dp[0][0][0] = 0;

    rep(i, ls+lt)rep(s, ls+1)rep(t, lt+1){
        if(dp[i][s][t]==-INF)continue;
        if(s<ls and t<lt){
            chmax(dp[i+1][s+1][t+1], dp[i][s][t] + score(s, t));
        }
        if(t<lt){
            chmax(dp[i+1][s][t+1], dp[i][s][t] - 5);
        }
        if(s<ls){
            chmax(dp[i+1][s+1][t], dp[i][s][t] - 5);
        }
    }

    ll ma = -INF; int end_idx = -1;
    rep(i, ls+lt+1)if(chmax(ma, dp[i][ls][lt]))end_idx = i;

    //復元パート
    int is = ls, it = lt; //次に入れる文字インデックス+1
    string rs = "", rt = "";

    for(int i=end_idx-1; i>=0; i--){
        //両方使った
        if(is > 0 and it > 0 and dp[i][is-1][it-1] == dp[i+1][is][it] - score(is-1, it-1)){
            rs += S[--is];
            rt += T[--it];
            continue;
        }
        //S側だけ採用
        if(is > 0 and dp[i][is-1][it] == dp[i+1][is][it] + 5){
            rs += S[--is];
            rt += "-";
            continue;
        }
        //T側だけ採用
        if(it > 0 and dp[i][is][it-1] == dp[i+1][is][it] + 5){
            rt += T[--it];
            rs += "-";
            continue;
        }
    }
    reverse(all(rs));
    reverse(all(rt));
    cout << rs << ln;
    cout << rt << ln;
}

