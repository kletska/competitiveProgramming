#include  <bits/stdc++.h>

using namespace std;

void pf(string &s, vector<int> &ans) {
  for (int i = 1; i < s.size(); i++){
    int j = ans[i - 1];
    while (j > 0 && s[i] != s[j])
      j = ans[j - 1];
    if (s[i] == s[j])
      j++;
    ans[i] = j;
  }
}

void zf(string &s, vector<int> &ans){
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) 
      ans[i] = min(r - i + 1, ans[i - l]);
    while (i + ans[i] < n && s[ans[i]] == s[i + ans[i]])
      ans[i]++;
    if (i + ans[i] - 1 > r) {
      l = i;
      r = i + ans[i] - 1;
    }
  }
}

main() {
  string s;
  cin >> s;
  vector<int> ans;
  zf(s, ans);
  ans[0] = s.size();
  for (auto i : ans) {
    cout << i << ' ';
  }
  cout << '\n';
}
