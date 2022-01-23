import sys
import collections

ma = []
input = sys.stdin.readline


def get_state(ch):
    if ch == '.' or ch == 'P' or ch == 'B':
        return 1
    if ch == '1':
        return 2
    if ch == '?':
        return 3
    return 4


R, C = map(int, input().split(' '))
for i in range(0, R):
    ma.append(input().replace('\n', ''))
x, y = map(int, input().split(' '))
x = x - 1
y = y - 1
state_ma = [[0 for _ in range(C)] for _ in range(R)]
visit = [[0 for _ in range(C)] for _ in range(R)]
comp_no = [[0 for _ in range(C)] for _ in range(R)]
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]
pb_flag = [0 for _ in range(1001*1001)]
for i in range(R):
    for j in range(C):
        state_ma[i][j] = get_state(ma[i][j])


def bfs(sx, sy, number):
    queue = collections.deque()
    visit[sx][sy] = 1
    queue.append((sx, sy))
    while queue:
        cur_item = queue.popleft()
        comp_no[cur_item[0]][cur_item[1]] = number
        for r in range(0, 4):
            tx = cur_item[0] + dx[r]
            ty = cur_item[1] + dy[r]
            if tx < 0 or ty < 0 or tx >= R or ty >= C:
                continue
            if state_ma[sx][sy] != state_ma[tx][ty]:
                continue
            if visit[tx][ty] == 1:
                continue
            queue.append((tx, ty))
            visit[tx][ty] = 1


no = 1
for i in range(0, R):
    for j in range(0, C):
        if visit[i][j] == 1:
            continue
        bfs(i, j, no)
        no = no + 1
for i in range(0, R):
    for j in range(0, C):
        if ma[i][j] == 'P' or ma[i][j] == 'B':
            pb_flag[comp_no[i][j]] = 1

# comp_no
g_no = 0
dir_dic = {'N': (-1, 0), 'W': (0, -1), 'E': (0, 1), 'S': (1, 0)}
g = []


def gyeongsa(tx, ty, g_lo, cc):
    x1 = tx + dir_dic[cc][0]
    y1 = ty + dir_dic[cc][1]
    st1, st2 = -1, -1
    no1, no2 = -1, -1
    if 0 <= x1 < R and 0 <= y1 < C:
        st1 = state_ma[x1][y1]
        no1 = comp_no[x1][y1]
    x1 = tx - dir_dic[cc][0]
    y1 = ty - dir_dic[cc][1]
    if 0 <= x1 < R and 0 <= y1 < C:
        st2 = state_ma[x1][y1]
        no2 = comp_no[x1][y1]
    if st1 == 2 and st2 == 1:
        g[g_lo].append([no1, no2, cc, tx, ty])


for i in range(R):
    for j in range(C):
        if ma[i][j] == '?':
            g.append([])
            gyeongsa(i, j, g_no, 'N')
            gyeongsa(i, j, g_no, 'W')
            gyeongsa(i, j, g_no, 'E')
            gyeongsa(i, j, g_no, 'S')
            while len(g[g_no]) < 2:
                g[g_no].append([-1, -1, 'N', i, j])
            g_no = g_no + 1
conn = [[] for _ in range(1001 * 1001)]
visit_comp = [0 for _ in range(1001*1001)]


def comp_bfs(s):
    v_list = []
    queue = collections.deque()
    visit_comp[s] = 1
    v_list.append(s)
    queue.append(s)
    while queue:
        cur = queue.popleft()
        if pb_flag[cur] == 1:
            return 1
        for ne in conn[cur]:
            if visit_comp[ne] == 1:
                continue
            v_list.append(ne)
            visit_comp[ne] = 1
            queue.append(ne)
    for cur in v_list:
        visit_comp[cur] = 0
    return 0


for t in range(1 << len(g)):
    # graph init
    temp = []
    for i in range(len(g)):
        if (t & (1 << i)) == 0:
            a = g[i][0][0]
            b = g[i][0][1]
            ch = g[i][0][2]
            if a != -1 and b != -1:
                conn[a].append(b)
                conn[b].append(a)
            temp.append(g[i][0])
        else:
            a = g[i][1][0]
            b = g[i][1][1]
            ch = g[i][1][2]
            temp.append(g[i][1])
            if a != -1 and b != -1:
                conn[a].append(b)
                conn[b].append(a)
    # print(temp)
    # comp_bfs
    if comp_bfs(comp_no[x][y]) == 1:
        ans = [['0' for _ in range(C)] for _ in range(R)]
        for i in range(R):
            for j in range(C):
                ans[i][j] = ma[i][j]
        for item in temp:
            ch = item[2]
            x = item[3]
            y = item[4]
            ans[x][y] = ch
        for i in range(R):
            print(''.join(ans[i]))
        exit(0)
    # graph clear
    for i in range(len(g)):
        if (t & (1 << i)) == 0:
            a = g[i][0][0]
            b = g[i][0][1]
            if a != -1 and b != -1:
                conn[a].clear()
                conn[b].clear()
        else:
            a = g[i][1][0]
            b = g[i][1][1]
            if a != -1 and b != -1:
                conn[a].clear()
                conn[b].clear()
print('-1')
