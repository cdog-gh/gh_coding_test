ma = [
    [0, 1, 0, 1, 0, 1, 3],
    [1, 0, 1, 0, 1, 0, 3],
    [0, 1, 0, 1, 0, 1, 3],
    [1, 0, 1, 0, 1, 0, 3],
    [0, 1, 0, 1, 0, 1, 3],
    [1, 0, 1, 0, 1, 0, 3],
    [2, 1, 0, 1, 0, 1, 3]
]
right_top = [(0, 1), (0, 3)]
right_down = [(0, 0), (1, 0), (2, 0), (3, 0), (4, 0), (5, 0), (0, 2), (1, 2), (2, 2), (3, 2), (4, 2), (5, 2), (0, 4),
              (1, 4), (2, 4), (3, 4)]
unit_r = 105
unit_c = 105
real_ma = [['.' for _ in range(unit_c * 7)] for _ in range(unit_r * 7)]
for i in range(7):
    for j in range(7):
        sx = unit_r * i
        sy = unit_c * j
        ex = sx + unit_r
        ey = sy + unit_c

        if ma[i][j] == 0:
            for x in range(sx, ex):
                for y in range(sy, ey):
                    real_ma[x][y] = '.'
        elif ma[i][j] == 1:
            for x in range(sx, ex):
                for y in range(sy, ey):
                    real_ma[x][y] = '1'
        # present block
        elif ma[i][j] == 2:
            for x in range(sx, ex):
                for y in range(sy, ey):
                    if (x + y) % 2 == 0 and y != sy:
                        real_ma[x][y] = 'B'
                    else:
                        real_ma[x][y] = '1'
        elif ma[i][j] == 3:
            for x in range(sx, ex):
                for y in range(sy, ey):
                    if (x + y) % 2 == 0:
                        real_ma[x][y] = '1'
                    else:
                        real_ma[x][y] = '.'
        if (i, j) in right_top:
            real_ma[sx][ey - 1] = '?'
        if (i, j) in right_down:
            real_ma[ex - 1][ey - 1] = '?'
file_num = 5
with open(f'large_{file_num}.in', 'w') as f:
    f.write(f'{unit_r * 7} {unit_c * 7}\n')
    for i in range(unit_r * 7):
        s = ''.join(real_ma[i])
        f.write(f'{s}\n')
    f.write('1 1\n')