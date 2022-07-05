arr = []
points = []
points_desc = []
dx = [-1, -1, -1, 0, 1, 1, 1, 0]
dy = [-1, 0, 1, 1, 1, 0, -1, -1]
ans = 0


def get_px(t):
    tx = points[t][0]
    ty = points[t][1]
    return arr[tx][ty]


def injup(t1, t2):
    tx = points[t1][0]
    ty = points[t1][1]
    gx = points[t2][0]
    gy = points[t2][1]
    for i in range(8):
        if tx + dx[i] == gx and ty + dy[i] == gy:
            return True
    return False


R, C, N = map(int, input().split())
_, _, _ = map(int, input().split())
a12, a23, a13 = map(int, input().split())
for i in range(R):
    temp = list(map(int, input().split()))
    arr.append(temp)
for i in range(R):
    for j in range(C):
        points.append([i, j])
        points_desc.append(tuple([-arr[i][j], i, j]))
points_desc = sorted(points_desc)
rr = [0] * 300
nj_v = 0
nj = [0] * 300
for i in range(len(points_desc)):
    lo = C*points_desc[i][1] + points_desc[i][2]
    rr[lo] = i
for i in range(R*C):
    nj_v = nj_v - points_desc[i][0]
    nj[i] = nj_v


def RR(X, T):
    if rr[X] <= T:
        return 1
    return 0


bonus = [-a12, -a23, -a13]
bonus = sorted(bonus)


for i in range(len(points)):
    for j in range(i+1, len(points)):
        for k in range(j+1, len(points)):
            injup_num = injup(i, j) + injup(j, k) + injup(i, k)
            #i & j, j & k, i & k injup?
            # this logic? select 3 space, and maximum injup charm point!
            r = get_px(i) + get_px(j) + get_px(k)
            r = r - sum(bonus[:injup_num]) 
            
            # n-3 rank nj_hup
            for t in range(N-4, N):
                # 실제 원소 수?
                real_wonso = t + 1 - RR(i, t) - RR(j, t) - RR(k, t)
                if real_wonso == N-3:
                    r2 = nj[t] - RR(i, t)*get_px(i) - RR(j, t)*get_px(j) - RR(k, t)*get_px(k)
                    if r + r2 > ans:
                        ans = r + r2
print(ans)