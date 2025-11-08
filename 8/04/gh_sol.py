Q = int(input())
for _ in range(Q):
    k = int(input())
    base = 60 * 6 + 6
    ans = base + (k // 50) * 12
    HH = ans // 60
    MM = ans % 60
    print(f"{HH:02d}:{MM:02d}")