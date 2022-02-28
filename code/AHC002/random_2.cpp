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

//デバッグ用カウンタ
int d_cnt = 0;

const int G_SIZ = 50; //グリッドのサイズ
const int TILE_SIZ = 2500; //タイルの最大数
const int LIMIT_TIME = 190; //制限時間

const int di[4]={-1,0,1,0};
const int dj[4]={0,1,0,-1};

map<int, char> idx_to_char; //方向を文字に変換する辞書

/* 入力受取 */
int si, sj;//初期位置、現在位置
int max_score;
vector tile_idx(G_SIZ, vector<int>(G_SIZ)); //タイル番号
vector point(G_SIZ, vector<int>(G_SIZ)); //ポイント
vector<bool> used(TILE_SIZ); //タイルの使用済みフラグ
vector<int> direction{0,1,2,3}; //方向
string result; //出力

//乱数生成
int random(const int &MIN, const int &MAX){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX - 1);

    return distr(eng);
}

//前準備
void init(){
    idx_to_char[0] = 'U';
    idx_to_char[1] = 'R';
    idx_to_char[2] = 'D';
    idx_to_char[3] = 'L';

    max_score = 0;
}

//入力処理
void input(){
    cin >> si >> sj;
    rep(i, G_SIZ)rep(j, G_SIZ) cin >> tile_idx[i][j];
    rep(i, G_SIZ)rep(j, G_SIZ) cin >> point[i][j];
}
//出力処理
void output(){
    cout << result << ln;
}

//座標移動。
//上右下左に1マス移動したy座標、x座標を返す。
//移動先が壁であれば(-1, -1)を返す
//i,j:座標 dir:移動方向
pii move(int i, int j, int dir){
    pii ret = {i + di[dir], j + dj[dir]};
    if(ret.first < 0 or ret.first >= G_SIZ or ret.second < 0 or ret.second >= G_SIZ){
        return {-1, -1};
    }
    return ret;
}

//経路をひとつ構築する
//最大スコアが更新された場合、文字列も更新する
/* ランダム移動 */
void generate_route(){
    int score = 0;
    string order = "";
    used.assign(TILE_SIZ, false);
    int ci = si, cj = sj;

    while(true){
        used[tile_idx[ci][cj]] = true;
        score += point[ci][cj];
        mt19937 get_rand_mt(random(0,10000));
        shuffle(all(direction), get_rand_mt);

        bool ismove = false;
        rep(i, 4){
            auto [nxi, nxj] = move(ci, cj, direction[i]);
            if(nxi == -1)continue; //画面外判定
            //未踏のタイルなら移動し、ループを抜ける
            if(used[tile_idx[nxi][nxj]] == false){
                ismove = true;
                ci = nxi, cj = nxj;
                order += idx_to_char[direction[i]];
                break;
            }
        }
        if(ismove == false) break;
    }

    if(chmax(max_score, score) == true){
        result = order;
    }
}

int main(){
    input();
    init();

    //時間ギリギリまでスコアを更新する
    while(clock() * 100 / CLOCKS_PER_SEC <= LIMIT_TIME){
        generate_route();
    }

    output();
}

