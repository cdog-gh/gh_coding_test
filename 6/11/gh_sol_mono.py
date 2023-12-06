import sys
from collections import deque
input = sys.stdin.readline
dq = deque()


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
        '''
        v v v
            v
        v v v
        
        v v v v
              v
        v v v v
        요래 있었다고 해 보자. 이 때 한 칸 왼쪽으로 이동하면
        
      o v v v
            v
      o v v v
      
      o v v v v
              v
      o v v v v
      이 o가 자료구조에 있는 아이들에 공통으로 추가될 것이고.
      
      새로 추가 되는 아이는
      v v v
          v
      v v v
      가 됨. 
        이 o를 관리하는 것이 base의 역할임.
        
        결국 우리는 자료구조에
        3 5 가 있었을 때, 이들 전체에 +3을 더한 다음에
        2를 추가하는 연산을 하는 것임.
        
        [3 5]
        [6 8]
        [2 6 8]
        
        이 되는 셈인데. 이걸 어떻게 관리하는가? 자료구조에 맨 처음에 넣은 것을 기준으로 보는 거임.
        
        구현의 편의성을 위해, 처음 base를 가장 끝 역디귿 (w1)짜리의 왼쪽 2개의 합에 -를 씌울 거임.
        자료구조에 넣을 때 마다 base는 w1짜리 width의 왼쪽 2개만큼 증가함. 이것은 끝의 놈 기준오르 보았을 때 누적되는 형태임.
        
        2 3 4 5 7 3
                 ...
        4 7 2 6 2 1
            ^
        
        현재 ^ 위치가 먼저 들어간다 하면 처음 base는 -6에서 6이 더해진 0이 됨.
        다음 그 왼쪽을 보자. 왼쪽이 들어갈 건데. 자료구조에 있는 넘을 변화시킬 순 없다.
        여기에 10이 들어갔다고 해 보자. 그러면 [10]이 있을 테고
        들어갈 놈이 13이라고 하면.
        

        먼저 [10 + 3 + 7]이 될 거고, 그 다음에 13이 들어갈 거임.
        결국 [13, 20] 순으로 있을 텐데. 이를 역관점으로 생각해 보면
        
        [10]이 있고
        역 ㄷ자의 결과 13에 -10을 빼 보자. (base에서 10을 더하면 10이 되니까)
        그러면 [10]에 13 - 10이 들어가는 것과 같다. right?
        
        [3, 10]에서 어떻게 복원하는가?
        base 값이 10이였음. 그러면 여기서 +10만 더하면 됨.        
        '''
        real = dig - base
        while dq:
            item = dq[-1]
            if item["value"] < real:
                break
            dq.pop()
        dq.append({"lo": w+w1, "value": real})
        
        # 최소값 뽑기
        while dq:
            item = dq[0]
            if item["lo"] <= w + w2:
                break
            dq.popleft()
        
        # 역 ㄷ 최대
        a = dq[0]["value"] + base
        # 1자 더하기
        a += (calc(1, w, h, w) - arr[1][w] - arr[h][w])
        if a < mini:
            mini = a
            # print(f"h = {h} w = {w} lo = {item['lo']}")


if mini == inf:
    print('No')
else:
    print(mini)
