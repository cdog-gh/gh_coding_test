"""
does not supported numpy in acmicpc.net
"""
import time
import numpy as np
dp_np = np.array([1])
n, M = map(int, input().split(' '))
s = time.time_ns()
'''
A = [-1, 0, 1, 2, ... ]
B = [1, 2, 3, 4, ... ]
REAL = [0, 1, 2, 3, ... ]
dp[x][h] = dp[x-1][h+1] + dp[x-1][h-1]을 vector operation으로 치환.
'''
for i in range(1, n-1):
    A = np.append([0], dp_np[:i])
    B = np.append(dp_np[1:], [0, 0])
    dp_np = np.sum([A, B], axis=0) % M
e = time.time_ns()
print(f'{(e-s)/(10**9):.2f} {dp_np[0]}')
