#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
constexpr char ln =  '\n';
constexpr int INF = 2e9+100;
constexpr long long LLINF = 3e18;
constexpr double EPS = 1e-9;
#define all(v) v.begin(), v.end()
#define rep(i, n) for(int i=0;i<(n);i++)
#define rept(i, j, n) for(int i=(j); i<(n); i++)
#define rrep(i, n) for(int i=(n)-1; i>=0; i--)
#define fore(i, a) for(auto &i:a)
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return true; } return false; }
template<typename T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> inline void UNIQUE(vector<T>& v) { v.erase(unique(v.begin(), v.end()), v.end()); }
inline int popcount(ll x) { return __builtin_popcountll(x); }
inline ll CEIL(ll a, ll b){return (a+b-1) / b;}
const string YesNo[2] = {"No", "Yes"};
inline void Yes(bool t = true) { cout << YesNo[t] << "\n"; }
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

const int CONTEST_NUM = 26;

int D;
vector<int> C(CONTEST_NUM);
vector scores(D, vector<int>(CONTEST_NUM));
vector<int> last;

//コンテストconの開催日をdayに書き換える
void update_last_contest(vector<int>& last, int day, int con_idx){
    last[con_idx] = day;
}

//スコア計算
//pre_score:=前日終了時のスコア day:=日程 con_idx:=開催するコンテスト last:=各コンテストが最後に開催された日(TODO:=参照にすべきか？)
int calc_score(int pre_score, int day, int con_idx, vector<int> &last){
    int next_score = pre_score;
    //コンテストが開催されたので、スコアが増加する
    next_score += scores[day][con_idx];
    //開催を記録する
    update_last_contest(last, day, con_idx);

    //開催されなかったコンテストのスコア減少処理
    for(int i=0; i<CONTEST_NUM; i++){
        next_score -= C[i] * (day - last[i]);
    }

    return next_score;
}

void score_resize(){
    scores.resize(D);
    for(int i=0; i<D; i++){
        scores[i].resize(CONTEST_NUM);
    }
}

void input(){
    cin >> D;
    for(int i=0; i<CONTEST_NUM; i++){
        cin >> C[i];
    }
    score_resize();
    for(int i=0; i<D; i++){
        for(int j=0; j<CONTEST_NUM; j++){
            cin >> scores[i][j];
        }
    }
    last.assign(CONTEST_NUM, -1);
}

void output(){

}

//T:B問題専用の入出力用配列 vals:出力用配列
vector<int> T, vals;

//B問題専用の入力
void input_B(){
    T.resize(D);
    vals.resize(D);
    for(int i=0; i<D; i++){
        cin >> T[i];
        T[i]--;
    }
}

//B問題専用の出力
void output_B(){
    for(auto &v : vals)cout << v << ln;
}

int main(){
    input();
    input_B();

    int cur_score = 0;
    for(int d=0; d<D; d++){
        cur_score = calc_score(cur_score, d, T[d], last);
        vals[d] = cur_score;
    }

    output_B();
}
