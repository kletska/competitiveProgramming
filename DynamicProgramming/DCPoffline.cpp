#include <bits/stdc++.h>

using namespace std;

const int N = 32;
const int NN = 1 << N / 2;
//#define int64_t long long

int64_t w[N];
int64_t c[N];
int64_t L, R;
int64_t inf = 2e18;
int64_t zero = 0;
pair<pair<int64_t, int64_t>, int> fst[NN];
pair<int64_t, int> t[4 * NN];
int64_t lst = 0;
int n;
#define M (l + r) / 2

pair<int64_t, int> build(int i = 0, int l = 0, int r = (1 << n / 2)) {
  return t[i] =  r - l == 1 ? make_pair(fst[l].first.second, fst[l].second) : max(build(2 * i + 1, l, M), build(2 * i + 2, M, r));
}

pair<int64_t, int> mx(int al, int ar, int i = 0, int l = 0, int r = (1 << n / 2)) {
  if (ar <= l or r <= al) {
    return {-inf, 0};
  }
  if (al <= l and r <= ar) {
    return t[i];
  }
  return max(mx(al, ar, 2 * i + 1, l, M), mx(al, ar, 2 * i + 2, M, r));
}

main() {
  cin >> n >> L >> R;
  for (int i = 0; i < n; ++i) {
    cin >> w[i] >> c[i];
  }
  int sn = n / 2;
  int fn = n - sn;
  for (int m = 0; m < (1 << sn); ++m) {
    fst[m].second = m;
    for (int i = 0; i < sn; ++i) {
      if ((m >> i) & 1) {
	fst[m].first.first += w[i];
	fst[m].first.second += c[i];
      }
    }
  }
  sort(fst, fst + (1 << sn));
  build();
  int64_t ans = 0;
  int ansf = -1, anss = -1;
  for (int m = 0; m < (1 << fn); ++m) {
    int64_t curw = 0;
    int64_t curc = 0;
    for (int i = 0; i < fn; ++i) {
      if ((m >> i) & 1) {
	curw += w[i + sn];
	curc += c[i + sn];
      }
    }
    int iinf = 1e9;
    int l = lower_bound(fst, fst + (1 << sn), make_pair(make_pair(L - curw, zero), 0)) - fst;
    int r = upper_bound(fst, fst + (1 << sn), make_pair(make_pair(R - curw, inf), iinf)) - fst;
    int64_t val;
    int ind;
    tie(val, ind) = mx(l, r);
    if (val + curc > ans) {
      ans = val + curc;
      ansf = ind;
      anss = m;
    }
  }
  if (ansf == -1) {
    cout << 0 << '\n';
    return 0;
  }
  int cnt = 0;
  for (int i = 0; i < sn; ++i) {
    if ((ansf >> i) & 1) {
      ++cnt;
    }
  }
  for (int i = 0; i < fn; ++i) {
    if ((anss >> i) & 1) {
      ++cnt;
    }
  }
  cout << cnt << '\n';
  for (int i = 0; i < sn; ++i) {
    if ((ansf >> i) & 1) {
      cout << i + 1 << ' ';
    }
  }
  for (int i = 0; i < fn; ++i) {
    if ((anss >> i) & 1) {
      cout << sn + i + 1 << ' ';
    }
  }
  cout << '\n';
}
