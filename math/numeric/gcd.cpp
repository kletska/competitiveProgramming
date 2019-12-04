int gcd (int a, int b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

tuple<int, int, int> gcd(int a, int b) {
  if (a == 0) {
    return {b, 0, 1};
  }
  int x, y, x1, y1, d;
  tie(d, x1, y1) = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return {d, x, y};
}
