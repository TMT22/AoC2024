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
pll player_start;
vector<pll> to_check;
vector<pll> player_dirs;

ll n, m;

bool in_board(ll i, ll j){
  return 0 <= i && i < n && 0 <= j && j < m;
}
void clean_board(){
  FOR(i, 0, n)FOR(j, 0, m) if(board[i][j] != '^' && board[i][j] != '#') board[i][j] = '.';
}

bool run_loops(bool save_seen_positions){
  pll player_pos = player_start;
  ll player_dir_idx = 0;
  vector<vector<vb> > board_check = vector<vector<vb> >(n, vector<vb>(m, vb(4, false)));
  
  while(in_board(player_pos.yy, player_pos.xx)){
    // Run loops
    if(board_check[player_pos.yy][player_pos.xx][player_dir_idx]) return true;


    board_check[player_pos.yy][player_pos.xx][player_dir_idx] = true;

    if(save_seen_positions && board[player_pos.yy][player_pos.xx] == '.') {
      to_check.pb(player_pos);

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

  return false;
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

  to_check = vector<pll>();

  player_start = mp(-1, -1);
  FOR(i, 0, n)FOR(j, 0, m) if(board[i][j] == '^') {
    player_start = mp(j, i);
  }

  player_dirs = vector<pll>();

  player_dirs.pb(mp(0, -1)); // up
  player_dirs.pb(mp(1, 0)); // right
  player_dirs.pb(mp(0, 1)); // down
  player_dirs.pb(mp(-1, 0)); // left

  

  // Find positions to check
  run_loops(true);
  clean_board();
  FOR(i, 0, n) {
    cout << board[i] << endl;
  }


  // Check all positions
  ll total = 0;
  FOR(i, 0, to_check.size()){
    cout << to_check[i].xx << " " << to_check[i].yy << endl;
    if(to_check[i].xx == player_start.xx && to_check[i].yy == player_start.yy) continue;

    board[to_check[i].yy][to_check[i].xx] = '#';
    if(run_loops(false)) total += 1;
    board[to_check[i].yy][to_check[i].xx] = '.';

  }

  cout << "Total: " << total << endl;
}

