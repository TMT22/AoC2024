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

string line;
ll n; vl mem;

int main(){

  ios_base::sync_with_stdio (false);
  cin.tie(NULL);

  ifstream file("Inputs/Test01.txt");
  string str;
  vector<string> lines = vector<string>();
  while (std::getline(file, str)) lines.pb(str);

  line = lines[0];
  n = 0;

  FOR(i, 0, line.size()) n += line[i] - '0';

  mem = vl(n, -1);

  vvl free_spaces = vvl (11, vl());

  ll mem_pos = 0;
  vector<pll> files = vector<pll>();

  FOR(i, 0, line.size()){
    ll num_blocks = line[i] - '0';

    if(i % 2 == 0) {
      FOR(j, 0, num_blocks) {
        mem[mem_pos + j] = i / 2;
      }
      line[i] = '0';
      files.pb(mp(mem_pos, num_blocks));
    }

    if(i % 2 == 1) {
      free_spaces[num_blocks].pb(mem_pos);
    }

    mem_pos += num_blocks;
  }


  cout << n << endl;
  

  FOR(k, 0, 11){
    cout << k << ": ";
    FOR(i, 0, free_spaces[k].size()) cout << free_spaces[k][i] << ' ';
    cout << endl;
  }

  for (ll k = files.size()-1; k >= 0; k--) {
    
    /*
    FOR(i, 0, n) cout << mem[i] << ' ';
    cout << endl;
    */

    // Get free_space
    ll file_pos = files[k].xx;
    ll file_size = files[k].yy;

    ll free_space_pos = oo;
    ll free_space_size = -1;

    FOR(s, file_size, 11) {
      if(free_spaces[s].size() > 0 && free_space_pos > free_spaces[s][0]){
        free_space_pos = free_spaces[s][0];
        free_space_size = s;
      }
    }

    cout << free_space_size << ' ' << free_space_pos << ' ' << file_pos << endl;

    if(free_space_size > 0 && free_space_pos < file_pos){
      // Adjust free_spaces
      free_spaces[free_space_size].erase(free_spaces[free_space_size].begin());
      
      ll left_over = free_space_size - file_size;

      if(left_over > 0) {
        free_spaces[left_over].pb(free_space_pos + file_size);
        sort(all(free_spaces[left_over]));
      }


      FOR(j, 0, file_size){
        mem[free_space_pos + j] = mem[file_pos + j];
        mem[file_pos + j] = -1;
      }
    }


  }
  




  // Get checksum
  ll total = 0;
  FOR(i, 0, n) if(mem[i] >= 0) total += i * mem[i];

  cout << "Total: " << total << endl;
}

