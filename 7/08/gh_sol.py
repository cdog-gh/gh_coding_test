import operator as op
from functools import reduce
from collections import Counter


def combi(n, k):
    if k == 0 or k == n:
        return 1
    t = reduce(op.mul, range(n, n-k, -1))
    d = reduce(op.mul, range(1, k+1))
    return t // d


mod = 1000000007
leni = int(input())
c = Counter(input())
tot = combi(leni, 2)
for k in c:
    v = c[k]
    if v < 2:
        continue
    tot += (2 ** v) - 1 - combi(v, 1) - combi(v, 2)
tot %= mod
print(tot)
