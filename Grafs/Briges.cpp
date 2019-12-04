#include <bits/stdc++.h>

using namespace std;

vector<int> g[100010];
pair<int, int> Es[200010];
int f[100010], t[100010];
vector<int> ans;
int cnt = 1;

int nxt(int e, int v) {
  return Es[e].first == v ? Es[e].second : Es[e].first;
}

void dfs(int i, int p = -1) {
  f[i] = t[i] = ++cnt;
  for (auto k : g[i]){
    int j = nxt(k, i);
    if (p == j) {
      continue;
    }
    if (!t[j]){
      dfs(j, i);
      f[i] = min(f[i], f[j]);
      if (f[j] > t[i]) {
	ans.push_back(k);
      }
    } else {
      f[i] = min(f[i], t[j]);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> Es[i].first >> Es[i].second;
    Es[i].first--;
    Es[i].second--;
    g[Es[i].first].push_back(i);
    g[Es[i].second].push_back(i);
  }
  for (int i = 0; i < n; i++) {
    if (!t[i]) {
      dfs(i, -1);
    }
  }
  cout << ans.size() << '\n';
  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] + 1 << ' ';
  }
  cout << '\n';
}
