rev = {
    "LU!": "3",
    "LD!": "9",
    "RU!": "1",
    "RD!": "7",
    "W!": "2",
    "A!": "6",
    "S!": "8",
    "D!": "4",
}
ori = {
    "LU": "7",
    "LD": "1",
    "RU": "9",
    "RD": "3",
    "W": "8",
    "A": "4",
    "S": "2",
    "D": "6",
}
to = {
    "1!": "9",
    "2!": "8",
    "3!": "7",
    "4!": "6",
    "6!": "4",
    "7!": "3",
    "8!": "2",
    "9!": "1"
}
note = input()
for k in ori:
    note = note.replace(k, ori[k])
for k in rev:
    note = note.replace(k, rev[k])
for k in to:
    note = note.replace(k, to[k])
lv = len(note)
ini = input()
for k in ori:
    ini = ini.replace(k, ori[k])
s = 0

# dummy character # add because logic more simple.
note += '#'
for i in range(len(ini)):
    if ini[i] == note[s]:
        s += 1
    else:
        s = 0
if s == lv:
    print("Yes")
else:
    print("No")
