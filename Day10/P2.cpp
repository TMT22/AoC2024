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


ll n_b, m_b;
vector<string> board;

ll n;
vvl graph;

bool in_board(ll x, ll y){
  return y >= 0 && y < n_b && x >= 0 && x < m_b;
}

ll to_id(ll x, ll y) {
  return y * m_b + x;
}

pll to_coor(ll id) {
  return mp(id%m_b, id/m_b);
}


ll bfs(ll start) {
  vb marked = vb(n, false);

  queue<ll> nodes;
  map<ll, ll> num_hikes;

  nodes.push(start);
  num_hikes[start] = 1;

  FOR(k, 0, 9){
    queue<ll> new_nodes;
    map<ll, ll> new_num_hikes;
    while(!nodes.empty()){
      ll curr = nodes.front(); nodes.pop();
      FOR(i, 0, graph[curr].size()) {
        ll next = graph[curr][i];
        if(!marked[next]){
          marked[next] = true;
          new_num_hikes[next] = 0;
          new_nodes.push(next);
        }

        new_num_hikes[next] += num_hikes[curr];
      }
    }
    nodes = new_nodes;
    num_hikes = new_num_hikes;
  }


  ll total = 0;
  while(!nodes.empty()){
      ll curr = nodes.front(); nodes.pop();
      total += num_hikes[curr];
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
  
  n_b = board.size(); m_b = board[0].size();

  n = n_b * m_b;
  graph = vvl(n, vl());


  FOR(y, 0, n_b)FOR(x, 0, m_b){
    if(in_board(x+1, y) && (board[y][x+1]-board[y][x])==1) graph[to_id(x, y)].pb(to_id(x+1, y));
    if(in_board(x-1, y) && (board[y][x-1]-board[y][x])==1) graph[to_id(x, y)].pb(to_id(x-1, y));
    if(in_board(x, y+1) && (board[y+1][x]-board[y][x])==1) graph[to_id(x, y)].pb(to_id(x, y+1));
    if(in_board(x, y-1) && (board[y-1][x]-board[y][x])==1) graph[to_id(x, y)].pb(to_id(x, y-1));
  }

  ll total = 0;
  FOR(y, 0, n_b)FOR(x, 0, m_b){
    if(board[y][x] == '0') {
      total += bfs(to_id(x, y));
      //cout << bfs(to_id(x, y)) << endl;;
    }
  }

  cout << "Total: " << total << endl;
}

