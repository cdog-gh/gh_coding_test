import random as rd
from game import game

turn = []

n, T = 500000, 500000
rc_num = 2*(10**9)
file_num = 20
cid = list(rd.sample(range(1, 500001), k=T))
for i in range(T):
    turn.append(rd.randint(1, n))

ans = []
deck = []
Op = ['', 'next', 'acquire', 'release']
rg = game(rc_num)
deck_pos = 0
for i in range(T):
    pn = turn[i]  # people id
    cur_card = rg.current_card(pn)

    # 현재 내 손에 들고 있는 카드가 있다면
    if cur_card:
        c_id, oper, num = cur_card
        ans.append(c_id)
        rg.process_turn(pn, cur_card)

    # 내 손에 들고 있는 카드가 없다면 deck 에서 새로 뽑을 수 있다.
    else:
        while True:
            cur_card = tuple([cid[deck_pos], Op[rd.randint(1, 3)], rd.randint(1, rc_num)])
            if rg.is_available(pn, cur_card):
                ans.append(cur_card[0])
                deck.append(cur_card)
                rg.process_turn(pn, cur_card)
                break
        deck_pos = deck_pos + 1

for i in range(len(ans)-len(deck)):
    cur_card = tuple([cid[deck_pos], Op[rd.randint(1, 3)], rd.randint(1, rc_num)])
    deck.append(cur_card)
    deck_pos = deck_pos + 1

with open(f'{file_num}.in', 'w') as f:
    f.write(f'{n} {T}\n')
    for i in range(T):
        f.write(f'{turn[i]} ')
    f.write('\n')
    for i in range(T):
        if deck[i][1] == 'next':
            f.write(f'{deck[i][0]} {deck[i][1]}\n')
        else:
            f.write(f'{deck[i][0]} {deck[i][1]} {deck[i][2]}\n')

with open(f'{file_num}.out', 'w') as f:
    for i in range(T):
        f.write(f'{ans[i]}\n')