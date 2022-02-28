#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()
constexpr char ln =  '\n';
template <class T1, class T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return true; } return false; }

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

//定数
//ターン数。300で固定
const int TURN = 300;
//盤面の大きさ。行、列ともに30で固定
const int GRID_SIZE = 30;
//極大な定数
const int INF = INT_MAX / 2;
//人間の行動モードを表す定数
const int JUNBI = 1;
const int SAGYOU = 2;
const int TOJIKOME = 3;

//4方向移動用の関数と配列。順に上、右、下、左
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
//移動後の配列を返す。個別に受け取れないが、バグりづらい。
pair<int, int> fourwayMove(int x, int y, int k){return {x + dx[k], y + dy[k]};}
//座標がグリッド枠内か判定する
bool inside(int x, int y){return x >= 0 and x < GRID_SIZE and y >= 0 and y < GRID_SIZE;}
//(x1, y1)と(x2, y2)のマンハッタン距離を返す
int getManhattanDistance(int x1, int y1, int x2, int y2){return abs(x1 - x2) + abs(y1 - y2);}

/////////////////////////////////////////////////////////////////////////////////////////////////////

//入力受取用の変数。N:=ペットの数、M:=人間の数
int N, M;
//出力用の文字列
string order;
//参照する文字列
const string destructDirectionStr = "urdl";
const string moveDirectionStr = "URDL";

///////////////////////////////////////////////////////////////////////////////////////////////////

//場の状態を表す配列
//0:移動、破壊共に可能 -1:破壊済み 1:移動のみ可能(同一ターンに他のユニットが移動する。使わないかも)
int grid_state[GRID_SIZE][GRID_SIZE];
//場の人間の数を記録する配列
int count_human[GRID_SIZE][GRID_SIZE];
//場のペットの数を記録する配列
int count_pet[GRID_SIZE][GRID_SIZE];

//区画番号と入り口番号を引数に取り、作業開始地点の座標を返す
//section_id:区間番号(0~29) point_id:開始地点番号(0~1)
pair<int, int> getDestcutStartPoint(int section_id, int point_id){
    //左側
    pair<int, int> ret;
    if(section_id % 3 == 0){
        if(point_id == 0){
            ret = {section_id, 6};
        }
        else{
            ret = {section_id+1, 0};
        }
    }
    //中央
    else if(section_id % 3 == 1){
        if(point_id == 0){
            ret = {section_id-1, 9};
        }
        else{
            ret = {section_id-1, 19};
        }
    }
    //右側
    else{
        if(point_id == 0){
            ret = {section_id-2, 22};
        }
        else{
            ret = {section_id-1, 29};
        }
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//構造体：人間
struct Human{
    int x, y; //現在地
    int id; //入力No.命令を書き込む際に参照する
    //行動モード
    //なし、探索モード、整備モード、閉じ込めモードを識別する
    int mode = 0;
    //目的地/整備地番号。探索モード、整備モード時に参照する
    int as_number = -1; //assignment number

    //コンストラクタ
    Human(int x_, int y_, int id_){
        x = x_; y = y_; id = id_;
        count_human[x][y]++;
    }
    
    //移動or破壊命令を書き込む
    void writeOrder(char c='.'){
        order[id] = c;
    }

    //方向kに隣接するマスに移動する。移動できればtrue、できなければfalseを返す
    bool move(int k){
        auto [nx, ny] = fourwayMove(x, y, k);
        if(inside(nx, ny) and grid_state[nx][ny] != -1){
            count_human[x][y]--; count_human[nx][ny]++;
            x = nx; y = ny;
            writeOrder(moveDirectionStr[k]);
            return true;
        }
        return false;
    }

    //指定のマスが破壊可能か調べる
    bool checkIsDestruct(int x_, int y_){
        if(count_human[x_][y_] > 0 or count_pet[x_][y_] > 0) return false;
        for(int k=0; k<4; k++){
            auto [nx, ny] = fourwayMove(x_, y_, k);
            if(!inside(nx, ny)) continue;
            if(count_pet[nx][ny] > 0) return false;
        }
        return true;
    }

    //方向kに隣接するマスを破壊する。破壊できればture、できなければfalseを返す
    bool destruct(int k){
       auto [nx, ny] = fourwayMove(x, y, k);
        if(inside(nx, ny) and grid_state[nx][ny] != -1 and checkIsDestruct(nx, ny)){
            grid_state[nx][ny] = -1;
            writeOrder(destructDirectionStr[k]);
            return true;
        }
        return false;
    }

    //その場に待機する。特に何もしないので、要らないかも。
    bool wait(){return true;}
};

//構造体：ペット
//指示通りに動くだけなので単純なつくり
struct Pet{
    int x, y; //現在地
    //※ペットは命令を与えないのでID不要
    int type; //ペットの種類。今のところ不要なステータス

    //コンストラクタ
    Pet(int x_, int y_, int t) : x{x_}, y{y_}, type{t}{
        count_pet[x][y]++;
    };

    //与えられた命令に従って移動する
    void move(string& order){
        for(auto& c : order){
            int k = moveDirectionStr.find(c);
            if(k == -1) continue; //停止命令
            auto [nx, ny] = fourwayMove(x, y, k);
            count_pet[x][y]--; count_pet[nx][ny]++;
            x = nx; y = ny;
        }
    }
};

//人間を格納する配列
vector<Human> humans;
//ペットを格納する配列
vector<Pet> pets;

//////////////////////////////////////////////////////////////////////////////////////////////////////

//試作。
//60個の作業に人員を配備する。
//整備したら下方向を破壊して、目的地を解除する。
//試作なので、目的地に着いたらすぐ次に移る。
const int START_POINT_NUMBER = 30, START_POINT_TYPE = 2; //30区画番号と、区画ごとの目的地数
// 区画の状態を表す整数
// -INF:未整備・人員未設定
// 0~9:未整備・人員設定済み、未到着(human.idを負の値で格納)
// 10:作業中
// INF:整備完了
int start_point_state[START_POINT_NUMBER][START_POINT_TYPE];
//開始地点の座標を格納する
pair<int, int> start_point_vertex[START_POINT_NUMBER][START_POINT_TYPE];
void initTrialHumanMove(){
    //初期化
    for(int i=0; i<START_POINT_NUMBER; i++){
        for(int j=0; j<START_POINT_TYPE; j++){
            start_point_state[i][j] = -INF;
            start_point_vertex[i][j] = 
        }
    }
}
void trialHumanMove(){
    //目的地設定フェーズ
    //全ての目的地を最適化する。
    vector<bool> selected(M, false);
    for(int start_point=0; start_point<START_POINT_NUMBER; start_point++){
        for(int point_type=0; point_type<START_POINT_TYPE; point_type++){
            //未整備 or 接近中 の場合、紐づける人間の最適化を行う
            if(start_point_state[start_point][point_type] < 10){
                //評価値。マンハッタン距離を用いる。
                int min_score = INF;
                //候補者のid。誰もいなければ-1
                int cand_id = -1;
                for(int m=0; m<M; m++){
                    auto& human = humans[m];
                    //作業モードの人間は対象外
                    if(human.mode == SAGYOU) continue;
                    //このフェーズで既に目的地を設定している場合は二重設定しない
                    if(selected[human.id]) continue;
                    int dist = getManhattanDistance()
                }
            }
            //整備中 or 整備完了 の場合、何もしない
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//入力処理
void input(){
    cin >> N;
    int x, y, t;
    for(int i=0; i<N; i++){
        cin >> x >> y >> t; x--, y--;
        Pet pet(x, y, t);
        pets.emplace_back(pet);
    }
    cin >> M;
    for(int i=0; i<M; i++){
        cin >> x >> y; x--, y--;
        Human human(x, y, i);
        //TODO:一番近い持ち場を求めるアルゴリズム書くかも
        humans.emplace_back(human);
    }
}



//入力チェック
// void inputCheck(){
//     cout << "-----------pet-----------------" << ln;
//     for(auto& pet : pets){
//         cout << pet.x << " " << pet.y << " " << pet.type << ln;
//     }
//     cout << "-----------human---------------" << ln;
//     for(auto& human : humans){
//         cout << human.x << " " << human.y << ln;
//     }
// }

//ペット移動チェック
// void petMoveCheck(){
//     for(auto &pet : pets){
//         cout << pet.x << " " << pet.y << ln;
//     }
// }

//乱数生成器
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
//0以上x未満の乱数を返す
int randint(int x){ return randXor() % x;}

//メイン処理
void humanAct(){
    //命令の初期化。待機で埋める
    order.clear();
    for(int i=0; i<M; i++)order += ".";

    // for(int i=0; i<M; i++){
        //auto& human = humans[i];

        //動作チェック。ランダムに移動または添削する
        // int act = randXor() % 11;
        // int dir = randXor() % 4;
        // if(act < 7){
        //     human.move(dir);
        // }
        // else if(act < 8){
        //     human.destruct(dir);
        // }
        // else{
        //     human.wait();
        // }
    // }

    //命令出力
    cout << order << flush << ln;
}

void petAct(){
    string pet_order;
    for(int i=0; i<N; i++){
        cin >> pet_order;
        if(pet_order == ".") continue;
        pets[i].move(pet_order); //命令に沿って移動させる
    }
}

int main(){
    input();

    for(int turn=0; turn<TURN; turn++){
        humanAct();
        petAct();
    }
}

