#include <bits/stdc++.h>

using namespace std;

int fs[100010];
vector<int> g[100010];
vector<int> ans;
map<pair<int, int>, int> m;

bool is(int a, int b, int c, int d) {
  return (a != b or c != d) and (a != d or c != b);
}

int main() {
  int n;
  cin >> n;
  int v1 = -1, v2 = -1;
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    if (k & 1 and v1 == -1) {
      v1 = i;
    } else if (k & 1 and v2 == -1) {
      v2 = i;
    } else if (k & 1) {
      cout << -1 << '\n';
      return 0;
    }
    for (int j = 0; j < k; j++) {
      int a;
      cin >> a;
      ++m[{min(i, a - 1), max(i, a - 1)}];
      g[i].push_back(a - 1);
    }
  }
  if (v1 != -1) {
    m[{min(v1, v2), max(v1, v2)}] += 2;
    g[v1].push_back(v2);
    g[v2].push_back(v1);
  }
  int fst = 0;
  stack<int> st;
  st.push(fst);
  while (!st.empty()) {
    int i = st.top();
    if (fs[i] == g[i].size()) {
      ans.push_back(i);
      st.pop();
    } else {
      int j = g[i][fs[i]];
      fs[i]++;
      if (m[{min(i, j), max(i, j)}] > 0) {
	m[{min(i, j), max(i, j)}] -= 2;
	st.push(j);
      }
    }
  }
  int k = 0;
  //cout << 1 << endl;
  if (v1 != -1) {
    ans.pop_back();
    for (; is(ans[k], v1, ans[(k + 1) % ans.size()], v2); k++) {
    }
    cout << ans.size() - 1 << '\n';
    for (int i = 0; i < ans.size(); i++) {
      cout << ans[(i + k + 1) % ans.size()] + 1 << ' ';
    }
    cout << '\n';
    return 0;
  }
  cout << ans.size() - 1 << '\n';
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] + 1 << ' ';
  }
  cout << '\n';
}
