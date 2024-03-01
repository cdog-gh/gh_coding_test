# string prefix 많이 겹치게 데이터 세팅.
import random as rd


def get_name(tar):
    ret = ""
    for _ in range(10):
        ret = chr(ord('a') + tar % 26) + ret
        tar = tar // 26
    return ret


def get_name_set(tar, start=None):
    li = []
    if start:
        cur = start
    else:
        cur = rd.randint(0, 10**14)
    for _ in range(tar):
        li.append(get_name(cur))
        cur = cur + rd.randint(1, 26)
    return cur, li


_, nn = get_name_set(2)  # 파일 조합 2개
sn, ne = get_name_set(200000)  # 확장자 200000개
_, ext = get_name_set(200000, start=sn)  # 비슷 비슷한 확장자 200000개
n = 2*(10**5)
m = 200000
M = 1000000000
dic = {}
file_num = 24
with open(f'{file_num}.in', 'w') as f:
    f.write(f'{n} {m}\n')
    for i in range(n):
        while True:
            A = rd.randrange(0, len(nn))
            B = rd.randrange(0, len(ext))
            kei = M*A + B
            if kei not in dic:
                dic[kei] = 1
                f.write(f'{nn[A]}.{ext[B]}\n')
                break
    rd.shuffle(ne)  # 확장자 shuffle
    for ext in ne:
        f.write(f'{ext}\n')
