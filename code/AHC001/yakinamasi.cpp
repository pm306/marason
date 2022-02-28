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
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return true; } return false; }
template<typename T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> inline void UNIQUE(vector<T>& v) { v.erase(unique(v.begin(), v.end()), v.end()); }
inline int popcount(ll x) { return __builtin_popcountll(x); }
inline ll CEIL(ll a, ll b){return (a+b-1) / b;}
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

//タイマー
bool timeCheck(int limit_time=190){return clock() * 100 / CLOCKS_PER_SEC <= limit_time;}

//[MIN, MAX)な乱数を返す
int random(const int &MIN, const int &MAX){
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX - 1);

    return distr(eng);
}

//0~1の乱数を返す
double random_d(double a=0, double b=1){
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(a, b);

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
void input_file(){
    ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    input();
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

//指定点の含有判定
//falseなら必ず0点
bool isGetScore(int idx){
    double X = x[idx] + 0.5, Y = y[idx] + 0.5;
    return a[idx] < X and X < c[idx] and b[idx] < Y and Y < d[idx];
}

//スコアの算出
//r:理想の面積 s:実際の面積
double calcScore(int idx){
    int area = calcArea(idx);
    return (1.0 - pow((1.0 - (double)min(area, r[idx]) / max(area, r[idx])), 2));
}

//最終スコアの算出
ll calcFinalScore(){
    long double ret = 0;
    for(int i=0; i<n; i++){
        ret += calcScore(i) / n  * 1e9;
    }
    ll result = round(ret);
    return result;
}

//枠外判定
//戻り値：枠内ならtrue
bool isInnerErea(int idx, int dir){
    switch (dir)
    {
    case 0:
        return a[idx] > 0;
    case 1:
        return d[idx] < EDGE_SIZE;
    case 2:
        return c[idx] < EDGE_SIZE;
    case 3:
        return b[idx] > 0;
    default:
        break;
    }
}

//1マス拡張
void expand(int idx, int dir){
    if(dir == 0)a[idx]--;
    if(dir == 1)d[idx]++;
    if(dir == 2)c[idx]++;
    if(dir == 3)b[idx]--;
}

//1マス縮小
void contract(int idx, int dir){
    if(dir == 0)a[idx]++;
    if(dir == 1)d[idx]--;
    if(dir == 2)c[idx]--;
    if(dir == 3)b[idx]++;
}

//衝突判定
bool isOrverlap(int idx){
    int x1 = a[idx] + c[idx];
    int y1 = b[idx] + d[idx];
    int height1 = (c[idx] - a[idx]) * 2;
    int width1 = (d[idx] - b[idx]) * 2;
    int col, x2, y2, height2, width2, dist, avg_width, avg_height;
    for(int i=0; i<n; i++){
        col = 0;
        if(idx == i)continue;
        //中心点、横幅、縦幅
        x2 = a[i] + c[i];
        y2 = b[i] + d[i];
        height2 = (c[i] - a[i]) * 2;
        width2 = (d[i] - b[i]) * 2;
        //横幅の検出
        dist = abs(y1 - y2) * 2;
        avg_width = width1 + width2;
        if(dist < avg_width)col++;
        //縦幅の検出
        dist = abs(x1 - x2) * 2;
        avg_height = height1 + height2;
        if(dist < avg_height)col++;
        if(col >= 2)return true;
    }

    return false;
}

//温度
//最初は確定、時間経過と共に線形に確率減少
bool isChange(){
    double temp = clock()/ (LIMIT_TIME * 10000.0);
    return temp <= random_d();
}

//拡張命令
void expandOrder(int idx, int dir){
    //はみ出す場合は何もしないで終了
    if(isInnerErea(idx, dir) == false)return;

    //変更前のスコアを計算
    double pre_score = calcScore(idx);

    //拡張する
    expand(idx, dir);
    //重なったら元に戻す
    if(isOrverlap(idx)){
        contract(idx, dir);
        return;
    }
    //スコアが悪化したら、一定確率で元に戻す
    double next_score = calcScore(idx);
    if(pre_score > next_score and !isChange()){
        contract(idx, dir);
    }
}

//平行移動命令
void moveOrder(int idx, int dir){
    //はみ出し判定
    if(isInnerErea(idx, dir) == false)return;

    //平行移動する
    //拡張
    expand(idx, dir);
    //他の広告と重なったら元に戻して終了
    if(isOrverlap(idx)){
        contract(idx, dir);
        return;
    }
    contract(idx, (dir+2)%4); //反対方向を1マス縮小する

    //必須となる点を抜ける場合は元に戻して終了
    if(!isGetScore(idx)){
        contract(idx, dir);
        expand(idx, (dir+2)%4);
    }
    //平行移動でスコアは下がらないので確率判定はしない
}
//縮小命令
void contractOrder(int idx, int dir){
    if(dir%2 == 0 and a[idx]+1 == c[idx] or dir%2 == 1 and b[idx]+1 == d[idx]){//これ以上縮小できない場合
        return;
    }
    double pre_score = calcScore(idx);
    //縮小する
    contract(idx, dir);

    double next_score = calcScore(idx);
    //スコアが下がった場合、一定確率で採用する。採用しない場合は元に戻す
    //必要点が範囲からなくなった場合は必ず元に戻す
    if(!isGetScore(idx) or pre_score > next_score and !isChange()){
        expand(idx, dir);
    }
}

//初期解。極小の広告を生成。
//戻り値：初期スコア
void init(){
    for(int i=0; i<n; i++){
        a[i] = x[i];
        b[i] = y[i];
        c[i] = x[i] + 1;
        d[i] = y[i] + 1;
    }
}

void solve(){
    init(); //極小の広告を出す
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distrA(0, n-1), distrB(0, 3), distrC(0, 2);

    ll cnt = 0;
    int idx, dir, order;
    while(++cnt){
        if(cnt % 20000 == 0 and timeCheck(LIMIT_TIME+3) == false)break;

        idx = distrA(eng); //加工する長方形
        dir = distrB(eng);//加工する方向
        order = distrC(eng);//加工内容。0:=拡大、1:=平行移動、2:=縮小

        if(order == 0){
            expandOrder(idx, dir);
        }
        else if(order == 1){
            moveOrder(idx, dir);
        }
        else if(order == 2){
            contractOrder(idx, dir);
        }
    }
    //debug(cnt);
}

int main(){
    input();
    //input_file();

    solve();

    output();
    //output_file();
    //cout << calcFinalScore() << ln;
}

