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

map<char, vector<pll> > frequencies_map;

bool in_board(pll pos){
  return pos.xx >= 0 && pos.yy >= 0 && pos.xx < m && pos.yy < n;
}

int main(){

  ios_base::sync_with_stdio (false);
  cin.tie(NULL);

  ifstream file("Inputs/Test01.txt");
  string str;
  board = vector<string>();
  while (std::getline(file, str)) board.pb(str);

  n = board.size(); m = board[0].size();
  cout << n << " " << m << endl;

  frequencies_map = map<char, vector<pll> >();

  FOR(i, 0, n)FOR(j, 0, m) if(board[i][j] != '.') {
    if(frequencies_map.count(board[i][j]) == 0){
      frequencies_map.insert(mp(board[i][j], vector<pll>()));
    } 
    
    frequencies_map[board[i][j]].pb(mp(j, i));
  }

  set<pll> antinodes;


  for (auto it = frequencies_map.begin(); it != frequencies_map.end(); it++) {
    char freq = it->first;
    vector<pll> positions = it->second;
    
    cout << it->first << " " << positions.size() <<  endl;

    FOR(i, 0, positions.size())FOR(j, i+1, positions.size()){
      pll p1 = positions[i];
      pll p2 = positions[j];

      pll dist = mp(p2.xx - p1.xx, p2.yy - p1.yy);

      pll anti_p1 = mp(p1.xx - dist.xx, p1.yy - dist.yy);
      pll anti_p2 = mp(p2.xx + dist.xx, p2.yy + dist.yy);

      if(in_board(anti_p1)) antinodes.insert(anti_p1);
      if(in_board(anti_p2)) antinodes.insert(anti_p2);
    }
  }

  cout << "Total: " << antinodes.size() << endl;


}

