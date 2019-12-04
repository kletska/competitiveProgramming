#include <bits/stdc++.h>

using namespace std;

#define M (l + r) / 2

const int N = 50100, inf = 2e9;
int n;
vector<int> g[N];

int p[N];
int sz[N];

int first[N];
int pos[N];
int unpos[N];
int curren = 0;

int arr[N];
int t2[4 * N];

int dfs1(int i = 0, int P = -1) {
  p[i] = P;
  sz[i] = 1;
  for (auto j : g[i]) 
    if (sz[j] == 0)
      sz[i] += dfs1(j, i);
  return sz[i];
}

void dfs2(int i = 0, int f = 0, int P = -1) {
  pos[i] = curren++;
  unpos[pos[i]] = i;
  first[i] = f;
  for (auto j : g[i]) {
    if (2 * sz[j] >= sz[i] and j != P) {
      f = f == -1 ? j : f;
      dfs2(j, f, i);
    }
  }
  for (auto j : g[i]) 
    if (2 * sz[j] < sz[i] and j != P) 
      dfs2(j, j);
}

int hldBuild(int i = 0, int l = 0, int r = n) {
  if (r - l == 1)
    return t2[i] = arr[unpos[l]];
  return t2[i] = max(hldBuild(2 * i + 1, l, M), hldBuild(2 * i + 2, M, r));
}

int chHld(int ind, int k, int i = 0, int l = 0, int r = n) {
  if (r - l == 1)
    return t2[i] = k;
  if (ind < M)
    return t2[i] = max(chHld(ind, k, 2 * i + 1, l, M), t2[2 * i + 2]);
  return t2[i] = max(t2[2 * i + 1], chHld(ind, k, 2 * i + 2, M, r));
}

int mxHld(int al, int ar, int i = 0, int l = 0, int r = n) {
  if (ar <= l or r <= al)
    return -inf;
  if (al <= l and r <= ar)
    return t2[i];
  return max(mxHld(al, ar, 2 * i + 1, l, M), mxHld(al, ar, 2 * i + 2, M, r));
}

inline int askWay(int u, int v) {
  int res = -inf;
  for (; first[u] != first[v]; u = p[first[u]], v = p[first[v]]) {
    res = max(res, mxHld(pos[first[v]], pos[v] + 1));
    res = max(res, mxHld(pos[first[u]], pos[u] + 1));
  }
  if (pos[v] > pos[u])
    swap(v, u);
  return max(res, mxHld(pos[v], pos[u] + 1));
}

main() {
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    g[a - 1].push_back(b - 1);
    g[b - 1].push_back(a - 1);
  }
  int m;
  dfs1();
  dfs2();
  hldBuild();
  cin >> m;
  for (int i = 0; i < m; ++i) {
    char a;
    int b, c;
    cin >> a >> b >> c;
    if (a == '!') 
      chHld(pos[b - 1], c);
    else
      cout << askWay(b - 1, c - 1) << '\n';
  }
}
