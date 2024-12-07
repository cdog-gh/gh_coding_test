import operator as op
from functools import reduce


def combi(n, k):
    if k == 0 or k == n:
        return 1
    # redoce의 경우 1번째 인자로 연산, 2번째 인자로 iterable한 것을 받는다.
    # iterable한 것을 돌면서 연산을 적용한다.
    t = reduce(op.mul, range(n, n-k, -1))
    # 이 경우, 1부터 k까지 곱하는 것임.
    d = reduce(op.mul, range(1, k+1))
    return t // d


lv = int(input())
if lv <= 5:
    print(4 ** lv)
else:
    rr = reduce(op.add, [combi(lv, rev) for rev in range(0, 6+1)])
    note = 8 ** lv
    ans = (rr * note) % 1000000007
    print(ans)