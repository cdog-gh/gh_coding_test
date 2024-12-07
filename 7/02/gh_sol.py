r = int(input())
f1, f2, f3 = map(int, input().split())
f = f1 + f2 + f3
if r <= f or r <= 240:
    print('high speed rail')
else:
    print('flight')