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
vector<set<int>> contest_days(CONTEST_NUM); //各コンテストの開催日程

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

//スコア獲得配列のリサイズ
void score_resize(){
    scores.resize(D);
    for(int i=0; i<D; i++){
        scores[i].resize(CONTEST_NUM);
    }
}

//入力
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
    last.assign(CONTEST_NUM, -1); //コンテストの開催記録リストを初期化
}

//出力
void output(){

}

//T:(初期)コンテスト日程
//vals:出力用配列
vector<int> T, vals;
int M;
vector<pii> query; //day日目に開催されるコンテストをqに変更するクエリリスト

//C問題専用の入力
void input_C(){
    T.resize(D);
    for(int i=0; i<D; i++){
        cin >> T[i];
        T[i]--;
    }
    cin >> M;
    query.resize(M);
    for(int i=0; i<M; i++){
        int d, q; cin >> d >> q;
        d--, q--;
        query[i] = {d, q};
    }
    vals.resize(M);
}

//局所探索用。
//各コンテストを集合に放り込んで、番兵として初日-1と最終日＋１を埋める。
void init_C(){
    for(int d=0; d<D; d++){
        contest_days[T[d]].insert(d); //T[d]番目のコンテストはd日目に開催される
    }
    for(int i=0; i<CONTEST_NUM; i++){
        contest_days[i].insert(-1); //初日の前日
        contest_days[i].insert(D); //最終日の翌日
    }
}

//C問題専用の出力
void output_C(){
    for(auto &v : vals)cout << v << ln;
}

//局所探索法
//戻り値：新スコア
//引数：元スコア、更新日、新しいコンテスト番号
int solve(int pre_score, int update_day, int after_contest){
    int new_score = pre_score;
    int before_contest = T[update_day]; //取りやめるコンテスト

    //コンテスト変更の影響:=開催スコア + 影響日数 * 不満度 * 影響単位(d-lastの変化度)
    int unit, days; //影響単位、影響日数

    //コンテストの取りやめ
    //前計算
    auto it = contest_days[before_contest].lower_bound(update_day); it--;
    unit = update_day - *it; //it:=直前にコンテストが開催された日のイテレータ
    days = *contest_days[before_contest].upper_bound(update_day) - update_day; //影響日数 = 次の開催日 - 改定日
    //計算
    new_score -= unit * C[before_contest] * days;
    new_score -= scores[update_day][before_contest];

    //コンテストの新規開催
    //前計算
    it = contest_days[after_contest].lower_bound(update_day); it--;
    unit = update_day - *it;
    days = *contest_days[after_contest].upper_bound(update_day) - update_day;
    //計算
    new_score += unit * C[after_contest] * days;
    new_score += scores[update_day][after_contest];

    //コンテスト記録の書き換え
    //集合からの削除と追加
    contest_days[before_contest].erase(update_day);
    contest_days[after_contest].insert(update_day);
    T[update_day] = after_contest; //開催記録の変更

    return new_score;
}

int main(){
    input();
    input_C();
    init_C();

    //初期解を求める
    int cur_score = 0;
    for(int d=0; d<D; d++){
        cur_score = calc_score(cur_score, d, T[d], last);
    }

    //クエリ処理(局所探索法)
    for(int m=0; m<M; m++){
        auto [update_day, after_contest] = query[m];
        cur_score = solve(cur_score, update_day, after_contest);
        vals[m] = cur_score;
    }

    output_C();
}

