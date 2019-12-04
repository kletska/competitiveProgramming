#include <bits/stdc++.h>

using namespace std;

const int N = 100100;

#define int int64_t

struct Q {
  int x1, x2;
  int y;
  int type;
  int i;
  Q(int a, int b, int c, int d, int e) : x1(a), x2(b), y(c), type(d), i(e) {}
};

int n, m;
int nm;
pair<int, int> t1[4 * N];
pair<int, int> t2[4 * N];
bool ans1[2 * N];
bool ans2[2 * N];
int res1[2 * N];
int res2[2 * N];
vector<Q> qs1;
vector<Q> qs2;

#define M (l + r) / 2 

pair<int, int>  mer(pair<int, int> a, pair<int, int> b) {
  int mx = max(a.first, b.first);
  int mn = min(a.second, b.second);
  return make_pair(mx, mn);
}


pair<int, int> ch1(int t, int ind, int i = 0, int l = 0, int r = N) {
  if (r - l == 1)
    return t1[i] = make_pair(t, t);
  if (ind < M)
    return t1[i] = mer(ch1(t, ind, 2 * i + 1, l, M), t1[2 * i + 2]);
  return t1[i] = mer(t1[2 * i + 1], ch1(t, ind, 2 * i + 2, M, r));
}

pair<int, int> ask1(int al, int ar, int i = 0, int l = 0, int r = N) {
  if (ar <= l or r <= al) {
    return make_pair((int) -2e9, (int) 2e9);
  }
  if (al <= l and r <= ar) {
    return t1[i];
  }
  return mer(ask1(al, ar, 2 * i + 1, l, M), ask1(al, ar, 2 * i + 2, M, r));
}


pair<int, int> ch2(int t, int ind, int i = 0, int l = 0, int r = N) {
  if (r - l == 1)
    return t2[i] = make_pair(t, t);
  if (ind < M)
    return t2[i] = mer(ch2(t, ind, 2 * i + 1, l, M), t2[2 * i + 2]);
  return t2[i] = mer(t2[2 * i + 1], ch2(t, ind, 2 * i + 2, M, r));
}

pair<int, int> ask2(int al, int ar, int i = 0, int l = 0, int r = N) {
  if (ar <= l or r <= al) {
    return make_pair((int) -2e9, (int) 2e9);
  }
  if (al <= l and r <= ar) {
    return t2[i];
  }
  return mer(ask2(al, ar, 2 * i + 1, l, M), ask2(al, ar, 2 * i + 2, M, r));
}

bool cmp(Q& a, Q& b) {
  return a.y < b.y or(a.y == b.y and a.type < b.type);
}

main() {
  int k, q;
  cin >> n >> m >> k >> q;
  nm = max(n, m);
  for (int i = 0; i < k; ++i) {
    int a, b;
    cin >> a >> b;
    qs1.push_back(Q(a, a, b, 0, 0));
    qs2.push_back(Q(b, b, a, 0, 0));
  }
  for (int i = 0; i < q; ++i) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    qs1.push_back(Q(a, c, b, -1, i));
    qs1.push_back(Q(a, c, d, 1, i));
    qs2.push_back(Q(b, d, a, -1, i));
    qs2.push_back(Q(b, d, c, 1, i));
  }
  sort(qs1.begin(), qs1.end(), cmp);
  int cnt = 1;
  for (auto q : qs1) {
    if (q.type == -1) {
      res1[q.i] = ask1(q.x1, q.x2 + 1).first;
    }
    if (q.type == 0) {
      ch1(cnt++, q.x1);
    }
    if (q.type == 1) {
      ans1[q.i] = ask1(q.x1, q.x2 + 1).second > res1[q.i];
    }
  }
  sort(qs2.begin(), qs2.end(), cmp);
  cnt = 1;
  for (auto q : qs2) {
    if (q.type == -1) {
      res2[q.i] = ask2(q.x1, q.x2 + 1).first;
    }
    if (q.type == 0) {
      ch2(cnt++, q.x1);
    }
    if (q.type == 1) {
      ans2[q.i] = ask2(q.x1, q.x2 + 1).second > res2[q.i];
    }
  }
  for (int i = 0; i < q; ++i) 
    if (ans1[i] or ans2[i])
      cout << "YES\n";
    else
      cout << "NO\n";
}
