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

  ll mem_pos = 0;
  ll line_end = line.size()-1;
  if (line_end % 2 == 1) line_end - 1; // Account for potential free block at the end


  FOR(i, 0, line.size()){
    ll num_blocks = line[i] - '0';

    if(i % 2 == 0) {
      FOR(j, 0, num_blocks) {
        mem[mem_pos + j] = i / 2;
      }
      line[i] = '0';
    }

    if(i % 2 == 1) {
      ll left_spaces = num_blocks;

      while(left_spaces > 0 && line_end > i) {
        ll to_use = min((ll) (line[line_end] - '0'), left_spaces);
        FOR(j, 0, to_use) mem[mem_pos + (num_blocks - left_spaces) + j] = line_end / 2;

        left_spaces -= to_use;
        line[line_end] = line[line_end] - to_use;

        if(line[line_end] == '0') line_end -= 2;
      }

    }


    mem_pos += num_blocks;
  }


  cout << n << endl;
  FOR(i, 0, n) cout << mem[i] << endl;


  // Get checksum
  ll total = 0;
  FOR(i, 0, n) if(mem[i] >= 0) total += i * mem[i];

  cout << "Total: " << total << endl;
}

