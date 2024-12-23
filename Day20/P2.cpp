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

vl distances_start;
vl previous_start;

vector<string> board;

pll start_coor, end_corr;

set<pll> on_path;

bool in_board(pll pos){
  return pos.xx >= 0 && pos.xx < m && pos.yy < n && pos.yy >= 0;
}

void run_dijkstra(){
  std::priority_queue<pair<pll, ll>, std::vector<pair<pll, ll> >, std::greater<pair<pll, ll> > > q;
  
  distances = vl(graph.size(), oo);
  previous = vl(graph.size(), -1);

  pll start = mp(0, end_corr.yy*m + end_corr.xx);

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



void run_dijkstra_start(){
  std::priority_queue<pair<pll, ll>, std::vector<pair<pll, ll> >, std::greater<pair<pll, ll> > > q;
  
  distances_start = vl(graph.size(), oo);
  previous_start = vl(graph.size(), -1);

  pll start = mp(0, start_coor.yy*m + start_coor.xx);

  q.push(mp(start, -1));

  while(!q.empty()){
    pair<pll, ll> curr_content = q.top(); q.pop();

    pll curr = curr_content.xx;
    ll prev_node = curr_content.yy;

    if(distances_start[curr.yy] <= curr.xx) continue;


    distances_start[curr.yy] = curr.xx;
    previous_start[curr.yy] = prev_node;

    FOR(j, 0, graph[curr.yy].size()){

      pll next = graph[curr.yy][j];

      ll dist = next.xx;
      ll next_node = next.yy;

      if(distances_start[curr.yy]+dist < distances_start[next_node]){
        q.push(mp(mp(distances_start[curr.yy]+dist, next_node), curr.yy));

      }

    }
  }
}


ll pos_to_save(pll pos, ll min_score){
  if(board[pos.yy][pos.xx] == '#') return 0;
  ll total = 0;

  FOR(i, -21, 22)FOR(j, -21, 22){
    if(abs(i)+abs(j) > 20) continue;

    pll next_pos = mp(pos.xx+i, pos.yy+j);


    if(!in_board(next_pos)) continue;
    if(board[next_pos.yy][next_pos.xx] == '#') continue;

    ll time_no_cheat = distances[pos.yy*m + pos.xx] + distances_start[pos.yy*m + pos.xx];
    ll time_with_cheat = distances[next_pos.yy*m + next_pos.xx] + distances_start[pos.yy*m + pos.xx] + (abs(i)+abs(j));

    ll saved = min_score - time_with_cheat;
    if(saved < 1) continue;
    cout << saved<< endl;
    if(saved < 40) continue;
    total++;
  }

  return total;

}


int main(){
  ios_base::sync_with_stdio (false);
  cin.tie(NULL);

  ifstream file("Inputs/Input2.txt");
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
  run_dijkstra_start();

  ll min_score = distances[start_coor.yy*m + start_coor.xx];


  ll total = 0;
  pll curr_corr  = start_coor;
  on_path.insert(end_corr);

  while(curr_corr.xx != end_corr.xx || curr_corr.yy != end_corr.yy){
    on_path.insert(curr_corr);
    ll curr_corr_n = previous[curr_corr.yy*m+curr_corr.xx];

    curr_corr.xx = curr_corr_n % m;
    curr_corr.yy = curr_corr_n / m;
  }
  on_path.insert(end_corr);

  
  
  
  FOR(y, 0, n)FOR(x, 0, m) {
    total += pos_to_save(mp(x, y), min_score);
  }
 
 /*
  curr_corr  = start_coor;
  
  while(curr_corr.xx != end_corr.xx || curr_corr.yy != end_corr.yy){
    //cout << curr_corr.xx << " " << curr_corr.yy << endl;
    //cout << pos_to_save(curr_corr, min_score) << endl;
    total += pos_to_save(curr_corr, min_score);
    ll curr_corr_n = previous[curr_corr.yy*m+curr_corr.xx];

    curr_corr.xx = curr_corr_n % m;
    curr_corr.yy = curr_corr_n / m;
  }
   */
  


  cout << "Total: "<< total << endl;

}

