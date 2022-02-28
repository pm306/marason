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

const int CON = 26; //コンテストの種類
int D; //開催日数
vector<int> C(CON);
int S[365][CON];

//評価関数
int calcScore(vector<int> &T){
    int res = 0;
    vector<int> last(CON, -1);

    rep(i, D){
        res += S[i][T[i]];
        last[T[i]] = i;
        rep(j, CON) res -= C[j] * (i - last[j]);
    }

    return res;
}

//コンテストごとの開催日を集合で持つ
vector<set<int>> contest_day(CON);
//変更クエリ対応スコア
//d日目のコンテストをnextにしたときのスコアを返す
int calcSearchScore(vector<int> &T, int pre_score, int d, int next){
    int pre = T[d];

    int score = pre_score;
    score -= S[d][pre];
    score += S[d][next];

    //pre
    auto it = contest_day[pre].upper_bound(d);
    int next_con = *it;
    it--; it--;
    int pre_con = *it;
    int sec1 = next_con - d, sec2 = d - pre_con;
    score -= sec1 * sec2 * C[pre];

    //next
    it = contest_day[next].lower_bound(d);
    next_con = *it, pre_con = *(--it);
    sec1 = next_con - d, sec2 = d - pre_con;
    score += sec1 * sec2 * C[next];

    return score;
}

//[MIN, MAX)な乱数を返す
int random(const int &MIN, const int &MAX){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX - 1);

    return distr(eng);
}

//ランダムなコンテスト表を作成
vector<int> getSchedule(){
    vector<int> T(D);
    rep(i, D)T[i] = random(0, CON);

    return T;
}


int main() {
    //input
    cin >> D;
    rep(i, CON) cin >> C[i];
    rep(i, D)rep(j, CON) cin >> S[i][j];

    //番兵
    rep(i, CON){
        contest_day[i].insert(-1);
        contest_day[i].insert(D);
    }

    vector<int> ans = getSchedule();
    int score = calcScore(ans);
    rep(d, D)contest_day[ans[d]].insert(d);

    int tmp_score = calcSearchScore(ans, score, 0, 6);

    const int LIMIT_TIME = 190;
    int d, q, pre_q;
    while(clock() * 100 / CLOCKS_PER_SEC <= LIMIT_TIME){
        while(true){
            d = random(0, D);
            q = random(0, CON);
            pre_q = ans[d];
            if(q != pre_q)break;
        }

        int tmp_score = calcSearchScore(ans, score, d, q);
        if(chmax(score, tmp_score)){
            ans[d] = q;
            contest_day[pre_q].erase(d);
            contest_day[q].insert(d);
        }
    }

    fore(a, ans) cout << a + 1 << ln;
    debug(score);
}

