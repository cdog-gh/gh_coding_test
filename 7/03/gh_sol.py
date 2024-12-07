def func(s: int, e: int):
    if e < s: # ex. s = 243, e = 202
        e += 43
    inner = 2 * (e - s)
    outer = 2 * 43 - inner
    if inner < outer:
        print("Inner circle line")
    elif inner > outer:
        print("Outer circle line")
    else:
        print("Same")


Q = int(input())
for _ in range(Q):
    a, b = map(int, input().split())
    func(a, b)