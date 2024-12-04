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

bool check_xmas(ll i, ll j, ll add_i, ll add_j){
  FOR(k, 0, 4){
    if(!in_board(i+k*add_i, j+k*add_j)) return false;
  }

  if(board[i][j] != 'X') return false;
  if(board[i+1*add_i][j+1*add_j] != 'M') return false;
  if(board[i+2*add_i][j+2*add_j] != 'A') return false;
  if(board[i+3*add_i][j+3*add_j] != 'S') return false;

  return true;
}

int find_xmas_at(ll i, ll j){
  ll sum = 0;

  if(check_xmas(i, j, 1, 0)) sum++;
  if(check_xmas(i, j, -1, 0)) sum++;
  if(check_xmas(i, j, 0, 1)) sum++;
  if(check_xmas(i, j, 0, -1)) sum++;

  if(check_xmas(i, j, 1, 1)) sum++;
  if(check_xmas(i, j, 1, -1)) sum++;
  if(check_xmas(i, j, -1, 1)) sum++;
  if(check_xmas(i, j, -1, -1)) sum++;

  return sum;
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
    total += find_xmas_at(i, j);
  }

  cout << "Total: " << total << endl;



}

