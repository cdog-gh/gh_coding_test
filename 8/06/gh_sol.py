from sys import stdin

ini = stdin.readline


def go():
    n = int(ini().strip())
    st = ini().strip().split(" ")
    no_underbar = list()
    no_underbar = [k for k in st if k.find("-") == -1]
    if len(st) == 1 or len(st) != len(no_underbar):
        print("NO")
        return
    print("YES" if len({k[-2:] for k in no_underbar}) == 1 else "NO")


Q = int(ini().strip())
for _ in range(Q):
    go()
