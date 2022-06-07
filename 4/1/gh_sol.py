a, b = map(int, input().split())
if (a * (100 - b))/100 >= 100:
    print('0')
else:
    print('1')