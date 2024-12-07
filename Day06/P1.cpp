#include "../bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef pair<ll,ll> pll;
typedef vector<bool> vb;
const ll oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c), end(c)
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define FORD(i,a,b) for (ll i = (b)-1; i >= (a); i--)
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define TR(X) ({ if(1) cerr << "TR: " << (#X) << " = " << (X) << endl; })


vector<string> board;
ll n, m;

bool in_board(ll i, ll j){
  return 0 <= i && i < n && 0 <= j && j < m;
}

int main(){

  ios_base::sync_with_stdio (false);
  cin.tie(NULL);

  ifstream file("Inputs/Test01.txt");
  string str;
  board = vector<string>();
  while (std::getline(file, str)) board.pb(str);

  m = board[0].size();
  n = board.size();

  pll player_pos = mp(-1, -1);
  FOR(i, 0, n)FOR(j, 0, m) if(board[i][j] == '^') {
    player_pos = mp(j, i);
    board[i][j] = 'S';
  }


  ll player_dir_idx = 0;

  vector<pll> player_dirs = vector<pll>();
  player_dirs.pb(mp(0, -1)); // up
  player_dirs.pb(mp(1, 0)); // right
  player_dirs.pb(mp(0, 1)); // down
  player_dirs.pb(mp(-1, 0)); // left

  ll total = 1;


  while(in_board(player_pos.yy, player_pos.xx)){
    if(board[player_pos.yy][player_pos.xx] == '.') {
      total++;
      if(player_dir_idx == 0) board[player_pos.yy][player_pos.xx] = 'U';
      if(player_dir_idx == 1) board[player_pos.yy][player_pos.xx] = 'R';
      if(player_dir_idx == 2) board[player_pos.yy][player_pos.xx] = 'D';
      if(player_dir_idx == 3) board[player_pos.yy][player_pos.xx] = 'L';
    }
    pll next_pos = mp(player_pos.xx + player_dirs[player_dir_idx].xx, player_pos.yy + player_dirs[player_dir_idx].yy);

    while(in_board(next_pos.yy, next_pos.xx) && board[next_pos.yy][next_pos.xx] == '#'){
      player_dir_idx = (player_dir_idx + 1) % 4;
      next_pos = mp(player_pos.xx + player_dirs[player_dir_idx].xx, player_pos.yy + player_dirs[player_dir_idx].yy);
    }

    player_pos = next_pos;
  }
  FOR(i, 0, n) {
    cout << board[i] << endl;
  }

  cout << "Total: " << total << endl;




}

