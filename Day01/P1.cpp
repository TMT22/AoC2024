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

int main(){

  ios_base::sync_with_stdio (false);
  cin.tie(NULL);

  ifstream file("Inputs/Test01.txt");
  string str;
  vector<string> lines = vector<string>();
  
  vector<ll> listA = vector<ll>();
  vector<ll> listB = vector<ll>();
  
  while (std::getline(file, str)) {
    ll a, b;
    istringstream strm(str);

    strm >> a; strm >> b;

    listA.pb(a); listB.pb(b);
  }

  sort(all(listA));
  sort(all(listB));

  int dist_total = 0;

  for (size_t i = 0; i < listA.size(); i++)
  {
    dist_total += abs(listA[i] - listB[i]);
  }

  cout << "Total distance: " << dist_total << endl;
  
}

