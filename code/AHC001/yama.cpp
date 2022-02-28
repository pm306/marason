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

const int EDGE_SIZE = 10000;
const int LIMIT_TIME = 490;

int d_cnt = 0;

//入出力用
int n;
vector<int> x, y, r;
vector<int> a, b, c, d;


bool timeCheck(){return clock() * 100 / CLOCKS_PER_SEC <= LIMIT_TIME;}

//[MIN, MAX)な乱数を返す
int random(const int &MIN, const int &MAX){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX - 1);

    return distr(eng);
}

void input(){
    cin >> n;
    x.resize(n); y.resize(n); r.resize(n);
    //出力用配列の準備
    a.resize(n); b.resize(n); c.resize(n); d.resize(n);
    for(int i=0; i<n; i++){
        cin >> x[i] >> y[i] >> r[i];
    }
}

//出力用
void output(){
    for(int i=0; i<n; i++){
        cout << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << ln << flush;
    }
}
void output_file(){
    ofstream writing_file;
    string filename = "output.txt";
    writing_file.open(filename, ios::out);
    for(int i=0; i<n; i++){
        writing_file << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << ln;
    }
    writing_file.close();
}


//長方形の面積を返す
int calcArea(int idx){
    return (c[idx] - a[idx]) * (d[idx] - b[idx]);
}

//スコアの算出
//r:理想の面積 s:実際の面積
double calcScore(double r, double s){
    return (1.0 - pow((1.0 - min(s, r) / max(s, r)), 2)) / n * 1e9;
}

//i番目の長方形を指定の方向に1マスぶん拡張する。はみ出し判定あり。
//i:=長方形の番号, dir:=拡張する方向
//戻り値：はみ出さなければtrue, はみ出したらfalse。
bool scale(int i, int dir){
    switch (dir)
    {
    case 0: //上
        if(a[i] <= 0)return false;
        a[i]--;
        break;
    case 1: //右
        if(d[i] >= EDGE_SIZE)return false;
        d[i]++;
        break;
    case 2: //下
        if(c[i] >= EDGE_SIZE)return false;
        c[i]++;
        break;
    case 3: //左
        if(b[i] <= 0)return false;
        b[i]--;
        break;
    default:
        break;
    }
    return true;
}

//拡張した長方形を元に戻す
void undo(int i, int dir){
    switch (dir)
    {
    case 0:
        a[i]++;
        break;
    case 1:
        d[i]--;
        break;
    case 2:
        c[i]--;
        break;
    case 3:
        b[i]++;
        break;
    default:
        break;
    }
}

//衝突判定。長方形が他の長方形と重なっていないか判定する。
//idx:=判定する長方形の番号
//戻り値：重なっていればtrue, 重なっていなければfalse
bool isOrverlap(int idx){
    int x1 = a[idx] + c[idx];
    int y1 = b[idx] + d[idx];
    int height1 = (c[idx] - a[idx]) * 2;
    int width1 = (d[idx] - b[idx]) * 2;
    for(int i=0; i<n; i++){
        int col = 0;
        if(idx == i)continue;
        //中心点、横幅、縦幅
        int x2 = a[i] + c[i];
        int y2 = b[i] + d[i];
        int height2 = (c[i] - a[i]) * 2;
        int width2 = (d[i] - b[i]) * 2;
        //横幅の検出
        int dist = abs(y1 - y2) * 2;
        int avg_width = width1 + width2;
        if(dist < avg_width)col++;
        //縦幅の検出
        dist = abs(x1 - x2) * 2;
        int avg_height = height1 + height2;
        if(dist < avg_height)col++;
        if(col >= 2)return true;
    }

    return false;
}

//初期解。極小の広告を生成。
//戻り値：初期スコア
ll init(){
    double score = 0;
    for(int i=0; i<n; i++){
        a[i] = x[i];
        b[i] = y[i];
        c[i] = x[i] + 1;
        d[i] = y[i] + 1;

        score += calcScore(r[i], 1.0);
    }

    ll ret = round(score);
    return ret;
}

//山登り法
void tozan_method(){
    init(); //極小の広告を出す

    while(timeCheck()){
        int ad_idx = random(0, n); //拡張する長方形
        int dir = random(0, 4); //拡張する方向
        double pre_score = calcScore(r[ad_idx], calcArea(ad_idx));

        if(scale(ad_idx, dir) == false){//はみ出したら取りやめ。はみださなければ拡張する
            continue;
        }
        if(isOrverlap(ad_idx)){ //他の長方形と衝突するなら取りやめ
            undo(ad_idx, dir); //元に戻す
            continue;
        }
        //スコアが悪化するなら取りやめ
        double next_score = calcScore(r[ad_idx], calcArea(ad_idx));
        if(pre_score > next_score){
            undo(ad_idx, dir);
        }
    }
}

int main(){
    input();

    tozan_method();

    output();
}

