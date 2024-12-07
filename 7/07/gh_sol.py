arr = [0] * 2005
n, c, k = map(int, input().split())
v = []
if k != 0:
    v = [int(k) for k in input().strip().split()]
for a in v:
    arr[a] = 1

lt = [0]
for v in range(2001):
    if arr[v] == 0:
        continue
    lt.append(v)
lt.append(n+1)

ans = [k for k in range(0, n+2)]
last = [k for k in range(0, n+2)]

for i in range(1, len(lt)):
    prev = lt[i-1]
    prev += 1
    cur = lt[i]
    last[prev], last[cur] = last[cur], last[prev]

for _ in range(c-1):
    s = " ".join([str(k) for k in ans[1: 1+n]])
    print(s)
s = " ".join([str(k) for k in last[1: 1+n]])
print(s)