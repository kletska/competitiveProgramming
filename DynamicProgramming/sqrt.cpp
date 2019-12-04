#include <bits/stdc++.h>

using namespace std;

main() {
  int64_t i = 1, j, n, ans = 0;
  cin >> n;
  for (; i <= n; ++i) {
    int64_t x = n / i;
    j = n / x;
    ans += (j - i + 1) * x;
    i = j;
  }
  cout << ans << '\n';
}
