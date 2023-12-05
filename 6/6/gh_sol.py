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
note = input()
for k in rev:
    note = note.replace(k, rev[k])
    # print(note)
for k in ori:
    note = note.replace(k, ori[k])
    # print(note)
# print('--')
ini = input()
for k in ori:
    ini = ini.replace(k, ori[k])
s = 0
for i in range(len(ini)):
    if s == len(note):
        s = 0
    else:
        if ini[i] == note[s]:
            s += 1
        else:
            s = 0
# print(note)
# print(ini)
if s == len(note):
    print("Yes")
else:
    print("No")
