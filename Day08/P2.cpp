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

int gcd(ll a, ll b){
    if(b==0) return a;
    else return gcd(b, a%b);
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
    
    cout << "-------" << endl;
    cout << it->first << " " << positions.size() << endl << endl;

    FOR(i, 0, positions.size())FOR(j, i+1, positions.size()){
      pll p1 = positions[i];
      pll p2 = positions[j];

      pll delta = mp(p2.xx - p1.xx, p2.yy - p1.yy);
      ll div = gcd(delta.xx, delta.yy);
      delta.xx /= div; delta.yy /= div;

      for(int k=0; k > -100; k--) {
        pll anti_p = mp(p1.xx - k * delta.xx, p1.yy - k * delta.yy);
        //cout << anti_p.xx << " " << anti_p.yy << endl;
        if(!in_board(anti_p)) break;
        antinodes.insert(anti_p);
      }

      for(int k=0; k < 100; k++) {
        pll anti_p = mp(p1.xx - k * delta.xx, p1.yy - k * delta.yy);
        //cout << anti_p.xx << " " << anti_p.yy << endl;
        if(!in_board(anti_p)) break;
        antinodes.insert(anti_p);
      }

    }
  }

  cout << "Total: " << antinodes.size() << endl;


}

