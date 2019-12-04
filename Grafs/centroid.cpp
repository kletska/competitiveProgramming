#include <bits/stdc++.h>

using namespace std;

const int N = 300100, Log = 23;
int level[N];
int p[N];
vector<pair<int, int>> g[N];
int ds[N][Log];
vector<pair<int, int>> staks[N];

void calc(int i, int cent, int p = -1, int d = 0) {
  ds[i][level[cent]] = d;
  for (auto j : g[i]) {
    if (j.first != p and level[j.first] == -1) {
      calc(j.first, cent, i, d + j.second);
    }
  }
}

int dfs2(int v, int sz, int& cent, int p = -1) {
  int sum = 1;
  for (auto x : g[v])
    if (level[x.first] == -1 and x.first != p)
      sum += dfs2(x.first, sz, cent, v);
  if (cent == -1 and 2 * sum >= sz)
    cent = v;
  return sum;
}


void build(int v = 0, int d = 0, int l = -1) {
  int cent = -1, tmp;
  dfs2(v, dfs2(v, tmp, tmp), cent);
  level[cent] = d;
  p[cent] = l;
  calc(cent, cent);
  for (auto x : g[cent]) 
    if (level[x.first] == -1)
      build(x.first, d + 1, cent);
}

int color[N];
int cnt = 1;

void ask2(int v, int d, int c) {
  while (!staks[v].empty() and staks[v].back().first <= d)
    staks[v].pop_back();
  staks[v].push_back(make_pair(d, c));
}

void ask(int v, int d, int c) {
  int u = v;
  while (u != -1) {
    if (d - ds[v][level[u]] >= 0)
      ask2(u, d - ds[v][level[u]], c);
    u = p[u];
  }
}

int inf = 1e9;

int gt2(int v, int d) {
  //cout << v << endl;
  //for (int i = 0; i < staks[v].size(); ++i)
  //cout << staks[v][i].first << ':' << staks[v][i].second << ' ';
  //cout << endl;
  if (staks[v].empty())
    return 0;
  
  int l = -1, r = staks[v].size();
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (staks[v][m].first < d) {
      r = m;
    } else {
      l = m;
    }
  }
  int ans = l == -1 ? 0 : staks[v][l].second;
  /*
  int ans = 0;
  for (int i = staks[v].size() - 1; i >= 0; --i)
    if (staks[v][i].first >= d and staks[v][i].second > ans)
    ans = staks[v][i].second;*/
  return ans;
}

int gt(int v) {
  //cout << v << endl;
  int ans = 0;
  int u = v;
  while (u != -1) {
    ans = max(ans, gt2(u, ds[v][level[u]]));
    //cout << color[ans] << endl;
    u = p[u];
  }
  return ans;
}

main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a - 1].push_back(make_pair(b - 1, c));
    g[b - 1].push_back(make_pair(a - 1, c));
  }
  for (int i = 0; i < n; ++i) {
    level[i] = -1;
  }
  build();
  int m;
  cin >> m;
  ask(0, 2e9, 0);
  for (int i = 0; i < m; ++i) {
    int a, b, c, d;
    cin >> a;
    if (a == 1) {
      cin >> b >> c >> d;
       ask(b - 1, c, cnt);
      color[cnt++] = d;
    }
    if (a == 2) {
      cin >> b;
      cout << color[gt(b - 1)] << '\n';
    }
  }
  cout << '\n';
}
