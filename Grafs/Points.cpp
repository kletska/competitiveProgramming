#include <bits/stdc++.h>
using namespace std;
 
vector <int> g[100010];
int ans[100010], t[100010], f[100010];
int tim = 0, k = 0;
 
void dfs(int i, int p) {
  t[i] = f[i] = ++tim;
  int ch = 0;
  for (auto j : g[i]) {
    if (j == p) {
      continue;
    }
    if (t[j]) {
      f[i] = min(f[i], t[j]);
    } else {
      ch++;
      dfs(j, i);
      f[i] = min(f[i], f[j]);
      if (f[j] >= t[i] && p != -1) {
	if (ans[i] == 0) { 
          k++;
	}
        ans[i] = 1;
      }
    }
  }
  if (p == -1 && ch > 1) {
    k++;
    ans[i] = 1;                   
  }
}
 
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g[a - 1].push_back(b - 1);
    g[b - 1].push_back(a - 1);
  }
  for (int i = 0; i < n; i++) {
    if (!t[i]) {
      dfs(i, -1);
    }
  }
  cout << k << '\n';
  for (int i = 0; i < n; i++) {
    if (ans[i] == 1) {
      cout << i + 1 << " ";
    }
  }
}
