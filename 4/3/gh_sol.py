import sys
input = sys.stdin.readline


u, f = map(int, input().split())
grp = dict()
fi = dict()
pn = {'R':4, 'W':2, 'X':1}


def add_group(user, group):
    if group not in grp:
        grp[group] = dict()
    grp[group][user] = 1


for i in range(u):
    dt = input().strip().split()
    add_group(dt[0], dt[0])
    if len(dt) > 1:
        groups = dt[1].split(",")
        for group in groups:
            add_group(dt[0], group)

for i in range(f):
    fn, pf, o, og = map(str, input().strip().split())
    fi[fn] = [pf, o, og]
    grp[og]

ans = []
q = int(input())
for i in range(q):
    un, fn, o = map(str, input().strip().split())
    # if user..
    f_data = fi[fn]
    f_owner = f_data[1]
    f_group = f_data[2]
    f_permi = f_data[0]
    
    p0 = int(f_permi[0])
    p1 = int(f_permi[1])
    p2 = int(f_permi[2])
    
    if un == f_owner:
        flag = ((p0 & pn[o]) == pn[o])
    elif un in grp[f_group]:
        flag = ((p1 & pn[o]) == pn[o])
    else:
        flag = ((p2 & pn[o]) == pn[o])
    if flag:
        ans.append('1')
    else:
        ans.append('0')
ret = "\n".join(ans)
print(ret)