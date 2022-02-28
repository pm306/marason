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

//コンテストの数
const int CON = 26;

int main() {
    int D; cin >> D;
    //コンテストごとの満足度の減少固定値
    vector<int> C(CON); rep(i, CON) cin >> C[i];
    //S[i][j]:=i日目にコンテストjを開催したときの満足度の上昇値
    vector S(D, vector<int>(CON));
    rep(i, D)rep(j, CON) cin >> S[i][j];

    //各日のコンテスト日程 0-indexed
    vector<int> T(D); rep(i, D) cin >> T[i], T[i]--;

    //コンテストごとの開催日を集合で持つ
    vector<set<int>> contest_day(CON);
    //番兵
    rep(i, CON){
        contest_day[i].insert(-1);
        contest_day[i].insert(D);
    }
    rep(d, D)contest_day[T[d]].insert(d);

    //コンテストごとの、最後に開催した日。満足度の減少に使う。初期値-1
    vector<int> last(CON, -1);

    //変更クエリ
    int m; cin >> m;
    vector<pii> Q(m);
    rep(i, m) cin >> Q[i].first >> Q[i].second, Q[i].first--, Q[i].second--;

    //暫定スコアの算出
    int score = 0;
    rep(d, D){
        //満足度の上昇
        score += S[d][T[d]];
        //開催の記録
        last[T[d]] = d;

        //満足度の減少
        rep(i, CON){
            score -= C[i] * (d - last[i]);
        }
    }

    vector<int> ans;

    //変更クエリ
    for(auto [d, next] :Q){
        //変更前のコンテスト番号を変数に格納
        int pre = T[d];

        debug(pre, next);

        //上昇変更処理
        score -= S[d][pre];
        score += S[d][next];

        //開催予定の変更
        T[d] = next;
        contest_day[pre].erase(d);


        //満足度の減少変化処理
        //pre
        auto it = contest_day[pre].lower_bound(d);
        int next_con = *it, pre_con = *(--it);
        int sec1 = next_con - d, sec2 = d - pre_con;
        score -= sec1 * sec2 * C[pre];

        //next
        it = contest_day[next].lower_bound(d);
        next_con = *it, pre_con = *(--it);
        sec1 = next_con - d, sec2 = d - pre_con;
        score += sec1 * sec2 * C[next];

        contest_day[next].insert(d);

        ans.push_back(score);
    }
    fore(a, ans)cout << a << ln;
}

