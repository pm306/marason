#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
constexpr char ln =  '\n';
constexpr int INF = 2e9+100;
constexpr long long LLINF = 3e18;
constexpr double EPS = 1e-9;
#define all(v) v.begin(), v.end()
#define rep(i, n) for(int i=0;i<(n);i++)
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a <= b) { a = b; return true; } return false; }
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

//乱数生成
static uint32_t randXor(){
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;

    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// 0以上1未満の小数をとる乱数
static double rand01(){return (randXor() + 0.5) * (1.0 / UINT_MAX);}

//タイマー
bool timeCheck(int limit_time){return clock() * 100 / CLOCKS_PER_SEC <= limit_time;}

//入力値
int n;
vector<int> X, Y, R;

//状態を保持する構造体
struct STATE{
    vector<int> a, b, c, d;
    STATE(){a.resize(n); b.resize(n); c.resize(n); d.resize(n);}
};

//入出力
void input(){
    cin >> n;
    X.resize(n); Y.resize(n); R.resize(n);
    for(int i=0; i<n; i++){
        cin >> X[i] >> Y[i] >> R[i];
    }
}
void input_file(){
    ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    input();
}
void output(STATE& state){
    for(int i=0; i<n; i++){
        cout << state.a[i] << " " << state.b[i] << " " << state.c[i] << " " << state.d[i] << ln;
    }
}
void output_file(STATE& state){
    ofstream writing_file;
    string filename = "output.txt";
    writing_file.open(filename, ios::out);
    for(int i=0; i<n; i++){
        writing_file << state.a[i] << " " << state.b[i] << " " << state.c[i] << " " << state.d[i] << ln;
    }
    writing_file.close();
}

//状態の初期化
void init(STATE& state){
    for(int i=0; i<n; i++){
        state.a[i] = X[i];
        state.b[i] = Y[i];
        state.c[i] = X[i] + 1;
        state.d[i] = Y[i] + 1;
    }
}

//状態のスコア計算(高速化なし)
ll calcAllScore(STATE& state){
    double score = 0;
    for(int i=0; i<n; i++){
        int area = (state.c[i] - state.a[i]) * (state.d[i] - state.b[i]);
        score += (1.0 - pow((1.0 - (double)min(area, R[i]) / max(area, R[i])), 2)) / n * 1e9;
    }
    return round(score);
}

//特定の広告のみのスコア計算
ll calcOneScore(int idx, STATE& state){
    double score = 0;
    int area =  (state.c[idx] - state.a[idx]) * (state.d[idx] - state.b[idx]);
    score += (1.0 - pow((1.0 - (double)min(area, R[idx]) / max(area, R[idx])), 2)) / n * 1e9;
    return round(score);
}

////////////////////////////////////////////////////////////////////////

//枠外判定
//戻り値：枠内ならtrue
bool isInnerErea(int idx, int dir, STATE& state){
    switch (dir)
    {
    case 0:
        return state.a[idx] > 0;
    case 1:
        return state.d[idx] < 10000;
    case 2:
        return state.c[idx] < 10000;
    case 3:
        return state.b[idx] > 0;
    default:
        break;
    }
}

//1マス拡張
void expand(int idx, int dir, STATE& state){
    switch (dir){
    case 0:
        state.a[idx]--;
        return;
    case 1:
        state.d[idx]++;
        return;
    case 2:
        state.c[idx]++;
        return;
    case 3:
        state.b[idx]--;
        return;
    default:
        break;
    }
}
//1マス縮小
void contract(int idx, int dir, STATE& state){
    switch (dir){
    case 0:
        state.a[idx]++;
        return;
    case 1:
        state.d[idx]--;
        return;
    case 2:
        state.c[idx]--;
        return;
    case 3:
        state.b[idx]++;
        return;
    default:
        break;
    }
}

//衝突判定
bool isOrverlap(int idx, STATE& state){
    int x1 = state.a[idx] + state.c[idx];
    int y1 = state.b[idx] + state.d[idx];
    int height1 = (state.c[idx] - state.a[idx]) * 2;
    int width1 = (state.d[idx] - state.b[idx]) * 2;
    int col, x2, y2, height2, width2, dist, avg_width, avg_height;
    for(int i=0; i<n; i++){
        col = 0;
        if(idx == i)continue;
        //中心点、横幅、縦幅
        x2 = state.a[i] + state.c[i];
        y2 = state.b[i] + state.d[i];
        height2 = (state.c[i] - state.a[i]) * 2;
        width2 = (state.d[i] - state.b[i]) * 2;
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

//指定点の含有判定
bool isGetScore(int idx, STATE& state){
    return state.a[idx] < X[idx] + 0.5 and X[idx] + 0.5 < state.c[idx] and state.b[idx] < Y[idx] + 0.5 and Y[idx] + 0.5 < state.d[idx];
}

//広告を１マス拡張する。拡張できない場合(スペースからはみ出るor他の広告と重なる)は変化させずにfalseを返す
bool expandOrder(int idx, int dir, STATE& state){
    //はみ出す場合は何もしないで終了
    if(isInnerErea(idx, dir, state) == false){
        return false;
    }

    //1マス拡張する
    expand(idx, dir, state);

    //他の長方形と重なったら元に戻す
    if(isOrverlap(idx, state)){
        contract(idx, dir, state);
        return false;
    }

    return true;
}

//平行移動命令
bool moveOrder(int idx, int dir, STATE& state){
    //はみ出し判定
    if(isInnerErea(idx, dir, state) == false){
        return false;
    }

    //平行移動する
    //拡張
    expand(idx, dir, state);
    //他の広告と重なったら元に戻して終了
    if(isOrverlap(idx, state)){
        contract(idx, dir, state);
        return false;
    }

    //平行移動 = 反対方向を1マス縮小する
    contract(idx, (dir+2)%4, state);

    //(x, y)から外れた場合は元に戻して終了
    if(isGetScore(idx, state) == false){
        contract(idx, dir, state);
        expand(idx, (dir+2)%4, state);
        return false;
    }
    return true;
}

//縮小命令
bool contractOrder(int idx, int dir, STATE& state){
    if(dir%2 == 0 and state.a[idx]+1 == state.c[idx] or dir%2 == 1 and state.b[idx]+1 == state.d[idx]){//これ以上縮小できない場合
        return false;
    }

    //縮小する
    contract(idx, dir, state);

    //(x,y)から外れた場合は元に戻して終了
    if(isGetScore(idx, state) == false){
        expand(idx, dir, state);
        return false;
    }
    return true;
}

STATE solve(){
    auto startClock = system_clock::now(); //開始時間を記録する
    const double TIME_LIMIT = 4.9;

    STATE state;
    init(state); //初期解を生成する

    //温度関数
    double start_temp = 10000;
    double end_temp = 100;
    double temp = start_temp;

    int idx, dir, order; //状態変化用の変数
    //ll steps = 0;
    double prob; //遷移確率変数
    while(true){
        //steps++;
        //制限時間を過ぎたら処理を打ち切る
        double now_time = duration_cast<microseconds>(system_clock::now() - startClock).count() * 1e-6;
        if(now_time >= TIME_LIMIT){
            break;
        }

        //ランダムに、状態に部分的な変化を加える
        idx = randXor() % n;
        dir = randXor() % 4;
        order = randXor() % 3;

        //更新前のスコアを得る
        ll cur_score = calcOneScore(idx, state);

        //温度の更新
        temp = start_temp + (end_temp - start_temp) * now_time / TIME_LIMIT;
        //if(steps % 100000 == 0)debug(temp, now_time);
        if(order == 0){
            //拡張
            if(expandOrder(idx, dir, state) == true){ //変更があった場合のみ処理を行う
                //スコアが上がったら採用する = スコアが上がらなければ一定確率で元に戻す
                ll new_score = calcOneScore(idx, state);
                if(chmax(cur_score, new_score) == false){
                    prob = exp((new_score-cur_score)/temp);
                    if(prob < rand01()){
                        contract(idx, dir, state);
                    }
                }
            }
        }
        else if(order == 1){
            moveOrder(idx, dir, state);
        }
        else if(order == 2){
            //縮小
            if(contractOrder(idx, dir, state) == true){
                ll new_score = calcOneScore(idx, state);
                //スコアが上がらなければ一定確率で元に戻す
                if(chmax(cur_score, new_score) == false){
                    prob = exp((new_score-cur_score)/temp);
                    if(prob < rand01()){
                        expand(idx, dir, state);
                    }
                }
            }
        }
    }
    //debug(steps);

    return state;
}

int main(){

    input();
    //input_file();

    STATE state = solve();

    //output(state);
    //output_file(state);
    cerr << calcAllScore(state) << ln;
}
