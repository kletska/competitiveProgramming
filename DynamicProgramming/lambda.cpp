#include <bits/stdc++.h>

using namespace std;
 
const int N = 250002;
vector<pair<int, int>> g[N];
long double c1[N], c2[N], m;
int64_t k1[N], k2[N];
 
void dfs(int v, int p) {
  c1[v] = c2[v] = k1[v] = k2[v] = 0;
  long double md = 0;
  int64_t kd = 0;
  for (auto u : g[v]) {
    if (u.first == p)
      continue;
    dfs(u.first, v);
    c1[v] += c2[u.first];
    k1[v] += k2[u.first];
    long double cd = c1[u.first] - c2[u.first] + u.second + m;
    if (cd > md) {
      md = cd;
      kd = k1[u.first] - k2[u.first] + 1;
    }
  }
  c2[v] = c1[v] + md;
  k2[v] = k1[v] + kd;
}
 
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, k, u, v, c;
  cin >> n >> k;
  for (int i = 0; i < n - 1; ++i) {
    cin >> u >> v >> c;
    u--;
    v--;
    g[u].push_back({v, c});
    g[v].push_back({u, c});
  }
  long double l = -1e12, r = 1e12, lc = 0, rc = 0;
  int64_t lk = 0, rk = N;
  for (int i = 0; i < 82; i++) {
    m = (l + r) / 2;
    dfs(0, -1);
    //cout << m << ' ' << k2[0] << '\n';
    if (k2[0] < k) {
      l = m;
      //assert(k2[0] >= lk);
      if (k2[0] != lk) {
	lc = c2[0] - m * k2[0];
	lk = k2[0];
      }
    } else {
      r = m;
      //assert(k2[0] <= rk);
      if (k2[0] != rk) {
	rc = c2[0] - m * k2[0];
	rk = k2[0];
      }
    }
  }
  if (rk == N)
    cout << "Impossible";
  else if (lk == rk)
    cout << (int64_t) round(rc);
  else
    cout << (int64_t) round(lc + (rc - lc) * (k - lk) / (rk - lk));
}
