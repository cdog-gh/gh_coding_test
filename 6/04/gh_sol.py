lv, verdict = input().split()
lv = int(lv)
r = 0
if verdict == 'bad':
    r = lv * 200
elif verdict == 'cool':
    r = lv * 400
elif verdict == 'great':
    r = lv * 600
elif verdict == 'perfect':
    r = lv * 1000
print(r)
