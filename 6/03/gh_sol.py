p, r = map(int, input().split())
percent = (100 * p) // r
if percent < 20:
    print('weak')
elif percent < 40:
    print('normal')
elif percent < 60:
    print('strong')
else:
    print('very strong')
