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

//入力
int N;
vector<int> B(3);
vector<vector<int>> L, R, A;

void input(){
    cin >> N;
    for(int i=0; i<3; i++){
        cin >> B[i];
    }
    L.resize(N); R.resize(N);
    for(int i=0; i<N; i++){
        L[i].resize(N);
        R[i].resize(N);
    }
    for(int i=0; i<N; i++)for(int j=0; j<N; j++){
        cin >> L[i][j];
    }
    for(int i=0; i<N; i++)for(int j=0; j<N; j++){
        cin >> R[i][j];
    }
}

void input_file(){
    ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    input();
}

void init(){
    A.resize(N);
    for(int i=0; i<N; i++){
        A[i].resize(N);
    }
}

void output(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << A[i][j];
            if(j != N-1)cout << " ";
        }
        cout << ln;
    }
}

//横１列をなめて、得点がBと合致する数を返す
tuple<int, int, int> cntYoko(vector<vector<int>> &grid, int h){
    int num;
    map<int, int> counter;
    for(int l=0; l<N-1; l++){
        num = 0;
        for(int r=l+1; r<=N; r++){
            num += grid[h][r-1];
            counter[num]++;
        }
    }
    return {counter[B[0]], counter[B[1]], counter[B[2]]};
}
//縦１列をなめて、得点がBと合致する数を返す
tuple<int, int, int> cntTate(vector<vector<int>> &grid, int w){
    int num;
    map<int, int> counter;
    for(int u=0; u<N-1; u++){
        num = 0;
        for(int d=u+1; d<=N; d++){
            num += grid[d-1][w];
            counter[num]++;
        }
    }
    return {counter[B[0]], counter[B[1]], counter[B[2]]};
}

int calcScore(vector<vector<int>> &grid){
    vector<int> cnt(3);

    for(int i=0; i<N; i++){
        auto [a, b, c] = cntYoko(grid, i);
        cnt[0] += a;
        cnt[1] += b;
        cnt[2] += c;
    }
    for(int i=0; i<N; i++){
        auto [a, b, c] = cntTate(grid, i);
        cnt[0] += a;
        cnt[1] += b;
        cnt[2] += c;
    }

    return cnt[0] * B[0] + cnt[1] * B[1] + cnt[2] * B[2];
}

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

const int LIMIT_TIME = 280;
bool timeCheck(){return clock() * 100 / CLOCKS_PER_SEC <= LIMIT_TIME;}

int main(){
    input();
    init();

    int max_score = 0;
    while(timeCheck()){
    vector AA(N, vector<int>(N));
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                AA[i][j] = clamp((int)(randXor() % 9 + 1), L[i][j], R[i][j]);
            }
        }

        int score = calcScore(AA);
        if(chmax(max_score, score)){
            A = AA;
        }
    }
    debug(max_score);

    output();
}
