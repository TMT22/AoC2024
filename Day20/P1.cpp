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
vector<vector<pll> > graph;
vl distances;
vl previous;

vector<string> board;

pll start_coor, end_corr;

bool in_board(pll pos){
  return pos.xx >= 0 && pos.xx < m && pos.yy < n && pos.yy >= 0;
}

void run_dijkstra(){
  std::priority_queue<pair<pll, ll>, std::vector<pair<pll, ll> >, std::greater<pair<pll, ll> > > q;
  
  distances = vl(graph.size(), oo);
  previous = vl(graph.size(), -1);

  pll start = mp(0, start_coor.yy*m + start_coor.xx);

  q.push(mp(start, -1));

  while(!q.empty()){
    pair<pll, ll> curr_content = q.top(); q.pop();

    pll curr = curr_content.xx;
    ll prev_node = curr_content.yy;

    if(distances[curr.yy] <= curr.xx) continue;


    distances[curr.yy] = curr.xx;
    previous[curr.yy] = prev_node;

    FOR(j, 0, graph[curr.yy].size()){

      pll next = graph[curr.yy][j];

      ll dist = next.xx;
      ll next_node = next.yy;

      if(distances[curr.yy]+dist < distances[next_node]){
        q.push(mp(mp(distances[curr.yy]+dist, next_node), curr.yy));

      }

    }
  }
}

ll pos_to_save(pll pos){
  if(board[pos.yy][pos.xx] == '#') return 0;
  ll total = 0;

  FOR(i, -2, 3)FOR(j, -2, 3){
    if(abs(i)+abs(j) != 2) continue;

    pll next_pos = mp(pos.xx+i, pos.yy+j);

    if(!in_board(next_pos)) continue;
    if(board[next_pos.yy][next_pos.xx] == '#') continue;

    ll saved = distances[next_pos.yy*m + next_pos.xx] - distances[pos.yy*m + pos.xx] - 2;
    if(saved >= 100) total++;
  }


  return total;



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


  graph = vector<vector<pll> >(n*m, vector<pll>());


  FOR(y, 0, n)FOR(x, 0, m) {
    if(board[y][x] == '#') continue;

    if(board[y-1][x] != '#') graph[y*m+x].pb(mp(1, (y-1)*m+x));
    if(board[y+1][x] != '#') graph[y*m+x].pb(mp(1, (y+1)*m+x));
    if(board[y][x-1] != '#') graph[y*m+x].pb(mp(1, y*m+(x-1)));
    if(board[y][x+1] != '#') graph[y*m+x].pb(mp(1, y*m+(x+1)));

    if(board[y][x] == 'S') start_coor = mp(x, y);
    if(board[y][x] == 'E') end_corr = mp(x, y);
  }

  run_dijkstra();

  ll total = 0;
  FOR(y, 0, n)FOR(x, 0, m){
      total += pos_to_save(mp(x, y));
  }




  cout << "Total: "<< total << endl;

}

