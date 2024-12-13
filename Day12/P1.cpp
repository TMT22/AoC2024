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

ll n, m;
vector<string> board;

vvl region_ids;
vvl perimeter_scores;

map<ll, pll> regions; // Area, perimeter




bool in_board(ll x, ll y){
  return x >= 0 && y >= 0 && x < m && y < n;
}

void flood_fill(ll start_x, ll start_y, ll region_id){
  char chr = board[start_y][start_x];

  queue<pll> nodes;
  nodes.push(mp(start_x, start_y));
  region_ids[start_y][start_x] = region_id;

  ll total_area = 0;
  ll total_perimeter = 0;

  while(!nodes.empty()){
    queue<pll> next_nodes;
    while(!nodes.empty()){
      pll curr = nodes.front(); nodes.pop();

      perimeter_scores[curr.yy][curr.xx] = 4;


      FOR(i, -1, 2)FOR(j, -1, 2){
        if(abs(i) == abs(j)) continue;


        if(!in_board(curr.xx-i, curr.yy-j)) continue;
        if(chr != board[curr.yy-j][curr.xx-i]) continue;

        perimeter_scores[curr.yy][curr.xx]--;

        if(region_ids[curr.yy-j][curr.xx-i] != -1) continue;

        
        region_ids[curr.yy-j][curr.xx-i] = region_id;
        next_nodes.push(mp(curr.xx-i, curr.yy-j));
      }

      total_area++;
      total_perimeter += perimeter_scores[curr.yy][curr.xx];

    }

    nodes = next_nodes;
  }

  cout << chr << ": " << total_area << " " << total_perimeter << endl;
  regions[region_id] = mp(total_area, total_perimeter);

}

int main(){

  ios_base::sync_with_stdio (false);
  cin.tie(NULL);

  ifstream file("Inputs/Test01.txt");
  string str;
  board = vector<string>();
  while (std::getline(file, str)) board.pb(str);

  n = board.size();
  m = board[0].size();

  region_ids = vvl(n, vl(m, -1));
  perimeter_scores = vvl(n, vl(m, -1));


  ll region_counter = 0;

  FOR(y, 0, n)FOR(x, 0, m){
    if(region_ids[y][x] != -1) continue;
    
    flood_fill(x, y, region_counter);
    region_counter++;
  }

  cout << endl;


  ll total = 0;
  for (auto const& x : regions) {
    total+= x.yy.xx * x.yy.yy;
  }

  cout << "Total: " << total << endl;

}

