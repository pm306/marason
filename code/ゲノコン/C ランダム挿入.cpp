#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
constexpr char ln =  '\n';
constexpr long long INF = 1LL<<60;
constexpr double EPS = 1e-9;
#define all(v) v.begin(), v.end()
#define rep(i, n) for(int i=0;i<(n);i++)
#define rept(i, j, n) for(int i=(j); i<(n); i++)
#define rrep(i, n) for(int i=(n)-1; i>=0; i--)
#define fore(i, a) for(auto &i:a)
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return true; } return false; }
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

const int NUM = 5;
int n, m;
unordered_map<char, int> genom;
ll score(vector<string> &S){
    ll sum_score = 0;
    rep(j, n){
        vector<int> cnt(5);
        rep(i, m){
            int idx = genom[S[i][j]];
            cnt[idx]++;
        }
        sum_score += accumulate(all(cnt), 0) - *max_element(all(cnt));
    }
    return sum_score;
}

void init(){
    genom['A'] = 0;
    genom['G'] = 1;
    genom['C'] = 2;
    genom['T'] = 3;
    genom['-'] = 4;
}

int main() {
    init(); //mapの準備

    // //MAXテスト
    // m = 40;
    // vector<string> S(m);
    // int siz = 750;
    // n = siz;
    // rep(i, m){
    //     //1つめは750文字。残りは1文字ずつ減らしていく
    //     rep(j, siz){
    //         S[i] += "A";
    //     }
    //     siz--;
    // }

    //input
    cin >> m;
    vector<string> S(m);
    rep(i, m){
        cin >> S[i];
        chmax(n, (int)S[i].size()); //最大文字長を得る
    }

    //乱数準備
    random_device rd;
    default_random_engine eng(rd());

    //一番良い結果を保存しておく
    ll min_score = INF;
    vector<string> res;

    //時間ギリまで回す
    //int cnt_time = 0; //計測用、本番は切る
    while(clock() / CLOCKS_PER_SEC < 8){ //とりあえず8秒
        //cnt_time++;

        //ゲノム構築
        vector<string> T(m);
        rep(i, m){
            int cur_index = 0; //現在の文字インデックス
            int in = -1;
            int haifun = n - (int)S[i].size();
            rep(j, n){
                uniform_int_distribution<int> distr(1, n - j); // n - (既に見た文字)から等確率で1つ選択する
                in = distr(eng);
                //"-"を挿入する
                if(in <= haifun){
                    T[i] += "-";
                    haifun--;
                }
                //挿入しない
                else{
                    T[i] += S[i][cur_index++];
                }
            }
        }

        ll tmp_score = score(T);
        if(chmin(min_score, tmp_score))res = T;
    }

    fore(a, res){
        cout << a << endl;
    }
}

