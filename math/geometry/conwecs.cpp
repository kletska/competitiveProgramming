#include <bits/stdc++.h>

using namespace std;

struct point {
  int64_t x, y;
  point(int64_t x, int64_t y):x(x), y(y){}
  point(){}
};

point operator -(point a, point b) {
  return point(a.x - b.x, a.y - b.y);
}

int64_t dp(point a, point b) {
  return a.x * b.x + a.y * b.y;
}

int64_t cp(point a, point b) {
  return a.x * b.y - b.x * a.y;
}

point o;

int64_t s(int n, vector<point> & ps){
  int64_t sq = 0;
  for (int i = 0; i < n; ++i) {
    sq = sq + cp(ps[i], ps[(i + 1) % n]);
  }
  return abs(sq);
}

bool cmp(point& a, point& b) {
  return cp(a - o, b - o) > 0 or(cp(a - o, b - o) == 0 and dp(a - o, a - o) < dp(b - o, b - o)); 
}

void conwa(vector<point>& a, vector<point>& ans) {
  for (int i = 0; i < a.size(); ++i) {
    if (a[i].y < a[0].y or(a[i].y == a[0].y and a[i].x < a[0].x)) {
      swap(a[0], a[i]);
    }
  }
  o = a[0];
  sort(a.begin() + 1, a.end(), cmp);
  ans.push_back(a[0]);
  ans.push_back(a[1]);
  for (int i = 2; i < a.size(); ++i) {
    if (cp(a[i] - ans[ans.size() - 2], ans[ans.size() - 1] - ans[ans.size() - 2]) == 0) {
      ans[ans.size() - 1] = a[i];
      continue;
    } 
    while (ans.size() > 2 and cp(a[i] - ans[ans.size() - 2], ans[ans.size() - 1] - ans[ans.size() - 2]) >= 0) {
      ans.pop_back();
    }
    ans.push_back(a[i]);
  }
  if (cp(ans[0] - ans[ans.size() - 2], ans[ans.size() - 1] - ans[ans.size() - 2]) == 0) {
    ans.pop_back();
  }
}

main() {
  int n;
  cin >> n;
  vector<point> ps;
  set<pair<int, int>> st;
  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    if (st.insert({a, b}).second) {
      ps.push_back(point(a, b));
    }
    //cin >> ps[i].x >> ps[i].y;
  }
  vector<point> ans;
  conwa(ps, ans);
  int64_t sq = s(ans.size(), ans);
  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i].x << ' ' << ans[i].y << '\n';
  }
  //cout << '\n';
  cout << sq / 2;
  if (sq % 2 == 1) {
    cout << ".5";
  }
  cout << '\n';
}
