import random as rd
n = 200000
q = 200000
print(f'{n} {q}')
li = list(range(1, n+1))
for i in range(1, len(li)):
    c = i * 20
    ti = rd.randrange(1, 10**9)
    print(f'{li[0]} {li[i]} {c} {ti}')
li2 = list(rd.sample(range(1, n+1), k=2))
c2 = rd.randrange(1, 10**9)
ti2 = rd.randrange(1, 10**9)
print(f'{li2[0]} {li2[1]} {c2} {ti2}')
