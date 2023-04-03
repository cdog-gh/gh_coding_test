import sys
input = sys.stdin.readline
print = sys.stdout.write

note = {
    "A": 0,
    "A#": 1,
    "B": 2,
    "C": 3,
    "C#": 4,
    "D": 5,
    "D#": 6,
    "E": 7,
    "F": 8,
    "F#": 9,
    "G": 10,
    "G#": 11
}
addi = [
    ("M", 4, 3), 
    ("m", 3, 4),
    ("aug", 4, 4), 
    ("dim", 3, 3)
]
con = list()
used = list()


def madi_to_note_data(madi_data):
    note_data = list()
    for ch in madi_data:
        if 'A' <= ch and ch <= 'G':
            note_num = note[str(ch)]
            note_data.append(note_num)
        elif ch == '-':
            continue
        elif '0' <= ch and ch <= '9':
            continue
        elif ch == '$':
            lo = len(note_data) - 1
            note_data[lo] = (note_data[lo] + 11) % 12
        elif ch == '#':
            lo = len(note_data) - 1
            note_data[lo] = (note_data[lo] + 1) % 12
    return note_data


def add(num, num2):
    return (num + num2) % 12



def chk(chord_num, cur_madi, pp, kk):
    # cur_madi - pp ~ ?
    lo = len(used[chord_num])
    if lo - kk < 0:
        return False
    if cur_madi - pp <= used[chord_num][lo-kk]:
        return True
    return False        


m, p, k = map(int, input().split())
chord_data = list()
for ch in note:
    for typ, d1, d2 in addi:
        um1 = note[ch]
        um3 = add(um1, d1)
        um5 = add(um3, d2)
        # ch + typ
        chord_data.append(tuple([f"{ch}{typ}", um1, um3, um5]))


for _ in range(48):
    con.append(list())
    used.append(list())

chord_data = sorted(chord_data)

for lo, dt in enumerate(chord_data):
    _, um1, um3, um5 = dt
    con[um1].append(lo)
    con[um3].append(lo)
    con[um5].append(lo)

last_used = [-1] * 48        
for cm in range(m):
    madi = input()
    cc = [0] * 48
    
    #nd_data = [0, 2, 0, 3, 11 ...]
    nd_data = madi_to_note_data(madi)
    
    for nd in nd_data:
        for chord_num in con[nd]:
            cc[chord_num] = cc[chord_num] + 1
    
    ans = -1
    max_freq = -1
    for i in range(48):
        # 이전 p개의 마디에 k회 이상 나왔는가?
        if chk(i, cm, p, k):
            continue
        if cc[i] > max_freq:
            max_freq = cc[i]
            ans = i
        
    if ans == -1:
        lu = 0x3f3f3f3f
        for i in range(48):
            if last_used[i] < lu:
                lu = last_used[i]
                ans = i
    last_used[ans] = cm
    used[ans].append(cm)
    
    print(f"{chord_data[ans][0]}\n")
