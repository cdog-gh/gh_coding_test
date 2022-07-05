import time
import random as rd


def str_to_int(tar):
    from_1970 = time.strptime(tar, '%Y-%m-%d %H:%M:%S')
    return int(time.mktime(from_1970))


def sec_to_str(sec):
    date_tuple = time.localtime(sec)
    return time.strftime('%Y-%m-%d %H:%M:%S', date_tuple)


n, Q = map(int, input().split())
li = []
for i in range(n):
    dt, lv = input().split('#')
    dt = str_to_int(dt)
    lv = int(lv)
    li.append((dt, lv))
for i in range(Q):
    ds, de, lv = input().split('#')
    ds = str_to_int(ds)
    de = str_to_int(de)
    lv = int(lv)
    ans = 0
    for d in li:
        if ds <= d[0] <= de and lv <= d[1]:
            ans = ans + 1
    print(ans)
    