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

vl distances_end;
vl previous_end;

vector<string> board;

pll start_coor, end_corr;

void run_dijkstra_start(){
  std::priority_queue<pair<pll, ll>, std::vector<pair<pll, ll> >, std::greater<pair<pll, ll> > > q;
  
  distances = vl(graph.size(), oo);
  previous = vl(graph.size(), -1);

  pll start = mp(0, 4*(start_coor.yy*m + start_coor.xx)+1);

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

void run_dijkstra_end(){
  std::priority_queue<pair<pll, ll>, std::vector<pair<pll, ll> >, std::greater<pair<pll, ll> > > q;
  
  distances_end = vl(graph.size(), oo);
  previous_end = vl(graph.size(), -1);


  q.push(mp(mp(0, 4*(end_corr.yy*m + end_corr.xx)+0), -1));
  q.push(mp(mp(0, 4*(end_corr.yy*m + end_corr.xx)+1), -1));
  q.push(mp(mp(0, 4*(end_corr.yy*m + end_corr.xx)+2), -1));
  q.push(mp(mp(0, 4*(end_corr.yy*m + end_corr.xx)+3), -1));


  while(!q.empty()){
    pair<pll, ll> curr_content = q.top(); q.pop();

    pll curr = curr_content.xx;
    ll prev_node = curr_content.yy;

    if(distances_end[curr.yy] <= curr.xx) continue;

    distances_end[curr.yy] = curr.xx;
    previous_end[curr.yy] = prev_node;

    FOR(j, 0, graph[curr.yy].size()){

      pll next = graph[curr.yy][j];

      ll dist = next.xx;
      ll next_node = next.yy;

      if(distances_end[curr.yy]+dist < distances_end[next_node]){
        q.push(mp(mp(distances_end[curr.yy]+dist, next_node), curr.yy));

      }

    }
  }

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

  // 0 North
  // 1 East
  // 2 South
  // 4 West
  graph = vector<vector<pll> >(n*m*4, vector<pll>());

  FOR(i, 0, n*m)FOR(k, 0, 4){
    graph[i*4 + k].pb(mp(1000, i*4 + ((k + 1) % 4)));
    graph[i*4 + k].pb(mp(1000, i*4 + ((k + 3) % 4)));
  }


  FOR(y, 0, n)FOR(x, 0, m) {
    if(board[y][x] == '#') continue;

    if(board[y-1][x] != '#') graph[(y*m+x)*4 + 0].pb(mp(1, ((y-1)*m+x)*4 + 0));
    if(board[y+1][x] != '#') graph[(y*m+x)*4 + 2].pb(mp(1, ((y+1)*m+x)*4 + 2));
    if(board[y][x-1] != '#') graph[(y*m+x)*4 + 3].pb(mp(1, (y*m+(x-1))*4 + 3));
    if(board[y][x+1] != '#') graph[(y*m+x)*4 + 1].pb(mp(1, (y*m+(x+1))*4 + 1));

    if(board[y][x] == 'S') start_coor = mp(x, y);
    if(board[y][x] == 'E') end_corr = mp(x, y);

  }

  run_dijkstra_start();
  run_dijkstra_end();

  ll min_score = oo;

  FOR(k, 0, 4){
    min_score = min(min_score, distances[4*(end_corr.yy*m+end_corr.xx)+k]);
  }

  ll total_tiles = 0;
  FOR(y, 0, n)FOR(x, 0, m){
    bool best_tile = false;
    FOR(k_s, 0, 4){
      if(best_tile) continue;
      if(distances[4*(y*m+x)+k_s] == oo) continue;
      if(distances_end[4*(y*m+x)+(k_s+2)%4] == oo) continue;
      if((distances[4*(y*m+x)+k_s] + distances_end[4*(y*m+x)+(k_s+2)%4]) == min_score){
        board[y][x] = 'O';
        best_tile = true;
        total_tiles++;
      }
    }
  }

  cout << "Min score: "<< min_score << endl;
  cout << "Total tiles: "<< total_tiles << endl;

  FOR(y, 0, n){
    FOR(x, 0, m) cout << board[y][x];
    cout << endl;
  }

}

