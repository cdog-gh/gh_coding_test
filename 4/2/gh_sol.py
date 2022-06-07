hh, mm = map(int, input().split(':'))
cur = (60 * hh + mm) % 720
hp = list(map(int, input().split()))
flag = [1] * 6
event = int(input())
for i in range(event):
    _, q2 = input().split()
    if q2 == '^':
        flag[cur // 120] = 0
    elif q2.endswith('HOUR'):
        cur = cur + int(q2[:1]) * 60
        cur = cur % 720
    else:
        cur = cur + int(q2[:2])
        cur = cur % 720
ans = 0
for i in range(6):
    ans = ans + flag[i] * hp[i]
if ans >= 100:
    print('100\n')
else:
    print(ans)