#include <bits/stdc++.h>

using namespace std;

const int N = 100100;
const int l0g = 25;
int n;

int dp[l0g][N];
int l0gs[N];
int arr[N];

void build() {
  for (int i = 2; i <= N; ++i)
    l0gs[i] = l0gs[i / 2] + 1;
  for (int i = 0; (1 << i) <= n; ++i)
    for (int j = 0; j + (1 << i) <= n; ++j)
      dp[i][j] = i == 0 ? arr[j] : min(dp[i - 1][j], dp[i][j + (1 << (i - 1))]);
}

int ask(int l, int r) {
  int l0g = l0gs[r - l + 1];
  return min(dp[l0g][l], dp[l0g][r - (1 << l0g) + 1]);
}
