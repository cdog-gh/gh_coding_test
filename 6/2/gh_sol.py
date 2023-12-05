import sys
input = sys.stdin.readline
n = int(input())
s = int(input())
arr = map(int, input().split())
ret = 1
for v in arr:
    if v > s:
        ret += 1
print(ret)
