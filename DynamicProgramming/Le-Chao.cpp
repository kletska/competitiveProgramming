#include <bits/stdc++.h>

using namespace std;



#define N 100010
#define M (l + r) / 2
int n;
const long long inf = 1e18;

pair<long long, long long> tree[8 * N];


long long x[N];
long long c[N];
long long t[N];
//long long dp[N];

long long f(pair<long long, long long> a, long long x) {
  return a.first * x + a.second;
}

void madd(pair<long long, long long> ln, int i = 0, int l = -N, int r = N) {
  if (f(ln, M) > f(tree[i], M)) {
    swap(ln, tree[i]);
  }
  if (ln.first == tree[i].first or r - l == 1) {
    return;
  } else if (ln.first < tree[i].first) {
    madd(ln, 2 * i + 1, l, M);
  } else {
    madd(ln, 2 * i + 2, M, r);
  }
}


long long gt(long long x, int i = 0, int l = -N, int r = N) {
  if (r - l == 1) {
    return f(tree[i], x);
  } else if (x < M) {
    return max(f(tree[i], x), gt(x, i * 2 + 1, l, M));
  } else {
    return max(f(tree[i], x), gt(x, i * 2 + 2, M, r));
  }
}



main() {
  for (int i = 0; i < 8 * N; ++i) {
    tree[i] = {0, -inf};
  }
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> c[i] >> t[i];
  }
  int64_t dp = 0;
  madd({x[n - 1], t[n - 1]});
  for (int i = n - 2; i >= 0; --i) {
    dp = max(c[i] * x[i] + gt(-c[i]), -c[i] * x[i] + gt(c[i]));
    madd({x[i], dp + t[i]});
  }
  cout << dp << '\n';
}
