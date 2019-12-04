#include <bits/stdc++.h>

using namespace std;

int arr1[100000];
int arr2[100000];
int ord[100000];
pair<double, int> res[100000];
int n, k;

bool check(double q) {
  for (int i = 0; i < n; ++i) {
    res[i].first = arr1[i] - q * arr2[i];
    res[i].second = i;
  }
  sort(res, res + n);
  reverse(res, res + n);
  double cur = 0;
  int cnt = 0;
  while (cnt < n and cur + res[cnt].first >= 0) {
    cur += res[cnt].first;
    cnt++;
  }
  return cnt >= k;
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> arr1[i] >> arr2[i];
    ord[i] = i;
  }
  double l = 0, r = 1e8;
  while (r - l > 1e-9) {
    double m = (l + r) / 2;
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  check(l);
  for (int i = 0; i < k; i++) {
    cout << res[i].second  + 1 << ' ';
  }
  cout << '\n';
}
