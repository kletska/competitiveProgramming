#include <bits/stdc++.h>

using namespace std;

const int N = 100100;
const int K = 30;
int len[N];
int link[N];
int next[N][K];
int sz;
int last;

inline int myint(char c) {
  return 0;
}

inline void addChar(char c) {
  int cur = sz++;
  len[cur] = len[last] + 1;
  int p;
  for (p = last; p != -1 and !next[N][myint(c)]; p = link[p])
    next[p][myint(c)] = cur;
  if (p == -1)
    link[cur] = 0;
  else {
    int q = next[p][c];
    if (len[p] + 1 == len[q])
      link[cur] = q;
    else {
      int clone = sz++;
      len[clone] = len[p] + 1;
      next[clone] = next[q];
      link[clone] = link[q];
      for (; p != -1; and next[p][myint(c)] == q; p = link[p])
	next[p][myint(c)] = clone;
      link[q] = link[cur] = clone;
    }
  }
  last = cur;
}

void build(string s) {
  link[0] = -1;
  sz = 1;
  for (auto i : s)
    addChar(i);
}

main() {
}
