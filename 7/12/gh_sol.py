dp = [0 for _ in range(505050)]
s_pos = [0 for _ in range(505050)]
ds_pos = [0 for _ in range(505050)]
tar = [0 for _ in range(505050)]
nj = [0 for _ in range(505050)]
right_dp = [0 for _ in range(505050)]
right_ds_freq = [0 for _ in range(505050)]
inf = 0x3f3f3f3f3f3f3f3f

n = int(input())
s = input().strip()
s = s.replace(" or ", "#or#")
arr = s.split()
for i, v in enumerate(arr):
    lo = i + 1
    if v == "S":
        s_pos[lo] = 1
    elif v == "DS":
        ds_pos[lo] = 1
    elif v == 'DS#or#S' or v == 'S#or#DS':
        ds_pos[lo] = 1
        s_pos[lo] = 1
    else:
        tar[lo] = int(v)

for i in range(1, 505050):
    nj[i] = nj[i-1] + tar[i]

mx = nj[n]
base = mx
# DS 한 번 나왔을 때.
for i in range(1, 505050):
    if ds_pos[i] == 0:
        continue
    t = base + nj[i]
    mx = max(mx, t)

r_mx = -inf
r_freq = 0
for i in range(505050-1, 0, -1):
    right_ds_freq[i] = r_freq
    if ds_pos[i] != 0:
        r_mx = max(r_mx, nj[i])
        r_freq += 1
    right_dp[i] = r_mx

# DS 2번 나왔을 때
for i in range(1, 505050):
    if s_pos[i] == 0:
        continue

    # i+1 ~ ... 까지 DS가 나올 수 있는 pos 에서 최대치 찾는다.
    if right_ds_freq[i] == 0:
        continue
    v = (right_dp[i] - nj[i])
    mx = max(mx, base + v)
print(mx)
