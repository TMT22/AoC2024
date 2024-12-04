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

bool check_mas(ll i, ll j){
  if(!in_board(i, j)) return false;
  if(!in_board(i+1, j+1)) return false;
  if(!in_board(i+1, j-1)) return false;
  if(!in_board(i-1, j+1)) return false;
  if(!in_board(i-1, j-1)) return false;


  if(board[i][j] != 'A') return false;
  if(!(board[i+1][j+1] == 'M' || board[i-1][j-1] == 'M')  ) return false;
  if(!(board[i+1][j+1] == 'S' || board[i-1][j-1] == 'S')  ) return false;

  if(!(board[i+1][j-1] == 'M' || board[i-1][j+1] == 'M')  ) return false;
  if(!(board[i+1][j-1] == 'S' || board[i-1][j+1] == 'S')  ) return false;

  if(!(board[i-1][j+1] == 'M' || board[i+1][j-1] == 'M')  ) return false;
  if(!(board[i-1][j+1] == 'S' || board[i+1][j-1] == 'S')  ) return false;

  if(!(board[i-1][j-1] == 'M' || board[i+1][j+1] == 'M')  ) return false;
  if(!(board[i-1][j-1] == 'S' || board[i+1][j+1] == 'S')  ) return false;

  return true;
}

int find_mas_at(ll i, ll j){
  if(check_mas(i, j)) {
    cout << i << ' ' << j << endl;
    return 1;
  }
  
  return 0;
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

  ll total = 0;
  FOR(i, 0, n)FOR(j, 0, m){
    total += find_mas_at(i, j);
  }

  cout << "Total: " << total << endl;



}

