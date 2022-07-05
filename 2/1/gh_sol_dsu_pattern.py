import sys
my_input = sys.stdin.readline
my_print = sys.stdout.write
n, m = map(int, my_input().split(' '))
files = [tuple(my_input().split('.')) for i in range(n)]
dic = set([my_input() for i in range(m)])
deco = sorted([[k[0], k[1] not in dic, k[1]] for k in files])
files = [tuple([k[0], k[2]]) for k in deco]
for i in range(n):
    my_print(f'{files[i][0]}.{files[i][1]}')