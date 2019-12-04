#include <bits/stdc++.h>

using namespace std;

long long dp[17][1 << 17];
int from[17][1 << 17];
int n;
int road[17][17];
 
 
int main() {
  cin >> n;
  int x;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> road[i][j];
      if (road[i][j] == 0) {
	road[i][j] = -1;
      }
    }
  }
  for (int i = 0; i < n; i++)
    for (int x = 0; x < 1 << n; x++)
      dp[i][x] = 1e7;
  dp[0][1] = 0;
  for (int x = 0; x < (1 << n); x++) {
    for (int i = 0; i < n; i++) {
      if (((x >> i) & 1) == 1) {
        for (int j = 0; j < n; j++) {
          if (((x >> j) & 1) and dp[j][x - (1 << i)] + road[j][i] < dp[i][x] and road[j][i] != -1) {
            dp[i][x] = dp[j][x - (1 << i)] + road[j][i];
	    from[i][x] = j;
	  }
	}
      }
    }
  }
  int k;
  int last = -1;
  long long mini = 1e7;
  for (int i = 0; i < n; i++) {
    if (dp[i][(1 << n) - 1] < mini) {
      mini = dp[i][(1 << n) - 1];
      last = i;
    }
  }
  if (last == -1) {
    cout << -1 << '\n';
    return 0;
  }
  x = (1 << n) - 1;
  vector<int> way;
  for (int i = 0; i < n; i++) {
    way.push_back(last + 1);
    int temp = last;
    last = from[last][x];
    x -= (1 << temp);
  }
  long long mo = 1e7;
  if (last == -1) {
    cout << -1 << '\n';
    return 0;
  }
  cout << mini << '\n';
  for (int i = n - 1; i >= 0; i--) {
    cout << way[i] << " "; 
  }
}
