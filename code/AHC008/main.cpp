#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
constexpr char ln =  '\n';
constexpr int INF = 2e9+100;
constexpr long long LLINF = 3e18;
#define all(v) v.begin(), v.end()
#define rep(i, n) for(int i=0;i<(n);i++)
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return true; } return false; }
template<typename T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T> inline void UNIQUE(vector<T>& v) { v.erase(unique(v.begin(), v.end()), v.end()); }
inline ll CEIL(ll a, ll b){return (a+b-1) / b;}

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

// 中央で二分割するだけ。
// 評価
// 作業員は一人いれば十分と踏んで、他の人は上下端に寄ってもらった

const int TURN = 300; //ターン数
const int SIZE = 30; //グリッドサイズ
const int dy[4]={0,1,0,-1};
const int dx[4]={-1,0,1,0};
const string destroy_direction = "urdl"; //マス破壊に対応した文字
const string move_direction = "URDL";
bool inside(int x, int y){return x >= 0 and x < SIZE and y >= 0 and y < SIZE;}

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

//入力データ
int N, M;
vector<int> px, py, pt, hx, hy;

//盤面の通行情報
//0:空き -1:通行不能 1:移動予約（そのターンに誰かが移動する予定。破壊不可）
vector grid(SIZE, vector<int>(SIZE));

//ランダムな移動方向を返す。移動可能なマスがなければ-1を返す
int getDirection(int x, int y){
    vector<int> dir;
    for(int k=0; k<4; k++){
        int nx = x+dx[k], ny = y+dy[k];
        if(!inside(nx, ny)) continue;
        if(grid[nx][ny] == -1) continue;
        dir.push_back(k);
    }
    if(dir.empty()) return -1;
    int r = randXor() % (int)dir.size();
    return dir[r];
}

//指定されたマスにペットがいるか調べる。いればtrue
bool existPet(int x, int y){
    for(int i=0; i<N; i++){
        if(x == px[i] and y == py[i]){
            return true;
        }
    }
    return false;
}

//指定されたマスに人間がいるか調べる。いればtrue
bool existPerson(int x, int y){
    for(int i=0; i<M; i++){
        if(x == hx[i] and y == hy[i]){
            return true;
        }
    }
    return false;
}

//各人のスコア計算
double calcScore(int hx, int hy){
    int R = 0, pet_count = 0;
    //bfs
    queue<pii> que; que.push({hx, hy});
    vector seen(SIZE, vector<bool>(SIZE)); seen[hx][hy] = true;
    while(que.size()){
        auto [x, y] = que.front(); que.pop();
        R++;
        if(existPet(x, y))pet_count++; //ペットがいれば数える
        for(int k=0; k<4; k++){
            int nx = x+dx[k], ny = y+dy[k];
            if(!inside(nx, ny))continue;
            if(grid[nx][ny] == -1)continue; //通行不能
            seen[nx][ny] = true;
            que.push({nx, ny});
        }
    }
    return(R / 900.0) * pow(2, -pet_count);
}

//総合スコア計算
ll calcSumScore(){
    double score = 0;
    for(int i=0; i<M; i++){
        score += calcScore(hx[i], hy[i]);
    }
    score /= M;
    ll ret = round(1e8 * score);
    return ret;
}

//入力を受け取る
void input(){
    cin >> N;
    px.resize(N); py.resize(N); pt.resize(N);
    for(int i=0; i<N; i++){
        cin >> px[i] >> py[i] >> pt[i]; px[i]--, py[i]--;
    }
    cin >> M;
    hx.resize(M); hy.resize(M);
    for(int i=0; i<M; i++){
        cin >> hx[i] >> hy[i]; hx[i]--, hy[i]--;
    }
}

//マスが埋め立て可能か判定する
bool isUmetate(int x, int y){
    //人がいれば埋められない
    for(int i=0; i<M; i++){
        if(x == hx[i] and y == hy[i]){
            return false;
        }
    }
    //ペットがいれば埋められない
    for(int i=0; i<N; i++){
        if(x == px[i] and y == py[i]){
            return false;
        }
    }
    //隣接4方向にペットがいれば埋められない
    for(int k=0; k<4; k++){
        int nx = x+dx[k], ny = y+dy[k];
        if(!inside(nx, ny)) continue;
        for(int i=0; i<N; i++){
            if(nx == px[i] and ny == py[i]){
                return false;
            }
        }
    }
    return true;
}


void solve(){
    int step = 0;
    if(hx[0] == 13 and hy[0] == 0) step += 1; //最初から(13,0)にいた場合
    for(int turn = 0; turn < TURN; turn++){
        string order = ""; //そのターンの行動

        for(int i=0; i<M; i++){
            if(i == 0){
                //(13, 0)に移動する
                if(step == 0){
                    if(hx[i] != 13){
                        if(hx[i] < 13){
                            hx[i]++;
                            order += "D";
                        }
                        else{
                            hx[i]--;
                            order += "U";
                        }
                    }
                    else{
                        if(hy[i] > 0){
                            hy[i]--;
                            order += "L";
                        }
                    }
                    //ステップ確認
                    if(hx[i] == 13 and hy[i] == 0)step += 1;
                }
                //(x,14)を埋める
                else if(step == 1){
                    //端から端まで埋める
                    //まだ埋め立てられていない
                    if(grid[hx[i]+1][hy[i]] != -1){
                        //埋め立て可能なら埋める
                        if(isUmetate(hx[i]+1, hy[i])){
                            grid[hx[i]+1][hy[i]] = -1;
                            order += "d";
                        }
                        //埋め立て不可能なら何もしない
                        else{
                            order += ".";
                        }
                    }
                    //既に埋め立てられている
                    else{
                        if(hy[i] == SIZE - 1){
                            step += 1;
                            order += ".";
                        }
                        else{
                            hy[i]++;
                            order += "R";
                        }
                    }
                }
                //工事完了です……
                else{
                    order += ".";
                }
            }
            //一人以外は上下の近い方の端に退避してもらう
            else{
                if(hx[i] > 0 and hx[i] <= 14){ 
                    hx[i]--;
                    order += "U";
                }
                else if(hx[i] > 14 and hx[i] < SIZE - 1){
                    hx[i]++;
                    order += "D";
                }
                else{
                    order += ".";
                }
            }

        }
        cout << order << flush << ln;

        //ペットの移動
        for(int i=0; i<N; i++){
            debug(px[i], py[i]);
            string pet_order; cin >> pet_order;
            if(pet_order == ".") continue;
            for(auto c : pet_order){
                int k = move_direction.find(c);
                //ペットの移動は必ず可能な範囲で与えられる？
                px[i] += dx[k], py[i] += dy[k];
            }
            debug(px[i], py[i]);
        }
    }
}

int main(){
    input();

    solve();
}
