arr = list(map(int, input().split()))
res = [k for k in arr if arr[0] - k <= 1000]
print(f"{len(res)-1}")
