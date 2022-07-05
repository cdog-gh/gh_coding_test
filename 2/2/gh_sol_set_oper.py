import sys
my_input = sys.stdin.readline
my_print = sys.stdout.write
key = set()
n, m = map(int, my_input().split(' '))
for i in range(n):
    key.add(my_input().replace('\n', ''))
for i in range(m):
    s = set(my_input().replace('\n', '').split(','))
    key -= s
    my_print(str(len(key))+'\n')
