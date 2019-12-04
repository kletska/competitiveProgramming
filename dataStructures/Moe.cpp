#include <bits/stdc++.h>
 
using namespace std;
 
int64_t arr[200100];
pair<pair<int, int>, int> qs[200010];
int64_t ans[200100];
const int k = 450;
int64_t cnt[100100];
int64_t res;

bool cmp(pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
  return a.first.first / k != b.first.first / k ? a.first.first < b.first.first : a.first.second < b.first.second; 
}

void fenvadd(int x, int64_t z) {
  for (int i = x; i <= 100000; i += i & -i) {
    cnt[i] += z;
  }
}

int64_t fenvget(int x, int64_t ans = 0) {
  for (int i = x; i > 0; i -= i & -i) {
    ans += cnt[i];
  }
  return ans;
}

void maddr(int64_t x) {
  res += fenvget(100000) - fenvget(x);
  fenvadd(x, 1);
}

void maddl(int64_t x) {
  res += fenvget(x - 1);
  fenvadd(x, 1);
}
 
void mdelr(int64_t x) {
  res -= fenvget(100000) - fenvget(x);
  fenvadd(x, -1);
}

void mdell(int64_t x) {
  res -= fenvget(x - 1);
  fenvadd(x, -1);
}

int main() {
  //freopen("riq.in", "r", stdin);
  //freopen("riq.out", "w", stdout);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) { 
    cin >> arr[i];
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> qs[i].first.first >> qs[i].first.second;
    --qs[i].first.first;
    --qs[i].first.second;
    qs[i].second = i;
  }
  sort(qs, qs + q, cmp);
  int l = 0, r = -1;
  for (int i = 0; i < q; ++i) {
    while (l > qs[i].first.first) {
      maddl(arr[l - 1]);
      l--;
    }
    while (r < qs[i].first.second) {
      maddr(arr[r + 1]);
      r++;
    } 
    while (l < qs[i].first.first)  {
      mdell(arr[l]);
      l++;
    } 
    while (r > qs[i].first.second) {
      mdelr(arr[r]);
      r--;
    }
    ans[qs[i].second] = res;
  }
  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }
  return 0;
}
