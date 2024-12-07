import sys
input = sys.stdin.readline


Q = int(input())
ans = []
for _ in range(Q):
    a, m = map(int, input().split())
    
    # 소비 전력 a / 1000 kW
    # m 분동안 씀.
    
    # kWh = (a * m) / (1000 * 3600)
    # cost per kWh = 1056/10
    # (1056 * a * m) / (1000 * 3600 * 10)
    # 1000W, 60분 => 105원임.
    a = (1056 * a * m * 60) // (1000 * 3600 * 10)
    ans.append(a)
print("\n".join([str(k) for k in ans]))
