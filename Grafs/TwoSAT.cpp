#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> g[200010], gt[200010];
vector<bool> used;
vector<int> order, comp;

void dfs1(int v) {
  used[v] = true;
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (!used[to])
      dfs1(to);
  }
  order.push_back(v);
}

void dfs2(int v, int cl) {
  comp[v] = cl;
  for (size_t i = 0; i < gt[v].size(); ++i) {
    int to = gt[v][i];
    if (comp[to] == -1)
      dfs2(to, cl);
  }
}

int main() {
  while (cin >> n >> m) {
    int nn = 2 * n;
    for (int i = 0; i < m; i++) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      b = (1 - b) * n;
      d = (1 - d) * n;
      g[(a + b + n) % nn].push_back(c + d);
      g[(c + d + n) % nn].push_back(a + b);
      gt[c + d].push_back((a + b + n) % nn);
      gt[a + b].push_back((c + d + n) % nn);
    }
    used.assign(nn, false);
    for (int i = 0; i < nn; ++i)
      if (!used[i])
	dfs1(i);
    comp.assign(nn, -1);
    for (int i = 0, j = 0; i < nn; ++i) {
      int v = order[nn - i - 1];
      if (comp[v] == -1)
	dfs2(v, j++);
    }
    for (int i = 0; i < n; ++i) {
      int ans = (comp[i] > comp[i + n]);
      cout << ans;
    }
    cout << '\n';
    for (int i = 0; i < nn; i++) {
      g[i].clear();
      gt[i].clear();
    }
    comp.clear();
    order.clear();
    used.clear();
  }
}
