R, C = map(int, input().split())
_, _, Rp, Cp = map(int, input().split())
ans = 0
for i in range(R):
    ans = ans + len([k for k in input() if k == 'P'])
if ans != Rp*Cp:
    print('1')
else:
    print('0')