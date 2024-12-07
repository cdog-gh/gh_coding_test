dp = [[0 for _ in range(0, 50000+1)] for _ in range(200+1)]
mod = 1000000007
n = int(input())
dp[0][0] = 1
for lo in range(1, n+1):
    a, m = map(int, input().split())
    cost = (96 * a * m) // 60000
    unit_cost = cost // 6
    for c in range(0, 50000+1):
        dp[lo][c] = dp[lo-1][c]
        if c >= unit_cost:
            dp[lo][c] += dp[lo-1][c - unit_cost]
            dp[lo][c] %= mod
ans = 0
c1, c2 = map(int, input().split())
for c in range(0, 50000+1):
    real_cost = 6*c
    if c1 <= real_cost <= c2:
        ans += dp[n][c]
ans %= mod
print(ans)
