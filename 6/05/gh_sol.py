import sys
print = sys.stdout.write


co = [0] * 505050
ans = list()
s, k = map(int, input().split())
for v in range(s, 0, -1):
    if not co[v + k]:
        co[v] = 1
        ans.append(v)
print(f"{len(ans)}\n")
ret_s = "\n".join(map(str, ans))
print(ret_s)
