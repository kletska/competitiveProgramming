#include <bits/stdc++.h>

using namespace std;

const int N = 100100;

int tx[N];
int sz[N];
int tl[N];
int tr[N];

int counterForNodes = 1;

#define myrand ((rand() << 15) + rand())

int newNode(int x) {
  tx[counterForNodes] = x;
  return (counterForNodes += (sz[counterForNodes] = 1));
}

void update(int rt) {
  sz[rt] = sz[tl[rt]] + sz[tr[rt]] + 1;
}

void merge(int& rt, int l, int r) {
  if (!l or !r)
    rt = l ? l : r;
  else if (myrand % (sz[l] + sz[r]) > sz[r])
    merge(tr[l], tr[l], r), rt = l;
  else
    merge(tl[r], l, tl[r]), rt = r;
  update(rt);
}

void split(int x, int rt, int& l, int& r) {
  if (!rt)
    l = r = 0;
  else if (x < tx[rt])
    split(x, tl[rt], l, tl[rt]), r = rt;
  else
    split(x, tr[rt], tr[rt], r), l = rt;
  update(rt);
}

void splitSZ(int x, int rt, int& l, int& r) {
  if (!rt)
    l = r = 0;
  else if (x < sz[tl[rt]])
    split(x, tl[rt], l, tl[rt]), r = rt;
  else
    split(x - sz[tl[rt]], tr[rt], tr[rt], r), l = rt;
  update(rt);
}
void build(vector<int>& arr) {
  int n = arr.size();
  
}

void buildSZ(vector<int>& arr) {
  int n = arr.size(); 
}
/*
void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
}
void erase (pitem & t, int key) {
    if (t->key == key)
        merge (t, t->l, t->r);
    else
        erase (key < t->key ? t->l : t->r, key);
}
pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
}
*/

string replace (char a, string b, string c) {
  
}

string pshow(string pref, int rt) {
  return replase('\n', ("\n" + pref)
}

string show(string pref, int rt) {
  if (!rt)
    return "";
  if (!tl[rt] and !tr[rt])
    return pshow(pref, tr);
  if (!tl[rt] or !tr[rt])
    return pshow(pref, rt) + "\n" + pref + "`--" + pshow(pref + "   ", tl[rt] ? tl[rt] : tr[rt]);
  return pshow(pref, rt) + "\n" +
    pref + "|--" + pshow(pref + "|  ", tl[rt])
    + "\n" +
    pref + "`--" + pshow(pref + "   ", tr[rt]);
}



string goodPrint(string pref, int rt) {
  return "< " + replace('\n', "\n: ", show("", rt));
}

main() {
}
