#include <bits/stdc++.h>

using namespace std;

int V1, V2;
int arr[2000];
int ord[2000];
vector<int> g[2000];
int u[2000], mt[200100];
int ans[2000];

bool try_k(int v, int t) {
  if (u[v] == t) {
    return false;
  }
  u[v] = t;
  for (auto i : g[v]) {
    if (mt[i] == -1 || try_k(mt[i], t)) {
      mt[i] = v;
      return true;
    }
  }
  return false;
}

void kuhn() {
  for (int i = 0; i < V1; ++i) {
    mt[i] = -1;
  }
  for (int i = 0; i < V1; ++i) {
    try_k(ord[i], i + 1);
  }
}

int main() {
  cin >> V1;
  for (int i = 0; i < V1; i++) {
    cin >> arr[i];
    ord[i] = i;
  }
  sort(ord, ord + V1, [&](int i, int j) {return arr[i] > arr[j];});
  for (int i = 0; i < V1; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int a;
      cin >> a;
      g[i].push_back(a - 1);
    }
  }
  kuhn();
  for (int i = 0; i < V1; i++) {
    if (mt[i] != -1) 
      ans[mt[i]] = i + 1;
  }
  for (int i = 0; i < V1; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
