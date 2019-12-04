#include <bits/stdc++.h>

using namespace std;

int n, k;
int mt[4000], Tm[4000];
bool LisS[4000];
bool RisS[4000];
vector<int> g[4000];

void dfs(int v) {
  LisS[v] = 1;
  for (auto i : g[v]) {
    RisS[i] = 1;
    if (mt[i] != -1 and !LisS[mt[i]]) {
      dfs(mt[i]);	
    }    
  }
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    for (int j = 0; j < a; j++) {
      int b;
      cin >> b;
      g[i].push_back(b - 1);
    }
  }
  for (int i = 0; i < k; i++) {
    mt[i] = -1;
  }
  for (int i = 0; i < n; i++) {
    cin >> Tm[i];
    --Tm[i];
    if (Tm[i] != -1) {
      mt[Tm[i]] = i;
    }
  }
  for (int i = 0; i < n; i++) {
    if (Tm[i] == -1) {
      dfs(i);
    }
  }
  int cnt1 = 0;
  for (int i = 0; i < n; i++) {
    if (!LisS[i]) {
      ++cnt1;
    }
  }
  int cnt2 = 0;
  for (int i = 0; i < k; i++) {
    if (RisS[i]) {
      ++cnt2;
    }
  }
  cout << cnt1 + cnt2 << '\n';
  cout << cnt1 << ' ';
  for (int i = 0; i < n; i++) {
    if (!LisS[i]) {
      cout << i + 1 << ' ';
    }
  }
  cout << '\n';
  cout << cnt2 << ' '; 
  for (int i = 0; i < k; i++) {
    if (RisS[i]) {
      cout << i + 1 << ' ';
    }
  }
  cout << '\n';
}
