import random as rd
# n = 200000
li = list()
for i in range(100000, 1, -1):
    c = (len(li) + 1) * 20
    ti = rd.randrange(1, 10**9)
    li.append([i+1, i, c, ti])
for j in range(100000, 10000, -1):
    c = (len(li) + 1) * 20
    ti = rd.randrange(1, 10**9)
    b = rd.randrange(2, 100000)
    li.append([1, j, c, ti])
for b in range(100000, 110000):
    c = (len(li) + 1) * 20
    ti = rd.randrange(1, 10**9)
    a = 99999
    li.append([b, a, c, ti])
n = 109999
Q = len(li)
print(f'{n} {Q}')
for item in li:
    print(f'{item[0]} {item[1]} {item[2]} {item[3]}')
