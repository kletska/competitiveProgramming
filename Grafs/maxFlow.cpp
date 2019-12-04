#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 510; 
const int INF = 1e18;

struct edge {
  int a, b, c, f;
};

int n, s, t, d[N], ptr[N], q[N];
vector<edge> e;
vector<int> g[N];
 
void addEdge(int a, int b, int cap) {
  edge e1 = {a, b, cap, 0};
  edge e2 = {b, a, 0, 0};
  g[a].push_back(e.size());
  e.push_back(e1);
  g[b].push_back(e.size());
  e.push_back(e2);
}
 
bool bfs() {
  queue<int> q;
  q.push(s);
  for (int i = 0; i < n; ++i) {
    d[i] = -1;
  }
  d[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < g[v].size(); ++i) {
      if (d[e[g[v][i]].b] == -1 && e[g[v][i]].f < e[g[v][i]].c) {
	q.push(e[g[v][i]].b);
	d[e[g[v][i]].b] = d[v] + 1;
      }
    }
  }
  return d[t] == -1;
}
 
int dfs(int v, int flow, int psh = 0) {
  //cout << v << endl;
  if (flow == 0 or v == t)
    return flow;
  for (; ptr[v] < g[v].size(); ++ptr[v]) {
    int i = g[v][ptr[v]], to = e[i].b;
    if (d[to] == d[v] + 1 and(psh = dfs(to, min(flow, e[i].c - e[i].f)))) {
      e[i].f += psh;
      e[i ^ 1].f -= psh;
      return psh;
    }
  }
  return 0;
}
 
int dinic() {
  for (int64_t flow = 0;;) {
    if (bfs()) {
      return flow;
    }
    for (int i = 0; i < n; ++i) {
      ptr[i] = 0;
    }
    //cout << 1 << endl;
    while (int64_t pushed = dfs(s, INF)) {
      flow += pushed;
      //cout << pushed;
    }
    //cout << 1 << endl;
  }
}


main() {
  int m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    addEdge(a - 1, b - 1, c);
  }
  s = 0;
  t = n - 1;
  //cout << 1 << endl;
  int ans = dinic();
  cout << ans << '\n';
  for (int i = 0; i < m; ++i) {
    cout << e[2 * i].f << '\n';
  }
}
