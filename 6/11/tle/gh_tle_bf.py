import sys
from collections import deque
input = sys.stdin.readline
dq = deque()


# int도 object이므로, locality가 좋지 않음.
arr = [[0 for j in range(3001)] for i in range(3001)]
nj = [[0 for j in range(3001)] for i in range(3001)]


def calc(x1: int, y1: int, x2: int, y2: int) -> int:
    return nj[x2][y2] - nj[x2][y1-1] - nj[x1-1][y2] + nj[x1-1][y1-1]


def calc_digguk(x1: int, y1: int, ww: int, hh: int) -> int:
    bottom = calc(x1, y1, x1, y1+ww)
    up = calc(x1+hh, y1, x1+hh, y1+ww)
    sero = calc(x1, y1+ww, x1+hh, y1+ww)
    return bottom + up + sero - arr[x1][y1+ww] - arr[x1+hh][y1+ww] 


inf = 0x3f3f3f3f3f3f3f3f
mini = inf
R, C = map(int, input().split())
h1, h2, w1, w2 = map(int, input().split())
for r in range(1, R+1):
    tmp = [0] + list(map(int, input().split()))
    for c in range(1, C+1):
        arr[r][c] = tmp[c]

for i in range(1, R+1):
    for j in range(1, C+1):
        nj[i][j] = nj[i-1][j] + nj[i][j-1] - nj[i-1][j-1] + arr[i][j]

for h in range(h1+1, h2+2):
    if h > R:
        break
    base = -(arr[1][C-w1] + arr[h][C-w1])
    h0 = h-1
    while dq:
        dq.pop()
    for w in range(C-w1, 0, -1):
        # 역 ㄷ자 구하기.
        # 꼭지점, 너비, 높이
        base += (arr[1][w] + arr[h][w])
        
        # 역 ㄷ자를 구할 건데.
        dig = calc_digguk(1, w, w1, h0)
        
        # dig - base를 넣는다. 어? 왜?
        real = dig - base
        dq.append(real)
        
        if len(dq) > w2 - w1 + 1:
            dq.popleft()
        
        # 역 ㄷ 최대
        a = min(dq)
        a += base
        # 1자 더하기
        a += (calc(1, w, h, w) - arr[1][w] - arr[h][w])
        if a < mini:
            mini = a
            # print(f"h = {h} w = {w} lo = {item['lo']}")


if mini == inf:
    print('No')
else:
    print(mini)
