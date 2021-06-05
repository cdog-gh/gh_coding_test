import random as rd
file_num = 25
n, T = 500000, 500000
M = 444187  # I attack M = 351061
LIM = 2*(10**9)
# resource = list(rd.sample(range(1, 2*(10**9)), k=T))
people = [k for k in range(1, n+1)]
rd.shuffle(people)
card = [k for k in range(1, T+1)]
rd.shuffle(card)

with open(f'{file_num}.in', 'w') as f:
    f.write(f'{n} {T}\n')
    for i in range(T):
        f.write(f'{people[i]} ')
    f.write('\n')
    for i in range(T):
        re = (M * i + 1)%(LIM)
        f.write(f'{card[i]} acquire {re}\n')

with open(f'{file_num}.out','w') as f:
    for cn in card:
        f.write(f'{cn}\n')
