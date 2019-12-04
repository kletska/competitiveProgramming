#include <bits/stdc++.h>

using namespace std;

const int N = 400100;
vector<int> cnt[N];
int mx = 0;

inline void cntclear() {
  for (int i = 0; i <= mx; ++i) {
    cnt[i].clear();
  }
  mx = 0;
}

inline void mysort(vector<pair<pair<int, int>, int>>& t) {
  cntclear();
  for (int i = 0; i < t.size(); ++i) {
    cnt[t[i].first.second].push_back(i);
    mx = max(mx, t[i].first.second);
  }
  vector<int> ord(t.size());
  int ccnt = 0;
  for (int i = 0; i <= mx; ++i) {
    for (auto j : cnt[i]) {
      ord[ccnt++] = j;
    }
  }
  vector<pair<pair<int, int>, int>> arr(t.size());
  for (int i = 0; i < t.size(); ++i) {
    arr[i] = t[ord[i]];
  }
  cntclear();
  for (int i = 0; i < t.size(); ++i) {
    cnt[arr[i].first.first].push_back(i);
    mx = max(mx, arr[i].first.first);
  }
  ccnt = 0;
  for (int i = 0; i <= mx; ++i) {
    for (auto j : cnt[i]) {
      ord[ccnt++] = j;
    }
  }
  for (int i = 0; i < t.size(); ++i) {
    t[i] = arr[ord[i]];
  }
}

inline void sufmas(vector<int>& c, vector<int>& ans) {
  vector<pair<pair<int, int>, int>> t(c.size()); //t[i] = { { first class, second class }, position }
  for (int i = 1; i < c.size(); i <<= 1) {
    for (int j = 0; j < c.size(); ++j)
      t[j] = {{c[j], c[(j + i) % c.size()]}, j};
    mysort(t);
    for (int cnt = 0, j = 0; j < c.size(); ++j) {
      if (j && t[j].first != t[j - 1].first)
	cnt++;
      c[t[j].second] = cnt;
    }
  }
  for (int i = 0; i < c.size(); i++)
    ans[c[i]] = i;
}

inline vector<int> lsp(vector<int> c, vector<int> suf, vector<int> unsuf) {
  vector<int> ans(c.size());
  for (int i = 0; i < c.size(); ++i) 
    for (; c[i + ans[i] == c[suf[unsuf[i] + 1] + ans[i]; ++ans[i]) {}
  return ans;
}

main() {
  string s;
  cin >> s;
  s.push_back('a' - 1);
  vector<int> c(s.size());
  for (int i = 0; i < c.size(); ++i) {
    c[i] = s[i] - 'a' + 1;
  }
  vector<int> ans(c.size());
  sufmas(c, ans);
  for (int i = 1; i < ans.size(); ++i) {
    cout << ans[i] + 1 << ' ';
  }
  cout << '\n';
}  
