import sys
from collections import defaultdict
input = sys.stdin.readline


u, f = map(int, input().split())
grp = defaultdict(dict)
fi = dict()
permission = {"0": "", "1": "X", "2": "W", "3": "XW", "4": "R", "5": "RX", "6": "RW", "7": "RWX"}
for i in range(u):
    dt = input().strip().split()
    grp[dt[0]][dt[0]] = 1
    if len(dt) > 1:
        groups = dt[1].split(",")
        for group in groups:
            grp[group][dt[0]] = 1
for i in range(f):
    fn, pf, o, og = map(str, input().strip().split())
    fi[fn] = [pf, o, og]
ans = []
q = int(input())
for i in range(q):
    un, fn, o = map(str, input().strip().split())
    f_data = fi[fn]
    f_owner = f_data[1]
    f_group = f_data[2]
    f_perm = f_data[0]
    perm_lo = 0 if un == f_owner else (1 if un in grp[f_group] else 2)
    if o in permission[f_perm[perm_lo]]:
        ans.append("1")
    else:
        ans.append("0")
    
ret = "\n".join(ans)
print(ret)