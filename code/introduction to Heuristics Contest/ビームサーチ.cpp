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
const int LIMIT_TIME = 190;

int D;
vector<int> C(CONTEST_NUM);
vector scores(D, vector<int>(CONTEST_NUM));
vector<set<int>> contest_days(CONTEST_NUM); //各コンテストの開催日程
vector<int> T; //各日のコンテスト開催日

//インデックスをstring型のアルファベット大文字に変換する
string idxToString(int idx){
    string res = "";
    res += (char)('A' + idx);
    return res;
}

//1日分のスコアを計算する
//戻り値:day日終了時のスコア
//pre_score:=前日終了時のスコア order:=命令（当日分含む）
int calcDailyScore(int pre_score, string order){
    int next_score = pre_score;
    int day = order.size() - 1; //何日目か
    assert(day >= 0);
    //コンテストが開催されたので、スコアが増加する
    next_score += scores[day][order.back() - 'A'];

    reverse(all(order)); //最後の開催日を求めるために反転
    //開催されなかったコンテストのスコア減少処理
    for(int i=0; i<CONTEST_NUM; i++){
        int idx = order.find(idxToString(i));
        int last = idx == -1 ? day + 1 : idx; //該当コンテストが最後に開催された日と、当日の差分
        next_score -= C[i] * last;
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
    //last.assign(CONTEST_NUM, -1); //コンテストの開催記録リストを初期化
    T.resize(D);
}

//ファイルから入力
void input_file(){
    ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
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
    //last.assign(CONTEST_NUM, -1); //コンテストの開催記録リストを初期化
    T.resize(D);
}

//出力
void output(){
    for(auto& t : T){
        cout << t + 1 << ln << flush;
    }
}
//ファイルに出力
void output_file(){
    ofstream writing_file;
    string filename = "output.txt";
    writing_file.open(filename, ios::out);
    for(auto& t : T){
        writing_file << t + 1 << ln;
    }
    writing_file.close();
}

//制限時間チェック
//trueならセーフ
bool timeCheck(){
    return clock() * 100 / CLOCKS_PER_SEC <= LIMIT_TIME;
}

//乱数生成 [min, max)
int random(const int &MIN, const int &MAX){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX - 1);

    return distr(eng);
}

//ビームサーチ
//K:=候補として残す解の数
pair<int, string> beamSearch(int K){
    int score;
    vector<pair<int, string>> cand; //解の候補
    //貪欲法で初期解をK個求める
    for(int c=0; c<CONTEST_NUM; c++){
        score = calcDailyScore(0, idxToString(c));
        cand.emplace_back(score, idxToString(c));
    }
    sort(all(cand), greater<pair<int, string>>()); //スコアの大きい順にソート
    cand.resize(K); //先頭K個だけ残す

    for(int d=1; d<D; d++){
        priority_queue<pair<int, string>> new_cand; //新しい解候補
        //新たな解候補を生成
        for(auto [cur_score, order] : cand){
            for(int c=0; c<CONTEST_NUM; c++){
                order += idxToString(c);
                int new_score = calcDailyScore(cur_score, order);
                new_cand.push({new_score, order});
                order.pop_back();
            }
        }
        //先頭K個を新たな解候補とする
        cand.clear();
        for(int i=0; i<K; i++){
            cand.emplace_back(new_cand.top());
            new_cand.pop();
        }
    }
    return cand[0];
}

int main(){
    input();
    //input_file();

    auto [final_score, res] = beamSearch(75);
    debug((long double)clock() / CLOCKS_PER_SEC);
    for(auto a : res){
        cout << (a - 'A' + 1) << ln << flush;
    }

    //output();
    //output_file();
}

