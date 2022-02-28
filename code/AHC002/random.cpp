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

//ランダム移動

//移動用配列
const int dx[4]={0,1,0,-1};
const int dy[4]={-1,0,1,0};

//移動方向を決める配列と、対応する文字
vector<int> direction = {0, 1, 2, 3};
map<int, char> direction_char;
//グリッドの長さ
const int g_size = 50;
//タイルの数
const int tile_size = 1250;

//デバッグ用カウンタ
int d_cnt = 0;

int main(){
    //前準備 TODO:関数化する
    direction_char[0] = 'U';
    direction_char[1] = 'R';
    direction_char[2] = 'D';
    direction_char[3] = 'L';

    /* 入力 */
    //始点
    int si, sj; cin >> si >> sj;
    //各座標のタイル番号
    vector tile_number(g_size, vector<int>(g_size));
    rep(i, g_size)rep(j, g_size) cin >> tile_number[i][j];
    //各座標の得点
    vector point(g_size, vector<int>(g_size));
    rep(i, g_size)rep(j, g_size) cin >> point[i][j];


    //出力文字列
    string result = "";
    //スコア(確認用)
    int score = point[si][sj];

    //現在地
    int ci = si, cj = sj;
    //各タイルが通過済みかどうか
    vector<int> used(tile_size, false);
    //ランダムに移動できるだけ移動する(最大1250回？)
    while(d_cnt++ <= 99999){
        debug(ci, cj);
        //今いるタイルを使用済みにする
        used[tile_number[ci][cj]] = true;

        //ランダムに4方向移動する。
        //移動する順番を決める
        mt19937 get_rand_mt(d_cnt);
        shuffle(all(direction), get_rand_mt);
        //移動フラグ
        bool move = false;
        rep(i, 4){
            int nxi = ci + dy[direction[i]], nxj = cj + dx[direction[i]];
            if(nxi < 0 or nxj < 0 or nxi >= g_size or nxj >= g_size) continue; //画面外
            int next_time_num = tile_number[nxi][nxj];
            if(used[next_time_num] == false){ //移動可能
                move = true;
                ci = nxi, cj = nxj; //移動
                score += point[ci][cj]; //スコア加算
                result += direction_char[direction[i]]; //移動記録
                break;
            }
        }
        if(move == false) break;
    }

    //結果を出力
    cout << result << ln;
}

