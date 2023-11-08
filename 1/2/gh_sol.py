import itertools
st = []
dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]


def func(start_x, start_y, r, c, q, ma):
    cx = start_x
    cy = start_y
    visit = {}
    temp = 0
    for op in q:
        cx = cx + dx[op]
        cy = cy + dy[op]
        if cx < 0 or cy < 0 or cx >= r or cy >= c:
            return 0
        if ma[cx][cy] == '#':
            return 0
        visit[(cx, cy)] = 1
    for cx, cy in visit:
        if ma[cx][cy] == 'S':
            temp += 1
    return temp


R, C, T = map(int, input().split())
sx = -1
sy = -1
for i in range(R):
    st.append(input())
    if st[i].find('G') != -1:
        sx, sy = i, st[i].find('G')
ans = 0
for query in itertools.product([0, 1, 2, 3], repeat=T):
    ans = max(ans, func(sx, sy, R, C, query, st))
print(ans)
