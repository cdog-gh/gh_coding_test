st = [['.' for _ in range(1000)] for _ in range(1000)]
# build a Turtle
for r in range(0, 490, 2):
    for c in range(0, 490):
        st[r][c] = 'T'
for r in range(1, 490, 4):
    st[r][0] = 'T'
for r in range(3, 490, 4):
    st[r][489] = 'T'

file_num = 23
r, c = 1000, 1000
with open(f'{file_num}.in', 'w') as f:
    f.write(f'{r} {c}\n')
    for i in range(1000):
        r = ''.join(st[i])
        f.write(f'{r}\n')
